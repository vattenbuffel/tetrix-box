#ifndef SERIAL_PRINT_H_
#define SERIAL_PRINT_H_
#include <Arduino.h>


void serial_printf(HardwareSerial& serial, const char* fmt, ...);
#define PRINTF(fmt, args) serial_printf(Serial, fmt, args)

#endif