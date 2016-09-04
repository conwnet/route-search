/**

	a simple time class to deal the time problem in the algorithm

*/


#ifndef _route_time_h
#define _route_time_h 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
		Time ti = Time(timer);
		if(day_sec / 3600 < ti.hour) ti.day += 1;
		ti.hour = day_sec / 3600; day_sec %= 3600;
		ti.minute = day_sec / 60; day_sec %= 60;
		ti.second = day_sec;
		ti.update();
		return ti;
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

	/// make the = operator with a format string
	Time operator= (const char *time_format_string) {
		if(strchr(time_format_string, '-')
			&& atoi(time_format_string) != 0) {
			timer = Time(time_format_string).timer;
		} else {
			year = month = day = 0;
			hour = atoi(time_format_string);
			minute = atoi(time_format_string + 3);
			second = atoi(time_format_string + 6);
		}
	}

	
/***
	/// useless because the copy structrue function
	/// make the = operator with a Time object
	Time operator= (const Time &time) {
		year = time.year;
		month = time.month;
		day = time.day;
		hour = time.hour;
		minute = time.minute;
		second = time.second;
	}
*/

	///make the - opeartor
	int operator- (const Time &time) {
		return timer - time.timer;
	}

	///make the - opeartor
	Time operator+ (const int interval) {
		int t = timer + interval;
		return Time(timer);
	}

	/// save as a string
	char *tostr(char *str) {
		sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d",
			year, month, day, hour, minute, second);
		return str;
	}
};

//typedef struct Time Time;


#endif







