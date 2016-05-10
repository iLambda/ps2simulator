#include "ps2simulator.h"

void ps2sim_init(unsigned char* datapin, unsigned char databit, unsigned char* clockpin, unsigned char clockbit) {
    // gather data_pin and clock_pin
    data_pin = datapin;
    data_bit = databit;
    clock_pin = clockpin;
    clock_bit = clockbit;
    // default them to high
    ps2sim_setdata(1);
    ps2sim_setclock(1);
}

void ps2sim_send(unsigned char buffer) {
  // put the clock and the data down
  ps2sim_setdata(0);
  ps2sim_setclock(1);
  delay_us(CLOCK_LENGTH_2);
  ps2sim_setdata(0);
  ps2sim_setclock(0);
  delay_us(CLOCK_LENGTH_2);

  // start sending bits
  i = 0;
  while (i < 8) {
    // set clock up
    ps2sim_setdata(buffer & (1 << i));
    ps2sim_setclock(1);
    delay_us(CLOCK_LENGTH_2);
    // down
    ps2sim_setclock(0);
    delay_us(CLOCK_LENGTH_2);
    // increment
    i++;
  }

  // parity bit
  ps2sim_setdata(ps2sim_oddparity(buffer));
  ps2sim_setclock(1);
  delay_us(CLOCK_LENGTH_2);
  ps2sim_setclock(0);
  delay_us(CLOCK_LENGTH_2);

  // end
  ps2sim_setdata(1);
  ps2sim_setclock(1);
  delay_us(CLOCK_LENGTH_2);
  ps2sim_setdata(1);
  ps2sim_setclock(0);
  delay_us(CLOCK_LENGTH_2);

  // put line back to high
  ps2sim_setdata(1);
  ps2sim_setclock(1);
}

unsigned char ps2sim_oddparity(unsigned char buffer) {
    unsigned parity = 0;
    while(buffer) {
      parity = 1 - parity;
      buffer = buffer & (buffer - 1);
    }
    return parity;
}

static void ps2sim_setdata(unsigned char value) {
  *data_pin ^= (-value ^ *data_pin) & (1 << data_bit);
}

static void ps2sim_setclock(unsigned char value) {
  *clock_pin ^= (-value ^ *clock_pin) & (1 << clock_bit);
}