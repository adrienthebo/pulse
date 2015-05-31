#ifndef _WHOA_H_
#define _WHOA_H_

#include "effect.h"

struct Whoa : Effect {
    
    float hue = 0;
    //float sat = 0.9;
    float sat = 0.0;
    float lum = 0.3;

    /*
     * How much to increment the hue for each index. Higher values mean faster
     * transitions through the spectrums, meaning a more compressed transition.
     */
    float hue_scale = 0.0101;

    /*
     * How much to decrement the luminosity for each index. Higher values mean
     * smaller bands of light and dark. Very low values mean the entire panel
     * will fade from light to dark.
     */
    float lum_scale = 0.0101;

    virtual void apply(Output *r) {
        Color c;
        for(int i = 0; i < r->get_length(); i++) {
            hue = increment_hue(hue);
            lum = decrement_lum(lum);
            c.convert_hcl_to_rgb(hue, sat, lum);
            r->set_pixel(i, c.red, c.green, c.blue);
        }
    }

protected:

    float increment_hue(float current) {
        float sum = current + hue_scale;
        if(sum >= 1.0) {
            sum--;
        }
        return sum;
    }

    float decrement_lum(float current) {
        float sum = current - lum_scale;
        if(sum <= 0.00001) {
            sum += 0.4;
        }
        return sum;
    }
};

#endif // _WHOA_H_
