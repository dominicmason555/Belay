#pragma once

#include <Arduino.h>

#include <evqueue.hpp>


class Output
{
private:
    size_t ir_tail, ble_tail;
public:
    void init();
    void tick(Queues& queues);

    Output():
        ir_tail(0),
        ble_tail(0)
    {};
};
