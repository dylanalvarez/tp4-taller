//
// Created by facundo on 22/10/17.
//

#include "LevelupType.h"

LevelupType::LevelupType(double (*getNecessaryExp)(int)) {
    this->getNecessaryExp = getNecessaryExp;
}
