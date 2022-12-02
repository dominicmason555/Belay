#pragma once

#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "evqueue.hpp"


const uint8_t MAX_DEVICES = 2;


class MyServerCallbacks : public BLEServerCallbacks {
private:
    uint8_t& devicesConnected;
    uint8_t& oldDevicesConnected;

public:
    void onConnect(BLEServer *pServer) {
        devicesConnected += 1;
    };

    void onDisconnect(BLEServer *pServer) {
        devicesConnected -= 1;
    }

    MyServerCallbacks(
        uint8_t& devicesConnected,
        uint8_t& oldDevicesConnected
    ): 
        devicesConnected(devicesConnected),
        oldDevicesConnected(oldDevicesConnected)
    {};
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
    BLEServer *pServer;
    BLECharacteristic *pTxCharacteristic;
    uint8_t devicesConnected = 0;
    uint8_t oldDevicesConnected = 0;

public:
    void tick(Queues& queues);

    void init(Queues& queues);

    Ble():
        pServer(nullptr),
        pTxCharacteristic(nullptr)
    {};
};