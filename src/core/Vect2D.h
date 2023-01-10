#ifndef Vect2D_H
#define Vect2D_H

#include <iostream>

/**
 * @brief Vecteur dans un espace en 2 dimensions
 * 
 */
struct Vect2D{

    /**
     * @brief float : ordonné du vecteur
     * 
     */
    float x;

    /**
     * @brief float : abscisse du vecteur
     * 
     */
    float y;


    /**
     * @brief Créer un vecteur avec un ordonné et une abscisse donnés
     * 
     * @param X float : ordonné du vecteur
     * @param Y float : abscisse du vecteur
     */
    Vect2D(float X=0, float Y=0);

    /**
     * @brief Constructeur par copie de Vect2D
     * 
     * @param v Vect2D : vecteur à copier
     */
    Vect2D(const Vect2D &v);


    /**
     * @brief Modifie l'ordonné et l'abscisse du vecteur
     * 
     * @param X float : ordonné du vecteur
     * @param Y float : abscisse du vecteur
     */
    void set(float X, float Y);

    /**
     * @brief Normalise le vecteur, c'est à dire ramène sa nomre à 1
     * 
     */
    void normaliser();

    /**
     * @brief Tourne le vecteur d'un angle données
     * 
     * @param angle float : angle selon lequel il faut tourner le vecteur, compris entre -180 et 180
     */
    void rotation (float angle);
    

    /**
     * @brief Vérifie si le vecteur est nul, c'est à dire x=y=0
     * 
     * @return true : si le vecteur est nul
     * @return false : si le vecteur n'est pas nul
     */
    bool estNul()const;

    /**
     * @brief Retourne la norme du vecteur
     * 
     * @return float : norme du vecteur
     */
    float norme();

    /**
     * @brief Fait le produit scalaire (usuel sur R^2) de deux vecteurs
     * 
     * @param v Vect2D : 2eme vecteur du produit scalaire 
     * @return float : résultat du produit scalaire des deux vecteurs
     */
    float scalaire(const Vect2D & v);

    /**
     * @brief Retourne l'angle entre deux vecteurs
     * 
     * @param v  Vect2D : vecteur à comparer
     * @return float : angle entre les deux vecteurs
     */
    float angle (Vect2D & v);

    /**
     * @brief Soustrait deux Vect2D
     * 
     * @param pt Vect2D : vecteur à soustraire
     * @return Vect2D : vecteur soustraction des deux autres
     */
    Vect2D operator-(const Vect2D& v) ;

    /**
     * @brief Copie un Vect2D
     * 
     * @param v Vect2D : vecteur à copier
     * @return Vect2D& : le vecteur copié
     */
    Vect2D &operator=(const Vect2D &v);

    /**
     * @brief Affiche le vecteur
     * 
     */
    void afficher();

    /**
     * @brief Affiche le vecteur
     * 
	 * @param o std::ostream : flux
	 * @param v Vect2D : vecteur à afficher
	 * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Vect2D & v);
    
};

#endif 