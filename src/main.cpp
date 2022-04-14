#include "button.h"
#include <Arduino.h>
#include "serial_print.h"
#include <SPI.h>
#include <Wire.h>

#define BUTTON_LEFT_GPIO 6
#define BUTTON_RIGHT_GPIO 7

button_t button_left, button_right;


void setup()
{
    Wire.begin();
    Serial.begin(115200);
    Serial.println("\nI2C Scanner");
}
 
void loop()
{
    byte error, address;
    int nDevices;
 
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 0; address <= 127; address++ )
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println(" !");
            nDevices++;
        }
        else if (error==4)
        {
            Serial.print("Unknow error at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.println(address,HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
    delay(30000);
 }