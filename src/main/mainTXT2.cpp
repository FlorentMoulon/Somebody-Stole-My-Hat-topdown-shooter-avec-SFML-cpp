#include <cassert>
#include <iostream>

#include "Jeu.h"

using namespace std;



bool txtBoucle (Jeu & jeu) {
    char p;
    Vect2D vectTir(0,1);

    for (unsigned int i=0; i<jeu.getTerrain().getHauteur(); i++){
        for (unsigned int j=0; j<jeu.getTerrain().getLargeur(); j++){
            for (int i=0; i<jeu.getConstPerso().getNombreProjectile(); i++){
                if(jeu.getConstPerso().getIemeProjectile(i).getPosition().x == j && jeu.getConstPerso().getIemeProjectile(i).getPosition().y == i){
                    cout<<'o';
                }
            }
            if(jeu.getConstPerso().getPosition().x == j && jeu.getConstPerso().getPosition().y == i){
                cout<<'$';
            }
            if(jeu.getConstIemeEnnemi(i).getPosition().x == j && jeu.getConstIemeEnnemi(0).getPosition().y == i){
                cout<<'%';
            }
            else{
                cout<<jeu.getTerrain().getYX(i, j);
            }
            cout<<' ';
        }cout<<endl;
    }cout<<endl;
	cout<<"Entrer une touche"<<endl;
    cin>>p;

	switch (p) {
		case 'q':
			jeu.actionClavier('q');
			break;
		case 'd':
			jeu.actionClavier('d');
			break;
		case 's':
			jeu.actionClavier('s');
			break;
		case 'z':
			jeu.actionClavier('z');
			break;
		case 'p':
			return true;
			break;
        case 'a':
			jeu.joueurTirer(vectTir);
			break;
        case 'g':
			jeu.genererTerrain();
			break;
        default:
            return true;
            break;
	}

    jeu.actionsAutomatiques();

    std::cout<<jeu.getConstPerso().getNombreProjectile()<<std::endl;

    //system("clear");

    return false;
}



int main ( int argc, char** argv ) {
	Jeu jeu;
    jeu.genererTerrain();

    bool stop = false;

    while(!stop){
        stop = txtBoucle(jeu);
    }


	return 0;
}
