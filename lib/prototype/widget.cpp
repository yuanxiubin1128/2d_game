#include "widget.hpp"

#include "object.hpp"

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>


prototype::Widget::Widget(EventQueue* e, World* w)
  : m_events(e)
  , m_world(w)
{
  setWindowTitle("2d_game");
  resize(m_world->getWidth(), m_world->getHeight());

  connect(this, SIGNAL(renderLoopBack()), this, SLOT(update()));
}

void prototype::Widget::render()
{
  emit renderLoopBack();
}

void prototype::Widget::paintEvent(QPaintEvent *event)
{
  std::vector<Object> objects = m_world->getObjects();
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    drawObject(*it, event);
}

void prototype::Widget::keyPressEvent(QKeyEvent *event)
{
  Event e;

  e.m_id = std::string("polsen");
  e.m_speed = 1;

  bool hit = false;

  switch (event->key()) {
    case Qt::Key_Up    : e.m_direction = 0; hit = true; break;
    case Qt::Key_Right : e.m_direction = 2; hit = true; break;
    case Qt::Key_Down  : e.m_direction = 4; hit = true; break;
    case Qt::Key_Left  : e.m_direction = 6; hit = true; break;
    default: break;
  }

  if (hit == true) {
    m_events->push(e);
    return;
  }

  Widget::keyPressEvent(event);
}

void prototype::Widget::keyReleaseEvent(QKeyEvent *event)
{
  Event e;

  e.m_id = std::string("polsen");
  e.m_speed = 0;
  e.m_direction = 8; // none

  m_events->push(e);
}

void prototype::Widget::drawObject(Object& o, QPaintEvent* event)
{
  QPainter painter(this);

//   painter.setBrushOrigin(o.m_x, o.m_y);
  painter.translate(width() / 2, height() / 2);

  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::darkGray);
  painter.drawEllipse(-7, -7, 20, 20);

  QRadialGradient gradient(-3, -3, 10);
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::darkYellow);

  painter.setBrush(gradient);
  painter.setPen(QPen(Qt::black, 0));
  painter.drawEllipse(-10, -10, 20, 20);
}