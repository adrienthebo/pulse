#include <OctoWS2811.h>
#include <Color.h>

#include "output-octo.h"
#include "view.h"
#include "framerate.h"

#include "effect-random.h"
#include "effect-warmrandom.h"
#include "effect-coolrandom.h"
#include "effect-emergency-lights.h"
#include "effect-strobe.h"
#include "effect-twinkle.h"
#include "effect-whoa.h"
#include "effect-rainbow.h"

#include "effect-serial.h"

Effect *e;
Output *output;

void setup_output() {
    output = new Octo(50 * 8, 50, WS2811_RGB);
    //r = new Octo(60 * 8, 60, WS2811_GRB);
    output->clear();
    output->show();
}

void setup_effect() {
    //effect = new Random();
    //effect = new CoolRandom();
    //effect = new Strobe();
    //effect = new EmergencyLights();
    //effect = new SerialDebugger();
    //effect = new Whoa();
    effect = new Rainbow();

    //effect = new Twinkle(400);
}

void setup() {
    setup_output();
    setup_effect();
}

void loop() {
    effect->apply(output);
    output->show();
    delay(FPS_60);
}
