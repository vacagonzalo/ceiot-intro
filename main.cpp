#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "PinNamesTypes.h"
#include "PwmOut.h"
#include "Ticker.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "modules/display/display.h"
#include "modules/plant/Plant.h"
#include <iostream>
#include <string>
using namespace std::chrono;

Plant plant = Plant(1, 2, 0.496, 0.1);
Ticker Simulation;
PwmOut led1(LED1);
PwmOut led2(LED2);
DigitalOut led3(LED3);

AnalogIn Actuator(A0);
InterruptIn ModeSelector(PG_0);
InterruptIn OnOff(PD_1);
bool analogMode{true};
float onoff{0};
float input{1};

int main() {
  displayInit();
  led1.period_ms(3);
  led2.period_ms(3);

  ModeSelector.mode(PullDown);
  delay(10);
  ModeSelector.fall([]() { analogMode = !analogMode; });

  OnOff.mode(PullDown);
  delay(10);
  OnOff.fall([]() { onoff = (onoff == 0) ? 1 : 0; });

  Simulation.attach([]() { led1.write(plant.Step(input) / 2); }, 10ms);
  while (true) {
    auto report = std::to_string(static_cast<int>(plant.Output() * 1000));

    auto actuator = Actuator.read();
    led2.write(actuator);

    auto r_act =
        "Actuator: " + std::to_string(static_cast<int>(actuator * 1000));
    std::cout << report << std::endl;

    displayCharPositionWrite(0, 0);
    displayStringWrite(r_act.c_str());
    displayCharPositionWrite(0, 1);
    auto line = "Output: " + report;
    displayStringWrite(line.c_str());

    led3.write(analogMode ? 1 : 0);
    input = analogMode ? actuator : onoff;
    delay(50);
  }
}