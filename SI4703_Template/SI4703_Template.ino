// si4703 FM tuner example //

#include "si4703.h"

#define FM_SDIO   6
#define FM_CLK    7
#define FM_SEN    5
#define FM_RST    13
 
si4703 radio(FM_SDIO, FM_CLK, FM_SEN, FM_RST);
 
int f_channel = 897; // divide 10 = dedicated MHz
 
void setup(){
  
  radio.init();
  Serial.begin(9600); 
 
  radio.fm_start(f_channel-760);
  radio.si_volume(1); // 0-15
  
}
 
void loop(){
  
  if(Serial.available()){
    char serial = Serial.read();
    if(serial == 'u'){radio.seek_up();}
    if(serial == 'd'){radio.seek_down();}
    }  
 
  Serial.print(" F = ");
  Serial.print(float((radio.nom_ch()+760.00)/10),2);
  Serial.print(" STC = ");
  Serial.print(radio.seach());
  Serial.print(" RSSI = ");
  Serial.print(radio.rss());
  Serial.print(" ST = ");
  Serial.println(radio.st_mn());

}