#include <LiquidCrystal.h>
#define BAT_PIN A0
#define WATER_PIN A1

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float b = 100.0;
int h = 0;
int m = -1;

int sensorValue         = 0;      // variable untuk menampung nilai baca dari sensor dalam bentuk integer
float tinggiAir         = 0;      // variabel untuk menampung ketinggian air
float sensorVoltage     = 0;      // untuk menampung nilai ketinggian air
int nilaiMax            = 1023;   // nilai "sensorValue" saat sensor terendam penuh kedalam air, bisa dirubah sesuai sensor dan jenis air yang anda pakai
float panjangSensor     = 4.0 ;   // 4.0 cm, bisa dirubah, menyesuikan dengan panjang sensor yang kalian gunakan

byte meter_s1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000
};
byte meter_s3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B11011,
  B11011
};
byte meter_s5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte meter_s7[8] = {
  B00000,
  B00000,
  B00000,
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
};
byte meter_s9[8] = {
  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte meter_s10[8] = {
  B00000,
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
};
byte meter_s20[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte meter_s30[8] = {
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
};

void writeMeter( int level, char label ) {
  lcd.setCursor(0,0);
  lcd.write( label );
  lcd.setCursor(1,0);
  lcd.write( ' ' );
  lcd.setCursor(2,0);
  lcd.write( ' ' );
  lcd.setCursor(3,0);
  lcd.write( ' ' );
  lcd.setCursor(4,0);
  lcd.write( ' ' );
  lcd.setCursor(5,0);
  lcd.write( ' ' );
  
  switch( level ){
   case 40:
         lcd.createChar(4, meter_s30);
         lcd.setCursor(5,0);
         lcd.write( 4 );
   case 30:
         lcd.createChar(4, meter_s30);
   case 20:
         if( level == 20 ) 
         lcd.createChar(4, meter_s20);
         lcd.setCursor(4,0);
         lcd.write( 4 );
   case 10:
         lcd.createChar(3, meter_s10);
   case 9:
         if( level == 9 ) 
         lcd.createChar(3, meter_s9);
         lcd.setCursor(3,0);
         lcd.write( 3 );
   case 7:
         lcd.createChar(2, meter_s7);
   case 5:
         if( level == 5 ) 
         lcd.createChar(2, meter_s5);
         lcd.setCursor(2,0);
         lcd.write( 2 );
   case 3:
         lcd.createChar(1, meter_s3);
   case 1:
         if( level == 1 )
         lcd.createChar(1, meter_s1);
         lcd.setCursor(1,0);
         lcd.write( 1 );
   case 0:
   default:
         break;
  }
}

void writeBattery(double a) {
  if (a >= 100.0) {
    lcd.setCursor(12, 0);
  } else if ((a < 100.0) && (a >= 10.0)) {
    lcd.setCursor(13, 0);
  } else {
    lcd.setCursor(14, 0);
  }
  
  lcd.print((int) a);
  lcd.print("%");
}

void writeTime(int hour, int minute) {
  if (hour < 10) {
    lcd.setCursor(7, 0);
  } else if ((hour >= 10) && (hour < 100)) {
    lcd.setCursor(6, 0);
  } else {
    return;
  }

  lcd.print(hour);
  lcd.print(":");

  lcd.setCursor(9, 0);
  if (minute < 10) {
    lcd.print(0);
  } else if ((minute >= 10) && (minute < 100)) {
    lcd.setCursor(9, 0);
  } else {
    return;
  }

  lcd.print(minute);
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  lcd.print("Nira: 100%, 4cm");
  writeMeter(9, 's');
  
  if (m == 59) {
    h++;
    m = 0;
  } else {
    m++;
  }
  
  writeTime(h, m);
  writeBattery(b);
  delay(1000);
  lcd.clear();
}
