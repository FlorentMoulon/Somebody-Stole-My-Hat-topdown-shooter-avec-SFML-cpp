#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include <termios.h>
#include <unistd.h> //??

#include "Jeu.h"
#include "Projectile.h"
#include "Vect2D.h"


void termMove(int x, int y) // deplace le curseur du terminal
{
    char t[16];
    sprintf(t, "\033[%d;%dH", y, x);
    printf("%s",t);
}

void termClear()  // efface le terminal
{
    system("clear");
}

void termInit()      // configure la saisie : ne pas afficher les caracteres tapes
{
    struct termios ttystate;
    bool state = true;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}




class WinTXT
{
private:

    int dimx;       //!< \brief largeur
    int dimy;       //!< \brief heuteur
    char* win;      //!< \brief stocke le contenu de la fentre dans un tableau 1D mais on y accede en 2D

public:

    WinTXT (int dx, int dy) {
        dimx = dx;
        dimy = dy;
        win = new char[dimx*dimy];
        clear();
        termInit();
    }

    void clear (char c=' ') {
        for(int i=0;i<dimx;++i)
            for(int j=0;j<dimy;++j)
                print(i,j,c);
    }

    void print (int x, int y, char c) {
        assert(x>=0);
        assert(y>=0);
        assert(x<dimx);
        assert(y<dimy);
        win[y*dimx+x] = c;
    }

    void print (int x, int y, char* c) {
        int i=0;
        while (c[i]!='\0') {print(x+i,y,c[i]);++i;}
    }

    void draw (int x=0, int y=0) {
        termMove(0,0);
        for(int j=0;j<dimy;++j) {
            for(int i=0;i<dimx;++i)
                printf("%c",win[j*dimx+i]);
            printf("\n");
        }
        termMove(0,dimy);
    }



    void pause() {

        printf("Appuyer sur une touche\n");
        while(!kbhit());

    }

    char getCh() { // lire un caractere si une touche a ete pressee
        char touche=0;

        if (kbhit())
            touche = fgetc(stdin);

        return touche;
    }

};



void txtAff(WinTXT & win, const Jeu & jeu) {
	const Terrain& ter = jeu.getConstTerrain();
	const Perso& joueur = jeu.getConstPerso();
    const Perso& ennemi = jeu.getConstIemeEnnemi(0);

	win.clear();

    // Affichage des murs

    for (unsigned int i=0; i<ter.getHauteur(); i++){
        for (unsigned int j=0; j<ter.getLargeur(); j++){
            win.print(j * 2 , i, ter.getYX(i, j));
        }
    }

    // Affichage du joueur
	win.print(joueur.getPosition().x * 2 , joueur.getPosition().y,'$');

    // Affichage ennemi
    win.print(ennemi.getPosition().x * 2 , ennemi.getPosition().y,'%');

    // Affichage des balles
    for (int i=0; i<jeu.getConstPerso().getNombreProjectile(); i++){
            win.print(jeu.getConstPerso().getIemeProjectile(i).getPosition().x * 2, jeu.getConstPerso().getIemeProjectile(i).getPosition().y, 'o');
        }


    win.print(0,0,jeu.getConstPerso().getNombreProjectile());   

	win.draw();
}

void txtBoucle (Jeu & jeu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (jeu.getConstTerrain().getLargeur()*2,jeu.getConstTerrain().getHauteur());

	bool ok = true;
	int c;

	do {
	    txtAff(win,jeu);

		usleep(100000);

		jeu.actionsAutomatiques();

        Vect2D vectdirection(0,1);

		c = win.getCh();
		switch (c) {
			case 'q':
				{jeu.actionClavier('q');}
				break;
			case 'd':
				{jeu.actionClavier('d');}
				break;
			case 's':
				{jeu.actionClavier('s');}
				break;
			case 'z':
				{jeu.actionClavier('z');}
				break;
            case 'g':
				{jeu.genererTerrain();}
				break;
            case 'a':
				{jeu.joueurTirer(vectdirection);}
				break;
			case 'p':
				{ok = false;}
				break;
            default:

                break;
		}

	} while (ok);

}




int main ( int argc, char** argv ) {
    termClear();
	Jeu jeu;

    jeu.genererTerrain();
	txtBoucle(jeu);

    termClear();
	return 0;
}
