#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "DS3231.h"

DS3231::DS3231()
{
    wiringPiSetup(); // Инициализация wiringPi
    i2c_fd = wiringPiI2CSetup(DEVICE_ADDR); // Инициализация I2C
    
    if (i2c_fd == -1) {
        printf("Ошибка инициализации I2C!\n");
    }
}

DS3231::~DS3231()
{
    close(i2c_fd); // Закрываем I2C соединение
}

uint8_t DS3231::dectobcd(const uint8_t val)
{
    return ((val / 10 * 16) + (val % 10));
}

uint8_t DS3231::bcdtodec(const uint8_t val)
{
    return ((val / 16 * 10) + (val % 16));
}

void DS3231::set_date(uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    wiringPiI2CWriteReg8(i2c_fd, REG_YEAR, ((year / 10) << 4) | (year % 10));
    wiringPiI2CWriteReg8(i2c_fd, REG_MON, ((month / 10) << 4) | (month % 10));
    wiringPiI2CWriteReg8(i2c_fd, REG_DATE, dectobcd(date));
    wiringPiI2CWriteReg8(i2c_fd, REG_DOW, dectobcd(day));
}

void DS3231::read_date(uint8_t *date, uint8_t *month, uint8_t *year, uint8_t *day)
{
    *day = bcdtodec(wiringPiI2CReadReg8(i2c_fd, REG_DOW));
    *date = bcdtodec(wiringPiI2CReadReg8(i2c_fd, REG_DATE));
    *month = bcdtodec(wiringPiI2CReadReg8(i2c_fd, REG_MON));
    *year = bcdtodec(wiringPiI2CReadReg8(i2c_fd, REG_YEAR));
}

void DS3231::set_time(uint8_t hour, uint8_t min, uint8_t sec)
{
    wiringPiI2CWriteReg8(i2c_fd, REG_SEC, dectobcd(sec));
    wiringPiI2CWriteReg8(i2c_fd, REG_MIN, dectobcd(min));
    wiringPiI2CWriteReg8(i2c_fd, REG_HOUR, dectobcd(hour));
}

void DS3231::read_time(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
    uint8_t data = wiringPiI2CReadReg8(i2c_fd, REG_SEC);
    *sec = bcdtodec(data & 0x7F); // Игнорируем старший бит (бит остановки)
    
    data = wiringPiI2CReadReg8(i2c_fd, REG_MIN);
    *min = bcdtodec(data & 0x7F);
    
    data = wiringPiI2CReadReg8(i2c_fd, REG_HOUR);
    *hour = bcdtodec(data & 0x3F); // Игнорируем биты формата (12/24 часа)
}
