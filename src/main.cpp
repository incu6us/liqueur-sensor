#include <Arduino.h>
#include <liqueur.h>

#ifdef CRITICAL_VOLTAGE_LEVEL
static unsigned int const min_voltage_level = CRITICAL_VOLTAGE_LEVEL;
#else
static unsigned int const min_voltage_level = 390;
#endif

#ifdef VOLTAGE_INDICATOR
static byte const voltage_indicator = VOLTAGE_INDICATOR;
#else
static byte const voltage_indicator = 3;
#endif

#ifdef WATER_INDICATOR
static byte const water_indicator = WATER_INDICATOR;
#else
static byte const water_indicator = 2;
#endif

#ifdef BUZZER
static byte const buzzer = BUZZER;
#else
static byte const buzzer = 4;
#endif


void startGreeting() {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
}

void lowVoltageAlarm() {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
}

void waterAlarm() {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(200);
}

bool isStarted;

void setup() {
    pinMode(voltage_indicator, INPUT);
    pinMode(water_indicator, INPUT);

    pinMode(buzzer, OUTPUT);
}

void loop(void) {
    if (!isStarted) {
        startGreeting();
        isStarted = true;
    }

    unsigned int voltage = analogRead(voltage_indicator);
    if (voltage < min_voltage_level) {
        lowVoltageAlarm();
    }

    if (digitalRead(water_indicator) == HIGH) {
        waterAlarm();
    }
}
