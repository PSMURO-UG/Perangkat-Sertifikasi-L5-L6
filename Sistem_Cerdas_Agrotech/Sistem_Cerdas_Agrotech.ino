//Melengkapi Program yang Sudah Diberi Tanda "###" & 
//Menyesuaikan Program Hingga Menghasilkan Keluaran yang Diinginkan
//Sampai Tidak Menampilkan Error

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>
#include <ThingSpeak.h>

#define DHTPIN    D6        // DHT11 Sensor on Digital Pin 
#define DHTTYPE   DHT11     // DHT TYPE
#define fanRelay  D5        // Fan Relay on Digital Pin
#define pumpRelay D4        // Pump Relay on Digital Pin
int soilPin = A0;           // Soil Moisture Sensor on Analog Pin

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(###, ###, ###);
elapsedMillis inputMillis;
elapsedMillis outputMillis;
elapsedMillis controlMillis;
elapsedMillis uploadMillis;
WifiClient client;

float soilRawValue = 0;   // Variable to Store the Soil Sensor Raw Analog value
int soilPercentage = 0;   // Variable to Store the Percentage Soil Value
int RT, RH;               // Variable to Store Room Temperature & Room Humidity Value

const char* apiKey        = "###";  // ThingSpeak API Key 
const char* wifiSSID      = "###";  // WiFi / Hotspot SSID
const char* wifiPASS      = "###";  // WiFi / Hotspot Password
const unsigned long chID  = ###;    // ThingSpeak Channel ID

//Multi Task Interval
const unsigned long inputInterval     = 2000;   // Sensor Readings (ms)
const unsigned long outputInterval    = 3000;   // LCD Display (ms)
const unsigned long controlInterval   = 4000;   // Relay Control (ms)
const unsigned long uploadInterval    = 5000;   // ThingSpeak POST (ms)

void setup() 
{
  Serial.begin(###);
  dht.begin();
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("C: ");
  lcd.setCursor(9, 0);
  lcd.print("H: ");
  lcd.setCursor(0, 1);
  lcd.print("W: ");

  ###(fanRelay,OUTPUT);
  ###(pumpRelay,OUTPUT);

  ###(fanRelay,HIGH);
  ###(pumpRelay,HIGH);

  WiFi.begin(###, ###);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);
}

void loop() 
{
  if (inputMillis >= inputInterval) 
  {
    ### = dht.readHumidity();
    ### = dht.readTemperature();         
    
    soilRawValue    = analogRead(soilPin);      
    soilPercentage  = map(soilRawValue, 0, 1023, ###, ###);
    
    inputMillis = 0;
  }

  if (outputMillis >= outputInterval) 
  {
    Serial.print("Room Temperature: ");
    Serial.print(###);
    Serial.println(" *C\t");
    Serial.print("Room Humidity: ");
    Serial.print(###);
    Serial.println(" %");
    Serial.print("Soil Wetness : ");
    Serial.print(###);
    Serial.println(" %");
    
    lcd.setCursor(3, 0);
    lcd.print(###);
    lcd.print(char(223));
    lcd.print("C");
    lcd.setCursor(13, 0);
    lcd.print(###);
    lcd.print("%");
    lcd.setCursor(9, 1);
    lcd.print(###);
    lcd.print("%");

    outputMillis = 0;
  }

  if (controlMillis >= controlInterval) 
  {
    if (RT > 30)
    {
      ###(fanRelay, ###);  //Turn ON Fan
    }
    else
    {
      ###(fanRelay, ###);  //Turn OFF Fan
    }
    if (soilPercentage > 70)
    {
      ###(pumpRelay, ###); //Turn OFF Pump
    }
    else
    {
      ###(pumpRelay, ###); //Turn ON Pump
    }

    controlMillis = 0;
  }

  if (uploadMillis >= uploadInterval) 
  {
    ThingSpeak.setField(1, ###); // Field 1 for Celsius
    ThingSpeak.setField(2, ###); // Field 2 for Humidity
    ThingSpeak.setField(3, ###); // Field 3 for Soil Wetness

    ThingSpeak.writeFields(###, ###); //Send Data to ThingSpeak using Channel ID & Write API Key
    
    uploadMillis = 0;
  }
}