#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "effect.h"
#include "util.h"

struct Random : Effect {

    virtual void apply_one(Output *output, int idx) {
        output->set_pixel(idx, red(), green(), blue());
    }

    virtual void apply(Output *output) {
        for(int i = 0; i < output->get_length(); i++) {
            apply_one(r, i);
        }
    }

protected:

    virtual float red() {
        return rand(max, passes);
    }

    virtual float green() {
        return rand(max, passes);
    }

    virtual float blue() {
        return rand(max, passes);
    }

    int max = 255;
    int passes = 4;
};

#endif // _RANDOM_H_
