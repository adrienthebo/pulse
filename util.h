#ifndef _UTIL_H_
#define _UTIL_H_

int rand(int max, int passes) {
    int rv = max;
    for(int i = 0; i < passes; i++) {
        rv = random(rv);
    }
    return rv;
}

#endif // _UTIL_H_
