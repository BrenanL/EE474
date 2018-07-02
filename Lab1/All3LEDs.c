#define RCGCPIO (*((unsigned int *)0x400FE608U))
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FC)))

int count = 0;
int countto = 100000; // delay time
int main() {
  RCGCPIO = 0x20;
  GPIOF_DIR = 0x0E;
  GPIOF_DEN = 0x0E;
  while (1) {
    GPIOF_DATA = 0x04;     // Change color
    count = 0;
    while (count <countto) { // delay function
        ++count;
    }
    GPIOF_DATA = 0x08;      // Change color
    count = 0;
    while (count <countto) {
      ++count;
    }
    GPIOF_DATA = 0x02;     // Change color
    count = 0;
    while (count <countto) {
      ++count;
    }
  }
  return 0;
}
