#include "output.hpp"


void Output::init()
{
    pinMode(6, OUTPUT);
}

void Output::tick(Queues& queues)
{
    // Log input events
    while (ir_tail != queues.ir_q.head)
    {
        switch (queues.ir_q.events[ir_tail])
        {
        case ir_ev_t::STAR:
            digitalWrite(6, HIGH);
            break;
        case ir_ev_t::CRUNCH:
            digitalWrite(6, LOW);
            break;
        default:
            break;
        }
        ir_tail = (ir_tail + 1) % IR_Q_LEN;
    }
    // Log BLE events
    while (ble_tail != queues.ble_q.head)
    {
        ble_ev event = queues.ble_q.events[ble_tail];
        switch (event.type)
        {
        case ble_ev_t::OUTPUT_WORD:
            digitalWrite(6, event.value);
            break;
        default:
            break;
        }
        ble_tail = (ble_tail + 1) % BLE_Q_LEN;
    }
}
