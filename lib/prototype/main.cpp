#include "event.hpp"
#include "world.hpp"
#include "logic.hpp"
#include "widget.hpp"
#include "loop.hpp"

#include <cpp_utils/Logger.hpp>

#include <iostream>

#include <QtGui/QApplication>


int main(int argc, char* argv[])
{
  Logger::createInstance();
  Logger::init(std::cout);
  Logger::setLogLevel(Logger::FINEST);
  QApplication app(argc, argv);

  prototype::EventQueue events;
  prototype::World world;
  prototype::Logic logic(&events, &world);
  prototype::Widget widget(&events, &world);
  prototype::Loop loop(&logic, &widget);

  widget.show();
  loop.start();
  return app.exec();
}

