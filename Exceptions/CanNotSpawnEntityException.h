//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_CANNOTSPAWNENTITYEXCEPTION_H
#define LABA1_CANNOTSPAWNENTITYEXCEPTION_H

#include <string>
#include "UniversalStringException.h"

class CanNotSpawnEntityException : UniversalStringException{
public:
    explicit CanNotSpawnEntityException(const std::string &message) : UniversalStringException(message) {}
};


#endif //LABA1_CANNOTSPAWNENTITYEXCEPTION_H
