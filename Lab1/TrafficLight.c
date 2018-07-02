#include <tm4c123gh6pm.h>
#include <stdint.h>

void LED_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x01;       // Activate clock for port A
  delay = SYSCTL_RCGC2_R;             // Allow time for clock to initialize

  GPIO_PORTA_PCTL_R &= ~0x00000F00;   // Regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x1C;        // Disable analog on PA2
  GPIO_PORTA_DIR_R |= 0x1C;          // Direction PA2 output
  GPIO_PORTA_AFSEL_R &= ~0x1C;        // regular port function
  GPIO_PORTA_DEN_R |= 0x1C;           // Enable digital port
}

void Switch_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001;       // Activate clock for port A
  delay = SYSCTL_RCGC2_R;             // Allow time for clock to initialize
  GPIO_PORTA_AMSEL_R &= ~0x60;        // Disable analog on PA5
  GPIO_PORTA_PCTL_R &= ~0x00F00000;   // PCTL GPIO on PA5
  GPIO_PORTA_DIR_R &= ~0x60;          // Direction PA5 input
  GPIO_PORTA_AFSEL_R &= ~0x60;        // PA5 regular port function
  GPIO_PORTA_DEN_R |= 0x60;           // Enable PA5 digital port

}

// Switch check functions
unsigned long Switch1(void) {
  
  return (GPIO_PORTA_DATA_R&0x20);
}
unsigned long Switch2(void) {
  
  return (GPIO_PORTA_DATA_R&0x40);
}

// LED On/Off functions
void LEDG_On(void) {
  GPIO_PORTA_DATA_R |= 0x04;
}
void LEDG_Off(void) {
  GPIO_PORTA_DATA_R &= ~0x04;
}
void LEDY_On(void) {
  GPIO_PORTA_DATA_R |= 0x08;
}
void LEDY_Off(void) {
  GPIO_PORTA_DATA_R &= ~0x08;
}
void LEDR_On(void) {
  GPIO_PORTA_DATA_R |= 0x10;
}
void LEDR_Off(void) {
  GPIO_PORTA_DATA_R &= ~0x10;
}

// Delay function
void delay(void) {  
  for (int i = 0; i <2000000; i++) {
  }
}

// Set state functions
void All_Off(void) {
  LEDG_Off();
  LEDY_Off();
  LEDR_Off();
}
void RED(void) {
  LEDG_Off();
  LEDY_Off();
  LEDR_On();
}
void GREEN(void) {
  LEDG_On();
  LEDY_Off();
  LEDR_Off();
}
void YELLOW(void) {
  LEDG_Off();
  LEDY_On();
  LEDR_Off();
}

int main() {
  Switch_Init();
  LED_Init();
  All_Off();
  int state = 0; // 0 - Red, 1 - Green, 2 - Yellow
  while(1) {
    switch(state) {
      case(0): 
        RED();
        delay();
        if (Switch2() || Switch1()) { //Override buttons
          state = 0;
          break;
        } else { // Go Green
          state = 1;
        }
      break;
      case(1):
        GREEN();
        delay();
        if (Switch1()) { // Stop button, go Red
          state = 0;
          break;
        } else if (Switch2()) { // Passenger, go yellow
          state = 2;
          break;
        } else {
          state = 0;
          break; }
      break;
      case(2):  
        YELLOW();
        delay();
        state = 0;   // Always go red
      break;
    }
  }
}     