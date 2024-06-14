byte led7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int doc, ngang;
int t=0;
#define SCLK 2
#define RCLK 1
#define DIO 0

#define chan 3
/****************************************************************/
#define sum 46
#define red 23
#define green 15
#define yellow 3
#define trai 5
/***************************************************************/

void setup() {
pinMode(SCLK,OUTPUT);
pinMode(RCLK,OUTPUT);
pinMode(DIO,OUTPUT);
}
void loop () {
    
    if (digitalRead(chan)==HIGH){
        t = 0;
        do {
            control();
        } while(t <= sum);
        
    }
}
void control() {

    if(t==0)
    {
        doc= trai; ngang= red;
    }
    if(t == trai)
    {
        doc= green;
    }
    if(t==trai+green)
    {
        doc= yellow;
    }
    if(t==trai+green+yellow)
    {
        doc= red; ngang= trai;
    }





    if(t==trai+green+yellow+trai)
    {
        ngang = green;
    }
    if(t==trai+green+yellow+trai+green)
    {
        ngang= yellow;
    }
    if(t==trai+green+yellow+trai+green+yellow)
    {
        ngang= red;
    }

    demsoled(doc,ngang);
    delay(1000);
    t = t + 1;
    doc--;
    ngang--;
}
void demsoled(int duong1, int duong2){
   shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong2%10]);
   shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong2/10]);

   shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong1%10]);
   shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong1/10]);
               
   digitalWrite(RCLK,LOW);
   digitalWrite(RCLK,HIGH);
      }
