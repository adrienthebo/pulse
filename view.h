#ifndef _VIEW_H_
#define _VIEW_H_

struct View {
    Output *_output;

    View(Output *output) {
        _output = output;
    }

    virtual void set_pixel(int x, int y, int r, int g, int b) {
        if(!is_valid(x, y)) {
            return;
        }
        _output->set_pixel(to_index(x, y), r, g, b);
    }

    virtual void clear_pixel(int x, int y) {
        set_pixel(x, y, 0, 0, 0);
    }

    bool is_valid(int x, int y) {
        return (
            (x < 0 || x >= _max_x) ||
            (y < 0 || y >= _max_y)
        );
    }

protected:
    int _max_x = 10;
    int _max_y = 10;

    int to_index(int x, int y) {
        int idx = 0;
        idx += x * 10;

        if ((x % 2 == 1 && x < 5) || (x % 2 == 0 && x >= 5)) {
            idx += 9 - y;
        } else {
            idx += y;
        }

        return idx;
    }
};

#endif // _VIEW_H_
