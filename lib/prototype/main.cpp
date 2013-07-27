

#include <timer.hpp>


int
main(int argc, char* argv[]) {


  Timer timer;
  EventQueue events;
  World world;

  Logic logic();
  logic.setEventQueue(events);
  logic.setWorldState(world);

  Widget widget;
  widget.setWorldState(world);
  widget.setEventQueue(events);

  widget.show();

  for( ;; ) {
  
    timer.start();

    int dt = timer.GetAvgTime();
    logic.Step(dt);
  
    widget.render();

    timer.stop();
  }


}

