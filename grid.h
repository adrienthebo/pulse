#ifndef _GRID_H_
#define _GRID_H_

#define GRID_NORMAL 0
#define GRID_REVERSE 1

uint32_t gridData[50][3] = {
    {0,   9, GRID_NORMAL},
    {9,   9, GRID_REVERSE},
    {18,  9, GRID_NORMAL},
    {27,  9, GRID_REVERSE},
    {36,  9, GRID_NORMAL},
    {45,  9, GRID_REVERSE},
    {54,  9, GRID_NORMAL},
    {63,  9, GRID_REVERSE},
    {72,  9, GRID_NORMAL},
    {81,  9, GRID_REVERSE},
    {90,  9, GRID_NORMAL},
    {99,  9, GRID_REVERSE},
    {108, 9, GRID_NORMAL},
    {117, 9, GRID_REVERSE},
    {126, 9, GRID_NORMAL},
    {135, 9, GRID_REVERSE},
    {144, 9, GRID_NORMAL},
    {153, 9, GRID_REVERSE},
    {162, 9, GRID_NORMAL},
    {171, 9, GRID_REVERSE},
    {180, 9, GRID_NORMAL},
    {189, 9, GRID_REVERSE},
    {198, 9, GRID_NORMAL},
    {207, 9, GRID_REVERSE},
    {216, 9, GRID_NORMAL},
    {225, 9, GRID_REVERSE},
    {234, 9, GRID_NORMAL},
    {243, 9, GRID_REVERSE},
    {252, 9, GRID_NORMAL},
    {261, 9, GRID_REVERSE},
    {270, 9, GRID_NORMAL},
    {279, 9, GRID_REVERSE},
    {288, 9, GRID_NORMAL},
    {297, 9, GRID_REVERSE},
    {306, 9, GRID_NORMAL},
    {315, 9, GRID_REVERSE},
    {324, 9, GRID_NORMAL},
    {333, 9, GRID_REVERSE},
    {342, 9, GRID_NORMAL},
    {351, 9, GRID_REVERSE},
};

struct Grid {

    bool isValidXIndex(uint32_t x) {
        return x >= 0 && x <= 8;
    }

    bool isValidYIndex(uint32_t y) {
        return y >= 0 && y <= 40;
    }

    bool isValidIndex(uint32_t x, uint32_t y) {
        return isValidXIndex(x) && isValidYIndex(y);
    }

    uint32_t indexOf(uint32_t x, uint32_t y) {
        if(!isValidIndex(x, y)) {
            return -1;
        }

        uint32_t rv = 0;

        uint32_t *row = gridData[y];

        uint32_t rowOffset = row[0];
        uint32_t rowLen    = row[1];
        uint32_t rowDir    = row[2];

        rv += rowOffset;

        if(rowDir == GRID_NORMAL) {
            rv += x;
        } else {
            rv += (rowLen - 1 - x);
        }
        return rv;
    }
};

#endif // _GRID_H_
