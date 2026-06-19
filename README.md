# Temperature Monitoring System Using Embedded C

This project demonstrates a basic embedded temperature monitoring system written in C.
It reads a simulated ADC value from an LM35-style temperature sensor, converts it to
temperature in Celsius/Fahrenheit, displays the status, and activates warning outputs
when the temperature crosses configured thresholds.

## Features

- ADC-to-temperature conversion for an LM35 sensor
- Normal, warning, and danger temperature states
- Fan, LED, and buzzer control logic
- Portable C simulation for testing on a computer
- Easy to adapt to AVR, PIC, STM32, Arduino-style C, or other microcontrollers

## Files

- `src/temperature_monitor.c` - main C source code
- `docs/project_report.md` - project explanation, components, algorithm, and output

## Build And Run On PC

Use GCC or any standard C compiler:

```bash
gcc src/temperature_monitor.c -o temperature_monitor
./temperature_monitor
```

On Windows PowerShell with GCC installed:

```powershell
gcc .\src\temperature_monitor.c -o temperature_monitor.exe
.\temperature_monitor.exe
```

## Hardware Concept

Suggested components for a real embedded build:

- Microcontroller: ATmega328P, PIC16F877A, STM32, or similar
- Temperature sensor: LM35
- Display: 16x2 LCD or serial monitor
- Output devices: LED, buzzer, fan/relay module
- Power supply: 5V regulated supply

## Thresholds

The default thresholds are:

- Below `35 C`: normal
- `35 C` to below `45 C`: warning, fan ON
- `45 C` and above: danger, fan ON, buzzer ON, red LED ON

You can change these values in `src/temperature_monitor.c`.

