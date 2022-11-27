#pragma once

#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRtext.h>
#include <IRutils.h>

#include "evqueue.hpp"


class Ir
{
private:
    IRrecv receiver;
    decode_results results;

public:
    void tick(Queues& queues);

    void init();

    Ir(): receiver(8, 512, 15, true) {};
};
