


class Logic {


public:

  void Step(int delta_time);

private:
  EventQueue* m_events;
  World* m_world;
  Timer m_timer;
}
