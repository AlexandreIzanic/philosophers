# Leçon 0003 — voyage du programme + le code a beaucoup avancé

## Ce qui s'est passé
L'utilisateur a demandé une 3e leçon pour « m'expliquer chaque étape du
programme ». J'ai dévié du plan (L0003 devait être data race) pour honorer la
demande : L0003 = **voyage chronologique** de `main()` à `cleanup()`.

## Découverte importante : l'état du code a bougé
Le code n'est plus le squelette décrit dans NOTES.md (version 2026-07-07 matin).
Il est maintenant **quasi complet** :
- Fichiers actuels : `main.c, init.c, messages.c, monitor.c, print.c, utils.c`.
- Le **monitor existe** (`monitor_routine`, `philo_is_dead`, `all_ate_enough`).
- `print_mutex`, `meal_mutex`, `stop_mutex` en place → data races traitées.
- `ft_usleep` (réveil anticipé sur `stop`) et `get_time_ms` présents.
- `last_meal_time` + `nb_meals_eaten` mis à jour sous `meal_mutex`.
- `cleanup` détruit les mutexes et free — pas de fuite évidente.
- Fin par quota de repas gérée (`all_ate_enough`).

Autrement dit : la plupart des « bugs/manques » listés dans NOTES.md (points 1-8)
ont été corrigés par l'utilisateur entre-temps. Les futures leçons ne doivent plus
présenter le monitor comme « à écrire » mais comme « à comprendre / durcir /
défendre ».

## Implications pédagogiques
- ZPD a changé : on n'est plus en phase construction mais en phase
  **consolidation + défense orale** (critère de succès de la mission :
  « savoir expliquer à l'oral »). Le voyage-du-programme y répond directement.
- Prochaines leçons candidates : (a) data race & pourquoi `print_mutex` — même si
  le mutex existe déjà, expliquer POURQUOI = valeur de soutenance ; (b) zoom
  monitor + précision timing (règle des 10 ms, `ft_usleep`) ; (c) vérifier avec
  `helgrind` (aucune ressource dédiée encore — gap dans RESOURCES.md).
- Nouveau composant réutilisable ajouté : `.flow` dans `lesson.css` (timeline
  numérotée pour tracer un déroulé). Réutilisable pour toute leçon « étape par
  étape ».
