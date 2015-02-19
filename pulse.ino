#include <OctoWS2811.h>
#include "renderer-octo.h"
#include "view.h"
#include "framerate.h"

#include "effect-random.h"
#include "effect-warmrandom.h"
#include "effect-coolrandom.h"
#include "effect-emergency-lights.h"
#include "effect-strobe.h"
#include "effect-twinkle.h"

#include "effect-serial.h"

Effect *e;
Renderer *r;

void setup_renderer() {
    r = new Octo(50 * 8, 50, WS2811_RGB);
    //r = new Octo(60 * 8, 60, WS2811_GRB);
    r->clear();
    r->show();
}

void setup_effect() {
    //e = new Random();
    //e = new CoolRandom();
    //e = new Strobe();
    //e = new EmergencyLights();
    //e = new SerialDebugger();

    e = new Twinkle(400);
}

void setup() {
    setup_renderer();
    setup_effect();
}

void loop() {
    e->apply(r);
    r->show();
    delay(FPS_15);
}
