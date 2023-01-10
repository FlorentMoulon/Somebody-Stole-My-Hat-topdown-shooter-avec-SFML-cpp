#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "iostream"

#include "Piece.h"
#include "Meuble.h"
#include "Porte.h"
#include "Point2D.h"
#include "Case.h"
#include "Vect2D.h"
#include "HitboxRectangle.h"


/**
 * @brief odélise un terrain avec des pieces entouré de mur, relier par des portes et rempli de meuble
 * 
 */
class Terrain
{
    public:


    /**
     * @brief Constructeur par défaut, créer un terrain vide de dimension 0 par 0
     * 
     */
    Terrain();

    /**
     * @brief Créer un terrain vide de dimension hauteur*largeur
     * 
     * @param hauteur unsigned int : hauteur du terrain (avec les murs)
     * @param largeur unsigned int : largeur du terrain (avec les murs)
     */
    Terrain(unsigned int hauteur, unsigned int largeur);

    /**
     * @brief Destructeur de Terrain
     * 
     */
    ~Terrain();


    /**
     * @brief Vérifi si une zone du terrain est vide
     * 
     * @param chg Point2D : Coin haut gauche de la zone à tester
     * @param cbd Point2D : Coin bas droit de la zone à tester
     * @return true si la zone testée est vide
     * @return false si la zone testée n'est pas vide
     */
    bool zoneEstVide(Point2D const & chg, Point2D const & cbd) const;

    /**
     * @brief Vérifi si une zone du terrain est un mur
     * 
     * @param chg Point2D : Coin haut gauche de la zone à tester
     * @param cbd Point2D : Coin bas droit de la zone à tester
     * @return true si la zone testée est entièrement rempli de mur
     * @return false si la zone testée n'est pas entièrement rempli de mur
     */
    bool zoneMur(Point2D const & chg, Point2D const & cbd) const;

    /**
     * @brief Vérifi si une case est vide
     * 
     * @param y unsigned int : abscisse de la case à tester
     * @param x unsigned int : ordonné de la case à tester
     * @return true si la case testée est vide
     * @return false si la case testée n'est pas vide
     */
    bool caseEstVide(unsigned int y, unsigned int x) const;

    /**
     * @brief Retrouve une porte d'une piece donnée
     * 
     * @param NoPiece Int : numéro de la piece
     * @return Point2D : les coordonnés d'une porte de la piece
     */
    Point2D retrouvePorte(int NoPiece);

    /**
     * @brief Affiche le terrain
     * 
     * @param o std::ostream : flux
     * @param t Terrain : terrain
     * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Terrain & t);

    /**
     * @brief Genere les murs, pieces, portes, et meubles du terrain
     * 
     */
    void generer();
    
    /**
     * @brief Vide le terrain, supprime tous les murs, pieces, portes, et meubles du terrain
     * 
     */
    void vider();

    /**
     * @brief Trouve une case vide du terrain
     * 
     * @return Point2D : une case vide du terrain
     */
    Point2D caseLibrePourDebuter() const;


    /**
     * @brief Vérifie si une hitbox est dans un mur ou un meuble
     * 
     * @param hitbox Hitbox : la hitbox à tester
     * @return true si la hitbox est dans un mur ou un meuble
     * @return false si la hitbox est dans une zone libre
     */
    bool hitboxEstDansMur(const HitboxRectangle & hitbox) const;

    /**
     * @brief Trouve le bon deplacement à faire pour ne pas rentrer des les murs, mais juste venir si coller
     * 
     * @param hitbox HitboxRectangle : la hitbox de l'objet à déplacer
     * @param hitboxVirtuelle HitboxRectangle : la hitbox virtuelle (prévusualisation du déplacement) de l'objet à déplacer
     * @param direction Vect2D : direction du deplacement
     * @return Vect2D : un vecteur qui permet de coller la hitbox au mur à la place de rentrer dedans
     */
    Vect2D collisionTerrain(const HitboxRectangle & hitbox, HitboxRectangle hitboxVirtuelle, const Vect2D & direction) const;
    
    /**
     * @brief Verifi si une droite passe par un mur ou un meuble
     * 
     * @param pt1 Point2D : un point de la droite
     * @param pt2 Point2D : un point de la droite différent du pt1
     * @return true si la droite passe par un mur ou un meuble
     * @return false si la droite ne passe pas par un mur ou un meuble (le chemin est libre)
     */
    bool droiteEstDansMur(const Point2D & pt1, const Point2D & pt2) const;


    /**
     * @brief Renvoie la hauteur du terrain
     * 
     * @return unsigned int : la hauteur 
     */
    unsigned int getHauteur() const;

    /**
     * @brief Renvoie la largeur du terrain
     * 
     * @return unsigned int : la largeur 
     */
    unsigned int getLargeur() const;

    /**
     * @brief Renvoie le type d'une case du terrain
     * 
     * @param y unsigned int : abscisse de la case à tester
     * @param x unsigned int : ordonné de la case à tester
     * @return char : le type de la case de coordonné (x,y), i.e terrain[y][x]
     */
    char getYX (const unsigned int y, const unsigned int x) const;

    /**
     * @brief Renvoie le nombre de meuble sur le terrain
     * 
     * @return unsigned int : le nombre de meuble sur le terrain
     */
    unsigned int getNbMeuble() const;

    /**
     * @brief Renvoie le Ieme Meuble du terrain
     * 
     * @param i Int : indice du meuble
     * @return Meuble : le Ieme Meuble du terrain
     */
    Meuble getIemeMeuble(int i) const;

    /**
     * @brief Renvoie le nombre de piece du terrain
     * 
     * @return unsigned int : le nombre de piece du terrain
     */
    unsigned int getNbPiece() const;

    /**
     * @brief Renvoie la Ieme piece du terrain
     * 
     * @param i Int : indice de la piece
     * @return Piece : la Ieme piece du terrain
     */
    Piece getIemePiece(int i) const;

    /**
     * @brief Renvoie le nombre de porte du terrain
     * 
     * @return unsigned int : le nombre de porte du terrain
     */
    unsigned int getNbPorte() const;

    /**
     * @brief Renvoie la Ieme porte du terrain
     * 
     * @param i Int : indice de la porte
     * @return Porte : la Ieme porte du terrain
     */
    Porte getIemePorte(int i) const;


    /**
     * @brief Tableau dynamique de case de dimansion hauteur*largeur, modélisant le terrain
     * 
     */
    std::vector< std::vector< Case > > m_matrice;



    private:

    unsigned int m_nbMeuble;
    std::vector< Meuble > m_meubles;
    unsigned int m_nbPiece;
    std::vector< Piece > m_pieces;
    unsigned int m_nbPorte;
    std::vector< Porte > m_portes;

    unsigned int m_hauteur;
    unsigned int m_largeur;

    unsigned int m_hauteurPieceMax;
    unsigned int m_hauteurPieceMin;
    unsigned int m_largeurPieceMax;
    unsigned int m_largeurPieceMin;
    unsigned int m_probaDiv;



    bool porteAutour(Point2D const & chg, Point2D const & cbd) const;
    void corrigerPorteVerticale(Porte const & porte);
    void corrigerPorteHorizontale(Porte const & porte);
    void corrigerPortes();
    void remplaceCase(char ancien, char nouveau);

    void diviser(Point2D const & pieceChg, Point2D const & pieceCbd, unsigned int probaDiv);

    bool meubleEstDans(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd) const;
    void ajouterMeubleAuMur(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd);
    void ajouterMeubleAuCentre(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd);
    void ajouterMeubleAuCentreGrand(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd);
    void dessinerMeuble(Meuble const & meuble);

    void remplirPieces();
    void remplirPieceChambre(Point2D const & pieceChg, Point2D const & pieceCbd);
    void remplirPieceDortoir(Point2D const & pieceChg, Point2D const & pieceCbd);
    void remplirPieceStockage(Point2D const & pieceChg, Point2D const & pieceCbd);
    void remplirPieceBureau(Point2D const & pieceChg, Point2D const & pieceCbd);
    void remplirPiecePrincipale(Point2D const & pieceChg, Point2D const & pieceCbd);
    void remplirPieceDEau(Point2D const & pieceChg, Point2D const & pieceCbd);

    void ajouterPiece(Point2D const & pieceChg, Point2D const & pieceCbd);
};

#endif // TERRAIN_H