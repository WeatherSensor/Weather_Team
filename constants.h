#ifndef CONSTANTS_H 
#define CONSTANTS_H

constexpr char gatt_tool_command[] = "gatttool -b ";
constexpr char char_read_command[] = " --char-read -a 0x006e";

const int response_size = 1024;
const int max_int = 0x7FFF;
const int offset = 0x10000;
const float voltage_multiplier = 10.0;
const float voltage_offset = 2000.0;
const float temperature_divider = 100.0;
const int temperature_hex_length = 4;
const int temperature_hex_start = 4;
const int humidity_hex_start = 8;
const int voltage_hex_start = 20;
const int humidity_hex_length = 2;
const int voltage_hex_length = 2;
const size_t red_led_pin = 17;
const size_t green_led_pin = 4;
const size_t blue_led_pin = 18;
const size_t buzzer_pin = 25;
const size_t leds_blink_seconds = 500000;
const size_t cooler_pin = 12;
#endif

