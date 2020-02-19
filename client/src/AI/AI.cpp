#include "AI.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

using namespace std;

int ap[10], rows, cols;
void AI::pick(World* world)
{
    rows = world->getMap()->getRowNum();
    cols = world->getMap()->getColNum();
    world->chooseHand({ world->getBaseUnitById(0),
        world->getBaseUnitById(1),
        world->getBaseUnitById(3),
        world->getBaseUnitById(6),
        world->getBaseUnitById(7) });

    fill(ap, ap + 10, 10);
}

map<int, int> att_path_wei, def_path_wei, att_unit_wei, def_unit_wei; ///unit -> weight, path -> weight
map<const Cell*, int> haste_wei, dup_wei, damage_wei, heal_wei, poison_wei; ///cell -> weight

void compute_weights(World* world)
{
    const Player *me = world->getMe(), *mate = world->getFriend(), *enemy1 = world->getFirstEnemy(), *enemy2 = world->getSecondEnemy();
    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){
            const Cell* cur = world->getMap()->cell(i, j);
            vector<const Unit*> units = world->getCellUnits(i, j);
            for(const Unit* unit : units){
                if(unit->getPlayerId() == world->getFirstEnemy()->getPlayerId() || unit->getPlayerId() == world->getSecondEnemy()->getPlayerId()){
                    damage_wei[cur] += min(max(0, unit->getHp()-1), 4) * ((unit->getTarget() != nullptr) * 2 + 1) * ((unit->getBaseUnit()->isMultiple()) * 2 + 1);
                    poison_wei[cur] += min(max(0, unit->getHp()-1), 5) * ((unit->getTarget() != nullptr) + 1) * ((unit->getBaseUnit()->isMultiple()) + 1);
                }
                else{
                    haste_wei[cur] += (unit->getTargetIfKing() == nullptr) * (min(max(0, unit->getHp()-1) * (unit->getRange()+1) * unit->getAttack() * ((unit->getBaseUnit()->isMultiple()) + 1), 1000));
                    heal_wei[cur] += min(unit->getBaseUnit()->getMaxHp() - unit->getHp(), 2) * unit->getRange() * unit->getAttack() * ((unit->getBaseUnit()->isMultiple()) + 1);
                    dup_wei[cur] += ((!(unit->getTargetIfKing() == nullptr)) + 1) * ((unit->getHp()/4) * (unit->getAttack()/4) * unit->getRange() * ((unit->getBaseUnit()->isMultiple()) + 1));
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

