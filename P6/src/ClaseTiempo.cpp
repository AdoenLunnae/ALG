/*!a pesar de que se puede trabajar con nanosegundos, se devuelven los tiempos en microsegundos*/

// http://man7.org/linux/man-pages/man2/clock_gettime.2.html
/*
Data Type: struct timespec

    The struct timespec structure represents an elapsed time. It is declared in sys/time.h and has the following members:

    time_t tv_sec
       This represents the number of whole seconds of elapsed time.
    long  tv_nsec
    This is the rest of the elapsed time (a fraction of a second), represented as the number of nanoseconds.
*/

// Ojo hay que compilar g++ -Wall main.cpp -lrt para incluir las librerías de tiempos.


#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring> //Para usar memset
#include <iostream>
#include <stdint.h> // Para usar uint64_t
#include "ClaseTiempo.hpp"
 /*!\brief Models a clock to measure performace.*/
Clock::Clock (){
  memset(&_start,0,sizeof(timespec));
  memset(&_stop,0,sizeof(timespec));
  _isStarted=false;
}

void Clock::start (){
  assert (!isStarted());
  clock_gettime (CLOCK_REALTIME, &_start);
  _isStarted=true;
}

void Clock::restart (){
  clock_gettime (CLOCK_REALTIME, &_start);
  _isStarted=true;
}

void Clock::stop (){
  assert (_isStarted);
  clock_gettime (CLOCK_REALTIME, &_stop);
  _isStarted=false;
}

bool Clock::isStarted() const{
  return _isStarted;
}

uint64_t Clock::elapsed() const{
  assert (!_isStarted);
  uint64_t startT = (uint64_t)_start.tv_sec * 1000000LL + (uint64_t)_start.tv_nsec / 1000LL;
  uint64_t stopT = (uint64_t)_stop.tv_sec * 1000000LL + (uint64_t)_stop.tv_nsec / 1000LL;
  return stopT-startT;
}
