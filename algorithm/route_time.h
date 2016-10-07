/**

    a simple time class to deal the time problem in the algorithm

*/


#ifndef _route_time_h
#define _route_time_h 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char _route_time_h_str[32];

struct Time {
    time_t timer;
    int year, month, day, hour, minute, second;

    /// default all 0
    Time() {
        year = month = day = hour = minute = second = 0;
    }

    Time(time_t timer) {
        this->timer = timer;
        tm *p = localtime(&timer);
        year = p->tm_year + 1900;
        month = p->tm_mon + 1;
        day = p->tm_mday;
        hour = p->tm_hour;
        minute = p->tm_min;
        second = p->tm_sec;
    }

    /// structure time use string like "2016-07-27 21:00:00"
    Time(const char *time_format_string) {
        year = atoi(time_format_string);
        month = atoi(time_format_string + 5);
        day = atoi(time_format_string + 8);
        hour = atoi(time_format_string + 11);
        minute = atoi(time_format_string + 14);
        second = atoi(time_format_string + 17);
        update();
    }

    void update() {
        tm time;
        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;
        time.tm_hour = hour;
        time.tm_min = minute;
        time.tm_sec = second;
        timer = mktime(&time);
    }

    /// reset time
    Time reset(int day_sec) {
        time_t dt = hour * 3600 + minute * 60 + second;
        time_t ret = timer - dt + day_sec;
        if(day_sec < dt)
            ret += 86400;
        return Time(ret);
    }
    
    /// copy structure
    Time(const Time &time) {
        hour = time.hour;
        minute = time.minute;
        second = time.second;
        update();
    }

    /// maximize the time
    void inf() {
        year = 9999;
        month = 12;
        day = 31;
        hour = 23;
        minute = 59;
        second = 59;
        update();
    }

    /// make the < operator
    bool operator< (const Time &time) const {
        return timer < time.timer;
    }

/**
    /// make the = operator with a format string
    Time operator= (const char *time_format_string) {
        if(strchr(time_format_string, '-')
            && atoi(time_format_string) != 0) {
            *this = Time(time_format_string);
        } else {
            year = month = day = 0;
            hour = atoi(time_format_string);
            minute = atoi(time_format_string + 3);
            second = atoi(time_format_string + 6);
        }
    }
*/
    
    /// useless because the copy structrue function
    /// make the = operator with a Time object
    Time operator= (const Time &time) {
        timer = time.timer;
        year = time.year;
        month = time.month;
        day = time.day;
        hour = time.hour;
        minute = time.minute;
        second = time.second;
    }

    ///make the - opeartor
    int operator- (const Time &time) {
        return timer - time.timer;
    }

    ///make the + opeartor
    Time operator+ (const int interval) {
        long t = timer + interval;
        return Time(t);
    }

    /// save as a string
    char *tostr() {
        sprintf(_route_time_h_str, "%04d-%02d-%02d %02d:%02d:%02d",
            year, month, day, hour, minute, second);
        return _route_time_h_str;
    }
};

//typedef struct Time Time;


#endif

