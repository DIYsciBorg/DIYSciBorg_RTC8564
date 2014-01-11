RTC8564-Arduino
===============

A complete library for the RTC8564 on Arduino

Be sure to check the demo sketch for complete details on how to use the library. Also, you must include the Wire library in your sketch!

The library should be pretty easy to use. Here is a basic description of each function. In place of the name you initiate the class with (RTC myClock in the example), I will just use RTC.something

RTC.reset()
Clears all registeres to safe values, clears timers and alarms, and sets the clock to January 1, 2010.

RTC.setTime(year, month, day, weekday, hour, minute, second)
Format the above as hex (0x13, 0x10.... etc). For the weekday, 0x00=Sunday

RTC.getTime()
Reads the clock data into a series of integer variables: Year, Month, Day, Weekday, Hour, Minute, Second.
I did enough formating to make the values useable as is. However, Year, Month and Day need the ",HEX" suffix when using print functions or the data appears unusual.

RTC:startTimer(mode, term)
Sets up a continuous periodic timer. mode indicates the period (0:second or 1:minute), while term indicates the number of counts to trigger the external interupt pin. For example, entering (1, 30) would trigger the interrupt every 30 minutes.

RTC:setAlarm()
This function not implemented yet!!!

RTC:start()
Manualry starts the clock. Useful when dynamically setting the time via user input

RTC:stop()
Used in conjunction with RTC:start()

RTC:isRunning()
Returns a boolean bit indicating the status of the clock when the Arduino powers up. Used to check if the backup battery kept the clock alive while the system was powered down. Usually used in the setup() function.
If the retuned value is 'false' then the clock was not running on power up and you should issue a reset, followed by setTime. If the retuned value is true, then you can trust that the clock time and settings are likely accurate after the power cycle.

