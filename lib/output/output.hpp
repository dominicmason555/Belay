#pragma once

#include <Arduino.h>

#include "evqueue.hpp"


struct OneShot
{
    bool is_set = false;
    uint32_t t_target = 0;
    uint8_t value = 0;
    void set(uint32_t delay, uint8_t value);
    bool check();
};


class Output
{
private:
    int pin_no;
    size_t ir_tail, ble_tail;
    OneShot power_cycle;
public:
    void init();
    void tick(Queues& queues);

    Output(int pin_no):
        ir_tail(0),
        ble_tail(0),
        pin_no(pin_no)
    {};
};
