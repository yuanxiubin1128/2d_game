#include <subsystem_1/dummy_class.hpp>
#include <world/world.hpp>

int
main(int argc, char* argv[])
{
  subsystem_1::Dummy_class d;

  world::World world("res/first_map.png");
  
  
  return 0;
}
