# Philosophers Glossary

Langage canonique de cet espace d'apprentissage. Toutes les leçons emploient ces
termes. On ajoute un terme seulement une fois que tu sais l'utiliser correctement.

## Terms

**Thread**:
Un fil d'exécution qui tourne en parallèle des autres, dans le même processus et donc
la même mémoire. Dans ce projet, un philosophe = un thread.
_Avoid_: process, tâche

**Mutex** (mutual exclusion) :
Un verrou qui garantit qu'un seul thread à la fois exécute une section critique ou
touche une donnée partagée. Une fourchette = un mutex.
_Avoid_: lock (en français), sémaphore

**Section critique** :
Le bout de code qui accède à une donnée partagée et qui ne doit être exécuté que par
un thread à la fois — encadré par `lock` puis `unlock`.
_Avoid_: zone protégée

**Data race** :
Bug où deux threads accèdent à la même donnée « en même temps » sans mutex, dont au
moins un en écriture. Résultat imprévisible et non reproductible.
_Avoid_: race condition (voir ci-dessous), conflit

**Deadlock** (interblocage) :
Situation où des threads s'attendent mutuellement pour toujours — p.ex. chacun tient
une fourchette et attend celle du voisin. Le programme se fige.
_Avoid_: blocage, freeze

**Starvation / mort** :
Un philosophe qui n'obtient pas ses deux fourchettes à temps dépasse `time_to_die`
depuis son dernier repas et meurt. La simulation doit le détecter.
_Avoid_: famine (seul), timeout

**Monitor** (moniteur) :
Le mécanisme (souvent un thread dédié) qui surveille en continu si un philosophe a
dépassé `time_to_die`, et arrête la simulation à la mort.
_Avoid_: watcher, superviseur

**time_to_die / time_to_eat / time_to_sleep** :
Les paramètres en millisecondes du sujet. `time_to_die` = délai max sans manger avant
la mort, compté depuis le début du **dernier repas**.
_Avoid_: durée, délai (seuls)
