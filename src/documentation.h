/** \mainpage Somebody Stole My Hat !


\section Présentation Présentation

Notre jeu est un jeu de tir, vu du dessus. Il s'inspire notamment du jeu "Hotline Miami", publié en 2012 (ou du jeu "Commando: Wolf of the Battlefield", publié en 1985, pour les plus connaisseurs).

Ce jeu a été créé par :

- Florent MOULON (12005134)

- Aurélien BOISSOT (12002425)

- Damien LAQUEUVRE (12006112)

Avec l'aimable participation d'Antoine pour les musiques et sons.

ID du projet sur la forge : 23105

<br> <br> <br>

\section Règles Règles du jeu

Le but de notre jeu est de tuer tous les ennemis présents dans une salle, puis de recommencer dans une salle suivante remplie d'un plus grand nombre d'ennemis, jusqu'à ce que le personnage soit touché par une balle ennemie et meure. Le personnage dispose de 10 munitions, qui se rechargent automatiquement lorsqu'elles atteignent 0.

<br>

\section Fonctionnalités Fonctionnalités

Notre jeu est composé de 4 écrans différents :

- L'écran de menu permet de lancer une partie ou de quitter le jeu.

- L'écran de jeu 

  
  
<br>

\section Organisation Organisation du projet

A la racine du projet se trouvent le Makefile pour compiler, le README.md pour expliquer le projet, et 5 dossiers :

- le dossier /bin contient les exécutables

- le dossier /data contient les différents sprites, les musiques, les sons et la police d'écriture utilisée.

- le dossier /doc contient le dossier /html qui contient la documentation Doxygen, la présentation orale, le diagramme UML et le diagramme de Gantt

- le dossier /obj contient les fichiers .o qui sont générés lors de la compilation.

- le dossier /src contient les fichiers .h et .cpp, regroupés en plusieurs dossiers.

- le dossier /tmp contient les images temporaires générées par le programme.


<br>

\section  compilation Compilation et exécution

Le jeu est fait pour être compilé et exécuté sous Linux ou sous Windows avec WSL.

- Si la librairie SFML n'est pas installée sur votre machine, vous devez l'installer avec la commande : `sudo apt-get install libsfml-dev`.

- Pour compiler le code il faut ouvrir un terminal à la racine du projet, et utiliser la commande `make`.

- Pour lancer le jeu il faut ouvrir un terminal à la racine du projet, et utiliser la commande `./bin/SFML.out`.


<br>

\section doc Généreration de la documentation de code
 Dépendance : doxygen http://www.stack.nl/~dimitri/doxygen/ <br>
 utiliser la commande $ doxygen doc/documentation.doxy <br>
 Puis ouvrir doc/html/index.html avec firefox

*/