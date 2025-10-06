//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_CELLIMPASSABLEEXCEPTION_H
#define LABA1_CELLIMPASSABLEEXCEPTION_H

#include <string>
#include "UniversalStringException.h"

class CellImpassableException : public UniversalStringException{
public:
    explicit CellImpassableException(const std::string &message) : UniversalStringException(message) {}
};


#endif //LABA1_CELLIMPASSABLEEXCEPTION_H
