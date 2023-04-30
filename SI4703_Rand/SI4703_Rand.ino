// si4703 FM tuner random glitch //

#include "hardware/structs/rosc.h"
#include "si4703.h"

#define FM_SDIO   6
#define FM_CLK    7
#define FM_SEN    5
#define FM_RST    13
 
si4703 radio(FM_SDIO, FM_CLK, FM_SEN, FM_RST);

int station[12] = {905, 921, 938, 975, 993, 1001, 1009, 1027, 1043, 1047, 1060, 1068};
 
static inline void seed_random_from_rosc(){
  
  uint32_t random = 0;
  uint32_t random_bit;
  volatile uint32_t *rnd_reg = (uint32_t *)(ROSC_BASE + ROSC_RANDOMBIT_OFFSET);

  for (int k = 0; k < 32; k++) {
    while (1) {
      random_bit = (*rnd_reg) & 1;
      if (random_bit != ((*rnd_reg) & 1)) break;
    }

    random = (random << 1) | random_bit;
  }
  
  srand(random);
}
 
void setup(){

  seed_random_from_rosc();
  radio.init();
  radio.si_volume(0); // 0...15 
  int t = rand()%12;
  radio.fm_start(station[t]);
  delay(500);
  radio.si_volume(1); // 0...15   

}

void loop(){

  radio.pr_si_write(0x03, rand());
  delay(100);

}