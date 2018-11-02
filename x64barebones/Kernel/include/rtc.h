#ifndef _RTC_H
#define _RTC_H

#include <stdint.h>

#define RTC_REGISTER_SELECTOR 0x70
#define RTC_DATA 0x71

void set_binary_time();
int get_hour();

#endif
