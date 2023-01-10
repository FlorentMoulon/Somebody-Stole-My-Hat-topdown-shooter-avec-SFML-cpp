#ifndef _JEU_H
#define _JEU_H

#include <vector>
#include "Perso.h"
#include "Ennemi.h"
#include "Terrain.h"
#include "Projectile.h"

/**
 * @brief Gère tous les éléments interactif d'un niveau du jeu en mode texte
 * 
 */
class Jeu {


    public :

    /**
     * @brief Constructeur par défaut de Jeu
     * 
     */
    Jeu ();

    /**
     * @brief Retourne le terrain du niveau
     * 
     * @return Terrain& : terrain du niveau
     */
    Terrain& getTerrain ();

    /**
     * @brief Retourne le perso du niveau
     * 
     * @return Perso& : perso du niveau
     */
    Perso& getPerso ();

    /**
     * @brief Retourne le terrain du niveau
     * 
     * @return const Terrain& : terrain du niveau
     */
    const Terrain& getConstTerrain () const;

    /**
     * @brief Retourne le perso du niveau
     * 
     * @return const Perso& : perso du niveau
     */
    const Perso& getConstPerso () const;

    /**
     * @brief Retourne l'Iemme ennemi du niveau
     * 
     * @param i int : indice de l'ennemi à retourner
     * @return const Ennemi& : Iemme ennemi du niveau
     */
    const Ennemi& getConstIemeEnnemi (int i) const;

    /**
     * @brief Retourne le nombre d'ennemi
     * 
     * @return int : nombre d'ennemi
     */
    int getNbEnnemi() const;

    /**
     * @brief Gère les actions clavier
     * 
     */
    void actionsAutomatiques ();

    /**
     * @brief Gère les actions clavier
     * 
     * @param touche char : touvhe utiliseé par l'utilisateur
     */
    void actionClavier(const char touche);

    /**
     * @brief Génère le terrain du niveau
     * 
     */
    void genererTerrain();

    /**
     * @brief Fait tirer le joueur
     * 
     * @param direction Vect2D : direction du tir
     */
    void joueurTirer(const Vect2D & direction);

    private :

	Terrain terrain;
	Perso perso;
    std::vector<Ennemi> ennemis;
    int nbEnnemi;

    void gestionDesBalles();
};

#endif
