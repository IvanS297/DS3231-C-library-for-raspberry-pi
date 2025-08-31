#ifndef DS3231_H
#define DS3231_H

#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DEVICE_ADDR         0x68

#define REG_SEC             0x00
#define REG_MIN             0x01
#define REG_HOUR            0x02
#define REG_DATE            0x04
#define REG_MON             0x05
#define REG_YEAR            0x06
#define REG_DOW             0x03

class DS3231
{
	private:
		int i2c_fd; // Файловый дескриптор I2C
		
		uint8_t dectobcd(const uint8_t val);
		uint8_t bcdtodec(const uint8_t val);

	public:
		void set_date(uint8_t date, uint8_t month, uint8_t year, uint8_t day);
		void read_date(uint8_t *date, uint8_t *month, uint8_t *year, uint8_t *day);
		
		void set_time(uint8_t hour, uint8_t min, uint8_t sec);
		void read_time(uint8_t *hour, uint8_t *min, uint8_t *sec);

		DS3231();
		~DS3231();
};

#endif
