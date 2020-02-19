#include "AI.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

using namespace std;

int ap[10];

void AI::pick(World* world)
{
    world->chooseHand({ world->getBaseUnitById(0),
        world->getBaseUnitById(1),
        world->getBaseUnitById(3),
        world->getBaseUnitById(6),
        world->getBaseUnitById(7) });

    fill(ap, ap + 10, 10);
}

void AI::turn(World* world)
{
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
