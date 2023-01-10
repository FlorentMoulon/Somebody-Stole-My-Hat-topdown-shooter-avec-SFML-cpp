#ifndef Item_H
#define Item_H

#include <iostream>
#include "Projectile.h"
#include "Perso.h"

/**
 * @brief Gère les objet que peut ramasser le perso
 * 
 */
class Item{
    public :

    /**
     * @brief Constructeur par défaut d'Item
     * 
     */
    Item();

    /**
     * @brief Créer un Item avec un nom donné
     * 
     * @param nom std::string : nom de l'item
     * @param estRamassable bool : défini si l'item est ramassable
     */
    Item(std::string nom, bool estRamassable);

    /**
     * @brief Destructeur d'Item
     * 
     */
    ~Item();
    

    protected :
    std::string m_nom;
    bool m_estRamassable;

};

#endif 