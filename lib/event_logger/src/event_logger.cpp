#include "event_logger.hpp"


void EventLogger::tick(Queues& queues)
{
    // Log input events
    while (ir_tail != queues.ir_q.head)
    {
        Serial.print("Key Event: ");
        switch (queues.ir_q.events[ir_tail])
        {
        case ir_ev_t::STAR:
            Serial.println("Star");
            break;
        case ir_ev_t::CRUNCH:
            Serial.println("Crunch");
            break;
        default:
            break;
        }
        ir_tail = (ir_tail + 1) % IR_Q_LEN;
    }
    // Log BLE events
    while (ble_tail != queues.ble_q.head)
    {
        Serial.print("BLE Event: ");
        ble_ev event = queues.ble_q.events[ble_tail];
        switch (event.type)
        {
        case ble_ev_t::CONNECTED:
            Serial.println("Connected");
            break;
        case ble_ev_t::DISCONNECTED:
            Serial.println("Disconnected");
            break;
        case ble_ev_t::LED_COLOUR:
            Serial.print("LED colour ");
            Serial.println(event.value);
            break;
        case ble_ev_t::OUTPUT_WORD:
            Serial.print("Output ");
            Serial.println(event.value);
            break;
        default:
            break;
        }
        ble_tail = (ble_tail + 1) % BLE_Q_LEN;
    }
}
