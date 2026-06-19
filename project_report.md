# Temperature Monitoring System Using Embedded C

## Objective

The aim of this project is to design a temperature monitoring system using embedded C.
The system reads temperature from a sensor, processes the value using a microcontroller,
and controls output devices such as an LCD, fan, LED, and buzzer based on the measured
temperature.

## Working Principle

An LM35 temperature sensor produces an analog voltage proportional to temperature.
For an LM35, the output is approximately `10 mV` per degree Celsius. The microcontroller
reads this analog voltage using its ADC module. The ADC value is converted into voltage,
then converted into temperature.

For a 10-bit ADC with a 5V reference:

```text
voltage = adc_value * 5.0 / 1023.0
temperature_c = voltage * 100.0
```

The system compares the temperature with predefined threshold values:

- Normal temperature: display normal status
- High temperature: turn ON fan and warning LED
- Critical temperature: turn ON fan, buzzer, and danger LED

## Required Components

- Microcontroller board
- LM35 temperature sensor
- 16x2 LCD display or serial display
- LED indicators
- Buzzer
- Fan or relay module
- Resistors and jumper wires
- 5V DC power supply

## Algorithm

1. Start the system.
2. Initialize ADC, display, and output pins.
3. Read the analog value from the temperature sensor.
4. Convert ADC value to voltage.
5. Convert voltage to temperature in Celsius.
6. Compare temperature with threshold values.
7. Display temperature and system status.
8. Control fan, LED, and buzzer.
9. Repeat continuously.

## Example Output

```text
ADC: 0614 | 30.01 C | 86.02 F | NORMAL  | Fan: OFF | Buzzer: OFF | LED: GREEN
ADC: 0756 | 36.95 C | 98.51 F | WARNING | Fan: ON  | Buzzer: OFF | LED: YELLOW
ADC: 0925 | 45.21 C | 113.38 F | DANGER | Fan: ON  | Buzzer: ON  | LED: RED
```

## Embedded Adaptation Notes

In a real microcontroller program, replace the simulated ADC function with the ADC
driver for your board. Replace the console `printf` display with LCD or UART display
functions. Replace the output print logic with GPIO writes.

Example mapping:

```c
fan_on = true;       // GPIO high to fan relay
buzzer_on = true;    // GPIO high to buzzer pin
led_state = LED_RED; // GPIO output to red LED
```

## Applications

- Industrial temperature monitoring
- Computer/server room monitoring
- Home automation
- Fire warning systems
- Greenhouse monitoring

