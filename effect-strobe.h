#ifndef _STROBE_H_
#define _STROBE_H_

#include "effect.h"

struct Strobe : Effect {

    int counter = 0;

    virtual void apply(Output *output) {
        for(int i = 0; i < output->get_length(); i++) {
            if (counter % 2 == 0) {
                output->set_pixel(i, 0xFFFFFF);
            } else {
                output->clear_pixel(i);
            }
        }
        counter++;
    }

protected:

};

#endif // _STROBE_H_

