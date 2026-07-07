# TEST.md — Cas de test Philosophers

Documentation de tous les cas de test pour valider le projet.
Format de sortie attendu : `timestamp_ms  id  action`
(actions : `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`)

---

## 0. Compilation

| # | Commande | Attendu |
|---|----------|---------|
| 0.1 | `make` | compile sans warning (`-Wall -Wextra -Werror`) |
| 0.2 | `make re` | recompile propre |
| 0.3 | `make` (2e fois) | `Nothing to be done for 'all'` |
| 0.4 | `norminette src/` | tous les fichiers `OK!` |

---

## 1. Validation des arguments (doivent tous être REJETÉS avec `Error`)

| # | Commande | Raison |
|---|----------|--------|
| 1.1 | `./philo` | pas assez d'arguments |
| 1.2 | `./philo 5 800 200` | pas assez d'arguments |
| 1.3 | `./philo 5 800 200 200 3 1` | trop d'arguments |
| 1.4 | `./philo 0 800 200 200` | nb_philo < 1 |
| 1.5 | `./philo 5 0 200 200` | time_to_die < 1 |
| 1.6 | `./philo 5 800 0 200` | time_to_eat < 1 |
| 1.7 | `./philo 5 800 200 0` | time_to_sleep < 1 |
| 1.8 | `./philo abc 800 200 200` | non numérique |
| 1.9 | `./philo 5 -800 200 200` | négatif |
| 1.10 | `./philo 5 800 200 200 -3` | nb_meals négatif |
| 1.11 | `./philo 5 99999999999999 200 200` | overflow > INT_MAX |
| 1.12 | `./philo 5 800 200 200 xyz` | dernier arg non numérique |
| 1.13 | `./philo 5 8.5 200 200` | flottant (point interdit) |

Vérif : le programme affiche `Error` et sort avec un code ≠ 0, sans crash.

---

## 2. Cas de MORT (un philosophe doit mourir)

| # | Commande | Attendu |
|---|----------|---------|
| 2.1 | `./philo 1 800 200 200` | 1 seul philo : prend 1 fourchette, meurt à ~800 ms |
| 2.2 | `./philo 4 310 200 100` | un philo meurt (~310 ms) |
| 2.3 | `./philo 4 200 205 200` | meurt pendant `is eating` (eat > die) |
| 2.4 | `./philo 5 200 100 100` | `die == eat+sleep` (marge nulle) → mort normale |
| 2.5 | `./philo 2 400 200 200` puis mort tôt selon planif. | vérifier détection |

Vérifs pour chaque mort :
- La ligne `died` est affichée **≤ 10 ms** après le dépassement de `time_to_die`.
- **Aucune ligne** n'est affichée **après** la ligne `died`.
- Un seul `died` dans toute la sortie.

Contrôle « rien après la mort » :
```bash
./philo 4 310 200 100 > out.log 2>&1
awk '/died/{f=1} f' out.log | tail -n +2 | wc -l   # doit afficher 0
```

---

## 3. Cas de SURVIE (personne ne doit mourir)

| # | Commande | Attendu |
|---|----------|---------|
| 3.1 | `./philo 5 800 200 200` | tourne indéfiniment, 0 mort |
| 3.2 | `./philo 4 410 200 200` | 0 mort (cas classique serré) |
| 3.3 | `./philo 5 600 150 150` | 0 mort |
| 3.4 | `./philo 200 800 200 200` | grand nombre, 0 mort |
| 3.5 | `./philo 100 800 200 200` | grand nombre, 0 mort |

Méthode (le buffering masque la sortie si on redirige puis kill) :
```bash
./philo 5 800 200 200 > out.log 2>&1 &
pid=$!; sleep 8; kill $pid; wait $pid 2>/dev/null
grep -c died out.log   # doit afficher 0
```

---

## 4. Fin par quota (`nb_meals`)

| # | Commande | Attendu |
|---|----------|---------|
| 4.1 | `./philo 5 800 200 200 7` | s'arrête quand chacun a mangé 7 fois, 0 mort |
| 4.2 | `./philo 5 800 200 200 20` | exactement 100 `is eating` (5×20), exit 0 |
| 4.3 | `./philo 4 410 200 200 10` | 40 repas, 0 mort |
| 4.4 | `./philo 1 800 200 200 1` | philo seul : ne peut pas manger → meurt |

Contrôle du nombre exact de repas :
```bash
./philo 5 800 200 200 20 > out.log 2>&1
grep -c "is eating" out.log   # doit afficher 100
```

---

## 5. Cas limites

| # | Commande | Attendu |
|---|----------|---------|
| 5.1 | `./philo 5 800 200 200 0` | must_eat = 0 : personne ne mange, sortie propre |
| 5.2 | `./philo +5 800 200 200 3` | signe `+` accepté |
| 5.3 | `./philo 2 60 60 60` | 2 philos, timings très courts |
| 5.4 | `./philo 3 610 200 100 10` | 3 philos (impair), quota atteint |

---

## 6. Contrôle du format de sortie

Chaque ligne doit matcher strictement :
```bash
./philo 4 310 200 100 > out.log 2>&1
grep -vE "^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$" out.log
# aucune ligne en sortie = 100% conforme
```

---

## 7. Stress / robustesse temporelle

| # | Commande | Attendu |
|---|----------|---------|
| 7.1 | `5 800 200 200` répété 10×, 8 s chacun | 0 mort sur les 10 runs (anti-famine) |
| 7.2 | `4 410 200 200` sur 15 s | 0 mort |

Boucle de stress famine :
```bash
m=0
for i in $(seq 1 10); do
  ./philo 5 800 200 200 > s.log 2>&1 & p=$!
  sleep 8; kill $p 2>/dev/null; wait $p 2>/dev/null
  [ "$(grep -c died s.log)" -ne 0 ] && m=$((m+1))
done
echo "runs avec mort: $m/10"   # doit afficher 0/10
```

---

## 8. Valgrind (mémoire & threads)

> Sous valgrind le temps réel s'écoule normalement mais le code est ~30× plus lent :
> utiliser un `time_to_die` **large** pour les tests « sans mort » (sinon tout le monde meurt).

### 8.1 Fuites mémoire
```bash
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 \
  ./philo 4 10000 100 100 3
```
Attendu : `in use at exit: 0 bytes`, `All heap blocks were freed`, `0 errors`.

### 8.2 Fuites sur chemin de mort
```bash
valgrind --leak-check=full --error-exitcode=42 ./philo 4 200 100 100
valgrind --leak-check=full --error-exitcode=42 ./philo 1 200 100 100
```
Attendu : `in use at exit: 0 bytes`, `0 errors`.

### 8.3 Data races (helgrind)
```bash
valgrind --tool=helgrind --error-exitcode=42 ./philo 4 10000 100 100 3
valgrind --tool=helgrind --error-exitcode=42 ./philo 4 200 100 100
```
Attendu : `0 errors from 0 contexts` (les `suppressed` = glibc/pthread, à ignorer).

### 8.4 Locks / ordre (drd)
```bash
valgrind --tool=drd --error-exitcode=42 ./philo 4 10000 100 100 3
```
Attendu : `0 errors from 0 contexts`.

---

## 9. Résumé des résultats attendus

| Domaine | État |
|---------|------|
| Compilation `-Wall -Wextra -Werror` | ✅ sans warning |
| Norminette | ✅ tout OK |
| Args invalides rejetés | ✅ |
| Détection de mort (≤ 10 ms, rien après) | ✅ |
| Survie (`5 800 200 200`, `4 410 200 200`) | ✅ 0 mort |
| Fin par quota (compte exact) | ✅ |
| Format sortie conforme | ✅ |
| Fuites mémoire | ✅ 0 |
| Data races (helgrind/drd) | ✅ 0 |
