//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "GameBoard.h"
#include "BoardCell.h"
#include "CellType.h"
#include "Direction.h"
#include "List.h"
#include "Utilities.h"
#include "MoveVehicle.h"


template<typename L, int I, CellType C>
struct GetCarFromList {
    constexpr static int col = ConditionalInteger<
            L::head::type == C,
            I,
            GetCarFromList<typename L::next, I + 1, C>::col
    >::value;
};

template<int I, CellType C>
struct GetCarFromList<List<>, I, C> {
    constexpr static int col = -1;
};

template<typename B, int R, CellType C, int H>
struct GetCarInner {
    constexpr static int row = -1;
    constexpr static int col = -1;
};

template<typename B, int R, CellType C> // H is a helper: it represents the last temp_col
struct GetCarInner<B, R, C, -1> {
    constexpr static int temp_col = GetCarFromList<typename B::head, 0, C>::col;

    constexpr static int row = ConditionalInteger<
            temp_col != -1,
            R,
            GetCarInner<typename B::next, R + 1, C, temp_col>::row
    >::value;

    constexpr static int col = ConditionalInteger<
            temp_col != -1,
            temp_col,
            GetCarInner<typename B::next, R + 1, C, temp_col>::col
    >::value;
};


template<typename B, int R, CellType C>
struct GetCar {
    constexpr static int col = GetCarInner<B, R, C, -1>::col;
    constexpr static int row = GetCarInner<B, R, C, -1>::row;
};

template<typename L, int I>
struct CheckEmpty {
    constexpr static bool value = CheckEmpty<typename L::next, I - 1>::value;
};
template<typename L>
struct CheckEmpty<L, 0> {
    constexpr static bool value_1 = L::head::type == EMPTY || L::head::type == X;
    constexpr static bool value = value_1 && CheckEmpty<typename L::next, 0>::value;
};
template<>
struct CheckEmpty<List<>, 0> {
    constexpr static bool value = true;
};

template<typename B>
struct CheckWin {
    constexpr static int red_car_row = GetCar<typename B::board, 0, X>::row;
    constexpr static int red_car_col = GetCar<typename B::board, 0, X>::col;

    constexpr static bool result = CheckEmpty<typename GetAtIndex<red_car_row, typename B::board>::value, red_car_col>::value;
};


template<typename B, typename LoM> // LoM -> List of Moves
struct CheckSolution {

    typedef typename MoveVehicle<B,
            GetCar<typename B::board, 0, LoM::head::type>::row,
            GetCar<typename B::board, 0, LoM::head::type>::col,
            LoM::head::direction, LoM::head::amount
    >::board new_board;

    constexpr static bool result = CheckSolution<new_board, typename LoM::next>::result;
};

template<typename B>
struct CheckSolution<B, List<>> {
    constexpr static bool result = CheckWin<B>::result;
};


#endif //OOP5_RUSHHOUR_H
