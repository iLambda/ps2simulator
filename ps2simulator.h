#ifndef NULL
#define NULL 0
#endif
#define CLOCK_LENGTH_2 25

static unsigned char* data_pin = NULL;
static unsigned char data_bit = NULL;
static unsigned char* clock_pin = NULL;
static unsigned char clock_bit = NULL;
static unsigned char i = 0;

void ps2sim_init(unsigned char* datapin, unsigned char databit, unsigned char* clockpin, unsigned char clockbit);
void ps2sim_send(unsigned char buffer);
unsigned char ps2sim_oddparity(unsigned char buffer);
static void ps2sim_setdata(unsigned char value);
static void ps2sim_setclock(unsigned char value);
