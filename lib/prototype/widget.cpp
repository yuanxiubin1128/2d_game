#include "widget.hpp"

prototype::Widget::Widget(EventQueue* e, World* w)
  : m_events(e)
  , m_world(w)
{
  connect(this, SIGNAL(renderLoopBack()), this, SLOT(update()));
}

void prototype::Widget::render()
{
  emit renderLoopBack();
}