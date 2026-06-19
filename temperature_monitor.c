#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define ADC_MAX_VALUE 1023.0f
#define ADC_REFERENCE_VOLTAGE 5.0f
#define LM35_CELSIUS_PER_VOLT 100.0f

#define WARNING_TEMP_C 35.0f
#define DANGER_TEMP_C 45.0f

typedef enum {
    STATUS_NORMAL,
    STATUS_WARNING,
    STATUS_DANGER
} TemperatureStatus;

typedef enum {
    LED_GREEN,
    LED_YELLOW,
    LED_RED
} LedState;

typedef struct {
    float celsius;
    float fahrenheit;
    TemperatureStatus status;
    bool fan_on;
    bool buzzer_on;
    LedState led;
} MonitoringState;

static float adc_to_voltage(uint16_t adc_value)
{
    return ((float)adc_value * ADC_REFERENCE_VOLTAGE) / ADC_MAX_VALUE;
}

static float voltage_to_celsius(float voltage)
{
    return voltage * LM35_CELSIUS_PER_VOLT;
}

static float celsius_to_fahrenheit(float celsius)
{
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

static MonitoringState evaluate_temperature(uint16_t adc_value)
{
    float voltage = adc_to_voltage(adc_value);
    float celsius = voltage_to_celsius(voltage);

    MonitoringState state;
    state.celsius = celsius;
    state.fahrenheit = celsius_to_fahrenheit(celsius);

    if (celsius >= DANGER_TEMP_C) {
        state.status = STATUS_DANGER;
        state.fan_on = true;
        state.buzzer_on = true;
        state.led = LED_RED;
    } else if (celsius >= WARNING_TEMP_C) {
        state.status = STATUS_WARNING;
        state.fan_on = true;
        state.buzzer_on = false;
        state.led = LED_YELLOW;
    } else {
        state.status = STATUS_NORMAL;
        state.fan_on = false;
        state.buzzer_on = false;
        state.led = LED_GREEN;
    }

    return state;
}

static const char *status_to_text(TemperatureStatus status)
{
    switch (status) {
    case STATUS_NORMAL:
        return "NORMAL ";
    case STATUS_WARNING:
        return "WARNING";
    case STATUS_DANGER:
        return "DANGER ";
    default:
        return "UNKNOWN";
    }
}

static const char *led_to_text(LedState led)
{
    switch (led) {
    case LED_GREEN:
        return "GREEN ";
    case LED_YELLOW:
        return "YELLOW";
    case LED_RED:
        return "RED   ";
    default:
        return "OFF   ";
    }
}

static const char *on_off(bool value)
{
    return value ? "ON " : "OFF";
}

static void display_state(uint16_t adc_value, MonitoringState state)
{
    printf("ADC: %04u | %6.2f C | %6.2f F | %s | Fan: %s | Buzzer: %s | LED: %s\n",
           adc_value,
           state.celsius,
           state.fahrenheit,
           status_to_text(state.status),
           on_off(state.fan_on),
           on_off(state.buzzer_on),
           led_to_text(state.led));
}

int main(void)
{
    uint16_t sample_adc_values[] = {
        410, 512, 614, 716, 756, 820, 925, 970
    };
    size_t sample_count = sizeof(sample_adc_values) / sizeof(sample_adc_values[0]);

    printf("Temperature Monitoring System Using Embedded C\n");
    printf("Sensor model: LM35 | ADC: 10-bit | Vref: %.1fV\n\n", ADC_REFERENCE_VOLTAGE);

    for (size_t i = 0; i < sample_count; i++) {
        uint16_t adc_value = sample_adc_values[i];
        MonitoringState state = evaluate_temperature(adc_value);
        display_state(adc_value, state);
    }

    return 0;
}

