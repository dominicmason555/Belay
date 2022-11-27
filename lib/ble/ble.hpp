#pragma once

#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "evqueue.hpp"

class MyServerCallbacks : public BLEServerCallbacks {
public:
    bool deviceConnected = false;
    bool oldDeviceConnected = false;

    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
    }
};


class MyCallbacks : public BLECharacteristicCallbacks {
    uint8_t led_r, led_g, led_b;
    Queues& queues;
    void onWrite(BLECharacteristic *pCharacteristic);
    public:
        MyCallbacks(Queues& queues): queues(queues){};
};


class Ble
{
private:
    BLEServer *pServer = NULL;
    BLECharacteristic *pTxCharacteristic;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;

public:
    void tick(Queues& queues);

    void init(Queues& queues);

    Ble():
        pServer(nullptr),
        pTxCharacteristic(nullptr)
    {};
};