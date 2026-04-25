#include <cstdlib>
#include <cstdio>
#include <atomic>
#include <csignal>

std::atomic<bool> running(true);

void HandleCancellation(const int arg_signal_number)
{
  static_cast<void>(arg_signal_number);
  running = false;
}

int main(int argc, char** argv)
{
  // Disable stdout buffering
#if (_DEBUG == 1)
  setbuf(stdout, NULL);
#endif

  // End endless while-loop with Ctrl+C and call destructors
  std::signal(SIGINT, HandleCancellation);
  uint32_t counter = 0U;

  /* BMI160 address is 0x69
   * PIN connection
   * ('breakout board' <- 'rpi0 pin'):
   *   VIN <- 3.3V
   *   3V3 <- nothing
   *   GND <- GND
   *   SCL <- i2c clock (3.3V)
   *   SDA <- i2c data  (3.3V)
   *   CS  <- nothing
   *   SA0 <- nothing
   *
   * Register 0x00 -> CHIP ID
   */

  while (running)
  {
    printf("%u\n", counter);
    counter++;
    sleep(1U);
  }

  return 0;
}
