#ifndef PROTOTYPE_WIDGET_HPP
#define PROTOTYPE_WIDGET_HPP

#include "event.hpp"
#include "world.hpp"

#include <QtGui/QWidget>

namespace prototype
{

  class Widget : public QWidget
  {
    Q_OBJECT

  public:

    Widget(EventQueue* e, World* w);

    void render();

  signals:
    void renderLoopBack();

  private:
    EventQueue* m_events;
    World* m_world;
  };


}

#endif // PROTOTYPE_WIDGET_HPP
