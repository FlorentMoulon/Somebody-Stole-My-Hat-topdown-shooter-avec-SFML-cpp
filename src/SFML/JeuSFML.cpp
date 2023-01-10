#include "JeuSFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <string>
#include <cassert>
#include <chrono>
#include <thread>

JeuSFML::JeuSFML() : m_nbMunitions(sf::Vector2f(0, 0), "Munitions : 10"), m_terSFML(20, 20, TAILLE_CASE), m_pathfinding(m_terSFML.m_ter), m_joueurSFML(100, 100, 12, 12, 0.4, 0.5, 0.5)
, m_ennemiType(50, 50, 6, 4, 0.4, 0.3, 0.3) {
    m_ennemiType.setArme(15, 10, 25, 0.5, 100, 0.25, 0.25);
    m_joueurSFML.setArme(6, 10, 25, 0.5, 100, 0.25, 0.25);
}


JeuSFML::~JeuSFML(){}

sf::Image JeuSFML::getImTer(){
    return m_terSFML.m_image;
}

void JeuSFML::init() {


    /*m_terSFML.m_ter.generer();
    m_terSFML.genererImage();
    m_textureFond.loadFromImage(m_terSFML.m_image);
    m_spriteFond.setTexture(m_textureFond);*/
    m_joueurSFML.setPosition(8, 8);
    m_viewSave.x = m_joueurSFML.m_perso.getPosition().x*TAILLE_CASE;
    m_viewSave.y = m_joueurSFML.m_perso.getPosition().y*TAILLE_CASE;

}



void JeuSFML::genererNiveau(int nbEnnemi, int dimTerX, int dimTerY){
    //m_terSFML.m_image.saveToFile("tmp/t1.png");

    //Terrain
    Terrain ter(dimTerX, dimTerY);
    ter.generer();
    TerrainSFML terSFML(ter, TAILLE_CASE);
    terSFML.genererImage();
    m_terSFML.changerTerrain(terSFML);

    //On change le fond
    m_textureFond.loadFromImage(m_terSFML.m_image);
    m_spriteFond.setTexture(m_textureFond);


    //Maj du pathfinding
    m_pathfinding.setGraph(m_terSFML.m_ter);
    std::cout<<m_terSFML.m_ter<<std::endl;
    

    //Personnage
    m_joueurSFML.setVivant();
    int pieceJ = placeJoueur();
    //m_terSFML.m_image.saveToFile("tmp/t2.png");

    //Ennemis
    m_ennemis.clear();
    for (int i = 0; i<nbEnnemi; i++){
        placeEnnemi(pieceJ);
    }

    //Vue
    m_viewSave.x = m_joueurSFML.m_perso.getPosition().x*TAILLE_CASE;
    m_viewSave.y = m_joueurSFML.m_perso.getPosition().y*TAILLE_CASE;
}


int JeuSFML::placeJoueur(){
    int NoPiece = rand() % m_terSFML.m_ter.getNbPiece();
    Point2D coord (definitCoordValide(NoPiece));
    m_joueurSFML.setPosition(coord);
    return NoPiece;
}


void JeuSFML::test(){
    for (int i = 0; i<(int)m_terSFML.m_ter.getNbPorte();i++){
    }
}

void JeuSFML::placeEnnemi(int pieceJoueur){
    int nbPiece =  m_terSFML.m_ter.getNbPiece();
    int NumPiece = rand() % nbPiece;
    while (NumPiece == pieceJoueur){
        NumPiece = rand() % nbPiece;
    }
    Point2D emplacement (definitCoordValide(NumPiece));
    m_ennemiType.setPosition(emplacement);

    int numNouvellePiece;
    if (NumPiece == 0) numNouvellePiece = NumPiece + 1;
    else numNouvellePiece = NumPiece - 1;



    //------------Definition patrouille ennemi
    std::vector <Point2D> patrouille;
    Point2D arrivee (definitCoordValide(numNouvellePiece));
    m_pathfinding.setArriveeDepart(emplacement, arrivee);
    patrouille = m_pathfinding.trouveChemin();
    m_ennemiType.m_ennemi.setCheminPatrouille(patrouille);
    

    //------------Definition chemin pathfind Joueur
    std::vector <Point2D> pathfind;
    arrivee = m_joueurSFML.m_perso.getPosition();
    m_pathfinding.setArriveeDepart(emplacement, arrivee);
    pathfind = m_pathfinding.trouveChemin();
    m_ennemiType.m_ennemi.setCheminJoueur(pathfind);
    
    
    m_ennemis.push_back(m_ennemiType);
}


Point2D JeuSFML::definitCoordValide(int NoPiece){
    //Initialisation

    int plageX = m_terSFML.m_ter.getIemePiece(NoPiece).getLargeur();
    int plageY = m_terSFML.m_ter.getIemePiece(NoPiece).getHauteur();
    int coinHgX = m_terSFML.m_ter.getIemePiece(NoPiece).getChg().x;
    int coinHgY = m_terSFML.m_ter.getIemePiece(NoPiece).getChg().y;
    
    int coordX = (rand() % plageX) + coinHgX ;
    int coordY = (rand() % plageY) + coinHgY ; 

    Point2D coordPorte(m_terSFML.m_ter.retrouvePorte(NoPiece));
    Point2D coordFin(coordX, coordY);
    
    //on créer le chemin entre le point et la porte
    m_pathfinding.setArriveeDepart(coordPorte, coordFin);
    //m_pathfinding.cheminExiste();
    while (!m_terSFML.m_ter.caseEstVide(coordFin.y, coordFin.x) || !(m_pathfinding.cheminExiste())){
        int coordX = (rand() % plageX) + coinHgX;
        int coordY = (rand() % plageY) + coinHgY; 
        coordFin.x = coordX;
        coordFin.y = coordY;
        m_pathfinding.setArriveeDepart(coordPorte, coordFin);
        
    }

    Point2D centre (0.3, 0.3);
    return (coordFin + centre);

    /*
    Point2D coordDepart (coordX, coordY);
    Point2D coordPorte(m_terSFML.m_ter.retrouvePorte(coordDepart));
    while (!departValide){
        if (coordX)
    }*/

}


void JeuSFML::affichageCollision(sf::RenderWindow & window){
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(0,0,0,0));
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(sf::Color(125, 250, 100));

    //Perso
    rectangle.setSize(sf::Vector2f(
        TAILLE_CASE * m_joueurSFML.m_perso.getHitbox().getLargeur(),
        TAILLE_CASE * m_joueurSFML.m_perso.getHitbox().getHauteur()));
    rectangle.setPosition(
        TAILLE_CASE * m_joueurSFML.m_perso.getHitbox().getChg().x,
        TAILLE_CASE * m_joueurSFML.m_perso.getHitbox().getChg().y);
    window.draw(rectangle);


    //balles perso
    for(int i = 0; i<m_joueurSFML.getNbProjectile(); i++){
        rectangle.setSize(sf::Vector2f(
            TAILLE_CASE * m_joueurSFML.getIemeProjectile(i).getHitbox().getLargeur(),
            TAILLE_CASE * m_joueurSFML.getIemeProjectile(i).getHitbox().getHauteur()));
        rectangle.setPosition(
            TAILLE_CASE * m_joueurSFML.getIemeProjectile(i).getHitbox().getChg().x,
            TAILLE_CASE * m_joueurSFML.getIemeProjectile(i).getHitbox().getChg().y);
        window.draw(rectangle);
    }

    //Ennemis
    for(int j=0; j< (int)m_ennemis.size(); j++){
        rectangle.setSize(sf::Vector2f(
            TAILLE_CASE * m_ennemis[j].m_ennemi.getHitbox().getLargeur(),
            TAILLE_CASE * m_ennemis[j].m_ennemi.getHitbox().getHauteur()));
        rectangle.setPosition(
            TAILLE_CASE * m_ennemis[j].m_ennemi.getHitbox().getChg().x,
            TAILLE_CASE * m_ennemis[j].m_ennemi.getHitbox().getChg().y);
        if (m_ennemis[j].estAggro()) rectangle.setOutlineColor(sf::Color(250, 120, 100));
        window.draw(rectangle);
        rectangle.setOutlineColor(sf::Color(125, 250, 100));


        //balles ennemis
        for(int i = 0; i<m_ennemis[j].getNbProjectile(); i++){
            rectangle.setSize(sf::Vector2f(
                TAILLE_CASE * m_ennemis[j].getIemeProjectile(i).getHitbox().getLargeur(),
                TAILLE_CASE * m_ennemis[j].getIemeProjectile(i).getHitbox().getHauteur()));
            rectangle.setPosition(
                TAILLE_CASE * m_ennemis[j].getIemeProjectile(i).getHitbox().getChg().x,
                TAILLE_CASE * m_ennemis[j].getIemeProjectile(i).getHitbox().getChg().y);
            window.draw(rectangle);
        }
    }

}


void JeuSFML::affichage(sf::RenderWindow & window, sf::View view, sf::View viewMinimap, sf::View viewNbBalles, bool tgcm) {
    window.clear();

    //affichages dans la vue principale
    window.setView(view);

    window.draw(m_spriteFond);

    //perso
    window.draw(m_joueurSFML.getSprite());
    for(int i = 0; i<m_joueurSFML.getNbProjectile(); i++){
        window.draw(m_joueurSFML.getIemeProjectile(i).getSprite());
    }

    //ennemis
    for(int j=0; j< (int)m_ennemis.size(); j++){
        window.draw(m_ennemis[j].getSprite());
        for(int i = 0; i<m_ennemis[j].getNbProjectile(); i++){
            window.draw(m_ennemis[j].getIemeProjectile(i).getSprite());
        }
    }
    

    //affichage de la minimap par dessus le jeu
    window.setView(viewMinimap);
    window.draw(m_spriteFond);
    window.draw(m_joueurSFML.getSprite());


    //affichage nbBalles
    window.setView(viewNbBalles);
    window.draw(m_nbMunitions.m_sprite);
    window.draw(m_nbMunitions.m_texte);

    window.setView(view); //on repasse la view du jeu comme view principale

    //affiche les boites de collisions, uniquement pour le debugage si le tgcm est activé
    if(tgcm){
        affichageCollision(window);
    }


    window.display();
}

void JeuSFML::supprimerEnnemi(int i){
    assert(i< (int)m_ennemis.size());

    m_ennemis.erase(m_ennemis.begin() + i);
}

void JeuSFML::suitSouris (const sf::RenderWindow & window) {
    sf::Vector2i coordSouris;
    sf::Vector2f coordSourisMonde;
    sf::Vector2f coordObjet;
    double angleRot;

    coordSouris = sf::Mouse::getPosition(window);
    coordSourisMonde = window.mapPixelToCoords(coordSouris);
    coordObjet = m_joueurSFML.getSprite().getPosition();
    float dx = coordObjet.x - coordSourisMonde.x;
    float dy = coordObjet.y - coordSourisMonde.y;
    angleRot = atan2(dy, dx) * 180 / PI;
    m_joueurSFML.setRotationSprite(angleRot+270);
}

void JeuSFML::orienterEnnemi (EnnemiSFML & ennemi, const sf::RenderWindow & window){
    sf::Vector2i coordSouris;
    sf::Vector2f coordSourisMonde;
    sf::Vector2f coordObjet;
    double angleRot;

    coordSouris = sf::Mouse::getPosition(window);
    coordSourisMonde = window.mapPixelToCoords(coordSouris);
    coordObjet = ennemi.getSprite().getPosition();
    float dx = coordObjet.x - coordSourisMonde.x;
    float dy = coordObjet.y - coordSourisMonde.y;
    angleRot = atan2(dy, dx) * 180 / PI;

    ennemi.setRotationSprite(angleRot+270);
}

void JeuSFML::deplacementView(sf::View & view, const Vect2D & vectDeplacement) {
    sf::Vector2f vectView = view.getCenter();
    Vect2D deplacement(m_joueurSFML.getSprite().getPosition().x + (vectDeplacement.x)*TAILLE_CASE,
                       m_joueurSFML.getSprite().getPosition().y + (vectDeplacement.y)*TAILLE_CASE);

    float xOffset = abs(vectView.x - deplacement.x);
    float yOffset = abs(vectView.y - deplacement.y);

    if(xOffset > 1*TAILLE_CASE) view.move(vectDeplacement.x*m_joueurSFML.m_perso.getVitesse()*TAILLE_CASE, 0);
    if(yOffset > 1*TAILLE_CASE) view.move(0, vectDeplacement.y*m_joueurSFML.m_perso.getVitesse()*TAILLE_CASE);
}


void JeuSFML::gestionBalles(const sf::SoundBuffer & buffer_impactBois, sf::Sound & son_impactBois,
                            const sf::SoundBuffer & buffer_degatEnnemi, sf::Sound & son_degatEnnemi){
    HitboxRectangle hitboxVirtuelle;
    bool aSupprimmer =false;
    //collision balle joueur

    for(int i=0; i< (int)m_joueurSFML.getNbProjectile() ; i++){
        aSupprimmer = false;

        //degat balle sur ennemi
        for(int j=0; j< (int)m_ennemis.size(); j++){
            if(m_ennemis[j].m_ennemi.estToucheParBalle(m_joueurSFML.getIemeProjectile(i).m_projectile)){
                //la balle à touché le Jeme ennemi
                m_ennemis[j].m_ennemi.prendreDegat(m_joueurSFML.getIemeProjectile(i).m_projectile.getDegat());
                aSupprimmer = true;
                son_degatEnnemi.setBuffer(buffer_degatEnnemi);
                son_degatEnnemi.play();
            }
        }
        
        hitboxVirtuelle = m_joueurSFML.getIemeProjectile(i).m_projectile.detecterCollision();

        if(! m_terSFML.m_ter.hitboxEstDansMur(hitboxVirtuelle)){
            //le chemin est libre, la balle avance
            m_joueurSFML.avancerIemeProjectile(i);
        }
        else{
            //la balle à ateint un obstacle
            aSupprimmer = true;
            son_impactBois.setBuffer(buffer_impactBois);
            son_impactBois.play();
        }

        //supression du projectile si il a touché quelquechose
        if(aSupprimmer){
            m_joueurSFML.supprimerIemeProjectile(i);
        }
    }

    //collision balle ennemis
    for(int j=0; j< (int)m_ennemis.size(); j++){

        for(int i=0; i< m_ennemis[j].getNbProjectile() ; i++){
            aSupprimmer = false;

            //degat balle sur perso
            if(m_joueurSFML.m_perso.estToucheParBalle(m_ennemis[j].getIemeProjectile(i).m_projectile)){
                //la balle à touché le joueur
                m_joueurSFML.m_perso.prendreDegat(m_ennemis[j].getIemeProjectile(i).m_projectile.getDegat());
                aSupprimmer = true;
            }

            //colision balle ennemi
            hitboxVirtuelle = m_ennemis[j].getIemeProjectile(i).m_projectile.detecterCollision();
            
            if( ! m_terSFML.m_ter.hitboxEstDansMur(hitboxVirtuelle)){
                //le chemin est libre, la balle avance
                m_ennemis[j].avancerIemeProjectile(i);
            }
            else{ 
                //la balle à ateint un obstacle
                aSupprimmer = true;
                son_impactBois.setBuffer(buffer_impactBois);
                son_impactBois.play();
            }

            //supression du projectile si il a touché quelquechose
            if(aSupprimmer){
                m_ennemis[j].supprimerIemeProjectile(i);
            }
        }
    }
}



void JeuSFML::ajouterEnnemi(const EnnemiSFML & ennemi) {
    m_ennemis.push_back(ennemi);
}

bool JeuSFML::departValide(const Point2D & pt){
    
    return false;
}

void JeuSFML::gestionMortEnnemis(const sf::SoundBuffer & buffer_mortEnnemi, sf::Sound & son_mortEnnemi){
    for(int i=0; i< (int)m_ennemis.size(); i++){
        if(m_ennemis[i].m_ennemi.getMort()){
            	supprimerEnnemi(i);
                son_mortEnnemi.setBuffer(buffer_mortEnnemi);
                son_mortEnnemi.play();
        }
    }
}

void JeuSFML::actionsAutoSFML(const sf::SoundBuffer & buffer_impactBois, sf::Sound & son_impactBois, 
                              const sf::SoundBuffer & buffer_degatEnnemi, sf::Sound & son_degatEnnemi,
                              const sf::SoundBuffer & buffer_mortEnnemi, sf::Sound & son_mortEnnemi) {
    Vect2D direction (0,0);
    ProjectileSFML p;

    gestionBalles(buffer_impactBois, son_impactBois, buffer_degatEnnemi, son_degatEnnemi);
    gestionMortEnnemis(buffer_mortEnnemi, son_mortEnnemi);

    //update cooldown ennemi
    for(unsigned int j=0; j<m_ennemis.size(); j++){
        m_ennemis[j].updateDelai();
    }

    //update cooldown perso 
    m_joueurSFML.updateDelai();
}

void JeuSFML::finNiveau(){
    if(m_ennemis.size() == 0){
    }
}


int JeuSFML::boucle(sf::RenderWindow & window, sf::View & view) {
    //tgcm : ta g**** c'est magique, empêche la mort du perso
    bool tgcm = false;
    bool ennemi_freeze = false;
    
    view.setCenter(m_viewSave);
    Point2D positionJoueur = positionJoueur;
    Point2D positionEnnemi;
    std::vector <Point2D> c; 
    int iteration = 0;


    //création de la view pour afficher le nombre de balles
    m_nbMunitions.setPosition(sf::Vector2f(0, window.getSize().y));
    m_nbMunitions.m_texte.move(40, -15);
    sf::View viewNbBalles = window.getDefaultView();
    viewNbBalles.move(-160, 100);


    //création de la mini-map
    sf::View viewMinimap(sf::Vector2f(m_terSFML.m_ter.getLargeur()*100/2, m_terSFML.m_ter.getLargeur()*100/2) , sf::Vector2f(m_terSFML.m_ter.getLargeur()*100, m_terSFML.m_ter.getHauteur()*100));
    sf::Vector2f tailleMinimap(0.2, 0.35);
    sf::Vector2f positionMinimap(1-tailleMinimap.x, 0);
    viewMinimap.setViewport(sf::FloatRect(positionMinimap, tailleMinimap));


    //musique de fond
    sf::Music backgroundMusic;
    assert(backgroundMusic.openFromFile("data/music/MusiqueJeu.wav"));
    backgroundMusic.setVolume(10);
    backgroundMusic.play();

    //chargement buffers sons
    sf::SoundBuffer buffer_mortPerso;
    assert(buffer_mortPerso.loadFromFile("data/music/VOIX/MORT_PERSO/MORT_PERSO_(1).ogg"));
    sf::Sound son_mortPerso;

    sf::SoundBuffer buffer_mortEnnemi;
    assert(buffer_mortEnnemi.loadFromFile("data/music/VOIX/MORT_ENNEMI/MORT_ENNEMI_(1).ogg"));
    sf::Sound son_mortEnnemi;

    sf::SoundBuffer buffer_degatPerso;
    assert(buffer_degatPerso.loadFromFile("data/music/VOIX/DEGAT_PERSO/DEGAT_PERSO_(1).ogg"));
    sf::Sound son_degatPerso;

    sf::SoundBuffer buffer_degatEnnemi;
    assert(buffer_mortPerso.loadFromFile("data/music/VOIX/DEGAT_ENNEMI/DEGAT_ENNEMI_(1).ogg"));
    sf::Sound son_degatEnnemi;

    sf::SoundBuffer buffer_footstepPerso1;
    assert(buffer_footstepPerso1.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_PERSO/FS_PERSO_(1).ogg"));
    sf::SoundBuffer buffer_footstepPerso2;
    assert(buffer_footstepPerso2.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_PERSO/FS_PERSO_(2).ogg"));
    sf::SoundBuffer buffer_footstepPerso3;
    assert(buffer_footstepPerso3.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_PERSO/FS_PERSO_(3).ogg"));
    sf::Sound son_footstepPerso;
    int delai_fsPerso = 8;
    int decompte_fsPerso = 8;

    //on ne joue pas les sons des pas des ennemis car cela fait trop de bruit (vu le nombre d'ennemis)
    /*sf::SoundBuffer buffer_footstepEnnemi1;
    assert(buffer_footstepEnnemi1.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_ENNEMI/FS_ENNEMI_(1).ogg"));
    sf::SoundBuffer buffer_footstepEnnemi2;
    assert(buffer_footstepEnnemi2.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_ENNEMI/FS_ENNEMI_(2).ogg"));
    sf::SoundBuffer buffer_footstepEnnemi3;
    assert(buffer_footstepEnnemi3.loadFromFile("data/music/FOOTSTEP/FOOTSTEP_ENNEMI/FS_ENNEMI_(3).ogg"));
    sf::Sound son_footstepEnnemi;
    int delai_fsEnnemi = 4;
    int decompte_fsEnnemi = 4;*/

    sf::SoundBuffer buffer_tir1;
    assert(buffer_tir1.loadFromFile("data/music/ARME/SHOT/KALASH_SHOT_(1).ogg"));
    sf::SoundBuffer buffer_tir2;
    assert(buffer_tir2.loadFromFile("data/music/ARME/SHOT/KALASH_SHOT_(2).ogg"));
    sf::Sound son_tir;

    sf::SoundBuffer buffer_reload;
    assert(buffer_reload.loadFromFile("data/music/ARME/RELOAD/KALASH_RELOAD_(1).ogg"));
    sf::Sound son_reload;

    sf::SoundBuffer buffer_impactPerso;
    assert(buffer_impactPerso.loadFromFile("data/music/ARME/IMPACT_PERSO/IMPACT_PERSO_(1).ogg"));
    sf::Sound son_impactPerso;

    sf::SoundBuffer buffer_impactEnnemi;
    assert(buffer_impactEnnemi.loadFromFile("data/music/ARME/IMPACT_ENNEMI/IMPACT_ENNEMI_(1).ogg"));
    sf::Sound son_impactEnnemi;

    sf::SoundBuffer buffer_impactBois;
    assert(buffer_impactBois.loadFromFile("data/music/ARME/IMPACT_BOIS/IMPACT_BOIS_(1).ogg"));
    sf::Sound son_impactBois;

    sf::SoundBuffer buffer_douille1;
    assert(buffer_douille1.loadFromFile("data/music/ARME/DOUILLE/KALASH_DOUILLE_(1).ogg"));
    sf::SoundBuffer buffer_douille2;
    assert(buffer_douille2.loadFromFile("data/music/ARME/DOUILLE/KALASH_DOUILLE_(2).ogg"));
    sf::SoundBuffer buffer_douille3;
    assert(buffer_douille3.loadFromFile("data/music/ARME/DOUILLE/KALASH_DOUILLE_(3).ogg"));
    sf::SoundBuffer buffer_douille4;
    assert(buffer_douille4.loadFromFile("data/music/ARME/DOUILLE/KALASH_DOUILLE_(4).ogg"));
    sf::Sound son_douille;

    int nbEnnemis = 5;
    int tailleX = 12;
    int tailleY = 12;

    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                backgroundMusic.stop();
                return -1;
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) {
                    m_viewSave.x = m_joueurSFML.m_perso.getPosition().x*TAILLE_CASE;
                    m_viewSave.y = m_joueurSFML.m_perso.getPosition().y*TAILLE_CASE;
                    view.setCenter(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
                    backgroundMusic.pause();
                    return 2;
                }
                if (event.key.code == sf::Keyboard::F) {
                    if (ennemi_freeze) ennemi_freeze = false;
                    else ennemi_freeze = true;
                }
            }

            
        }


        //joue les son de la mort du perso
        if(m_joueurSFML.m_perso.getMort() && !tgcm) {
            iteration = 0;
            nbEnnemis = 5;
            tailleX = 12;
            tailleY = 12;
            genererNiveau (nbEnnemis, tailleX, tailleY);
            view.setCenter(m_viewSave);
            son_mortPerso.setBuffer(buffer_mortPerso);
            son_mortPerso.play();
            backgroundMusic.stop();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            return 3;
        }

        if( m_ennemis.size() == 0 ){
            nbEnnemis += rand() % 2;
            tailleX += rand() % 3;
            tailleY = tailleX;
            genererNiveau (nbEnnemis, tailleX, tailleY);
            view.setCenter(m_viewSave);
            viewMinimap.setSize(sf::Vector2f(m_terSFML.m_ter.getLargeur()*100, m_terSFML.m_ter.getHauteur()*100));
            viewMinimap.setCenter(sf::Vector2f(m_terSFML.m_ter.getLargeur()*100/2, m_terSFML.m_ter.getLargeur()*100/2));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            iteration = 0;
        }



        Vect2D vecteurDeplacement(0, 0);
        ProjectileSFML projectile;


        //gestion des input clavier


        //tgcm
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            tgcm = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            tgcm = false;
        }
	    
        //faire freeze les ennemis 
        

        //rechargement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            m_joueurSFML.recharger();

            m_nbMunitions.m_texte.setString("Rechargement...");
            son_reload.setBuffer(buffer_reload);
            son_reload.play();
        }

        //deplacement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            vecteurDeplacement.y +=-5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            vecteurDeplacement.x +=-5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            vecteurDeplacement.y +=5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            vecteurDeplacement.x +=5;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
            sf::Vector2i coordSouris = sf::Mouse::getPosition(window);
            sf::Vector2f coordSourisMonde = window.mapPixelToCoords(coordSouris);
            sf::Vector2f coordPerso = m_joueurSFML.getSprite().getPosition();

            Vect2D vectTir(coordSourisMonde.x - coordPerso.x, coordSourisMonde.y - coordPerso.y);
            vectTir.normaliser();

            bool tireVraiment = m_joueurSFML.tirer(vectTir, projectile);
            if(tireVraiment){
                //Recul perso :
                Vect2D reculView(vectTir.x*-5*0.01, vectTir.y*-5*0.01);
                deplacementView(view, reculView);
                vecteurDeplacement.x += vectTir.x*-5;
                vecteurDeplacement.y += vectTir.y*-5;

                int nbBalles = m_joueurSFML.getNbBalleRestante();
                if(nbBalles != 0) {
                    m_nbMunitions.m_texte.setString("Munitions : " + std::to_string(nbBalles));
                } else {
                    m_nbMunitions.m_texte.setString("Rechargement...");
                    son_reload.setBuffer(buffer_reload);
                    son_reload.play();
                }

                //son tir
                int rand_tir = rand()%2+1;
                if (rand_tir==1) {
                    son_tir.setBuffer(buffer_tir1);
                }
                else {
                    son_tir.setBuffer(buffer_tir2);
                }
                son_tir.play();
                
                //son douille
                int rand_douille = rand()%4 + 1;
                switch(rand_douille) {
                case 1 :
                    son_douille.setBuffer(buffer_douille1);
                    break;
                case 2 :
                    son_douille.setBuffer(buffer_douille2);
                    break;
                case 3 :
                    son_douille.setBuffer(buffer_douille3);
                    break;
                case 4 :
                    son_douille.setBuffer(buffer_douille4);
                    break;
                default : 
                    break;
                }
                son_douille.play();
            }    
        }
        
        //déplacement perso
        if(! vecteurDeplacement.estNul()){
            vecteurDeplacement.normaliser();

            vecteurDeplacement = m_terSFML.m_ter.collisionTerrain( 
                m_joueurSFML.m_perso.getHitbox(), 
                m_joueurSFML.m_perso.detecterCollision(vecteurDeplacement),
                vecteurDeplacement
            );

            m_joueurSFML.deplacement(vecteurDeplacement);
            if(decompte_fsPerso-1 <= 0) {
                decompte_fsPerso = delai_fsPerso;
                int rand_fsPerso = rand()%3+1;
                switch (rand_fsPerso) {
                case 1 :
                    son_footstepPerso.setBuffer(buffer_footstepPerso1);
                    break;
                case 2 :
                    son_footstepPerso.setBuffer(buffer_footstepPerso2);
                    break;
                case 3 :
                    son_footstepPerso.setBuffer(buffer_footstepPerso3);
                    break;
                default : 
                    break;
                }
                son_footstepPerso.play();
            } else decompte_fsPerso--;
            

            deplacementView(view, vecteurDeplacement);
        }


        //déplacement ennemis
        

        positionJoueur = m_joueurSFML.m_perso.getPosition();
        for (int i = 0; i < (int)m_ennemis.size(); i++){
            Vect2D direction (0,0);
            if (iteration%20 == i){
                positionEnnemi = m_ennemis[i].m_ennemi.getPosition();
                m_pathfinding.setArriveeDepart(positionEnnemi, positionJoueur);
                c.clear();
                c = m_pathfinding.trouveChemin();
                if (c.size()!=0){
                    m_ennemis[i].setCheminJoueur(c);
                }
            }
            if (m_ennemis[i].estAggro()) {
                //on regarde si l'ennemi voit le perso
                if (!m_terSFML.m_ter.droiteEstDansMur(m_joueurSFML.m_perso.getHitbox().getChg(), m_ennemis[i].m_ennemi.getHitbox().getChg())
                    && !m_terSFML.m_ter.droiteEstDansMur(m_joueurSFML.m_perso.getHitbox().getChd(), m_ennemis[i].m_ennemi.getHitbox().getChd())
                    && !m_terSFML.m_ter.droiteEstDansMur(m_joueurSFML.m_perso.getHitbox().getCbg(), m_ennemis[i].m_ennemi.getHitbox().getCbg())
                    && !m_terSFML.m_ter.droiteEstDansMur(m_joueurSFML.m_perso.getHitbox().getCbd(), m_ennemis[i].m_ennemi.getHitbox().getCbd())
                    ){ 
                    
                    if (iteration > 50) m_ennemis[i].tirEnnemi(positionJoueur, projectile);
                } else if (!ennemi_freeze) direction = m_ennemis[i].cheminDeplacement();
            }
            else if (!ennemi_freeze){
                direction = m_ennemis[i].patrouilleDeplacement();
                
            }
        
            
            if (m_ennemis[i].m_ennemi.estDansChampVision(positionJoueur)
            &&!m_terSFML.m_ter.droiteEstDansMur(positionJoueur, m_ennemis[i].getPosition())){
                m_ennemis[i].setAggro(true);
            }

            //collision avec le terrain
            direction = m_terSFML.m_ter.collisionTerrain( 
                m_ennemis[i].m_ennemi.getHitbox(), 
                m_ennemis[i].m_ennemi.detecterCollision(direction),
                direction);

            bool toucheEnnemi = false;

            //collision entre ennemi
            /*for (int j = 0; j < (int)m_ennemis.size(); j++){
                if(i != j && m_ennemis[i].m_ennemi.estEnContact(m_ennemis[j].m_ennemi.getHitbox())){
                    toucheEnnemi = true;
                }
            }*/

            if(! toucheEnnemi) m_ennemis[i].deplacement(direction);
            

            /*if(decompte_fsEnnemi-1 <= 0) {
                decompte_fsEnnemi = delai_fsEnnemi;
                son_footstepEnnemi.setBuffer(buffer_footstepEnnemi3);
                son_footstepEnnemi.play();
            } else decompte_fsEnnemi--;*/
        
        }

        actionsAutoSFML(buffer_impactBois, son_impactBois, buffer_degatEnnemi, son_degatEnnemi, buffer_mortEnnemi, son_mortEnnemi);
        iteration++;
        
        m_joueurSFML.ajusterSrpite();

        suitSouris(window);


        if(tgcm){
            m_joueurSFML.m_perso.setVivant();
        }
        
        affichage(window, view, viewMinimap, viewNbBalles, tgcm);
    }
}