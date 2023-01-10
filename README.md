
# Somebody Stole My Hat !

  
  

## Présentation

Notre jeu est un jeu de tir, vu du dessus. Il s'inspire notamment du jeu "Hotline Miami", publié en 2012 (ou du jeu "Commando: Wolf of the Battlefield", publié en 1985, pour les plus connaisseurs).

  
  

## Informations générales

Ce jeu a été créé par :

- Florent MOULON (12005134)

- Aurélien BOISSOT (12002425)

- Damien LAQUEUVRE (12006112)

Avec l'aimable participation d'Antoine pour les musiques et sons.

  

ID du projet sur la forge : 23105

  
  

## Règles du jeu

Le but de notre jeu est de tuer tous les ennemis présents dans une salle, puis de recommencer dans une salle suivante, plus grande, et remplie d'un plus grand nombre d'ennemis, jusqu'à ce que le personnage soit touché par une balle ennemie et meure. Le personnage dispose de 10 munitions, qui se rechargent automatiquement lorsqu'elles atteignent 0.

  
  

## Fonctionnalités

Notre jeu est composé de 4 écrans différents :

- L'écran de menu permet de lancer une partie (c'est-à-dire accéder à l'écran de jeu) ou de quitter le jeu.

- L'écran de jeu est composé de plusieurs éléments : 
	- La majorité de l'écran est occupé par le jeu en lui-même. La carte de jeu est composée d'un ensemble de salles générées procéduralement. Puis des ennemis sont répartis aléatoirement sur la carte, et le joueur apparaît dans une des pièces. Le joueur doit alors réussir à tuer tous les ennemis en leur tirant dessus, sans se faire toucher par les balles ennemies. Lorsque tous les ennemis ont été tués, une nouvelle carte, plus grande que la précédente, est générée procéduralement. Elle contient également un plus grand nombre d'ennemis.
	- Dans le coin supérieur droit de l'écran se trouve une mini carte permettant d'afficher une version réduite du terrain afin de se situer dans celui-ci. Il permet aussi d'afficher la position du joueur dans le terrain.
	- Dans le coin inférieur gauche de l'écran se trouve un affichage indiquant le nombre de munitions restantes au personnage.

- L'écran de pause apparaît lorsque l'on appuie sur la touche Echap lorsque l'on est en jeu. Celui-ci permet de reprendre le jeu où l'on en était, ou de revenir au menu principal.

- L'écran de Game Over apparait lorsque notre personnage meurt. On peut alors revenir au menu.
  
  

## Compilation et exécution

Le jeu est fait pour être compilé et exécuté sous Linux ou sous Windows avec WSL.

- Si la librairie SFML n'est pas installée sur votre machine, vous devez l'installer avec la commande : `sudo apt-get install libsfml-dev`.

- Pour compiler le code il faut ouvrir un terminal à la racine du projet, et utiliser la commande `make`.

- Pour lancer le jeu il faut ouvrir un terminal à la racine du projet, et utiliser la commande `./bin/SFML.out`.

- Vous pouvez ensuite quitter le jeu en appuyant sur la touche Echap, ou en cliquant sur le bouton quitter.

  
  
  

## Organisation du projet

A la racine du projet se trouvent le Makefile pour compiler, le README.md pour expliquer le projet, et 6 dossiers :

- le dossier /bin contient les exécutables

- le dossier /data contient les différents sprites, les musiques, les sons et la police d'écriture utilisée.

- le dossier /doc contient le dossier /html qui contient la documentation Doxygen, la présentation orale, le diagramme UML et le diagramme de Gantt

- le dossier /obj contient les fichiers .o qui sont générés lors de la compilation.

- le dossier /src contient les fichiers .h et .cpp, regroupés en plusieurs dossiers.

- le dossier /tmp contient les images temporaires générées par le programme.



## Généreration de la documentation de code
Dépendance : [Page web de Doxygen](https://www.doxygen.nl/)

- Dans un terminal à la racine du projet, utiliser la commande `doxygen doc/documentation.doxy` pour générer la documaentation. Puis ouvrir le fichier doc/html/index.html avec Firefox.
