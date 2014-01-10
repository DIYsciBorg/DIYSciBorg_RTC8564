#include "Arduino.h"
#include "DIYSciBorg_RTC8564.h"
#include  <Wire.h>
#include <WConstants.h>

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#define RTC8564_ID 0x51

#define BCD2Decimal(x)    (((x>>4)*10)+(x&0xf))
/* the above first takes the left most bits, shifts them right, (now 0-F, but will only
   ever be 0-6) and multiplies by 10. Then we mask the orginal firt 4 and add. */

/* RTC preset clock*/
#define RTC_SEC  0x00  // seconds
#define RTC_MIN  0x30  // minutes
#define RTC_HOUR 0x12  // hours
#define RTC_DAY  0x01  // day
#define RTC_WEEK 0x01  // weekday 00=sunday 06=saturday
#define RTC_MON  0x01  // month
#define RTC_YEAR 0x10  // year


RTC::RTC()
{      
  // variable init. We have no pins to set up
  // user must call RTC,begin in setup to start
}


boolean RTC::isRunning(){
  Wire.beginTransmission(RTC8564_ID);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(RTC8564_ID, 1);
    if(Wire.available()){
      uint8_t VLbit = Wire.read();
      return (VLbit & 0x80 ? false : true);
    }
    return false;
}


void RTC::stop(){
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x20);			// 00 Control 1, STOP=1
  Wire.endTransmission();
}

void RTC::start(){
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x00);			// 00 Control 1, STOP=0
  Wire.endTransmission();
}

void RTC::reset(){
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x20);			// 00 Control 1, STOP=1
    Wire.write(0x00);			// 01 Control 2
    Wire.write(RTC_SEC);		// 02 Seconds
    Wire.write(RTC_MIN);		// 03 Minutes
    Wire.write(RTC_HOUR);		// 04 Hours
    Wire.write(RTC_DAY);		// 05 Days
    Wire.write(RTC_WEEK);		// 06 Weekdays
    Wire.write(RTC_MON);		// 07 Months
    Wire.write(RTC_YEAR);		// 08 Years
    Wire.write(0x00);			// 09 Minutes Alarm
    Wire.write(0x00);			// 0A Hours Alarm
    Wire.write(0x00);			// 0B Days Alarm
    Wire.write(0x00);			// 0C Weekdays Alarm
    Wire.write(0x00);			// 0D CLKOUT
    Wire.write(0x00);			// 0E Timer control
    Wire.write(0x00);			// 0F Timer
  Wire.endTransmission();
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x00);			// 00 Control 1, STOP=0
  Wire.endTransmission();
}


void RTC::setTime(unsigned int setYear, unsigned int setMonth, unsigned int setDay,
                 unsigned int setWeekday, unsigned int setHour, unsigned int setMinute,
                 unsigned int setSecond){
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x20);			// 00 Control 1, STOP=1    stops the clock
    Wire.write(0x00);			// 01 Control 2
    Wire.write(setSecond);
    Wire.write(setMinute);
    Wire.write(setHour);
    Wire.write(setDay);
    Wire.write(setWeekday);
    Wire.write(setMonth);
    Wire.write(setYear);
    Wire.endTransmission();
  Wire.beginTransmission(RTC8564_ID);
    Wire.write(0x00);			// first send starting register 00 
    Wire.write(0x00);			// 00 Control 1, STOP=0   Restarts the clock
  Wire.endTransmission();
}



void RTC::getTime(){
  uint8_t buff[7];
  Wire.beginTransmission(RTC8564_ID);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(RTC8564_ID, 7);
  for(int i=0; i<7; i++){
    if(Wire.available()){
      buff[i] = Wire.read();
    }
  } 
  Second      = BCD2Decimal((buff[0] & 0x7f));
  Minute      = BCD2Decimal((buff[1] & 0x7f));
  Hour        = BCD2Decimal((buff[2] & 0x3f));
  Day         = (buff[3] & 0x3f);
  Weekday     = buff[4] & 0x07;
  Month       = (buff[5] & 0x1f);
  Year        = (0x2000+buff[6]);
  //Century      = (buff[5] & 0x80) ? 1 : 0; 
}

void RTC::startTimer(unsigned int mode, unsigned long term){
 Wire.beginTransmission(RTC8564_ID);
  Wire.write(0x01);
  Wire.write(0x11);
  Wire.endTransmission();
  
  byte buf[2];
  if (mode == 1){
    buf[0] = 0x83;
  } else {
    buf[0] = 0x82;
  }
  buf[1] = term;
  Wire.beginTransmission(RTC8564_ID);
  Wire.write(0x0E);
  Wire.write(buf, 2);
  Wire.endTransmission();
}



////   useful codes:
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}
