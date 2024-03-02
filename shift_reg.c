#include <stdio.h>
#include "pico/stdlib.h"

// SER - Serial Input
#define GP_DATA 6

// SRCLK - Shift Register Clock
// POSITIVE-EDGED triggered. Bits are PUSHED-IN on the rising edge of the
// clock.
#define GP_CLOCK 7

// RCLK - Register Clock / Latch
// When pulled HIGH, contents of the shift register are copied into the latch
// register, which eventually appears at the ouput.
#define GP_LATCH 8

// SRCLR - Shift Register Clear
// Reset the entire shift register. Active low pin, pull LOW to perform the
// reset.
#define GP_SRCLR 9

#define COMMON_ANODE 0
#define COMMON_CATHODE 1

// Shift Register => Digit Display
// Qa => PIN (a)
// Qb => PIN (b)
// Qc => PIN (c)
// Qd => PIN (d)
// Qe => PIN (e)
// Qf => PIN (f)
// Qg => PIN (g)
// Qh => PIN (DP)
// 
// Digit Display Schema
//   ---a---
//   -     -
//   f     b
//   -     -
//   ---g---
//   -     -
//   e     c
//   -     -
//   ---d--- DP
//
const uint num[10] = {
  252,                          // 0
  96,                           // 1
  218,                          // 2
  242,                          // 3
  102,                          // 4
  182,                          // 5
  190,                          // 6
  224,                          // 7
  254,                          // 8
  230                           // 9
};

void
sreg_init ()
{
  gpio_set_function (GP_DATA, GPIO_FUNC_SIO);
  gpio_set_function (GP_CLOCK, GPIO_FUNC_SIO);
  gpio_set_function (GP_LATCH, GPIO_FUNC_SIO);
  gpio_set_function (GP_SRCLR, GPIO_FUNC_SIO);

  gpio_set_dir (GP_DATA, true);
  gpio_set_dir (GP_CLOCK, true);
  gpio_set_dir (GP_LATCH, true);
  gpio_set_dir (GP_SRCLR, true);

  gpio_put (GP_SRCLR, 1);
  sleep_ms (100);
  gpio_put (GP_SRCLR, 0);
  sleep_ms (100);
  gpio_put (GP_SRCLR, 1);
  sleep_ms (100);
}

void
sreg_update (uint val, uint common_pin, uint decimal_point)
{
  uint number, digit;
  number = num[val];

  if (decimal_point)
    {
      number++;
    }


  gpio_put (GP_LATCH, 0);
  for (int i = 0; i < 8; i++)
    {
      digit = !!(number & (1 << i));

      if (common_pin == COMMON_ANODE)
        {
          digit = !digit;
        }
      gpio_put (GP_DATA, digit);
      gpio_put (GP_CLOCK, 1);
      sleep_us (1);
      gpio_put (GP_CLOCK, 0);
      sleep_us (1);
    }
  gpio_put (GP_LATCH, 1);
}

uint
add_decimal (uint val)
{
  val++;
  return val;
}

int
main ()
{
  stdio_init_all ();

  sreg_init ();

  while (1)
    {
      for (int index = 0; index < 10; index++)
        {
          printf ("Display number %d...\n", index);
          sreg_update (index, COMMON_ANODE, 0);
          sleep_ms (1000);

          printf ("Display number %d with decimal point...\n", index);
          sreg_update (index, COMMON_ANODE, 1);
          sleep_ms (1000);
        }
    }

  return 0;
}
