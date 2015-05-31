#ifndef _EFFECT_H_
#define _EFFECT_H_

struct Effect {
    virtual void apply(Output *r) = 0;
};

#endif // _EFFECT_H_
