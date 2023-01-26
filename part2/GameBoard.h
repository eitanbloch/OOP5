//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

template<typename LoL> // LoL -> List of Lists
struct GameBoard {
    typedef LoL board;
    static constexpr int length = board::size;
    static constexpr int width = board::head::size;

};

#endif //OOP5_GAMEBOARD_H
