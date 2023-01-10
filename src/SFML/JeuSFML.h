#ifndef JeuSFML_H
#define JeuSFML_H

#include "EcranBase.h"
#include "TerrainSFML.h"
#include "PersoSFML.h"
#include "EnnemiSFML.h"
#include "Chemin.h"
#include "Bouton.h"

#include <vector>

/**
 * @brief (hérite de la classe EcranBase) Permet de gérer le jeu avec SFML
 * 
 */
class JeuSFML : public EcranBase {
    public :

    /**
     * @brief Constructeur par défaut de JeuSFML
     * 
     */
    JeuSFML();

    /**
     * @brief Destructeur par défaut de JeuSFML
     * 
     */
    ~JeuSFML();


    /**
     * @brief Renvoie l'image correspondant au terrain du jeu
     * 
     * @return sf::Image : image du terrain du jeu
     */
    sf::Image getImTer();


    /**
     * @brief Permet de générer un niveau à partir de dimensions, et d'y placer des ennemis
     * 
     * @param nbEnnemi int : nombre d'ennemis dans le niveau
     * @param dimTerX int : dimension en largeur du terrain
     * @param dimTerY int : dimension en longueur du terrain
     */
    void genererNiveau(int nbEnnemi, int dimTerX, int dimTerY);


    /**
     * @brief Permet d'afficher des informations dans le temrinal, pour débugger
     * 
     */
    void test();
    

    /**
     * @brief Initialise le JeuSFML en initialisant les données membres du jeuSFML
     * 
     */
    void init();

    
    /**
     * @brief Permet d'afficher tous les sprites (ennemis, personnage, balles) dans la fenêtre grâce aux views
     * 
     * @param window RenderWindow : fenêtre dans laquelle on affiche nos sprites
     * @param view View : vue porincipale qui correspond au jeu
     * @param viewMinimap View : vue secondaire qui contient la mini-map
     * @param viewNbBalles View : vue secondaire qui contient le nombre de balles
     */
    void affichage(sf::RenderWindow & window, sf::View view, sf::View viewMinimap, sf::View viewNbBalles, bool tgcm);

    /**
     * @brief Permet d'orienter le personnage pour qu'il suive le pointeur de la souris
     * 
     * @param window RenderWindow : fenêtre dans laquelle on orient le personnage
     */
    void suitSouris (const sf::RenderWindow & window);

    /**
     * @brief Permet d'orienter un ennemi pour qu'il s'oriente corectement
     * 
     * @param window RenderWindow : fenêtre dans laquelle on orient l'ennemi
     */
    void orienterEnnemi (EnnemiSFML & ennemi, const sf::RenderWindow & window);

    /**
     * @brief Actions automatiques de JeuSFML (déplacement des ennemis, gestion des projectiles)
     * 
     * @param buffer_impactBois SoundBuffer : buffer pour le son d'impact sur le bois
     * @param son_impactBois Sound : son pour l'impact sur le bois
     * @param buffer_degatEnnemi SoundBuffer : buffer pour le son de dégat des ennemis
     * @param son_degatEnnemi Sound : son pour le dégat des ennemis
     * @param buffer_mortEnnemi SoundBuffer : buffer pour le son de mort des ennemis
     * @param son_mortEnnemi Sound : son pour la mort des ennemis
     */
    void actionsAutoSFML(const sf::SoundBuffer & buffer_impactBois, sf::Sound & son_impactBois, 
                         const sf::SoundBuffer & buffer_degatEnnemi, sf::Sound & son_degatEnnemi,
                         const sf::SoundBuffer & buffer_mortEnnemi, sf::Sound & son_mortEnnemi);

    /**
     * @brief Boucle principale du jeu
     * 
     * @param window RenderWindow : fenêtre dans laquelle on affiche le jeu
     * @param view View : vue utilisée pour afficher le jeu
     * @return int 
     */
    virtual int boucle(sf::RenderWindow & window, sf::View & view);

    /**
     * @brief Permet d'ajouter un ennemi au jeu
     * 
     * @param ennemi EnnemiSFML : ennemi à ajouter au jeu
     */
    void ajouterEnnemi(const EnnemiSFML & ennemi);

    /**
     * @brief Gère le déplacement de la vue lorsque l'on déplace le personnage
     * 
     * @param view View : vue que l'on déplace
     * @param vectDeplacement Vect2D : vecteur de déplacement du personnage
     */
    void deplacementView(sf::View & view, const Vect2D & vectDeplacement);


    /**
     * @brief Permet d'ajouter un ennemi au jeu
     * 
     * @param ennemi Ennemi : ennemi à ajouter au jeu
     */
    void ajouterEnnemi(const Ennemi & ennemi);
    
    /**
     * @brief Permet de supprimer le i-ème ennemi du jeu
     * 
     * @param i int : indice de l'ennemi que l'on veut supprimer
     */
    void supprimerEnnemi(int i);

    bool departValide(const Point2D & pt);

    sf::Vector2f m_viewSave;
    Bouton m_nbMunitions;


    private :

    void gestionBalles(const sf::SoundBuffer & buffer_impactBois, sf::Sound & son_impactBois,
                       const sf::SoundBuffer & buffer_degatEnnemi, sf::Sound & son_degatEnnemi);

    int placeJoueur();
    void placeEnnemi(int pieceJoueur);
    Point2D definitCoordValide(int numPiece);

    void affichageCollision(sf::RenderWindow & window);

    void finNiveau();
    void gestionMortEnnemis(const sf::SoundBuffer & buffer_mortEnnemi, sf::Sound & son_mortEnnemi);



    TerrainSFML m_terSFML;
    //Terrain m_terVision
    Chemin m_pathfinding;
    PersoSFML m_joueurSFML;
    std::vector <EnnemiSFML> m_ennemis;

    EnnemiSFML m_ennemiType;

    sf::Texture m_textureFond;
    sf::Sprite m_spriteFond;
};



#endif