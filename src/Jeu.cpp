#include "Jeu.h"
#include "Vect2D.h"
#include "iostream"


Jeu::Jeu () : terrain(30, 40), perso(100, 100, 11, 11, 1, 0.1, 0.1), nbEnnemi(1){
    Ennemi e(100, 100, 10, 2, 1, 0.1, 0.1);
    perso.setArme(30,50,100, 1, 100, 0.5, 0.5);
    e.ajouterPointPatrouille(10,10);
    e.ajouterPointPatrouille(10,1);
    e.ajouterPointPatrouille(14,5);
    ennemis.push_back(e);

}

Terrain& Jeu::getTerrain (){
    return terrain;
}

Perso& Jeu::getPerso () {
    return perso;
}

const Terrain& Jeu::getConstTerrain () const {
    return terrain;
}

const Perso& Jeu::getConstPerso () const {
    return perso;
}

const Ennemi& Jeu::getConstIemeEnnemi (int i) const {
    return ennemis[i];
}


void Jeu::actionClavier (const char touche) {
    Vect2D vecteurDeplacement(0, 0);
    //perso.affichePosition();

    switch(touche) {
        case 'z' :
            vecteurDeplacement.y -=1;
            break;
        case 'q' :
            vecteurDeplacement.x -=1;
            break;
        case 's' :
            vecteurDeplacement.y +=1;
            break;
        case 'd' :
            vecteurDeplacement.x +=1;
            break;
    }

    HitboxRectangle hitboxVirtuelle = perso.detecterCollision(vecteurDeplacement);
    if( ! terrain.hitboxEstDansMur(hitboxVirtuelle)){
        perso.deplacement(vecteurDeplacement);
    }else{
	}
}

void Jeu::genererTerrain() {
	terrain.generer();
}


void Jeu::gestionDesBalles () {
    HitboxRectangle hitboxVirtuelle;


    for(int i=0; i< perso.getNombreProjectile() ; i++){
        
        //degat balle sur ennemi
        for(int j=0; j<=nbEnnemi; j++){
            if(ennemis[j].estToucheParBalle(perso.getIemeProjectile(i))){
                ennemis[j].prendreDegat(perso.getIemeProjectile(i).getDegat());
                perso.supprimerIemeProjectile(i);
            }
        }

        //colision balle perso
        hitboxVirtuelle = perso.getIemeProjectile(i).detecterCollision();
        
        if( ! terrain.hitboxEstDansMur(hitboxVirtuelle)){
            perso.avancerIemeProjectile(i);
        }
        else{
            perso.supprimerIemeProjectile(i);
        }
    }




    for(int j=0; j<=nbEnnemi; j++){

        for(int i=0; i< ennemis[j].getNombreProjectile() ; i++){

            //degat balle sur perso
            if(perso.estToucheParBalle(ennemis[j].getIemeProjectile(i))){
                perso.prendreDegat(ennemis[j].getIemeProjectile(i).getDegat());
                ennemis[j].supprimerIemeProjectile(i);
            }

            //colision balle enemi
            hitboxVirtuelle = ennemis[j].getIemeProjectile(i).detecterCollision();
            
            if( ! terrain.hitboxEstDansMur(hitboxVirtuelle)){
                ennemis[j].avancerIemeProjectile(i);
            }
            else{
                ennemis[j].supprimerIemeProjectile(i);
            }
        }
    }

}

void Jeu::actionsAutomatiques(){
    gestionDesBalles();
    HitboxRectangle hitboxVirtuelle;
        
    //deplacement ennemis avec collision
    for(int j=0; j<=nbEnnemi; j++){
        hitboxVirtuelle = ennemis[j].patrouilleDetecterCollision();
        if( ! terrain.hitboxEstDansMur(hitboxVirtuelle)){
            ennemis[j].patrouilleDeplacement();
        }else{

        }

        //update cooldown ennemi
        ennemis[j].updateDelai();
    }

    perso.updateDelai();
}


void Jeu::joueurTirer(const Vect2D & direction){
    perso.tirer(direction);
}