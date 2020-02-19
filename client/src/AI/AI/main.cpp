#include "AI.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

using namespace std;

int ap[10], rows, cols;
void AI::pick(World* world)
{
    rows = world->getMap()->rowNum;
    cols = world->getMap()->colNum;
    world->chooseHand({ world->getBaseUnitById(0),
        world->getBaseUnitById(1),
        world->getBaseUnitById(3),
        world->getBaseUnitById(6),
        world->getBaseUnitById(7) });

    fill(ap, ap + 10, 10);
}

map<int, int> att_path_wei, def_path_wei, att_unit_wei, def_unit_wei; ///unit -> weight, path -> weight
map<pair<int, int>, int> hiest_wei, dup_wei, damage_wei, heal_wei, poison_wei; ///cell -> weight

void compute_weights(World* world)
{
    Player me = world->getMe(), mate = world->getFriend(), enemy1 = world->getFirstEnemy(), enemy2 = world->getSecondEnemy();
    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){
            vector<Unit> units = getCellUnits(i, j);
            for(Unit unit : units){
                if(unit->playerId == world->getFirstEnemy()->playerId || unit->playerId == world->getSecondEnemy()->playerId){

                }
                else{
                    if(unit->playerId = me->playerId);
                }
            }
        }
    }
}

void AI::turn(World* world)
{
    compute_weights(world);
}

void AI::end(World* world, std::map<int, int>& scores)
{
    cout << "Results:" << endl;
    cout << "Me: " << scores[world->getMe()->getPlayerId()] << endl;
    cout << "My Friend: " << scores[world->getFriend()->getPlayerId()] << endl;
    cout << "Opponent #1: " << scores[world->getFirstEnemy()->getPlayerId()] << endl;
    cout << "Opponent #2: " << scores[world->getSecondEnemy()->getPlayerId()] << endl;
    cout << "------------------" << endl;
}
