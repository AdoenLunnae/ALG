#ifndef CLASS_CLOCK
#define CLASS_CLOCK
    #include <cassert>
    #include <ctime>
    #include <cstdio>
    #include <cstring> //Para usar memset
    #include <iostream>
    #include <stdint.h> // Para usar uint64_t

    /*!\brief Models a clock to measure performace.*/
    class Clock{
    private:
    timespec _start;
    timespec _stop;
    bool _isStarted;
    public:
    Clock ();
    /*!\brief Starts the clock.
     * \pre not isStarted()
     * \post isStarted()
     */
    void start ();
    /*!\brief Re-starts the clock.
     * \post isStarted()
     */
    void restart ();

    /*!\brief Stops the clock.
     * \pre isStarted()
     * \post not isStarted()
     */
    void stop ();
    /*!\brief Is the clock started?
     * \return true if the clock is started currently.
     */
    bool isStarted() const;
    /*!\brief Return the elapsed time in mcs.*/
    uint64_t elapsed() const;
};
#endif
