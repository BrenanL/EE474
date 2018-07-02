#include <stdint.h>

#define RCGCPIO (*((unsigned int *)0x400FE608U))
#define GPIOF_BASE 0x40025000
#define GPIO_LOCK 0x4C4F434B
#define GPIO_PORTF_PUR_R (*((volatile uint32_t *)0x40025510))
#define GPIO_PORTF_CR_R (*((volatile uint32_t *)0x40025524))
#define GPIO_PORTF_LOCK_R (*((volatile uint32_t *)0x40025520))
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FC)))

int main() {
  // Configure Port
  RCGCPIO = 0x20;
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = 0xFF;
  GPIO_PORTF_PUR_R = 0x11;
  GPIOF_DIR = 0x0E;
  GPIOF_DEN = 0x1F;
  GPIOF_DATA = 0;

  while (1) {
    int check = GPIOF_DATA & 0x11; // Check buttons
    if (check == 0x01) {           // SW1 - RED
      GPIOF_DATA = (1<<1);
    }
    else if (check == 0x10) {      // SW2 - GREEN
      GPIOF_DATA = (1<<3);
    }
    else {
      GPIOF_DATA = 0;              // Otherwise off
    }
  }
}


