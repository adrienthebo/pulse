#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include "effect.h"

struct Rainbow : Effect {
    
    int index = 0;
    float hue = 0;
    float sat = 0.6;
    float lum = 0.1;

    float scale = 0.04;

    virtual void apply(Renderer *r) {
        Color c;

        hue = increment_hue(hue);
        c.convert_hcl_to_rgb(hue, sat, lum);

        for(int i = 0; i < 9; i++) {
            r->set_pixel(index, c.red, c.green, c.blue);
            index = next_index(index, r->get_length());
        }
    }

protected:

    int next_index(int current, int max) {
        int next = current + 1;
        if(next >= max) {
            return 0;
        } else {
            return next;
        }
    }

    float increment_hue(float current) {
        float sum = current + scale;
        if(sum >= 1.0) {
            sum--;
        }
        return sum;
    }
};

#endif // _RAINBOW_H_
