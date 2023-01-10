EXEC_NAME = SFML.out SFML2.out TXT.out TXT2.out Chemin.out TEST.out
OBJS = obj/HitboxRectangle.o obj/Item.o obj/Perso.o obj/Ennemi.o obj/Point2D.o obj/Projectile.o obj/Terrain.o obj/Vect2D.o obj/Meuble.o obj/Case.o obj/Jeu.o obj/Piece.o obj/Porte.o obj/Chemin.o obj/Noeud.o obj/Arme.o
OBJS_SFML=obj/TerrainSFML.o obj/PersoSFML.o obj/EnnemiSFML.o obj/ProjectileSFML.o obj/JeuSFML.o obj/Menu.o obj/Bouton.o obj/ArmeSFML.o obj/Pause.o obj/GameOver.o


DEPD_CORE = src/core/Vect2D.h src/core/Point2D.h src/core/HitboxRectangle.h 

DEPD_SFML = src/SFML/TerrainSFML.h src/SFML/PersoSFML.h src/SFML/EnnemiSFML.h src/SFML/ProjectileSFML.h src/SFML/JeuSFML.h src/SFML/ArmeSFML.h

DEPD_ECRAN = src/SFML/EcranBase.h src/SFML/Menu.h src/SFML/JeuSFML.h src/SFML/Bouton.h src/SFML/Pause.h src/SFML/GameOver.h

DEPD_TER = src/terrain/Case.h src/terrain/Meuble.h src/terrain/Piece.h src/terrain/Porte.h src/terrain/Terrain.h  

DEPD_PERSO = src/perso/Perso.h src/perso/Ennemi.h 

DEPD_PATHFINDING = src/pathfinding/Chemin.h src/pathfinding/Noeud.h

DEPD_ITEM = src/item/Item.h src/item/Projectile.h  src/item/Arme.h


INC = -Isrc -Isrc/core -Isrc/SFML -Isrc/terrain -Isrc/perso -Isrc/pathfinding -Isrc/item
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#---------VARIABLE DE COMPILATIONS------------#
CC = g++ $(INC)
FLAGS = -Wall -ggdb -g


#---------DIFFERENTS EXECUTABLES------------#
all: $(EXEC_NAME)

SFML.out: $(OBJS) $(OBJS_SFML) obj/mainSFML.o 
	$(CC) -g $(OBJS) $(OBJS_SFML) obj/mainSFML.o -o bin/SFML.out $(LIBS)

SFML2.out: $(OBJS) $(OBJS_SFML) obj/mainSFML2.o 
	$(CC) -g $(OBJS) $(OBJS_SFML) obj/mainSFML2.o -o bin/SFML2.out $(LIBS)

TXT.out: $(OBJS) obj/mainTXT.o 
	$(CC) -g $(OBJS) obj/mainTXT.o  -o bin/TXT.out 

TXT2.out: $(OBJS) obj/mainTXT2.o 
	$(CC) -g $(OBJS) obj/mainTXT2.o -o bin/TXT2.out 

TEST.out: $(OBJS) obj/main.o 
	$(CC) -g $(OBJS) obj/main.o -o bin/TEST.out 
	
Chemin.out: $(OBJS) $(OBJS_SFML) obj/mainChemin.o 
	$(CC) -g $(OBJS) $(OBJS_SFML) obj/mainChemin.o -o bin/Chemin.out $(LIBS)


#---------DEPENDANCES ELEMENTAIRES------------#

obj/HitboxRectangle.o : src/core/HitboxRectangle.h src/core/HitboxRectangle.cpp 
	$(CC) $(FLAGS) -c src/core/HitboxRectangle.cpp -o obj/HitboxRectangle.o

obj/Point2D.o : src/core/Point2D.h src/core/Point2D.cpp $(DEPD_CORE)
	$(CC) $(FLAGS) -c src/core/Point2D.cpp -o obj/Point2D.o

obj/Vect2D.o : src/core/Vect2D.h src/core/Vect2D.cpp 
	$(CC) $(FLAGS) -c src/core/Vect2D.cpp -o obj/Vect2D.o




#---------DEPENDANCES PATHFINDING------------#
obj/Noeud.o : src/pathfinding/Noeud.cpp $(DEPD_CORE) $(DEPD_PATHFINDING)
	$(CC) $(FLAGS) -c src/pathfinding/Noeud.cpp -o obj/Noeud.o

obj/Chemin.o : src/pathfinding/Chemin.cpp $(DEPD_CORE) $(DEPD_PATHFINDING) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/pathfinding/Chemin.cpp -o obj/Chemin.o


#---------DEPENDANCES PERSO------------#
obj/Perso.o : src/perso/Perso.cpp $(DEPD_CORE) $(DEPD_PERSO)
	$(CC) $(FLAGS) -c src/perso/Perso.cpp -o obj/Perso.o

obj/Ennemi.o : src/perso/Ennemi.cpp $(DEPD_CORE) $(DEPD_PERSO)
	$(CC) $(FLAGS) -c src/perso/Ennemi.cpp -o obj/Ennemi.o


#---------DEPENDANCES ITEM------------#
obj/Item.o : src/item/Item.cpp $(DEPD_CORE) $(DEPD_ITEM) $(DEPD_PERSO)
	$(CC) $(FLAGS) -c src/item/Item.cpp -o obj/Item.o

obj/Projectile.o : src/item/Projectile.h src/item/Projectile.cpp $(DEPD) $(DEPD_ITEM)
	$(CC) $(FLAGS) -c src/item/Projectile.cpp -o obj/Projectile.o

obj/Arme.o : src/item/Arme.h src/item/Arme.cpp $(DEPD) $(DEPD_ITEM)
	$(CC) $(FLAGS) -c src/item/Arme.cpp -o obj/Arme.o


#---------DEPENDANCES TERRAIN------------#
obj/Meuble.o : src/terrain/Meuble.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/terrain/Meuble.cpp -o obj/Meuble.o

obj/Porte.o : src/terrain/Porte.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/terrain/Porte.cpp -o obj/Porte.o

obj/Piece.o : src/terrain/Piece.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/terrain/Piece.cpp -o obj/Piece.o

obj/Terrain.o : src/terrain/Terrain.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/terrain/Terrain.cpp -o obj/Terrain.o

obj/Case.o : src/terrain/Case.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/terrain/Case.cpp -o obj/Case.o


#---------DEPENDANCES JEU------------#
obj/Jeu.o : src/Jeu.h src/Jeu.cpp $(DEPD_CORE) $(DEPD_TER) $(DEPD_PERSO)
	$(CC) $(FLAGS) -c src/Jeu.cpp -o obj/Jeu.o


#---------DEPENDANCES SFML------------#
obj/TerrainSFML.o : src/SFML/TerrainSFML.cpp $(DEPD_CORE) $(DEPD_SFML) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/SFML/TerrainSFML.cpp -o obj/TerrainSFML.o

obj/PersoSFML.o : src/SFML/PersoSFML.cpp $(DEPD_CORE) $(DEPD_SFML) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/SFML/PersoSFML.cpp -o obj/PersoSFML.o

obj/EnnemiSFML.o : src/SFML/EnnemiSFML.cpp $(DEPD_CORE) $(DEPD_SFML) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/SFML/EnnemiSFML.cpp -o obj/EnnemiSFML.o

obj/ArmeSFML.o : src/SFML/ArmeSFML.cpp $(DEPD_CORE) $(DEPD_SFML)
	$(CC) $(FLAGS) -c src/SFML/ArmeSFML.cpp -o obj/ArmeSFML.o

obj/ProjectileSFML.o : src/SFML/ProjectileSFML.cpp $(DEPD_CORE) $(DEPD_SFML)
	$(CC) $(FLAGS) -c src/SFML/ProjectileSFML.cpp -o obj/ProjectileSFML.o

obj/JeuSFML.o : src/SFML/JeuSFML.cpp $(DEPD_CORE) $(DEPD_SFML) $(DEPD_ECRAN)
	$(CC) $(FLAGS) -c src/SFML/JeuSFML.cpp -o obj/JeuSFML.o

obj/Menu.o : src/SFML/Menu.cpp $(DEPD_SFML) $(DEPD_ECRAN)
	$(CC) $(FLAGS) -c src/SFML/Menu.cpp -o obj/Menu.o

obj/Pause.o : src/SFML/Pause.cpp $(DEPD_SFML) $(DEPD_ECRAN)
	$(CC) $(FLAGS) -c src/SFML/Pause.cpp -o obj/Pause.o

obj/Bouton.o : src/SFML/Bouton.cpp $(DEPD_SFML)
	$(CC) $(FLAGS) -c src/SFML/Bouton.cpp -o obj/Bouton.o

obj/GameOver.o : src/SFML/GameOver.cpp $(DEPD_SFML) $(DEPD_ECRAN)
	$(CC) $(FLAGS) -c src/SFML/GameOver.cpp -o obj/GameOver.o


#---------DEPENDANCES MAIN------------#
obj/mainSFML.o : src/main/mainSFML.cpp $(DEPD_CORE) $(DEPD_SFML) $(DEPD_ECRAN)
	$(CC) $(FLAGS) -c src/main/mainSFML.cpp -o obj/mainSFML.o

obj/mainSFML2.o : src/main/mainSFML2.cpp $(DEPD_CORE) $(DEPD_SFML)
	$(CC) $(FLAGS) -c src/main/mainSFML2.cpp -o obj/mainSFML2.o

obj/mainTXT.o : src/main/mainTXT.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/main/mainTXT.cpp -o obj/mainTXT.o

obj/mainTXT2.o : src/main/mainTXT2.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/main/mainTXT2.cpp -o obj/mainTXT2.o

obj/main.o : src/main/main.cpp $(DEPD_CORE) $(DEPD_TER)
	$(CC) $(FLAGS) -c src/main/main.cpp -o obj/main.o

obj/mainChemin.o : src/main/mainChemin.cpp $(DEPD_CORE) $(DEPD_SFML)
	$(CC) $(FLAGS) -c src/main/mainChemin.cpp -o obj/mainChemin.o

#---------FONCTION ANNEXES------------#
clean:
	rm $(OBJS) $(OBJS_SFML)

veryclean: clean
	rm *.out
