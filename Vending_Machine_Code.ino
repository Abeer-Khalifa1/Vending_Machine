#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define pb1 22
#define pb2 23
#define pb3 24
#define pb4 25
#define SS_PIN 53
#define RST_PIN 48
#define coin_sensor 26
#define check_sensor 27
#define buzzer 28

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Define the UID to compare with
byte targetUID[] = { 0xE1, 0x50, 0x83, 0x45 };  // E1 50 83 45
bool cardDetected = false;
int coinCounter = 0;
bool coin = 0;
int candy_button = 0;
bool flag = 0;
int price = 0;
bool flag2 = 0;
int corcb = 0;
bool check = 1;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
  mfrc522.PCD_Init();
  lcd.clear();

  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
  pinMode(pb3, INPUT);
  pinMode(pb4, INPUT);
  pinMode(coin_sensor, INPUT);
  pinMode(check_sensor, INPUT);
  pinMode(buzzer, OUTPUT);

  servo1.attach(7);
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);

  lcd.setCursor(0, 0);
  lcd.print("Welcome");

  lcd.setCursor(0, 1);
  lcd.print("Choose a snack");
  delay(500);
}

void loop() {
  if (digitalRead(pb1)) {
    Serial.println("Button 1 pressed");
    candy_button = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Price is $2");
    delay(500);
    price = 2;
    lcd.setCursor(0, 1);
    lcd.print("Card 1 or Coin 2");
    delay(500);

  } else if (digitalRead(pb2)) {
    Serial.println("Button 2 pressed");
    candy_button = 2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Price is $4");
    delay(500);
    price = 4;
    lcd.setCursor(0, 1);
    lcd.print("Card 1 or Coin 2");
    delay(500);

  } else if (digitalRead(pb3)) {
    Serial.println("Button 3 pressed");
    candy_button = 3;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Price is $3");
    delay(500);
    price = 3;
    lcd.setCursor(0, 1);
    lcd.print("Card 1 or Coin 2");
    delay(500);

  } else if (digitalRead(pb4)) {
    Serial.println("Button 4 pressed");
    candy_button = 4;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Price is $1");
    delay(500);
    price = 1;
    lcd.setCursor(0, 1);
    lcd.print("Card 1 or Coin 2");
    delay(500);
  }

  if (candy_button) {
    if (digitalRead(pb1) == 1) {
      corcb = 1;
    }
    if (digitalRead(pb2) == 1) {
      corcb = 2;
    }
    if (corcb == 1) {
      lcd.clear();
      lcd.print("Insert card");
      delay(500);
      if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        if (compareUID(mfrc522.uid.uidByte, targetUID, mfrc522.uid.size)) {
          Serial.println("Target card detected!");
          Serial.print("UID: ");
          printUID(mfrc522.uid.uidByte, mfrc522.uid.size);
          cardDetected = true;
          digitalWrite(buzzer, HIGH);
          delay(50);
          digitalWrite(buzzer, LOW);
          delay(50);
          digitalWrite(buzzer, HIGH);
          delay(50);
          digitalWrite(buzzer, LOW);
          delay(50);
          lcd.clear();
          lcd.print("Card Approved");
          delay(500);
          flag = 1;
          if (candy_button == 1) {
            candy1();
          } else if (candy_button == 2) {
            candy2();
          } else if (candy_button == 3) {
            candy3();
          } else if (candy_button == 4) {
            candy4();
          }
        }
      }
    } else if (corcb == 2) {
      coin = digitalRead(coin_sensor);
      Serial.println(coin);
      lcd.clear();
      lcd.print("Insert coins");
      delay(500);
      while (coinCounter < price) {
        coin = digitalRead(coin_sensor);
        if (!coin) {

          coinCounter = coinCounter + 1;
          lcd.clear();
          lcd.print("You inserted: ");
          lcd.setCursor(0, 1);
          lcd.print(coinCounter);
          lcd.setCursor(3, 1);
          lcd.print("coins");
          delay(500);
          coin = 1;
        }
        flag = 1;
      }
      if (candy_button == 1) {
        candy1();
      } else if (candy_button == 2) {
        candy2();
      } else if (candy_button == 3) {
        candy3();
      } else if (candy_button == 4) {
        candy4();
      }
    }
  }
}


// Function to compare UIDs
bool compareUID(byte array1[], byte array2[], int size) {
  for (int i = 0; i < size; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}

// Function to print UID
void printUID(byte array[], int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(array[i], HEX);
    Serial.print(" ");
  }
}

void candy1() {
  if (candy_button == 1 && flag) {
    lcd.clear();
    lcd.print("Please Wait");
    delay(500);
    servo1.write(180);
    delay(2000);
    servo1.write(90);
    cardDetected = false;
    coinCounter = 0;
    corcb=0;
    candy_button = 0;
    flag = 0;
    delay(2000);
    candy_delivered();
  }
}


void candy2() {
  if (candy_button == 2 && flag) {
    lcd.clear();
    lcd.print("Please Wait");
    delay(500);
    servo2.write(180);
    delay(2000);
    servo2.write(90);
    cardDetected = false;
    coinCounter = 0;
    candy_button = 0;
    corcb=0;
    flag = 0;
    candy_button = 0;
    delay(2000);
    candy_delivered();
  }
}

void candy3() {
  if (candy_button == 3 && flag) {
    lcd.clear();
    lcd.print("Please Wait");
    delay(500);
    servo3.write(180);
    delay(2000);
    servo3.write(90);
    cardDetected = false;
    corcb=0;
    coinCounter = 0;
    candy_button = 0;
    flag = 0;
    candy_button = 0;
    delay(2000);
    candy_delivered();
  }
}

void candy4() {
  if (candy_button == 4 && flag) {
    lcd.clear();
    lcd.print("Please Wait");
    delay(500);
    servo4.write(180);
    delay(2000);
    servo4.write(90);
    corcb=0;
    cardDetected = false;
    coinCounter = 0;
    candy_button = 0;
    flag = 0;
    candy_button = 0;
    delay(2000);
    candy_delivered();
  }
}

void candy_delivered() {
  check = digitalRead(check_sensor);
  if (!check) {
    lcd.clear();
    lcd.print("Enjoy");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Choose a snack");
    check = 1;
    corcb=0;
    cardDetected = false;
    coinCounter = 0;
    candy_button = 0;
    flag = 0;
    candy_button = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error");
    lcd.setCursor(0, 1);
    lcd.print("Contact Support");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Choose a snack");
    check = 1;
    corcb=0;
    cardDetected = false;
    coinCounter = 0;
    candy_button = 0;
    flag = 0;
    candy_button = 0;
  }
}