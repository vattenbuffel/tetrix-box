#ifndef SERIAL_PRINT_H_
#define SERIAL_PRINT_H_
#include <Arduino.h>


void serial_printf(HardwareSerial& serial, const char* fmt, ...);

#endif