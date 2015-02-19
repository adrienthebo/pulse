#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "effect.h"
#include "effect-random.h"

struct SerialDebugger : Effect {

    int idx = 0;
    int color = 0xFFFFFF;

    SerialDebugger() {
        Serial.begin(9600);
    }

    void respond() {
        Serial.print("idx: ");
        Serial.print(idx);
        Serial.print(", color: 0x");
        Serial.print(color, HEX);
        Serial.println();
    }

    virtual void apply(Renderer *r) {
        if (Serial.available()) {
            char c = Serial.read();
            int old = idx;

            switch(c) {
                case 'u':
                    idx++;
                    break;
                case 'd':
                    idx--;
                    break;
                case 'r':
                    color = 0xFF0000;
                    break;
                case 'g':
                    color = 0x00FF00;
                    break;
                case 'b':
                    color = 0x0000FF;
                    break;
                case 'w':
                    color = 0xFFFFFF;
                    break;
                case 'o':
                    color = 0x010101;
                    break;
                default:
                    Serial.println("?");
                    return;
            }

            respond();
            r->clear_pixel(old);
            r->set_pixel(idx, color);
        }
    }
};

#endif // _SERIAL_H_
