#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Config.h"

class BluetoothCommand {
private:
    BluetoothSerial SerialBT;
public:
    void begin();
    void processCommands();
};

extern BluetoothCommand btCommand;

#endif
