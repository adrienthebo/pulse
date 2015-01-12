#include <OctoWS2811.h>
#include "renderer-octo.h"
#include "view.h"
#include "framerate.h"

#include "effect-random.h"
#include "effect-warmrandom.h"
#include "effect-coolrandom.h"
#include "effect-emergency-lights.h"

Effect *e;
Renderer *r;

void setup() {
  r = new Octo(60 * 8, 60, WS2811_GRB);
  r->clear();
  e = new CoolRandom();
}

void loop() {
    e->apply(r);
    r->show();
    delay(FPS_7);
}
