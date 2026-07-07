# Notes

## Préférences de l'utilisateur
- **Langue : français.** Toutes les leçons et interactions en français.
- Étudiant 42 (login: aizanic). Projet : Philosophers (mandatory).
- Apprend mieux ancré dans **son propre code** (il a déjà un squelette).

## État du code (au 2026-07-07)
Fichiers : `src/main.c`, `src/messages.c`, `src/utils.c`, `src/print.c`, `src/philo.h`.

Ce qui marche :
- Parsing des arguments + `ft_atoi` avec garde INT_MAX/MIN.
- Création d'un thread par philosophe, mutex par fourchette.
- Ordre pair/impair de prise des fourchettes (anti-deadlock) — déjà présent.
- Horodatage relatif via `start_time()` (static) + `gettimeofday`.

Bugs / manques à traiter (futures leçons) :
1. **Aucun monitor de mort** : rien ne vérifie `time_to_die`. Le sujet l'exige.
2. **`last_meal_time` jamais mis à jour** et `is_dead` jamais utilisé.
3. **Data race sur `printf`** : pas de mutex d'affichage → sorties mélangées.
4. **Data race sur `nb_meals_eaten`** : lu/écrit sans protection.
5. La condition de boucle `philo_routine` (`< max_meals || max_meals == 0`)
   ne s'arrête jamais proprement et n'écoute pas la mort.
6. `usleep` long pour manger/dormir → mort détectée en retard (précision).
7. Pas de `pthread_mutex_destroy` ni de `free` en fin de programme (fuites).
8. `one_philo` fait un `usleep` bloquant au lieu d'une vraie logique.

## Design system du cours (canonique)
- Feuille de style unique : `assets/lesson.css` (classes : .callout, .callout.ok,
  .callout.warn, .rules, .dragons, .source, .ask, .lesson-nav, .quiz).
- Quiz réutilisable : `assets/quiz.js` (div.quiz[data-answer], .opt, .feedback).
- Glossaire : `GLOSSARY.md` (markdown). Carte : `reference/carte-du-projet.html`.
- NE PAS réintroduire style.css ni glossary.html (doublons supprimés le 2026-07-07
  après fusion de deux sessions parallèles).

## Plan de progression
- L0001 : orientation — les deux dragons (deadlock / mort). ✅ fait.
- L0002 : deadlock & ordre des fourchettes (ancré dans son code). ✅ fait.
- L0003 (prochaine) : data race + mutex d'affichage (le `printf` non protégé).
- Puis : le monitor de mort (thread superviseur + last_meal_time protégé).
- Puis : arrêt propre de la simulation (flag stop protégé).
- Puis : précision du timing (ft_usleep) + cleanup/destroy/free.
