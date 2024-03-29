#ifndef PROTOTYPE_WIDGET_HPP
#define PROTOTYPE_WIDGET_HPP

#include "event.hpp"
#include "world.hpp"

#include <QtGui/QWidget>

class QPaintEvent;
class QKeyEvent;

namespace prototype
{

  class Object;

  class Widget : public QWidget
  {
    Q_OBJECT

  public:

    Widget(EventQueue* e, World* w);

    void setFps(float fps) { m_fps = QString::number(fps, 'f', 2); }
    void render();

  signals:
    void renderLoopBack();

  protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

  private:

    void drawObject(prototype::Object& o, QPaintEvent* event);

    EventQueue* m_events;
    World* m_world;
    QString m_fps;
  };


}

#endif // PROTOTYPE_WIDGET_HPP
