//
// Created by Artem on 07.10.2025.
//

#ifndef LABA1_CONSTANTS_H
#define LABA1_CONSTANTS_H


#include <vector>

class Constants {
public:
    struct XYPair{
        int x, y;
    };

    struct dxdy{ //нужна чтобы в некоторый контекст можно было передать именно её
        int x, y;
    };
    static inline const std::vector<Constants::dxdy> dxdys{{-1, 1},
                                                      {0,  1},
                                                      {1,  1},
                                                      {1,  0},
                                                      {1,  -1},
                                                      {0,  -1},
                                                      {-1, -1},
                                                      {-1, 0}};
};


#endif //LABA1_CONSTANTS_H
