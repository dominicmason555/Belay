#include "led.hpp"


void Led::init()
{
    pixels.begin();
}


void Led::tick(Queues& queues)
{
    while (ble_tail != queues.ble_q.head)
    {
        ble_ev event = queues.ble_q.events[ble_tail];
        switch (event.type)
        {
        case ble_ev_t::LED_COLOUR:
        led_r = event.value >> 16;         // Top byte is R
        led_g = (event.value >> 8) & 0xFF; // Next byte is G
        led_b = event.value & 0xFF;        // Next byte is B
            break;
        default:
            break;
        }
        ble_tail = (ble_tail + 1) % BLE_Q_LEN;
    }

    if (rising) {
        breathe_phase++;
        if (breathe_phase > 99) {
            rising = false;
        }
    } else {
        breathe_phase--;
        if (breathe_phase < 1) {
            rising = true;
        }
    }

    uint8_t breathing_r = (led_r * breathe_phase) / 100;
    uint8_t breathing_g = (led_g * breathe_phase) / 100;
    uint8_t breathing_b = (led_b * breathe_phase) / 100;

    pixels.setPixelColor(0, breathing_r, breathing_g, breathing_b);
    pixels.show();
}
