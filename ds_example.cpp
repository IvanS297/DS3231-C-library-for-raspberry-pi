#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include "DS3231.h"

int main()
{
    printf("Инициализация DS3231...\n");
    
    // Создаем объект RTC
    DS3231 rtc;
    
    // Читаем время
    uint8_t hour, min, sec;
    rtc.read_time(&hour, &min, &sec);
    
    // Читаем дату
    uint8_t date, month, year, day;
    rtc.read_date(&date, &month, &year, &day);
    
    // Выводим время и дату
    printf("Текущее время: %02d:%02d:%02d\n", hour, min, sec);
    printf("Текущая дата: %02d.%02d.20%02d\n", date, month, year);
    printf("День недели: %d\n", day);
    
    // Пример установки времени (раскомментируйте при необходимости)
    // rtc.set_time(12, 30, 0); // Установить время 12:30:00
    // rtc.set_date(15, 5, 23, 2); // Установить дату 15.05.2023, вторник (2)
    
    return 0;
}
