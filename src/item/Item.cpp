#include "Item.h"
#include <iostream>

Item::Item(){

}

Item::Item(std::string nom, bool estRamassable) : m_nom(nom), m_estRamassable(estRamassable){

}

Item::~Item(){

}
    