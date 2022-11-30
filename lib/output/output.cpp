#include "output.hpp"


void OneShot::set(uint32_t delay, uint8_t new_value)
{
    is_set = true;
    t_target = millis() + delay;
    value = new_value;
}


bool OneShot::check()
{
    bool cooked = is_set && (t_target <= millis());
    if (cooked)
    {
        is_set = false;
    }
    return cooked;
}


void Output::init()
{
    pinMode(pin_no, OUTPUT);
}


void Output::tick(Queues& queues)
{
    // Log input events
    while (ir_tail != queues.ir_q.head)
    {
        switch (queues.ir_q.events[ir_tail])
        {
        case ir_ev_t::STAR:
            digitalWrite(pin_no, HIGH);
            break;
        case ir_ev_t::ZERO:
            Serial.println("Setting Power-Cycle One-Shot");
            digitalWrite(pin_no, LOW);
            power_cycle.set(1000, 1);
            break;
        case ir_ev_t::CRUNCH:
            digitalWrite(pin_no, LOW);
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
            digitalWrite(pin_no, event.value);
            break;
        default:
            break;
        }
        ble_tail = (ble_tail + 1) % BLE_Q_LEN;
    }
    // Check one-shot
    if (power_cycle.check())
    {
        digitalWrite(pin_no, power_cycle.value);
        Serial.print("Power-Cycle One-Shot fired: ");
        Serial.println(power_cycle.value);
    }
}
