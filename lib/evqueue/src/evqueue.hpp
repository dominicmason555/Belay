#pragma once

#include <array>


const size_t IR_Q_LEN = 16;
const size_t BLE_Q_LEN = 16;


template<class T, size_t N> class EvQueue
{
public:
    std::array<T, N> events;
    size_t head;

    EvQueue(): head(0){};
};


enum class ir_ev_t
{
    ZERO       = 0,
    ONE        = 1,
    TWO        = 2,
    THREE      = 3,
    FOUR       = 4,
    FIVE       = 5,
    SIX        = 6,
    SEVEN      = 7,
    EIGHT      = 8,
    NINE       = 9,
    STAR       = 10,
    CRUNCH     = 11,
    UP         = 12,
    DOWN       = 13,
    LEFT       = 14,
    RIGHT      = 15,
    OK         = 16
};


enum class ble_ev_t
{
    CONNECTED    = 0,
    DISCONNECTED = 1,
    LED_COLOUR   = 2,
    OUTPUT_WORD  = 3
};


struct ble_ev
{
    ble_ev_t type;
    uint32_t value;
};


using ir_q_t = EvQueue<ir_ev_t, IR_Q_LEN>;
using ble_q_t = EvQueue<ble_ev, BLE_Q_LEN>;

struct Queues
{
    ir_q_t ir_q;
    ble_q_t ble_q;
};

struct Tails
{
    size_t ir_tail;
    size_t ble_tail;

    Tails():
        ir_tail(0),
        ble_tail(0)
    {};
};
