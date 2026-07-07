# Espace d'apprentissage initialisé + orientation + leçon deadlock

L'utilisateur (étudiant 42, login aizanic) a un squelette de Philosophers qui
compile mais est incomplet (pas de monitor de mort, état partagé non protégé).
Mission établie : finir le mandatory correctement ET maîtriser threads/mutexes,
enseignement en français.

Prior knowledge démontré : il a lui-même écrit la stratégie pair/impair de prise
des fourchettes dans `pick_up_forks`. Donc il a déjà une intuition des mutexes
comme verrous de ressource. Les leçons partent de SON code, pas de zéro — c'est
son zone of proximal development.

Note process : deux sessions d'enseignement ont tourné en parallèle et produit
deux jeux d'artefacts. Fusionnés en un cours unique (design `lesson.css` +
`GLOSSARY.md` + `carte-du-projet.html`), doublons supprimés. Numérotation finale :
0001 = orientation (deux dragons), 0002 = deadlock & ordre des fourchettes.

Implications : ne pas ré-enseigner « qu'est-ce qu'un mutex » à froid. Prochaine
leçon (0003) = data race + mutex d'affichage (le `printf` non protégé est le bug
le plus visible et enchaîne naturellement sur le concept de section critique).
