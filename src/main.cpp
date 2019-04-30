#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <Arduino.h>
#include <liqueur.h>

#ifdef CRITICAL_VOLTAGE_LEVEL
static int const min_voltage_level = CRITICAL_VOLTAGE_LEVEL;
#else
static int const min_voltage_level = 390;
#endif

#ifdef VOLTAGE_INDICATOR
static unsigned int const voltage_indicator = VOLTAGE_INDICATOR;
#else
static unsigned int const voltage_indicator = 3;
#endif

#ifdef WATER_INDICATOR
static unsigned int const water_indicator = WATER_INDICATOR;
#else
static unsigned int const water_indicator = 2;
#endif

#ifdef BUZZER
static unsigned int const buzzer = BUZZER;
#else
static unsigned int const buzzer = 0;
#endif

#ifdef LED
static unsigned int const led = LED;
#else
static unsigned int const led = 4;
#endif

void startGreeting()
{
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(50);
}

void lowVoltageAlarm()
{
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void waterAlarm()
{
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(200);
}

bool isStarted;

void setup()
{
  pinMode(voltage_indicator, INPUT);
  pinMode(water_indicator, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop(void)
{
  if (!isStarted)
  {
    startGreeting();
    isStarted = true;
  }

  int voltage = analogRead(voltage_indicator);
  if (voltage < min_voltage_level)
  {
    lowVoltageAlarm();
  }

  int water = analogRead(water_indicator);
  if (water > 100)
  {
    waterAlarm();
  }
}
