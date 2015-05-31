#ifndef _EMERGENCY_LIGHTS_H
#define _EMERGENCY_LIGHTS_H

#include "effect.h"

struct EmergencyLights : Effect {

    int state = 0;
    int intensity = 0x8F;

    bool is_red(int group) {
        return (
                group % 2 == 0 &&
                (
                    state == 1 ||
                    state == 3
                )
               );
    }

    bool is_blue(int group) {
        return (
                group % 2 == 1 &&
                (
                    state == 7 ||
                    state == 9
                )
               );
    }

    virtual void apply_group(Output *r, int group) {
        int rgb = 0;

        if(is_blue(group)) {
            rgb = intensity;
        } else if(is_red(group)) {
            rgb = intensity << 16;
        }

        for(int offset = 0; offset < 3; offset++) {
            int idx = group * 3 + offset;
            r->set_pixel(idx, rgb);
        }
    }

    virtual void apply(Output *r) {
        for(int i = 0; i < r->get_length(); i++) {
            int group = i / 3;
            apply_group(r, group);
        }

        if(state++ > 10) {
            state = 0;
        }
    }
};

#endif // _EMERGENCY_LIGHTS_H
