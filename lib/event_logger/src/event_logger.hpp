#pragma once

#include <Arduino.h>

#include "evqueue.hpp"


class EventLogger
{
private:
    size_t ir_tail, ble_tail;
public:
    void tick(Queues& queues);

    EventLogger():
        ir_tail(0),
        ble_tail(0)
    {};
};
