#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Point2D.h"
#include "Case.h"
#include "Terrain.h"
#include "HitboxRectangle.h"

using namespace std;



int main()
{
    srand(time(NULL));

    Terrain t(20,20);

    t.generer();
    cout<<t<<endl;

    Point2D test(3.48, 1);
    Point2D testf(6.15, 17.15);
    if(t.droiteEstDansMur(test, testf))std::cout << "dqgsfdg"<< std::endl;

    return 0;
}