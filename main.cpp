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
PwmOut led(LED1);

int main() {
  displayInit();
  led.period_ms(3);
  Simulation.attach([]() { led.write(plant.Step(1) / 2); }, 10ms);
  while (true) {
    auto report = std::to_string(static_cast<int>(plant.Output() * 1000));
    std::cout << report << std::endl;
    displayCharPositionWrite(0, 0);
    displayStringWrite("Gonzalo Vaca");
    displayCharPositionWrite(0, 1);
    auto line = "Output: " + report;
    displayStringWrite(line.c_str());
    delay(500);
  }
}