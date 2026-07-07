# Notes

## Préférences de l'utilisateur
- **Langue : français.** Toutes les leçons et interactions en français.
- Étudiant 42 (login: aizanic). Projet : Philosophers (mandatory).
- Apprend mieux ancré dans **son propre code** (il a déjà un squelette).

## État du code (au 2026-07-07, MAJ après L0003)
Fichiers : `src/main.c`, `src/init.c`, `src/messages.c`, `src/monitor.c`,
`src/print.c`, `src/utils.c`, `src/philo.h`.

**Le code est maintenant quasi complet** — l'utilisateur a corrigé la plupart des
manques listés dans la version précédente de ces notes. Ce qui est en place :
- Parsing + `ft_atoi` (garde INT_MAX/MIN) + `validate_args`.
- Un thread par philo, un mutex par fourchette, ordre pair/impair anti-deadlock.
- **Monitor** (`monitor_routine`, `philo_is_dead`, `all_ate_enough`) : détecte la
  mort ET la fin par quota de repas.
- `print_mutex`, `meal_mutex`, `stop_mutex` → data races traitées.
- `last_meal_time` + `nb_meals_eaten` maj sous `meal_mutex`.
- `ft_usleep` avec réveil anticipé sur `stop` ; `get_time_ms`.
- `cleanup` : destroy des mutexes + free.
- `one_philo` : logique dédiée (prend 1 fourchette, attend, meurt).

À creuser/durcir (futures leçons — plus de la consolidation que de la
construction) :
- Vérifier l'absence de data race à l'outil : `valgrind --tool=helgrind`
  (pas encore de ressource dédiée — gap dans RESOURCES.md).
- Précision du timing / règle des 10 ms (zoom sur `ft_usleep` + monitor).
- Expliquer POURQUOI chaque mutex (valeur soutenance), même s'ils existent déjà.

## Design system du cours (canonique)
- Feuille de style unique : `assets/lesson.css` (classes : .callout, .callout.ok,
  .callout.warn, .rules, .dragons, .source, .ask, .lesson-nav, .quiz, .flow).
- `.flow` = timeline numérotée (ajoutée en L0003) pour tracer un déroulé étape
  par étape. Réutilisable.
- Quiz réutilisable : `assets/quiz.js` (div.quiz[data-answer], .opt, .feedback).
- Glossaire : `GLOSSARY.md` (markdown). Carte : `reference/carte-du-projet.html`.
- NE PAS réintroduire style.css ni glossary.html (doublons supprimés le 2026-07-07
  après fusion de deux sessions parallèles).

## Plan de progression
- L0001 : orientation — les deux dragons (deadlock / mort). ✅ fait.
- L0002 : deadlock & ordre des fourchettes (ancré dans son code). ✅ fait.
- L0003 : voyage du programme, de main() à cleanup() (vue d'ensemble). ✅ fait.
- L0004 : data race & POURQUOI le print_mutex — 2 raisons, dont l'astuce
  print_mutex tenu pendant la levée de stop (rien après « died »). ✅ fait.
- L0005 (candidate) : zoom monitor + précision timing (règle 10 ms, ft_usleep).
- Puis : vérifier à l'outil avec helgrind (trouver une ressource d'abord).
- Puis : arrêt propre déjà en place → le durcir / cas limites de soutenance.
