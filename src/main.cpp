#include <Arduino.h>

#include "evqueue.hpp"
#include "event_logger.hpp"
#include "ir.hpp"
#include "ble.hpp"
#include "led.hpp"
#include "output.hpp"


const int RELAY_PIN = 6;


Queues queues;
EventLogger event_logger;
Ir ir;
Ble ble;
Led led;
Output output(RELAY_PIN);


void setup() {
    Serial.begin(115200);

    ir.init();
    led.init();
    output.init();
    ble.init(queues);

    Serial.println("Initialisation complete");
}


void loop() {
    ir.tick(queues);
    ble.tick(queues);
    led.tick(queues);
    output.tick(queues);
    event_logger.tick(queues);
    delay(5);
}
