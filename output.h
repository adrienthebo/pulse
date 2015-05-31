#ifndef _OUTPUT_H_

struct Output {

    Output(int length) {
        _length = length;
    }

    virtual void set_pixel(int idx, int r, int g, int b) = 0;
    virtual void set_pixel(int idx, int rgb) = 0;

    virtual void clear_pixel(int idx) {
        set_pixel(idx, 0, 0, 0);
    }

    virtual void clear() {
        for(int idx = 0; idx < _length; idx++) {
            clear_pixel(idx);
        }
    }

    virtual void show() = 0;

    virtual bool busy() = 0;

    int get_length() { return _length; }

protected:

    int _length;
};

#endif // _OUTPUT_H_
