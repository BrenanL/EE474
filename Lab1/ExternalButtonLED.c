#include <tm4c123gh6pm.h>
#include <stdint.h>

void LED_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x01;       // Activate clock for port A
  delay = SYSCTL_RCGC2_R;             // Allow time for clock to initialize

  GPIO_PORTA_PCTL_R &= ~0x00000F00;   // Regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x04;        // Disable analog on PA2
  GPIO_PORTA_DIR_R |= 0x04;          // Direction PA2 output
  GPIO_PORTA_AFSEL_R &= ~0x04;        // regular port function
  GPIO_PORTA_DEN_R |= 0x04;           // Enable digital port
}

void Switch_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001;       // Activate clock for port A
  delay = SYSCTL_RCGC2_R;             // Allow time for clock to initialize
  GPIO_PORTA_AMSEL_R &= ~0x20;        // Disable analog on PA5
  GPIO_PORTA_PCTL_R &= ~0x00F00000;   // PCTL GPIO on PA5
  GPIO_PORTA_DIR_R &= ~0x20;          // Direction PA5 input
  GPIO_PORTA_AFSEL_R &= ~0x20;        // PA5 regular port function
  GPIO_PORTA_DEN_R |= 0x20;           // Enable PA5 digital port

}

// Switch check functions
unsigned long Switch1(void) {
  
  return (GPIO_PORTA_DATA_R&0x20);
}

// LED On/Off functions
void LED_On(void) {
  GPIO_PORTA_DATA_R |= 0x04;
}
void LED_Off(void) {
  GPIO_PORTA_DATA_R &= ~0x04;
}

int main() {
  Switch_Init();
  LED_Init();
  LED_Off();
  while(1) {
    if (Switch1()) {
      LED_On();
    } else {
      LED_Off();
    }
  }
}     