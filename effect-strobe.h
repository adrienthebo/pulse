#ifndef _STROBE_H_
#define _STROBE_H_

#include "effect.h"

struct Strobe : Effect {

    int counter = 0;

    virtual void apply(Output *r) {
        for(int i = 0; i < r->get_length(); i++) {
            if (counter % 2 == 0) {
                r->set_pixel(i, 0xFFFFFF);
            } else {
                r->clear_pixel(i);
            }
        }
        counter++;
    }

protected:

};

#endif // _STROBE_H_

