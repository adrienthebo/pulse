#ifndef _WHOA_H_
#define _WHOA_H_

#include "effect.h"

struct Whoa : Effect {
    
    float hue = 0;
    float sat = 0.6;
    float lum = 0.1;

    float scale = 0.003;

    virtual void apply(Renderer *r) {
        Color c;
        for(int i = 0; i < r->get_length(); i++) {
            hue = increment_hue(hue);
            c.convert_hcl_to_rgb(hue, sat, lum);
            r->set_pixel(i, c.red, c.green, c.blue);
        }
    }

protected:

    float increment_hue(float current) {
        float sum = current + scale;
        if(sum >= 1.0) {
            sum--;
        }
        return sum;
    }
};

#endif // _WHOA_H_
