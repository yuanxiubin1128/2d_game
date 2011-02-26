#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

class Mutex 
{

public:

  Mutex(int kind = PTHREAD_MUTEX_DEFAULT);
  ~Mutex();

  void lock();
  void unlock();
  bool tryLock(int interval = 0);


private:

  Mutex(const Mutex& m);
  Mutex& operator=(const Mutex& m);

  pthread_mutex_t m_mutex;

};

#endif // MUTEX_HPP

