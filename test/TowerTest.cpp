//
// Created by facundo on 10/10/17.
//

#include "TowerTest.h"
#include "../src/model/FireTower.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TowerTest);

void TowerTest::towersStartWithZeroExperience() {
    Vector pos(0,0);
    tower = new FireTower(pos, 1, 0);

    CPPUNIT_ASSERT(tower->getExperience() == 0);

    delete tower;
}
