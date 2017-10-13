//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_TOWERTEST_H
#define TOWERDEFENSE_TOWERTEST_H


#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/Tower.h"

class TowerTest : public CppUnit::TestCase{
public:
    CPPUNIT_TEST_SUITE(TowerTest);
        CPPUNIT_TEST(towersStartWithZeroExperience);
    CPPUNIT_TEST_SUITE_END();

protected:
    void towersStartWithZeroExperience();
private:
    Tower* tower = nullptr;

};


#endif //TOWERDEFENSE_TOWERTEST_H
