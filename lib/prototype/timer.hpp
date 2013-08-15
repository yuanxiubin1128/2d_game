#ifndef PROTOYPE_TIMIR_HPP
#define PROTOYPE_TIMIR_HPP

#include <chrono>
#include <array>


namespace prototype
{

  template <typename Duration_ = std::chrono::microseconds,
            typename Clock_ = std::chrono::system_clock,
            std::size_t N_ = 5>
  class Timer
  {
  public:

    typedef Duration_ Duration;
    typedef typename Duration_::rep RepT;
    typedef std::chrono::time_point<Clock_> TimePoint;

  private:

    class FastCyclicBuffer
    {
    public:
      FastCyclicBuffer() : m_end(0), m_container() { m_container.fill(RepT()); }

      void push_back(const RepT& value) { m_container[m_end] = value; increaseindex(); }
      RepT getSum() const { RepT retval = RepT(); for (std::size_t i=0; i<N_; retval+=m_container[i++]); return retval; }
      float getAvarege() const { return getSum() / float(N_); }

    private:
      void increaseindex() { m_end++; if (m_end==N_) m_end=0; }

      std::size_t m_end;
      std::array<RepT, N_> m_container;
    };

  public:

    Timer() : m_start(), m_diffs() {}

    Timer(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(const Timer&) = delete;

    void registerStart(TimePoint now = Clock_::now()) { m_start = now; }
    void registerStop(TimePoint now = Clock_::now()) {
      m_diffs.push_back(std::chrono::duration_cast<Duration>(now - m_start).count());
    }

    TimePoint getTime() const { return Clock_::now(); }

    float getAvaregeDelta() const { return m_diffs.getAvarege(); }


  private:

    TimePoint m_start;
    FastCyclicBuffer m_diffs;
  };

} // namespace prototype

#endif // PROTOYPE_TIMIR_HPP

