# ARCHITECTURE.md — Fonctionnement du programme Philosophers

Modèle : **1 thread par philosophe** + **1 thread monitor** + le thread `main`.
Ressources partagées protégées par mutex. Fin de simulation via un flag `stop`.

---

## 1. Vue d'ensemble des fichiers et fonctions

```mermaid
flowchart TB
    subgraph mainc["main.c"]
        M[main]
        SP[start_philos]
        CPT[create_philo_threads]
        PR[philo_routine]
    end
    subgraph initc["init.c"]
        IA[init_args]
        IT[init_table]
        IP[init_philos]
        CL[cleanup]
    end
    subgraph utilsc["utils.c"]
        VA[validate_args]
        IPN[is_positive_number]
        AT[ft_atoi]
        JT[join_threads]
        OP[one_philo]
    end
    subgraph msgc["messages.c"]
        PUF[pick_up_forks]
        PE[philo_eat]
        PS[philo_sleep]
        PT[philo_think]
        PDF[put_down_forks]
    end
    subgraph printc["print.c"]
        GT[get_time_ms]
        IST[is_stopped]
        SS[set_stop]
        FU[ft_usleep]
        CPTS[custom_print_timestamp]
    end
    subgraph monc["monitor.c"]
        MR[monitor_routine]
        PID[philo_is_dead]
        AAE[all_ate_enough]
        PD[print_death]
    end

    M --> VA & IA & IT & IP & CPT & CL
    VA --> IPN & AT
    IA --> AT
    CPT --> OP & SP & JT & MR
    SP --> PR
    PR --> PE & PS & PT & IST
    PE --> PUF & CPTS & FU & PDF & GT
    PS --> CPTS & FU
    PT --> CPTS & FU
    PUF --> CPTS
    MR --> PID & AAE & PD & SS & IST
    CPTS --> IST & GT
    FU --> IST & GT
    PD --> GT
    OP --> CPTS & FU & PD
```

---

## 2. Structures de données

```mermaid
classDiagram
    class t_table {
        int nb_philo
        int time_to_die
        int nb_meals
        int time_to_eat
        int time_to_sleep
        long start_time
        int stop
        pthread_mutex_t stop_mutex
        pthread_mutex_t print_mutex
        t_philo philos
        pthread_mutex_t forks
    }
    class t_philo {
        int id
        int nb_meals_eaten
        int max_meals
        pthread_mutex_t left_fork
        pthread_mutex_t right_fork
        int time_to_eat
        int time_to_sleep
        long last_meal_time
        pthread_mutex_t meal_mutex
        t_table table
    }
    t_table "1" --> "N" t_philo : philos[]
    t_table "1" --> "N" fork : forks[]
    t_philo --> t_table : table
    t_philo ..> fork : left_fork / right_fork
```

Champs protégés par mutex : `stop` (stop_mutex), `nb_meals_eaten` +
`last_meal_time` (meal_mutex), `stdout` (print_mutex). `nb_meals = -1` signifie
« pas de limite de repas ».

Partage des fourchettes en anneau : `philo[i].left = forks[i]`,
`philo[i].right = forks[(i+1) % nb_philo]`.

```mermaid
flowchart LR
    F0((fork0)) --- P1[philo1]
    P1 --- F1((fork1))
    F1 --- P2[philo2]
    P2 --- F2((fork2))
    F2 --- P3[philo3]
    P3 --- F0
```

---

## 3. Cycle de vie global (main)

```mermaid
sequenceDiagram
    participant Main as main
    participant Init as init.c
    participant Philos as N threads philo
    participant Mon as thread monitor

    Main->>Main: validate_args(argc, argv)
    alt args invalides
        Main-->>Main: printf("Error"), return 1
    end
    Main->>Init: init_args() + init_table() + init_philos()
    Note over Init: start_time = get_time_ms()<br/>init mutex forks/meal/stop/print
    Main->>Philos: create_philo_threads() → pthread_create × N
    Main->>Mon: pthread_create(monitor)
    par Simulation
        Philos->>Philos: eat / sleep / think (boucle)
        Mon->>Mon: surveille mort + quota
    end
    Mon-->>Main: set stop → threads sortent
    Main->>Philos: join_threads()
    Main->>Mon: pthread_join(monitor)
    Main->>Init: cleanup() (destroy mutex + free)
    Main-->>Main: return 0
```

---

## 4. Routine d'un philosophe — `philo_routine`

```mermaid
flowchart TD
    A[Début thread] --> B{id pair ?}
    B -- oui --> C[ft_usleep time_to_eat/2 + 1<br/>décalage anti-collision]
    B -- non --> D
    C --> D{is_stopped ?}
    D -- oui --> Z[return NULL]
    D -- non --> E[lock meal_mutex]
    E --> F{max_meals >= 0<br/>et repas atteints ?}
    F -- oui --> G[unlock + break] --> Z
    F -- non --> H[unlock meal_mutex]
    H --> I[philo_eat]
    I --> J{is_stopped ?}
    J -- oui --> Z
    J -- non --> K[philo_sleep]
    K --> L[philo_think]
    L --> D
```

---

## 5. Manger — `philo_eat` (section critique)

```mermaid
sequenceDiagram
    participant P as philo_eat
    participant Fk as forks (mutex)
    participant Mm as meal_mutex
    participant Pr as print_mutex

    P->>Fk: pick_up_forks()
    Note over Fk: pair: right puis left<br/>impair: left puis right<br/>(évite le deadlock)
    Fk->>Pr: print "has taken a fork" ×2
    P->>Mm: lock
    Note over Mm: last_meal_time = get_time_ms()
    P->>Mm: unlock
    P->>Pr: print "is eating"
    P->>P: ft_usleep(time_to_eat)
    P->>Mm: lock
    Note over Mm: nb_meals_eaten++
    P->>Mm: unlock
    P->>Fk: put_down_forks() (unlock left + right)
```

Ordre de prise des fourchettes (anti-deadlock) :

```mermaid
flowchart LR
    subgraph pair["philo id PAIR"]
        R1[lock right] --> L1[lock left]
    end
    subgraph impair["philo id IMPAIR"]
        L2[lock left] --> R2[lock right]
    end
```

---

## 6. Surveillant — `monitor_routine`

```mermaid
flowchart TD
    A[Début monitor] --> B{is_stopped ?}
    B -- oui --> Z[return NULL]
    B -- non --> C[i = 0]
    C --> D{i < nb_philo ?}
    D -- non --> H{all_ate_enough ?}
    D -- oui --> E[philo_is_dead i ?]
    E -- oui --> F[print_death → set stop] --> Z
    E -- non --> G[i++] --> D
    H -- oui --> I[set_stop] --> Z
    H -- non --> J[usleep 500 µs] --> B
```

`philo_is_dead(i)` :

```mermaid
flowchart TD
    A[lock meal_mutex] --> B[since = now - last_meal_time]
    B --> C[full = nb_meals>=0 ET repas atteints]
    C --> D[unlock meal_mutex]
    D --> E{full ?}
    E -- oui --> F[return 0 // rassasié, jamais mort]
    E -- non --> G{since > time_to_die ?}
    G -- oui --> H[return 1 // mort]
    G -- non --> I[return 0]
```

---

## 7. Affichage sûr et arrêt sans course

Règle clé : `print_mutex` protège **à la fois** l'affichage **et** la pose du flag
`stop`, pour garantir qu'**aucune ligne n'est écrite après `died`**.

```mermaid
sequenceDiagram
    participant Mon as monitor (print_death)
    participant Pr as print_mutex
    participant St as stop_mutex
    participant Ph as thread philo (custom_print)

    Note over Ph: veut écrire "is eating"
    Mon->>Pr: lock
    Mon->>Mon: printf "... died"
    Mon->>St: lock → stop = 1 → unlock
    Mon->>Pr: unlock
    Ph->>Pr: lock (obtenu après le monitor)
    Ph->>St: is_stopped() → 1
    Note over Ph: stop == 1 → n'affiche RIEN
    Ph->>Pr: unlock
```

`custom_print_timestamp` :

```mermaid
flowchart LR
    A[lock print_mutex] --> B{is_stopped ?}
    B -- non --> C[printf timestamp id message]
    B -- oui --> D[ne rien afficher]
    C --> E[unlock print_mutex]
    D --> E
```

---

## 8. Temporisation précise — `ft_usleep`

`usleep` seul est imprécis et n'écoute pas l'arrêt. `ft_usleep` découpe l'attente
en petits pas de 200 µs et sort dès que `stop` est levé.

```mermaid
flowchart TD
    A[start = get_time_ms] --> B{now - start < ms ?}
    B -- non --> Z[fin]
    B -- oui --> C{is_stopped ?}
    C -- oui --> Z
    C -- non --> D[usleep 200] --> B
```

---

## 9. Carte des mutex (qui protège quoi)

```mermaid
flowchart TB
    subgraph forks["forks[] (N mutex)"]
        FK[Exclusion sur chaque fourchette]
    end
    subgraph meal["meal_mutex (1 par philo)"]
        MM[last_meal_time + nb_meals_eaten]
    end
    subgraph stop["stop_mutex (global)"]
        SM[flag stop]
    end
    subgraph print["print_mutex (global)"]
        PM[stdout + atomicité mort/stop]
    end

    PE[philo_eat] --> FK & MM
    MON[monitor] --> MM & SM & PM
    CP[custom_print_timestamp] --> PM & SM
    FUS[ft_usleep] --> SM
```

Ordre de verrouillage (jamais inversé → pas de deadlock entre mutex globaux) :
`print_mutex` **puis** `stop_mutex`. `meal_mutex` et `forks` se prennent seuls.

---

## 10. Référence fonction par fonction

### main.c
| Fonction | Rôle |
|----------|------|
| `main` | Valide les args, initialise, lance threads, join, nettoie. |
| `start_philos` | Crée les N threads philosophes ; en cas d'échec : `set_stop` + join partiel. |
| `create_philo_threads` | Cas `nb_philo == 1` → `one_philo` ; sinon crée philos + monitor, join tout. |
| `philo_routine` | Boucle de vie d'un philo : décalage pair, check quota, eat/sleep/think, sortie sur `stop`. |

### init.c
| Fonction | Rôle |
|----------|------|
| `init_args` | Parse argv → `t_table` (nb_meals = -1 si absent). |
| `init_table` | `start_time`, mutex `stop`/`print`, alloc + init `forks[]`. Renvoie 1 si `malloc` échoue. |
| `init_philos` | Alloc + init chaque `t_philo` (fourchettes, meal_mutex, table). Renvoie 1 si `malloc` échoue. |
| `cleanup` | Destroy tous les mutex (tolérant `philos == NULL`) + `free`. |

### utils.c
| Fonction | Rôle |
|----------|------|
| `one_philo` | Cas 1 philo : lock 1 fourchette, attend `time_to_die`, meurt. |
| `is_positive_number` | Valide une chaîne : `+` optionnel, chiffres, `<= INT_MAX`. |
| `validate_args` | Vérifie toutes les chaînes + bornes (`nb_philo/die/eat/sleep >= 1`). |
| `join_threads` | `pthread_join` sur les threads. |
| `ft_atoi` | Conversion str → int (avec bornes). |

### messages.c
| Fonction | Rôle |
|----------|------|
| `pick_up_forks` | Prend les 2 fourchettes selon parité (anti-deadlock), affiche « has taken a fork ». |
| `put_down_forks` | Relâche les 2 fourchettes. |
| `philo_eat` | Prend fourchettes, met à jour `last_meal_time`, mange (`ft_usleep`), incrémente repas, relâche. |
| `philo_sleep` | Affiche « is sleeping » puis `ft_usleep(time_to_sleep)`. |
| `philo_think` | Affiche « is thinking » puis attend `(die-eat-sleep)/2` (anti-famine). |

### print.c
| Fonction | Rôle |
|----------|------|
| `get_time_ms` | Temps courant en ms (`gettimeofday`). |
| `is_stopped` | Lit `stop` sous `stop_mutex`. |
| `set_stop` | Met `stop = 1` sous `stop_mutex`. |
| `ft_usleep` | Attente précise interruptible par `stop`. |
| `custom_print_timestamp` | Affiche `timestamp id message` sous `print_mutex`, rien si `stop`. |

### monitor.c
| Fonction | Rôle |
|----------|------|
| `print_death` | Affiche `died` + pose `stop`, atomiquement sous `print_mutex`. |
| `philo_is_dead` | Vrai si `now - last_meal > time_to_die` et philo non rassasié. |
| `all_ate_enough` | Vrai si `nb_meals` défini et tous ont atteint leur quota. |
| `monitor_routine` | Boucle : détecte mort (→ `print_death`) ou fin quota (→ `set_stop`). |

---

## 11. Conditions d'arrêt

```mermaid
flowchart TD
    A[Simulation en cours] --> B{Un philo dépasse time_to_die ?}
    B -- oui --> C[monitor: print_death + stop=1]
    A --> D{Tous ont mangé nb_meals fois ?}
    D -- oui --> E[monitor: stop=1]
    C --> F[Tous les threads voient stop → sortent]
    E --> F
    F --> G[main: join + cleanup → return 0]
```
