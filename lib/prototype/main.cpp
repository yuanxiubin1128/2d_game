#include "timer.hpp"
#include "event.hpp"
#include "world.hpp"
#include "logic.hpp"
#include "widget.hpp"

int main(int argc, char* argv[])
{
  prototype::Timer timer;
  prototype::EventQueue events;
  prototype::World world;

  prototype::Logic logic;
  logic.setEventQueue(&events);
  logic.setWorldState(&world);

  prototype::Widget widget;
  widget.setWorldState(&world);
  widget.setEventQueue(&events);

  while(1) {

    timer.registerStart();

    float dt = timer.getAvaregeDelta();
    logic.step(dt);
    widget.render();

    timer.registerStop();
  }

  return 0;
}

