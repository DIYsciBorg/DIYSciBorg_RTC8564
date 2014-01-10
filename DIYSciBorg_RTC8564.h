#ifndef DIYSciBorg_RTC8564_h
#define DIYSciBorg_RTC8564_h

#include "Arduino.h"
//#include "DIYSciBorg_RTC8564.cpp"

class RTC
{
  public:
    RTC();
    void setTime(unsigned int setYear, unsigned int setMonth, unsigned int setDay,
                 unsigned int setWeekday, unsigned int setHour, unsigned int setMinute,
                 unsigned int setSecond);
    void getTime();        // reads the time and returns it in a friendly format
    void startTimer(unsigned int mode, unsigned long term);
    void setAlarm();
    void start();
    void stop();
    int Year, Month, Day, Weekday, Hour, Minute, Second;
    int alarmHour, alarmMinute, alarmDay, alarmWeekday;   
   // int setYear, setMonth, setDay, setWeekday, setHour, setMinute, setSecond;
    int setalarmHour, setalarmMinute, setalarmDay, setalarmWeekeday;
    int setTimer;
    void reset();
    boolean isRunning();
  private:
    
};



#endif


