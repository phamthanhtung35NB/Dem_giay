/*
shiftOut ra 1 Module LED 7 đoạn đơn
*/
//chân ST_CP của 74HC595 load
int latchPin = 8;
//chân SH_CP của 74HC595 cl_kl
int clockPin = 12;
//Chân DS của 74HC595  sdi
int dataPin = 11;
 ////////////////////////////////
 //chân ST_CP của 74HC595
int latchPin2 = 7;
//chân SH_CP của 74HC595
int clockPin2 = 13;
//Chân DS của 74HC595
int dataPin2 = 10;
// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt
 
//mảng có 10 số (từ 0-9) và 
const byte Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};
// byte led7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int doc, ngang;
int t=0;
String mauDoc,mauNgang;
// #define SCLK 13
// #define RCLK 12
// #define DIO 11

#define chan 6
/****************************************************************/
int sum =46;
int red =23;
int green =15;
int yellow= 3;
int trai =5;
/***************************************************************/

void setup() {
// pinMode(SCLK,OUTPUT);
// pinMode(RCLK,OUTPUT);
// pinMode(DIO,OUTPUT);
pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(chan, INPUT);
Serial.begin(9600);
}
void HienThiLED7doan(int Giatri, byte SoLed = 2) {
 // Khai báo mảng động để lưu các chữ số của Giatri
 byte *array = new byte[SoLed];
 // Lấy các chữ số của Giatri từ phải qua trái và lưu vào mảng array
 for (byte i = 0; i < SoLed; i++) {
   // Lấy chữ số hàng đơn vị của Giatri và gán vào array[i]
   array[i] = (byte)(Giatri % 10UL);
   // Loại bỏ chữ số hàng đơn vị của Giatri bằng cách chia cho 10
   Giatri = (unsigned long)(Giatri / 10UL);
 }
 // Đặt chân latchPin ở mức thấp để chuẩn bị gửi dữ liệu
 digitalWrite(latchPin, LOW);

 // Gửi dữ liệu cho từng LED 7 đoạn, bắt đầu từ LED cao nhất
 for (int i = 0; i <SoLed; i++) {
   // Gửi dữ liệu tương ứng với chữ số trong array[i] đến LED 7 đoạn
   shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]);
 }

 // Đặt chân latchPin ở mức cao để hiển thị dữ liệu trên LED 7 đoạn
 digitalWrite(latchPin, HIGH);

 // Giải phóng bộ nhớ đã cấp phát động cho mảng array
 free(array);
}
void HienThiLED7doan2(int Giatri, byte SoLed = 2) {
  byte *array= new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải quá trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri /10UL);
  }
  digitalWrite(latchPin2, LOW);
  for (int i = 0; i <SoLed; i++)
    shiftOut(dataPin2, clockPin2, MSBFIRST, Seg[array[i]]); 
  digitalWrite(latchPin2, HIGH);
  free(array);
}
void loop () {
  
    Serial.println("--------------------------------");
    if (digitalRead(chan)==HIGH){
//    if (1){
        t = 0;
        do {
            control();
        } while(t <= sum);
        
    }else{
      HienThiLED7doan(0,2);
    HienThiLED7doan2(0,2);
    }
}

void control() {

    if(t==0)
    {
      
        doc= trai; ngang= red;
        mauDoc="trai";
        mauNgang="do";
    }
    if(t == trai)
    {
      mauDoc="xanh";
        doc= green;
    }
    if(t==trai+green)
    {
      mauDoc="vang";
        doc= yellow;
    }
    if(t==trai+green+yellow)
    {
      mauDoc="do";
      mauNgang="trai";
        doc= red; ngang= trai;
    }

    if(t==trai+green+yellow+trai)
    {
      mauNgang="xanh";
        ngang = green;
    }
    if(t==trai+green+yellow+trai+green)
    {mauNgang="vang";
        ngang= yellow;
    }
    if(t==trai+green+yellow+trai+green+yellow)
    {
      mauNgang="do";
        ngang= red;
    }
    
    Serial.print("doc ");
    Serial.print(mauDoc);
    Serial.print(" ");
    Serial.print(doc);
    Serial.print("----ngang ");
    Serial.print(mauNgang);
    Serial.print(" ");
    Serial.print(ngang);
    Serial.println("");
    // demsoled(doc,ngang);
    HienThiLED7doan(doc,2);
    HienThiLED7doan2(ngang,2);
    delay(1000);
    t = t + 1;
    doc--;
    ngang--;
}
// void demsoled(int duong1, int duong2){
//    shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong2%10]);
//    shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong2/10]);

//    shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong1%10]);
//    shiftOut(DIO, SCLK, MSBFIRST, led7seg[duong1/10]);
               
//    digitalWrite(RCLK,LOW);
//    digitalWrite(RCLK,HIGH);
// }
