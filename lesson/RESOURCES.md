# Threads & Mutexes (Philosophers) — Resources

## Knowledge

- [Book: *The Little Book of Semaphores* — Allen B. Downey (Green Tea Press, CC BY-NC-SA)](https://greenteapress.com/wp/semaphores/)
  Manuel gratuit, référence sur la synchronisation concurrente. Chapitre
  "Dining Philosophers" = exactement ce projet. Use for: comprendre deadlock,
  starvation, et les patterns de solution (ordre des ressources, serveur).

- [man pthreads (7) — pthread_create, pthread_join](https://man7.org/linux/man-pages/man7/pthreads.7.html)
  Source primaire de l'API POSIX threads. Use for: signatures exactes,
  comportement de création/jointure des threads.

- [man pthread_mutex_lock (3)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
  Source primaire. Use for: sémantique lock/unlock, ce qui se passe en cas de
  double lock (deadlock) et d'unlock d'un mutex non détenu.

- [man pthread_create (3) — création de threads](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
  Source primaire. Use for: signature exacte, passage d'argument à la routine.

- [Guide: Philosophers 42 — ruinadd (Medium)](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
  Guide communautaire orienté sujet 42. Use for: interprétation du barème,
  pièges de correction. (Secondaire — vérifier contre les sources primaires.)

## Wisdom (Communities)

- [42 Discord / piscine locale + pairs sur le cluster](https://42.fr)
  Use for: soutenance blanche, faire relire son monitor par un pair, tester
  des cas limites ensemble.
- [r/C_Programming](https://reddit.com/r/C_Programming)
  Use for: questions pointues sur pthreads, revue de patterns de sync.

## Gaps
- Pas encore de ressource dédiée sur la **précision du timing** (ft_usleep
  robuste) — à trouver pour la leçon sur le timing.
