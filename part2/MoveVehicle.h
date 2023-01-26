//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H


#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "Utilities.h"
#include "TransposeList.h"


template<CellType C, Direction D, int A>
struct Move {
    static constexpr CellType type = C;
    static constexpr Direction direction = D;
    static constexpr int amount = A;

    // make sure cell is not empty
    static_assert(type != EMPTY, "Move received empty cell");
};


// get the cell at (R,C) in the board
template<typename B, int R, int C>
struct GetCell {
    typedef typename GetAtIndex<C, typename GetAtIndex<R, typename B::board>::value>::value cell;
};
template<typename B, int R, int C, typename Cell>
struct SetCell {
    // get the row
    typedef typename GetAtIndex<R, typename B::board>::value row;

    // set the cell in the row
    typedef typename SetAtIndex<C, Cell, row>::list new_row;

    // set the row in the board
    typedef typename SetAtIndex<R, new_row, typename B::board>::list new_board;

    typedef GameBoard<new_board> value;
};

template<typename L, CellType VT, int I>
struct getVehicleStart {
    constexpr static int value = ConditionalInteger<
            L::head::type == VT,
            I,
            getVehicleStart<typename L::next, VT, I + 1>::value
    >::value;
};

template<CellType VT, int I>
struct getVehicleStart<List<>, VT, I> {
    constexpr static int value = -1;
};

// move the vehicle
template<typename B, int R, int VS, int VE, int Step, int A>
struct MoveAll {
    typedef typename GetCell<B, R, VS>::cell last_cell;
    typedef typename GetCell<B, R, VE + Step>::cell new_cell;

    static_assert(new_cell::type == EMPTY, "Vehicle cannot move");

    // move once and update the board
    typedef typename SetCell<B, R, VE + Step, last_cell>::value temp_board;
    // move the last cell to empty
    typedef typename SetCell<temp_board, R, VS, BoardCell<EMPTY, last_cell::direction, last_cell::length>>::value final_board;

    // move the rest of the vehicle
    typedef typename MoveAll<final_board, R, VS + Step, VE + Step, Step, A - 1>::board board;

};
template<typename B, int R, int VS, int VE, int Step>
struct MoveAll<B, R, VS, VE, Step, 0> {
    typedef B board;
};

/*
 * B - the board before the move
 * R - the row of the vehicle to move
 * C - the column of the vehicle to move
 * D - the direction to move the vehicle
 * A - the amount to move the vehicle
 */
template<typename B, int R, int C, Direction D, int A>
struct MoveVehicle {
    static_assert(R >= 0 && R < B::length, "Row is out of bounds");
    static_assert(C >= 0 && C < B::width, "Column is out of bounds");

    // get the cell object
    typedef typename GetCell<B, R, C>::cell cell;

    static_assert(cell::type != EMPTY, "Cell is empty");
    static_assert(cell::direction < 2 && D < 2 || cell::direction >= 2 && D >= 2,
                  "Cell is not moving in the right direction");

    // transpose the board if the vehicle is moving vertically
    typedef typename Conditional
            <D < 2,
                    typename Transpose<typename B::board>::matrix,
                    //else
                    typename B::board>
    ::value curr_board_inner;
    typedef GameBoard<curr_board_inner> curr_board;

    // update direction, row and col after transpose
    static constexpr Direction direction = static_cast<Direction>(ConditionalInteger<D < 2, D + 2, D>::value);
    static constexpr int row = ConditionalInteger<D < 2, C, R>::value;
    static constexpr int col = ConditionalInteger<D < 2, R, C>::value;

    // get the beginning and end of the vehicle
    static constexpr int left_col = getVehicleStart<
            typename GetAtIndex<row, typename curr_board::board>::value,
            GetCell<curr_board, row, col>::cell::type,
            0>::value;
    static constexpr int right_col = left_col + cell::length - 1;

    static constexpr int move_direction = ConditionalInteger<direction == RIGHT, 1, -1>::value;
    static constexpr int start_col = ConditionalInteger<direction == RIGHT, left_col, right_col>::value;
    static constexpr int end_col = ConditionalInteger<direction == RIGHT, right_col, left_col>::value;

    // move the vehicle
    typedef typename MoveAll<curr_board, row, start_col, end_col, move_direction, A>::board almost_board;

    typedef typename Conditional
            <D < 2,
                    typename Transpose<typename almost_board::board>::matrix,
                    //else
                    typename almost_board::board
            >::value inner_board;

    typedef GameBoard<inner_board> board;
};


#endif //OOP5_MOVEVEHICLE_H
