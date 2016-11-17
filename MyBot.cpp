#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <set>
#include <fstream>

#include "hlt.hpp"
#include "networking.hpp"

int main() {
    srand(time(NULL));

    std::cout.sync_with_stdio(0);

    unsigned char myID;
    hlt::GameMap presentMap;
    getInit(myID, presentMap);
    sendInit("MyC++Bot");

    std::set<hlt::Move> moves;
    while(true) {
        moves.clear();

        getFrame(presentMap);

        for(unsigned short a = 0; a < presentMap.height; a++) {
            for(unsigned short b = 0; b < presentMap.width; b++) {
				hlt::Site &now = presentMap.getSite({b, a});
				int directions;
				bool attack = false;
                if (now.owner == myID) {
					if(now.strength < now.production*10){
						directions = 0;
					} else{
						directions = (rand()%4)+1;
					}
					for( unsigned short d = 1; d < 5; d++){
						hlt::Site neighborSite = presentMap.getSite({b, a}, (unsigned char)d);
						if(now.strength > neighborSite.strength && neighborSite.owner != myID){
							directions = d;
							attack = true;
							break;
						}
					}
					if(!attack){
						hlt::Site eastNeighbor = presentMap.getSite({b, a}, (unsigned char)2);
						int randnum = rand()%2;
						directions = 0;
						if(eastNeighbor.owner == myID && now.strength > 50 ){
							directions = 2;
						}
						hlt::Site southtNeighbor = presentMap.getSite({b, a}, (unsigned char)3);
						if(southtNeighbor.owner == myID && now.strength > 50 && randnum){
							directions = 3;
						}
					}
                    moves.insert({ { b, a }, (unsigned char)directions });
                }
            }
        }

        sendFrame(moves);
    }

    return 0;
}
