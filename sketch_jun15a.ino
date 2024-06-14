byte led7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int doc, ngang;
int t=0;
#define SCLK 13
#define RCLK 12
#define DIO 11

#define chan 3
/****************************************************************/
int sum =46;
int red =23;
int green =15;
int yellow= 3;
int trai =5;
/***************************************************************/

void setup() {
pinMode(SCLK,OUTPUT);
pinMode(RCLK,OUTPUT);
pinMode(DIO,OUTPUT);
Serial.begin(9600);
}
void loop () {
    Serial.println("--------------------------------");
//    if (digitalRead(chan)==HIGH){
    if (1){
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
    
    Serial.print("doc ");
    Serial.print(doc);
    Serial.print("----ngang ");
    Serial.print(ngang);
    Serial.println("");
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
