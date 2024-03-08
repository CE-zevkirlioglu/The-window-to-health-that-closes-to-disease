#include <Bonezegei_DHT11.h>
#include <Servo.h>

int sensorPin = A0; //Yağmur Sensörü bağlayacağımız pin
int esikDegeri = 100; //Su miktarı için eşik değeri
int buzzerPin = 8; //Buzzerı bağlayacağımız pin
int veri; //Yağmur Sensörden okuduğumuz değer
int closed = 1;
Servo sm1;
Bonezegei_DHT11  dhtINSIDE(3);
Bonezegei_DHT11  dhtOUTSIDE(2);

void setup() {
  Serial.begin(9600);
  dhtINSIDE.begin();
  dhtOUTSIDE.begin();
  sm1.attach(10);
  sm1.write(89);
  pinMode(buzzerPin, OUTPUT); //Buzzer bağladığımız pini OUTPUT olarak ayarlıyoruz.  
  Serial.println("Program başladı!");
  Serial.println("---------------------");
}

void loop() {
  delay(5000);
  dhtINSIDE.getData();
  dhtOUTSIDE.getData();
  veri = analogRead(sensorPin); //Yağmur Sensörden analog veriyi okuyoruz.

  float humidityIN = dhtINSIDE.getHumidity();
  float temperatureIN = dhtINSIDE.getTemperature();
  Serial.print("İçeri sıcaklığı: ");
  Serial.println(temperatureIN);
  Serial.print("İçeri nemi: ");
  Serial.println(humidityIN);

  float humidityOUT = dhtOUTSIDE.getHumidity();
  float temperatureOUT = dhtOUTSIDE.getTemperature();
  Serial.print("Dışarı sıcaklığı: ");
  Serial.println(temperatureOUT);
  Serial.print("Dışarı nemi: ");
  Serial.println(humidityOUT);
  Serial.print("Kapalı mı = ");
  Serial.println(closed);
  Serial.println(" ");
  delay(5000);

  if (veri > esikDegeri && closed != 1){ //Sensör verisi eşik değerini geçerse if içerisindeki kodlar uygulanır.
    
    digitalWrite(buzzerPin,HIGH);
    delay(2000);
    digitalWrite(buzzerPin,LOW);
    delay(2000);

    sm1.write(80); // kapanırken
    delay(3800);
    sm1.write(89);
    closed = 1;
  }
  else if(veri > esikDegeri && closed == 1){
    sm1.write(89);
    Serial.println("Yagmur var!");
    Serial.println(" ");
  }
  else { //Sensör verisi eşik değerinden küçük olursa if içerisindeki kodlar uygulanır.
      if((15 < temperatureOUT && temperatureOUT < 25) && (30 < humidityOUT && humidityOUT < 50)){
        if(closed == 1){
          digitalWrite(buzzerPin,HIGH);
          delay(500);
          digitalWrite(buzzerPin,LOW);
          delay(500);
          digitalWrite(buzzerPin,HIGH);
          delay(500);
          digitalWrite(buzzerPin,LOW);
          
          Serial.println("İçerisi ve Dışarısı ideal durumda!");
          Serial.println(" ");
          sm1.write(95); // açılırken
          delay(3950);
          sm1.write(89);
          closed = 0;
        }
      }
    else if(temperatureIN < 15 && temperatureIN < temperatureOUT){
      if(closed == 1){
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        delay(500);
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        
        Serial.println("İçerinin sıcaklığı idealden düşük!");
        Serial.println(" ");
        sm1.write(95); // açılırken
        delay(3950);
        sm1.write(89);
        closed = 0;
      }
    }
    else if(25 < temperatureIN && temperatureOUT < temperatureIN){
      if(closed == 1){
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        delay(500);
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);

        Serial.println("İçerinin sıcaklığı idealden yüksek!");
        Serial.println(" ");
        sm1.write(95); // açılırken
        delay(3950);
        sm1.write(89);
        closed = 0;
      }
    }
    else if(humidityIN > 50 && humidityOUT < humidityIN){
      if(closed == 1){
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        delay(500);
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        
        Serial.println("İçerinin nemi idealden yüksek!");
        Serial.println(" ");
        sm1.write(95); // açılırken
        delay(3950);
        sm1.write(89);
        closed = 0;
      }
    }
    else if(humidityIN < 30 && humidityOUT > humidityIN){
      if(closed == 1){
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        delay(500);
        digitalWrite(buzzerPin,HIGH);
        delay(500);
        digitalWrite(buzzerPin,LOW);
        
        Serial.println("İçerinin nemi idealden düşük!");
        Serial.println(" ");
        sm1.write(95); // açılırken
        delay(3950);
        sm1.write(89);
        closed = 0;
      }
    }
    else{
      if(closed == 0){
        digitalWrite(buzzerPin,HIGH);
        delay(2000);
        digitalWrite(buzzerPin,LOW);
        
        sm1.write(80); // kapanırken
        delay(3800);
        sm1.write(89);
        closed = 1;
      }
    }
  }
}
