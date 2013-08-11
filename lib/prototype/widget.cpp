#include "widget.hpp"

#include "object.hpp"

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>


prototype::Widget::Widget(EventQueue* e, World* w)
  : m_events(e)
  , m_world(w)
  , m_fps()
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
  QPainter painter(this);

  painter.setPen(QPen(QColor("orange")));
  painter.drawText(QPointF(m_world->getWidth()-50, 20), m_fps);

  std::vector<Object>& objects = m_world->getObjectsRef();
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    drawObject(*it, event);
}

void prototype::Widget::keyPressEvent(QKeyEvent *event)
{
  Event e;

  e.m_id = std::string("polsen");
  e.m_speed = 100;  // pixel/s

  bool hit = false;

  /// @todo handle multiple pressed keys: up + right, etc
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

  QWidget::keyPressEvent(event);
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
  QColor orange = QColor("orange");

  painter.setPen(QPen(orange));
  painter.drawText(QPointF(o.m_x+5, o.m_y-15), QString::fromStdString(o.m_id));

  painter.setBrush(QBrush(orange));
  painter.setPen(QPen(Qt::black, 0));
  painter.drawEllipse(o.m_x-10, o.m_y-10, 20, 20);
}