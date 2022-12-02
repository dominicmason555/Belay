#include "ble.hpp"

const std::string led_str = "led";
const std::string output_str = "out";

const char SERVICE_UUID[37] = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
const char CHARACTERISTIC_UUID_RX[37] = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
const char CHARACTERISTIC_UUID_TX[37] = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E";


void enqueue(ble_ev ev, Queues& queues)
{
    queues.ble_q.events[queues.ble_q.head] = ev;
    queues.ble_q.head = (queues.ble_q.head + 1) % BLE_Q_LEN;
}


void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string rxValue = pCharacteristic->getValue();
    ble_ev_t event_type = ble_ev_t::LED_COLOUR;
    uint32_t value = 0;

    if (rxValue.length() >= 3) {
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
        {
            Serial.print(rxValue[i]);
        }
        Serial.println();
        if (rxValue.compare(0, 3, led_str) == 0)
        {
            event_type = ble_ev_t::LED_COLOUR;
            value = strtoul(rxValue.substr(3).c_str(), nullptr, 16);
        }
        if (rxValue.compare(0, 3, output_str) == 0)
        {
            event_type = ble_ev_t::OUTPUT_WORD;
            value = strtoul(rxValue.substr(3).c_str(), nullptr, 16) > 0 ? 1 : 0;
        }
        enqueue({event_type, value}, queues);
    }
}


void Ble::init(Queues& queue)
{
    // Create the BLE Device
    BLEDevice::init("Dasonic Momson");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(
        new MyServerCallbacks(devicesConnected, oldDevicesConnected)
    );

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);

    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks(queue));

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");
}


void Ble::tick(Queues& queues)
{
    if (devicesConnected != oldDevicesConnected)
    {
        Serial.print("Devices now connected: ");
        Serial.println(devicesConnected);
        if (devicesConnected < MAX_DEVICES)
        {
            delay(500); // Wait for bluetooth stack
            pServer->startAdvertising(); // Restart advertising
            Serial.println("start advertising");
        }
        oldDevicesConnected = devicesConnected;
    }
    if (devicesConnected < oldDevicesConnected) {
        enqueue({ble_ev_t::DISCONNECTED, 0}, queues);
    }
    if (devicesConnected > oldDevicesConnected) {
        enqueue({ble_ev_t::CONNECTED, 0}, queues);
    }
}
