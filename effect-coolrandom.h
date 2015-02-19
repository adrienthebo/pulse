#ifndef _COOLRANDOM_H_
#define _COOLRANDOM_H_

#include "effect.h"
#include "effect-random.h"

struct CoolRandom : Random {

    virtual void apply_one(Renderer *r, int idx) {
        set_scale();
        Random::apply_one(r, idx);
    }

protected:
    int _scale = 0;
    int passes = 5;

    virtual void set_scale() {
        _scale = rand(max, passes);
    }

    virtual float red() {
        return 0;
    }

    virtual float green() {
        return rand(max, passes);
    }

    virtual float blue() {
        return rand(max, passes);
    }
};

#endif // _COOLRANDOM_H_

