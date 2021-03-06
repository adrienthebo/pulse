#ifndef _OUTPUT_OCTO_H_
#define _OUTPUT_OCTO_H_
#include "output.h"

struct Octo : Output {

    Octo(int length, int strip_length) : Octo(length, strip_length, WS2811_RGB) {
    }

    Octo(int length, int strip_length, int flags) : Output(length) {
        _strip_length = strip_length;
        _flags = flags;

        int buffer_size = _length * 6;

        _frame_buf = new int[buffer_size];
        _draw_buf  = new int[buffer_size];

        _pixels = new OctoWS2811(_strip_length, _frame_buf, _draw_buf, _flags);
        _pixels->begin();
    }

    ~Octo() {
        delete[] _frame_buf;
        delete[] _draw_buf;
        delete _pixels;
    }

    void show() {
        _pixels->show();
    }

    void set_pixel(int idx, int r, int g, int b) {
        _pixels->setPixel(idx, r, g, b);
    }

    void set_pixel(int idx, int rgb) {
        _pixels->setPixel(idx, rgb);
    }

    bool busy() {
        _pixels->busy();
    }

    protected:

    void *_frame_buf;
    void *_draw_buf;
    int _strip_length;
    int _flags;

    OctoWS2811 *_pixels;
};

#endif // _OUTPUT_OCTO_H_
