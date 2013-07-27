

class timer {

public:
  void RegisterStart();
  void RegisterStop();

  int GetAvgDelta();

private:
  int m_time;
  queue<float> m_diffs;

}
