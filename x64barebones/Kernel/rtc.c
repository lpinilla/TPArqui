#include <rtc.h>

extern uint8_t io_read(uint16_t port);
extern void io_write(uint16_t port, uint8_t data);

void set_binary_time(){
  io_write(RTC_REGISTER_SELECTOR, 0x0B);
  uint8_t aux = io_read(RTC_DATA);
  aux = aux | 0x04 ;
  io_write(RTC_DATA, aux);
}

int get_hour(){
  io_write(RTC_REGISTER_SELECTOR, 0x00);
  return (int)io_read(RTC_DATA);
}
