/**

	a simple time class to deal the time problem in the algorithm

*/


#ifndef _route_time_h
#define _route_time_h 1

#include <stdio.h>
#include <time.h>

struct Time {
	int time_stamp;
	
	/// default all 0
	Time() {
		year = month = day = hour = minute = second = 0;
	}
	
	/// structure time use string like "2016-07-27 21:00:00"
	Time(const char *time_format_string) {
		
	}

	/// copy structure
	Time(const Time &time) {
		year = time.year;
		month = time.month;
		day = time.day;
		hour = time.hour;
		minute = time.minute;
		second = time.second;
	}

	/// maximize the time
	void inf() {
		year = 9999;
		month = 12;
		day = 31;
		hour = 23;
		minute = 59;
		second = 59;
	}

	/// make the < operator
	bool operator< (const Time &time) const {
		if(year != time.year)
			return year < time.year;
		if(month != time.month)
			return month < time.month;
		if(day != time.day)
			return day < time.day;
		if(hour != time.hour)
			return hour < time.hour;
		if(minute != time.minute)
			return minute < time.minute;
		return second < time.second;
	}

	/// make the = operator with a format string
	Time operator= (const char *time_format_string) {
		int entire_string = 0;
		for(int i = 0; *(time_format_string + i); i++) {
			if(*(time_format_string + i) == '-') {
				entire_string = 1;
				break;
			}
		}
		if(entire_string) {
			sscanf(time_format_string,
				"%d-%d-%d %d:%d:%d",
				&year, &month, &day, &hour, &minute, &second);
		
		} else {
			sscanf(time_format_string,
				"%d:%d:%d", &hour, &minute, &second);
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
		int sum1 = hour * 3600 + minute * 60 + second;
		int sum2 = time.hour * 3600 + time.minute * 60 + time.second;
		return sum1 - sum2;
	}

	/// save as a string
	char *tostr(char *str) {
		sprintf(str, "%d-%d-%d %d:%d:%d",
			year, month, day, hour, minute, second);
	}
};

typedef struct Time Time;


#endif







