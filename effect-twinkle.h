#ifndef _TWINKLE_H_
#define _TWINKLE_H_

#include "util.h"
#include "effect.h"

struct Twinkle : Effect {

    Twinkle(uint32_t count) {
        direction = new bool[count];
        luma      = new uint8_t[count];
        max       = new uint8_t[count];
        memset(direction, 0, sizeof(bool) * count);
        memset(luma, 0, sizeof(uint8_t) * count);
        memset(max, 16, sizeof(uint8_t) * count);
    }

    virtual void apply(Output *r) {
        for(int i = 0; i < r->get_length(); i++) {
            uint8_t newval;
            if(direction[i]) {
                newval = increment(i);
            } else {
                newval = decrement(i);
            }
            r->set_pixel(i, (newval << 16) | (newval << 8) | newval);
        }
    }

protected:

    uint8_t decrement(int index) {
        if(luma[index] <= 0) {
            direction[index] = true;
            max[index] = speed * rand(224 / speed, passes);
        } else {
            luma[index] -= speed;
        }
        return luma[index];
    }

    uint8_t increment(int index) {
        if(luma[index] >= max[index]) {
            direction[index] = false;
        } else {
            luma[index] += speed;
        }
        return luma[index];
    }

    bool    *direction;
    uint8_t *luma;
    uint8_t *max;

    int speed = 1;
    int passes = 3;
};

#endif // _TWINKLE_H_


