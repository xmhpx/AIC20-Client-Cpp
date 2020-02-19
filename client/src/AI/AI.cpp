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
map<pair<int, int>, int> haste_wei, dup_wei, damage_wei, heal_wei, poison_wei; ///cell -> weight

void compute_weights(World* world)
{
    Player *me = world->getMe(), *mate = world->getFriend(), *enemy1 = world->getFirstEnemy(), *enemy2 = world->getSecondEnemy();
    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){
            vector<Unit> units = getCellUnits(i, j);
            for(Unit unit : units){
                if(unit.playerId == world->getFirstEnemy()->playerId || unit.playerId == world->getSecondEnemy()->playerId){
                    damage_wei[i][j] += min(max(0, unit.hp-1), 4) * ((unit.target != nullptr) * 2 + 1) * ((unit.baseUnit.isMultiple)*2 + 1);
                    poison_wei[i][j] += min(max(0, unit.hp-1), 5) * ((unit.target != nullptr) + 1) * ((unit.baseUnit.isMultiple) + 1);
                }
                else{
                    haste_wei[i][j] += min(max(0, unit.hp-1) * (unit.range+1) * unit.attack * ((unit.baseUnit.isMultiple) + 1), 1000);
                    heal_wei[i][j] += min(unit.baseUnit.maxHP - unit.hp, 2) * unit.range * unit.attack * ((unit.baseUnit.isMultiple) + 1);
                    dup_wei[i][j] += (unit.hp/4) * (unit.attack/4) * unit.range * ((unit.baseUnit.isMultiple) + 1);
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

