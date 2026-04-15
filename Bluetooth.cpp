#include "Bluetooth.h"

BluetoothCommand btCommand;

void BluetoothCommand::begin() {
    SerialBT.begin("Breadcrumb_BT"); // device name for pairing
    Serial.println("Bluetooth Started! Ready to pair.");
}

void BluetoothCommand::processCommands() {
    if (SerialBT.available()) {
        String msg = SerialBT.readStringUntil('\n');
        msg.trim(); // strip whitespace/newlines
        
        if (msg.length() > 0) {
            char cmdType = msg.charAt(0);
            float value = msg.substring(1).toFloat();

            switch (cmdType) {
                case 'P':
                case 'p':
                    Kp = value;
                    SerialBT.print("Kp updated to: "); SerialBT.println(Kp);
                    Serial.print("Kp updated to: "); Serial.println(Kp);
                    break;
                case 'I':
                case 'i':
                    Ki = value;
                    SerialBT.print("Ki updated to: "); SerialBT.println(Ki);
                    Serial.print("Ki updated to: "); Serial.println(Ki);
                    break;
                case 'D':
                case 'd':
                    Kd = value;
                    SerialBT.print("Kd updated to: "); SerialBT.println(Kd);
                    Serial.print("Kd updated to: "); Serial.println(Kd);
                    break;
                case 'S':
                case 's':
                    baseSpeed = (int)value;
                    SerialBT.print("baseSpeed updated to: "); SerialBT.println(baseSpeed);
                    Serial.print("baseSpeed updated to: "); Serial.println(baseSpeed);
                    break;
                default:
                    SerialBT.println("Unknown command. Use P<val>, I<val>, D<val>, S<val>");
                    break;
            }
        }
    }
}
