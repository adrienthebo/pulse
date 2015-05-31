struct RGBWalk : Effect {

    virtual void apply(Output *r) {
        switch(state) {
            case 0: // Red
                r->set_pixel(idx, brightness, 0, 0);
                break;
            case 1: // Green
                r->set_pixel(idx, 0, brightness, 0);
                break;
            case 2: // Blue
                r->set_pixel(idx, brightness, 0, 0);
                break;
            case 3:
                //r->clear_pixel(idx);
                shift_counter(r);
                break;
            default:
                r->set_pixel(0, 255, 0, 0);
        }
        state = (state + 1) % 4;
    }

    private:

    uint32_t idx  = 0;
    uint8_t state = 0;
    uint8_t brightness = 32;

    void shift_counter(Output *r) {
        idx = (idx + 1) % r->get_length();
    }
};
