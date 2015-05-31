#ifndef _WARMRANDOM_H_
#define _WARMRANDOM_H_

#include "effect.h"
#include "effect-random.h"

struct WarmRandom : Random {

    virtual void apply_one(Output *r, int idx) {
        set_scale();
        Random::apply_one(r, idx);
    }

protected:
    int _scale = 0;

    virtual void set_scale() {
        _scale = rand(max, passes);
    }

    virtual float red() {
        return _scale;
    }

    virtual float green() {
        return _scale * random(10) * 0.1;
    }

    virtual float blue() {
        return 0;
    }
};

#endif // _WARMRANDOM_H_
