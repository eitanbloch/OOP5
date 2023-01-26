//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "Direction.h"
#include "CellType.h"

template<CellType T, Direction D, int I>
struct BoardCell {
    static constexpr CellType type = T;
    static constexpr Direction direction = D;
    static constexpr int length = I;
};

#endif //OOP5_BOARDCELL_H
