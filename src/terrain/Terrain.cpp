#include "Terrain.h"
#include "math.h"
#include "cassert"
#include <vector>



/**
 * @brief Ramène la taille des piece dans un intervalle résonable
 * 
 * @param taille int : taille à limiter
 * @return int : taille un fois réduite
 */
int limiteur(int taille){
    int tailleLimite = 7;

    if (taille<4){
        return 4;
    }
    else if(taille < tailleLimite){
        return taille;
    }else{
        return tailleLimite + log(taille - tailleLimite);
    }
}











Terrain::Terrain() : m_nbMeuble(0), m_nbPiece(0), m_hauteur(0), m_largeur(0), m_hauteurPieceMax(0), m_hauteurPieceMin(0),
m_largeurPieceMax(0), m_largeurPieceMin(0), m_probaDiv(0)
{

}

Terrain::Terrain(unsigned int hauteur, unsigned int largeur) : m_nbMeuble(0), m_nbPiece(0), m_hauteur(hauteur), m_largeur(largeur),
m_hauteurPieceMax(limiteur(hauteur/2.5)), m_hauteurPieceMin(limiteur(hauteur/6)), m_largeurPieceMax(limiteur(largeur/2.5)),
m_largeurPieceMin(limiteur(largeur/6)), m_probaDiv((largeur+hauteur)/0.2)
{
    Case c;
    for (unsigned int i=0; i<m_hauteur; i++){
        std::vector <Case> tabTemp;
        for (unsigned int j=0; j<m_largeur; j++){
            if(i==0 || j==0 || i==m_hauteur-1 || j==m_largeur-1){
                c.type='X';
            }else{
                c.type=' ';
            }
            tabTemp.push_back(c);
        }
        m_matrice.push_back(tabTemp);
    }
}


Terrain::~Terrain()
{
    vider();
}









std::ostream& operator<<(std::ostream& o, const Terrain & t){
    for (unsigned int i=0; i<t.m_hauteur; i++){
        for (unsigned int j=0; j<t.m_largeur; j++){
            o<<t.m_matrice[i][j].type<<" ";
        }o<<std::endl;
    }o<<std::endl;

    return o;
}


void Terrain::vider(){
    for (unsigned int i=0; i<m_hauteur; i++){
        for (unsigned int j=0; j<m_largeur; j++){
            if(i==0 || j==0 || i==m_hauteur-1 || j==m_largeur-1){
                m_matrice[i][j].type='X';
            }else{
                m_matrice[i][j].type=' ';
            }
        }
    }

    m_nbMeuble=0;
    m_meubles.clear();
    m_nbPiece=0;
    m_pieces.clear();
    m_nbPorte = 0;
    m_portes.clear();
}

void Terrain::remplaceCase(char ancien, char nouveau){
    for (unsigned int i=0; i<m_hauteur; i++){
        for (unsigned int j=0; j<m_largeur; j++){
            if(m_matrice[i][j].type == ancien)
            m_matrice[i][j].type = nouveau;
        }
    }
}







bool Terrain::caseEstVide(unsigned int y, unsigned int x) const{
    assert(x >= 0);
    assert(y >= 0);
    assert(x <= m_largeur-1);
    assert(y <= m_hauteur-1);

    return (m_matrice[y][x].type == ' ' || m_matrice[y][x].type == '-');
}


Point2D Terrain::retrouvePorte(int NoPiece){
    Point2D coord(m_pieces[NoPiece].getChg());
    int largeur = m_pieces[NoPiece].getLargeur();
    int hauteur = m_pieces[NoPiece].getHauteur();
    coord.x -= 1;
    coord.y -= 1;
    for (int i = 0; i <= largeur; i++){
        if (m_matrice[coord.y][coord.x].type=='-') return coord;
        coord.x += 1;
    }
    for (int j = 0; j <= hauteur; j++){
        if (m_matrice[coord.y][coord.x].type=='-') return coord;
        coord.y += 1;
    }
    for (int i = 0; i <= largeur; i++){
        if (m_matrice[coord.y][coord.x].type=='-') return coord;
        coord.x -= 1;
    }
    for (int j = 0; j <= hauteur; j++){
        if (m_matrice[coord.y][coord.x].type=='-') return coord;
        coord.y -= 1;
    }

    return coord;
}



bool Terrain::zoneEstVide(Point2D const & chg, Point2D const & cbd) const{
    assert(cbd.x >= 0);
    assert(cbd.y >= 0);
    assert(chg.x >= 0);
    assert(chg.y >= 0);
    assert(cbd.x <= m_largeur-1);
    assert(cbd.y <= m_hauteur-1);
    assert(chg.x <= m_largeur-1);
    assert(chg.y <= m_hauteur-1);

    for (int i=chg.x; i<=cbd.x; i++){
        for (int j=chg.y; j<=cbd.y; j++){
            if(m_matrice[j][i].type != ' '){
                return false;
            }
        }
    }

    return true;
}


bool Terrain::zoneMur(Point2D const & chg, Point2D const & cbd) const{
    assert(chg.x >= 0);
    assert(chg.y >= 0);
    assert(cbd.x <= m_largeur);
    assert(cbd.y <= m_hauteur);

    for (int i=chg.x; i<=cbd.x; i++){
        for (int j=chg.y; j<=cbd.y; j++){
            if(m_matrice[j][i].type != 'X' && m_matrice[j][i].type != '-'){
                return false;
            }
        }
    }

    return true;
}

bool Terrain::hitboxEstDansMur(HitboxRectangle const & hitbox) const{
    if(caseEstVide(floor(hitbox.getChg().y),floor(hitbox.getChg().x))
    && caseEstVide(floor(hitbox.getChd().y),floor(hitbox.getChd().x))
    && caseEstVide(floor(hitbox.getCbg().y),floor(hitbox.getCbg().x))
    && caseEstVide(floor(hitbox.getCbd().y),floor(hitbox.getCbd().x))
    )return false;

    else return true;
}

Vect2D Terrain::collisionTerrain(const HitboxRectangle & hitbox, HitboxRectangle hitboxVirtuelle, const Vect2D & direction) const{
    if(! direction.estNul()){
        while (hitboxEstDansMur(hitboxVirtuelle)){
            hitboxVirtuelle.setCentre(
                hitboxVirtuelle.getCentre().x - direction.x*0.05,
                hitboxVirtuelle.getCentre().y - direction.y*0.05
            );
        }
    }   
    
    Vect2D deplacement(
        hitboxVirtuelle.getCentre().x - hitbox.getCentre().x,
        hitboxVirtuelle.getCentre().y - hitbox.getCentre().y
    );

    return deplacement;
}


bool Terrain::droiteEstDansMur(const Point2D & pt1, const Point2D & pt2) const{
    float xmin, ymin, xmax, ymax, a, b, x, y;

    if(pt1.x <= pt2.x){
        xmin = pt1.x;
        xmax = pt2.x;
        a = (pt1.y - pt2.y)/(pt1.x - pt2.x);
        b = pt1.y - a*pt1.x;
    }else{
        xmin = pt2.x;
        xmax = pt1.x;
        a = (pt2.y - pt1.y)/(pt2.x - pt1.x);
        b = pt2.y - a*pt2.x;
    }

    for (float i=xmin; i<=xmax; i++){
        y = a*i+b;
        if(!caseEstVide(floor(y), floor(i))){
            return true;
        }
    }



    if(pt1.y <= pt2.y){
        ymin = pt1.y;
        ymax = pt2.y;
        a = (pt1.y - pt2.y)/(pt1.x - pt2.x);
        b = pt1.y - a*pt1.x;
    }else{
        ymin = pt2.y;
        ymax = pt1.y;
        a = (pt2.y - pt1.y)/(pt2.x - pt1.x);
        b = pt2.y - a*pt2.x;
    }

    for (float i=ymin; i<=ymax; i++){
        if(a == 0) x = 0;
        else x = (i-b)/a;
        if(!caseEstVide(floor(i), floor(x))){
            return true;
        }
    }

    return false;
}





unsigned int Terrain::getHauteur() const {
    return m_hauteur;
}

unsigned int Terrain::getLargeur() const {
    return m_largeur;
}

char Terrain::getYX (const unsigned int y, const unsigned int x) const {
	assert(x>=0);
	assert(y>=0);
	assert(x<m_largeur);
	assert(y<m_hauteur);
	return m_matrice[y][x].type;
}


unsigned int Terrain::getNbMeuble() const{
    return m_nbMeuble;
}

Meuble Terrain::getIemeMeuble(int i) const{
    assert(i >= 0);
    assert(i < (int)m_nbMeuble);
    return m_meubles[i];
}

unsigned int Terrain::getNbPiece() const{
    return m_nbPiece;
}

Piece Terrain::getIemePiece(int i) const{
    assert(i >= 0);
    assert(i < (int) m_nbPiece);
    return m_pieces[i];
}

unsigned int Terrain::getNbPorte() const{
    return m_nbPorte;
}

Porte Terrain::getIemePorte(int i) const{
    assert(i >= 0);
    assert(i < (int) m_nbPorte);
    return m_portes[i];
}







bool Terrain::porteAutour(Point2D const & chg, Point2D const & cbd) const{
    assert(chg.x > 0);
    assert(chg.y > 0);
    assert(cbd.x < m_largeur-1);
    assert(cbd.y < m_hauteur-1);

    for (int i=chg.x; i<=cbd.x; i++){
        if(m_matrice[chg.y-1][i].type == '-'){
            return true;
        }
        if(m_matrice[cbd.y+1][i].type == '-'){
            return true;
        }
    }
    for (int j=chg.y; j<=cbd.y; j++){
        if(m_matrice[j][chg.x-1].type == '-'){
            return true;
        }
        if(m_matrice[j][cbd.x+1].type == '-'){
            return true;
        }
    }

    return false;
}


Point2D Terrain::caseLibrePourDebuter() const{
    Point2D pt;
    int i = 0;
    int j = 0;
    while(!caseEstVide(m_hauteur-2 +i, m_largeur/2 +j)){
        i = rand()%5;
        j = rand()%5;
    }

    pt.set(m_largeur/2, m_hauteur-2);
    return pt;
}
















void Terrain::generer(){
    vider();
    Point2D chg(1,1);
    Point2D cbd(m_largeur-2,m_hauteur-2);

    diviser(chg,cbd,m_probaDiv);
    corrigerPortes();
    remplirPieces();

    remplaceCase('.', ' ');
}



void Terrain::corrigerPorteVerticale(Porte const & porte){
    assert(porte.x > 0);
    assert(porte.y > 0);
    assert(porte.x < (int) m_largeur - 1);
    assert(porte.y < (int) m_hauteur - 1);


    if (m_matrice[porte.y][porte.x-1].type == 'X'  ||   m_matrice[porte.y][porte.x+1].type == 'X'){ 
        //on regarde a gauche et à droite de la porte si elle est bloqué par un mur
        
        if(m_matrice[porte.y-2][porte.x-1].type == ' '  &&  m_matrice[porte.y-2][porte.x+1].type == ' '){
            //on regarde si on peut décalé la porte de 2 case en haut (si libre gauche et à droite)
            m_matrice[porte.y-2][porte.x].type = '-';
        }
        else if(m_matrice[porte.y-1][porte.x-1].type == ' '  &&  m_matrice[porte.y-1][porte.x+1].type == ' '){
            //on regarde si on peut décalé la porte de 1 case en haut (si libre en gauche et à droite) (normalement tjs possible)
            m_matrice[porte.y-1][porte.x].type = '-';
        }
        else{
            //problème
            std::cout<<std::endl<<"problème porte"<<std::endl;
        }



        if(m_matrice[porte.y+2][porte.x-1].type == ' '  &&  m_matrice[porte.y+2][porte.x+1].type == ' '){
            //on regarde si on peut décalé la porte de 2 case en bas (si libre gauche et à droite)
            m_matrice[porte.y+2][porte.x].type = '-';
        }
        else if(m_matrice[porte.y+1][porte.x-1].type == ' '  &&  m_matrice[porte.y+1][porte.x+1].type == ' '){
            //on regarde si on peut décalé la porte de 1 case en bas (si libre en gauche et à droite) (normalement tjs possible)
            m_matrice[porte.y+1][porte.x].type = '-';
        }
        else{
            //problème
            std::cout<<std::endl<<"problème porte"<<std::endl;
        }
    
        m_matrice[porte.y][porte.x].type = 'X'; //on enleve l'ancienne porte
    }
}


void Terrain::corrigerPorteHorizontale(Porte const & porte){
    assert(porte.x > 0);
    assert(porte.y > 0);
    assert(porte.x < (int) m_largeur - 1);
    assert(porte.y < (int) m_hauteur - 1);


    if (m_matrice[porte.y-1][porte.x].type == 'X'  ||   m_matrice[porte.y+1][porte.x].type == 'X'){ 
        //on regarde au dessus et en dessous de la porte si elle est bloqué par un mur
        
        if(m_matrice[porte.y-1][porte.x-2].type == ' '  &&  m_matrice[porte.y+1][porte.x-2].type == ' '){
            //on regarde si on peut décalé la porte de 2 case à gauche (si libre en dessus en dessous)
            m_matrice[porte.y][porte.x-2].type = '-';
        }
        else if(m_matrice[porte.y-1][porte.x-1].type == ' '  &&  m_matrice[porte.y+1][porte.x-1].type == ' '){
            //on regarde si on peut décalé la porte de 1 case à gauche (si libre en dessus en dessous) (normalement tjs possible)
            m_matrice[porte.y][porte.x-1].type = '-';
        }
        else{
            //problème
            std::cout<<std::endl<<"problème porte"<<std::endl;
        }



        if(m_matrice[porte.y-1][porte.x+2].type == ' '  &&  m_matrice[porte.y+1][porte.x+2].type == ' '){
            //on regarde si on peut décalé la porte de 2 case à droite (si libre en dessus en dessous)
            m_matrice[porte.y][porte.x+2].type = '-';
        }
        else if(m_matrice[porte.y-1][porte.x+1].type == ' '  &&  m_matrice[porte.y+1][porte.x+1].type == ' '){
            //on regarde si on peut décalé la porte de 1 case à droite (si libre en dessus en dessous) (normalement tjs possible)
            m_matrice[porte.y][porte.x+1].type = '-';
        }
        else{
            //problème
            std::cout<<std::endl<<"problème porte"<<std::endl;
        }
    
        m_matrice[porte.y][porte.x].type = 'X'; //on enleve l'ancienne porte
    }
}

void Terrain::corrigerPortes(){
    for (unsigned int i=0; i<m_nbPorte; i++){
        if(m_portes[i].orientation == 'v') corrigerPorteVerticale(m_portes[i]);
        else corrigerPorteHorizontale(m_portes[i]);
    }
}



void Terrain::dessinerMeuble(Meuble const & meuble){
    assert(meuble.getChg().x > 0);
    assert(meuble.getChg().y > 0);
    assert(meuble.getCbd().x < m_largeur-1);
    assert(meuble.getCbd().y < m_hauteur-1);

    for (int i=meuble.getChg().x-1; i<=meuble.getCbd().x+1; i++){
        for (int j=meuble.getChg().y-1; j<=meuble.getCbd().y+1; j++){
            if(m_matrice[j][i].type == ' ')m_matrice[j][i].type = '.';
        }
    }

    for (int i=meuble.getChg().x; i<=meuble.getCbd().x; i++){
        for (int j=meuble.getChg().y; j<=meuble.getCbd().y; j++){
            m_matrice[j][i].type = meuble.getType();
        }
    }
}


bool Terrain::meubleEstDans(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd) const{
    if (meuble.getChg().x >= pieceChg.x &&
    meuble.getChg().x <= pieceCbd.x &&
    meuble.getChg().y >= pieceChg.y &&
    meuble.getChg().y <= pieceCbd.y &&

    meuble.getCbd().x >= pieceChg.x &&
    meuble.getCbd().x <= pieceCbd.x &&
    meuble.getCbd().y >= pieceChg.y &&
    meuble.getCbd().y <= pieceCbd.y)
    {
        return true;
    }

    else{
        return false;
    }
}


void Terrain::ajouterMeubleAuMur(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;

    int nbEssai = 0;
    int nbEssaiMax = 100;


    do{
        nbEssai ++;
        meuble.tournerAleatoirement();

        switch(meuble.getDir()) {
            case 'h':
                meuble.setChg(
                    rand()%largeurPiece + pieceChg.x 
                    ,pieceChg.y );
                break;
            case 'b':
                meuble.setChg(
                    rand()%largeurPiece + pieceChg.x 
                    ,pieceCbd.y - meuble.getHauteur() + 1);;
                break;
            case 'd':
                meuble.setChg(
                    pieceCbd.x - meuble.getLargeur() + 1
                    ,rand()%hauteurPiece + pieceChg.y );
                break;
            case 'g':
                meuble.setChg(
                    pieceChg.x 
                    ,rand()%hauteurPiece + pieceChg.y );
                break;
            default:
                break;
        }
    }while((
        ! meubleEstDans(meuble, pieceChg, pieceCbd) ||
        ! zoneEstVide(meuble.getChg(),meuble.getCbd()) ||
        porteAutour(meuble.getChg(),meuble.getCbd())
    )
        && nbEssai < nbEssaiMax);

    if(nbEssai < nbEssaiMax){
        m_meubles.push_back(meuble);
        m_nbMeuble ++;
        dessinerMeuble(meuble);
    }
}


void Terrain::ajouterMeubleAuCentre(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    
    int nbEssaiMax = 50;
    int nbEssai = 0;

    if(largeurPiece-2 >= (int) meuble.getLargeur() && hauteurPiece-2 >= (int) meuble.getHauteur()){
        do{
            nbEssai ++;
            meuble.tournerAleatoirement();

            int largeurLibre = largeurPiece - meuble.getLargeur();
            if(largeurLibre <= 0) largeurLibre = 1;
            int hauteurLibre = hauteurPiece - meuble.getHauteur();
            if(hauteurLibre <= 0) hauteurLibre = 1;

            meuble.setChg(
                (pieceChg.x + ceil(largeurPiece/2) - meuble.getLargeur()) + 1 + rand()%(largeurLibre) - largeurLibre/2
                ,(pieceChg.y + ceil(hauteurPiece/2) - meuble.getHauteur()) + 1 + rand()%(hauteurLibre) - hauteurLibre/2);

        }while((
            ! meubleEstDans(meuble, pieceChg, pieceCbd) ||
            ! zoneEstVide(meuble.getChg(),meuble.getCbd()) || 
            porteAutour(meuble.getChg(),meuble.getCbd())
            )
            && nbEssai < nbEssaiMax);

        if(nbEssai < nbEssaiMax){
            m_meubles.push_back(meuble);
            m_nbMeuble ++;
            dessinerMeuble(meuble);
        }
    }
}

void Terrain::ajouterMeubleAuCentreGrand(Meuble & meuble, Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;

    int nbEssaiMax = 10;
    int nbEssai = 0;
    

    if(largeurPiece-2 >= (int) meuble.getLargeur() && hauteurPiece-2 >= (int) meuble.getHauteur()){
        do{
            nbEssai ++;
            meuble.tournerAleatoirement();

            int largeurLibre = largeurPiece - meuble.getLargeur();
            if(largeurLibre <= 0) largeurLibre = 1;
            int hauteurLibre = hauteurPiece - meuble.getHauteur();
            if(hauteurLibre <= 0) hauteurLibre = 1;

            meuble.setChg(
                (pieceChg.x + ceil(largeurPiece/2) - meuble.getLargeur()) + 1,
                (pieceChg.y + ceil(hauteurPiece/2) - meuble.getHauteur()) + 1);

        }while((
            ! meubleEstDans(meuble, pieceChg, pieceCbd) ||
            ! zoneEstVide(meuble.getChg(),meuble.getCbd()) || 
            porteAutour(meuble.getChg(),meuble.getCbd())
            )
            && nbEssai < nbEssaiMax);

        if(nbEssai < nbEssaiMax){
            m_meubles.push_back(meuble);
            m_nbMeuble ++;
            dessinerMeuble(meuble);
        }
    }
}


void Terrain::remplirPieceChambre(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble placard(2, 1, 'p', 0, 3);
    Meuble petitLit(1, 2, 'l', 6, 3);
    Meuble grandLit(2, 3, 'l', 0, 0);
    Meuble tableDeNuit(1, 1, 't', 28, 0);
    Meuble miroir(1, 1, 'm', 28, 0);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);


    if (nbMeublePiece >= 3){ //grand lit
        ajouterMeubleAuMur(grandLit,pieceChg,pieceCbd);
    }else{ //petit lit
        ajouterMeubleAuMur(petitLit,pieceChg,pieceCbd);
    }

    ajouterMeubleAuMur(tableDeNuit,pieceChg,pieceCbd);

    if (nbMeublePiece >= 4) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
    if (nbMeublePiece >= 5) ajouterMeubleAuMur(tableDeNuit,pieceChg,pieceCbd);
    if (nbMeublePiece >= 6) ajouterMeubleAuMur(miroir,pieceChg,pieceCbd);
}


void Terrain::remplirPieceDortoir(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble placard(2, 1, 'p', 0, 3);
    Meuble petitLit(1, 2, 'l', 6, 3);
    Meuble tableDeNuit(1, 1, 't', 28, 0);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);


    ajouterMeubleAuMur(petitLit,pieceChg,pieceCbd);
    ajouterMeubleAuMur(petitLit,pieceChg,pieceCbd);
    ajouterMeubleAuMur(tableDeNuit,pieceChg,pieceCbd);

    if (nbMeublePiece >= 4) ajouterMeubleAuMur(petitLit,pieceChg,pieceCbd);
    if (nbMeublePiece >= 5) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
    if (nbMeublePiece >= 6) ajouterMeubleAuMur(petitLit,pieceChg,pieceCbd);
}


void Terrain::remplirPieceStockage(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble placard(2, 1, 'p', 0, 3);
    Meuble etagere(2, 1, 'p', 0, 3);
    Meuble coffre(2, 1, 'c', 0, 3);
    Meuble caisse(1, 1, 'C', 28, 1);
    Meuble tonneau(1, 1, 'T', 28, 1);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);

    int r;

    for (int i=0; i<=nbMeublePiece; i++){
        r = rand()%5;
        switch(r) {
            case 0:
                ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
                break;
            case 1:
                ajouterMeubleAuMur(etagere,pieceChg,pieceCbd);
                break;
            case 2:
                ajouterMeubleAuMur(coffre,pieceChg,pieceCbd);
                break;
            case 3:
                ajouterMeubleAuMur(caisse,pieceChg,pieceCbd);
                break;
            case 4:
                ajouterMeubleAuCentre(tonneau,pieceChg,pieceCbd);
                break;
            default:
                break;
        }
    }
}


void Terrain::remplirPieceBureau(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble petitBureau(2, 1, 'b', 0, 3);
    Meuble grandBureau(3, 2, 'b', 0, 7);
    Meuble coffre(2, 1, 'c', 0, 3);
    Meuble placard(2, 1, 'p', 0, 3);
    Meuble poubelle(1, 1, 'v', 28, 1);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);


    if (nbMeublePiece >= 3){ //grand bureau
        ajouterMeubleAuCentre(grandBureau,pieceChg,pieceCbd);
    }else{ //petit bureau
        ajouterMeubleAuCentre(petitBureau,pieceChg,pieceCbd);
    }

    ajouterMeubleAuMur(coffre,pieceChg,pieceCbd);

    if (nbMeublePiece >= 4) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
    if (nbMeublePiece >= 5) ajouterMeubleAuMur(poubelle,pieceChg,pieceCbd);
    if (nbMeublePiece >= 6) ajouterMeubleAuMur(coffre,pieceChg,pieceCbd);
}


void Terrain::remplirPiecePrincipale(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble petiteTable(2, 2, 't', 0, 5);
    Meuble grandeTable(3, 2, 't', 0, 7);
    Meuble tresGrandeTable(5, 3, 't', 12, 0);
    Meuble placard(2, 1, 'p', 0, 3);
    Meuble piano(3, 2, 'n', 0, 7);
    Meuble tonneau(1, 1, 'T', 28, 1);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);

    if (nbMeublePiece >= 5){ // tresGrandeTable
        ajouterMeubleAuCentreGrand(tresGrandeTable,pieceChg,pieceCbd);
    }else if (nbMeublePiece >= 3){ //grandeTable bureau
        ajouterMeubleAuCentre(grandeTable,pieceChg,pieceCbd);
    }else{ //petiteTable
        ajouterMeubleAuCentre(petiteTable,pieceChg,pieceCbd);
    }

    if (nbMeublePiece >= 4) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
    if (nbMeublePiece >= 5) ajouterMeubleAuMur(tonneau,pieceChg,pieceCbd);
    if (nbMeublePiece >= 6) ajouterMeubleAuMur(piano,pieceChg,pieceCbd);
}


void Terrain::remplirPieceDEau(Point2D const & pieceChg, Point2D const & pieceCbd){
    assert(pieceCbd.x > 0);
    assert(pieceCbd.y > 0);
    assert(pieceChg.x > 0);
    assert(pieceChg.y > 0);
    assert(pieceCbd.x < m_largeur);
    assert(pieceCbd.y < m_hauteur);
    assert(pieceChg.x < m_largeur);
    assert(pieceChg.y < m_hauteur);

    Meuble placard(2, 1, 'p', 0, 3);
    Meuble petiteBaignoire(2, 1, 'b', 0, 3);
    Meuble grandBaignoire(2, 2, 'b', 0, 5);
    Meuble porteManteau(1, 1, 'i', 28, 1);

    int largeurPiece = pieceCbd.x - pieceChg.x;
    int hauteurPiece = pieceCbd.y - pieceChg.y;
    int nbMeublePiece = floor(largeurPiece*hauteurPiece / 9);


    if (nbMeublePiece >= 3){ //grandBaignoire
        ajouterMeubleAuMur(grandBaignoire,pieceChg,pieceCbd);
    }else{ //petiteBaignoire
        ajouterMeubleAuMur(petiteBaignoire,pieceChg,pieceCbd);
    }

    ajouterMeubleAuMur(porteManteau,pieceChg,pieceCbd);

    if (nbMeublePiece >= 4) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
    if (nbMeublePiece >= 5) ajouterMeubleAuMur(porteManteau,pieceChg,pieceCbd);
    if (nbMeublePiece >= 6) ajouterMeubleAuMur(placard,pieceChg,pieceCbd);
}









void Terrain::ajouterPiece(Point2D const & pieceChg, Point2D const & pieceCbd){
    Piece nvPiece(pieceChg, pieceCbd);

    m_pieces.push_back(nvPiece);
    m_nbPiece ++;
}


void Terrain::remplirPieces(){
    int r;
    int nbTypePiece = 6;

    for(unsigned int i=0; i<m_nbPiece; i++){

        r = rand()%nbTypePiece;
        switch(r) {
            case 0:
                remplirPieceChambre(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            case 1:
                remplirPieceBureau(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            case 2:
                remplirPieceDortoir(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            case 3:
                remplirPieceStockage(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            case 4:
                remplirPiecePrincipale(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            case 5:
                remplirPieceDEau(m_pieces[i].getChg(), m_pieces[i].getCbd());
                break;
            default:
                break;
        }
    }
}











void Terrain::diviser(Point2D const & pieceChg, Point2D const & pieceCbd, unsigned int probaDiv){
    unsigned int largeurPiece = pieceCbd.x - pieceChg.x;
    unsigned int hauteurPiece = pieceCbd.y - pieceChg.y;

    unsigned int r=rand()%100 + 1;

    if(r<=probaDiv || largeurPiece>=m_largeurPieceMax || hauteurPiece>=m_hauteurPieceMax){ //on divise en 2

        if (largeurPiece > hauteurPiece && largeurPiece>m_largeurPieceMin*2){ //coupure verticale
            
            int coupure = rand()%(largeurPiece-m_largeurPieceMin*2) + pieceChg.x + m_largeurPieceMin;

            Porte porte;
            porte.x=coupure;
            porte.y=(int) (pieceChg.y+pieceCbd.y)/2;
            porte.orientation='v';

            m_portes.push_back(porte);
            m_nbPorte ++;
            
            for(int i=pieceChg.y; i<=pieceCbd.y; i++){
                m_matrice[i][porte.x].type='X';
            }
            m_matrice[porte.y][porte.x].type='-';

            Point2D nvChg(porte.x+1, pieceChg.y);
            Point2D nvCbd(porte.x-1, pieceCbd.y);
            diviser(pieceChg, nvCbd, probaDiv/2);
            diviser(nvChg, pieceCbd, probaDiv/2);
        }

        else if(hauteurPiece>m_hauteurPieceMin*2){   //coupure horizontale


            int coupure = rand()%(hauteurPiece-m_hauteurPieceMin*2) + pieceChg.y + m_hauteurPieceMin;

            Porte porte;
            porte.x=(int) (pieceChg.x+pieceCbd.x)/2;
            porte.y=coupure;
            porte.orientation='h';

            m_portes.push_back(porte);
            m_nbPorte ++;

            for(int i=pieceChg.x; i<=pieceCbd.x; i++){
                m_matrice[porte.y][i].type='X';
            }
            m_matrice[porte.y][porte.x].type='-';

            Point2D nvChg(pieceChg.x, porte.y+1); 
            Point2D nvCbd(pieceCbd.x, porte.y-1);
            diviser(pieceChg, nvCbd, probaDiv/2);
            diviser(nvChg, pieceCbd, probaDiv/2);
        }
        
        else{ //remplir les pieces
           ajouterPiece(pieceChg, pieceCbd);
        }
    }
    else{ //remplir les pieces
        ajouterPiece(pieceChg, pieceCbd);
    }
}
