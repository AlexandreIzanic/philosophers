# Mission: Threads & Mutexes (projet Philosophers 42)

## Why
Finir le projet Philosophers de 42 correctement — le rendre robuste et le
défendre en soutenance — tout en acquérant une vraie maîtrise de la
programmation concurrente (threads POSIX, mutexes, data races, deadlocks) qui
servira dans les projets suivants et en entretien technique.

## Success looks like
- Le programme respecte le sujet : un philosophe qui dépasse `time_to_die`
  meurt, la mort est détectée et annoncée en < 10 ms, sans mélange d'affichage.
- Aucune data race : `helgrind`/`valgrind --tool=helgrind` est propre.
- Aucun deadlock, même avec beaucoup de philosophes.
- Savoir expliquer à l'oral : pourquoi un mutex, pourquoi l'ordre des
  fourchettes, pourquoi le monitor, où sont les états partagés.

## Constraints
- Enseignement en **français**.
- Code en C, norme 42 (Norminette), pas de variables globales.
- L'utilisateur a déjà un squelette de code qui compile mais est incomplet
  (pas de monitor de mort, état partagé non protégé).

## Out of scope
- Le bonus (processus + sémaphores) pour l'instant — d'abord le mandatory.
- Autres langages / autres modèles de concurrence (async, acteurs).
