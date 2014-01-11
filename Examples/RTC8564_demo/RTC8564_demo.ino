/* RTC8564 library demo
	Written by Emery Premeaux
	www.DIYSciB.org
	
	This project is open source
    Feel free to use, modify or redistribute
    It would be nice if you keep the original
    author information above.  ;)
      
    Written on Arduino v 1.0.4
*/

#include "DIYSciBorg_RTC8564.h"
#include  <Wire.h>

RTC myClock;
/* periodic timer interval unit  0:seconds/1:minute */
#define RTC_INTERRUPT_MODE 0
/* measurement interval(RTC interrupt interval) */
#define RTC_INTERRUPT_TERM 10
/* 0, 10 will cause an interrupt on the clock output every 10 seconds */



void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  /* If clock was running at power up, it will continue with 
     that time.
     If clock was not running, it will be reset with safe values,
     then the current time will be loaded with setTime
   */
  int Status = myClock.isRunning();
    // if unset, then set the clock
    if (Status == false){
      myClock.reset();   // sets all registeres in stable states
                  //year, month, day, weekday, hour, minute, second
      myClock.setTime(0x13, 0x01, 0x10, 0x05, 0x14, 0x20, 0x00);
    }
    // If it is running, leave it alone
  // Now lets enable the interrupt timer
  myClock.startTimer(RTC_INTERRUPT_MODE, RTC_INTERRUPT_TERM);
}


void serialEvent(){
  while(Serial.available()){
    char inChar =(char)Serial.read();
      switch (inChar){
        case 's':
          myClock.stop();
          break;
        case 'r':
          myClock.start();
          break;}
  }
}


void loop(){
  myClock.getTime();
  
 // Serial.println("myClock says...");
  Serial.print(myClock.Year, HEX);
  Serial.print("/");
  Serial.print(myClock.Month, HEX);
  Serial.print("/");
  Serial.print(myClock.Day, HEX);
  Serial.print(" ");
  Serial.print(GetWeekday());
  Serial.print(" ");
  Serial.print(myClock.Hour);
  Serial.print(":");
  Serial.print(myClock.Minute);
  Serial.print(":");
  Serial.println(myClock.Second);
//  Serial.print("VL bit status: ");
//  Serial.println(RTCstatus);
  delay(1000);
}


String GetWeekday(){
  switch (myClock.Weekday){
    case 0:  //Sunday
      return("Sunday");
      break;
    case 1:  //Monday
      return("Monday");
      break;
    case 2:  //Tuesday
      return("Tuesday");
      break;
    case 3:  //Wednesday
      return("Wednesday");
      break;
    case 4:  //Thursday
      return("Thursday");
      break;
    case 5:  //Friday
      return("Friday");
      break;
    case 6:  //Saturday
      return("Saturday");
      break;
    default:
      return("UNKNOWN!");
      break;
  }
}
