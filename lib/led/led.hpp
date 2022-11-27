#pragma once

#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#include "evqueue.hpp"


class Led
{
private:
    size_t ir_tail, ble_tail;
    Adafruit_NeoPixel pixels;
    uint8_t led_r, led_g, led_b;
    uint8_t breathe_phase = 0;
    bool rising = true;
public:
    void init();
    void tick(Queues& queues);

    Led():
        ir_tail(0),
        ble_tail(0),
        pixels(1, 7, NEO_GRB + NEO_KHZ800),
        led_r(5),
        led_g(0),
        led_b(5)
    {};
};
