#ifndef PROTOYPE_TIMIR_HPP
#define PROTOYPE_TIMIR_HPP

#include <chrono>
#include <array>


namespace prototype
{

  template <typename T = double,
            std::size_t N = 5,
            typename Clock = std::chrono::system_clock,
            typename Duration = std::chrono::microseconds>
  class Timer
  {
    class FastCyclicBuffer
    {
    public:
      FastCyclicBuffer() : m_end(0), m_container() { m_container.fill(T()); }

      void push_back(const T& value) { m_container[m_end] = value; increaseindex(); }
      T getAvarege() const { T retval; for (std::size_t i=0; i<N; retval=m_container[i++]); return retval; }

    private:
      void increaseindex() { m_end++; if (m_end==N) m_end=0; }

      std::size_t m_end;
      std::array<T, N> m_container;
    };


  public:

    Timer() : m_start(), m_diffs() {}

    Timer(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(const Timer&) = delete;


    void registerStart() { m_start = Clock::now(); }
    void registerStop() {
      std::chrono::time_point<Clock> stop = Clock::now();
      T elapsed_time = std::chrono::duration_cast<Duration>(stop - m_start).count();
      m_diffs.push_back(elapsed_time);
    }

    T getAvaregeDelta() const { return (double)1 / m_diffs.getAvarege(); }

  private:

    std::chrono::time_point<Clock> m_start;
    FastCyclicBuffer m_diffs;
  };

} // namespace prototype

#endif // PROTOYPE_TIMIR_HPP

