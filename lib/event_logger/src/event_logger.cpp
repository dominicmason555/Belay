#include "event_logger.hpp"


void EventLogger::tick(Queues& queues)
{
    // Log input events
    while (ir_tail != queues.ir_q.head)
    {
        Serial.print("Key Event: ");
        switch (queues.ir_q.events[ir_tail])
        {
        case ir_ev_t::ONE:
            Serial.println("One");
            break;
        case ir_ev_t::TWO:
            Serial.println("Two");
            break;
        case ir_ev_t::THREE:
            Serial.println("Three");
            break;
        case ir_ev_t::FOUR:
            Serial.println("Four");
            break;
        case ir_ev_t::FIVE:
            Serial.println("Five");
            break;
        case ir_ev_t::SIX:
            Serial.println("Six");
            break;
        case ir_ev_t::SEVEN:
            Serial.println("Seven");
            break;
        case ir_ev_t::EIGHT:
            Serial.println("Eight");
            break;
        case ir_ev_t::NINE:
            Serial.println("Nine");
            break;
        case ir_ev_t::STAR:
            Serial.println("Star");
            break;
        case ir_ev_t::ZERO:
            Serial.println("Zero");
            break;
        case ir_ev_t::CRUNCH:
            Serial.println("Crunch");
            break;
        case ir_ev_t::UP:
            Serial.println("Up");
            break;
        case ir_ev_t::LEFT:
            Serial.println("Left");
            break;
        case ir_ev_t::OK:
            Serial.println("Ok");
            break;
        case ir_ev_t::RIGHT:
            Serial.println("Right");
            break;
        case ir_ev_t::DOWN:
            Serial.println("Down");
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
