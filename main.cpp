#include "AnalogIn.h"
#include "PinNames.h"
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

AnalogIn Actuator(A0);
float input{1};
int main() {
  displayInit();
  led1.period_ms(3);
  led2.period_ms(3);
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

    input = actuator;
    delay(500);
  }
}