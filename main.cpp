#include "PinNames.h"
#include "PwmOut.h"
#include "Ticker.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "modules/plant/Plant.h"
#include <iostream>
#include <string>

using namespace std::chrono;

Plant plant = Plant(1, 2, 0.496, 0.1);
Ticker Simulation;
PwmOut led(LED1);

int main() {
  led.period_ms(3);
  Simulation.attach([]() { led.write(plant.Step(1)/2); }, 10ms);
  while (true) {
    auto report = static_cast<int>(plant.Output() * 1000);
    std::cout << std::to_string(report) << std::endl;
    delay(500);
  }
}