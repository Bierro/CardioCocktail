// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

#include <SPI.h>
#include <SD.h>

RTC_PCF8523 rtc;

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 10;

//Parameters for reading / writing on the SD
char* sampleFileUrl = "sample1.txt";
char* targetFileUrl = "lastdata.txt";
int nbOfEntries = 1440;

//Parameters for the input conversion
float defaultSdDev = 3; // 6 percents of Rum as default
float computedSdDev = .5f;
float rumSdDevMultiplier = .02f; // Convert the standard deviation into a percentage of Rum

//Parameters for the pouring
int liqVol = 180; //Amount of liquid we want to pour in the glass in Milliliters
float rumFlow = 2; //in ml / sec
float cokeFlow = 2; // in ml / sec

//Variables controlling the number of reps
DateTime lastDate = DateTime(2000, 1, 21, 3, 0, 0);
boolean onlyOnePerDay = true;
boolean doneforTheDay = false;

//Pins used
int switchPin = 2;
int rumValvePin = 4;
int cokeValvePin = 6;


void setup () {

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }

  Serial.begin(57600);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // put your setup code here, to run once:
  pinMode(switchPin, INPUT);
  pinMode(rumValvePin, OUTPUT);
  pinMode(cokeValvePin, OUTPUT);
}

void loop () {
    DateTime now = rtc.now();

    //If we only want one drink per day and we already poured, wait for the next day!
    if (onlyOnePerDay){
      if (lastDate.year() != 2000 && lastDate.year() == now.year() && lastDate.month() == now.month() && lastDate.day() == now.day()) {
        Serial.println("You already poured yourself a glass today!");
        delay (20000);
        return;
      }
    }

    //Check it the switch is on
    if (digitalRead(switchPin) == LOW) {
     Serial.println("Switch ON!!");
    }
    else{
      Serial.println("Switch OFF!!");
      delay (2000);
      //return;
    }

    //Check if Card is here
    if (!card.init(SPI_HALF_SPEED, chipSelect)) {
      Serial.println("Can't find card!");
      computedSdDev = defaultSdDev;
    } else {
      Serial.println("SD Card found!!");

      //Get the data from the SD Card
      Serial.print("Initializing SD card...");

      if (!SD.begin(10)) {
          Serial.println("initialization failed!");
          return;
      }
      else{
          Serial.println("initialization done.");
          Serial.println("");

          char* filename;
          // check if the file exists
          if ( SD.exists(targetFileUrl) || SD.exists(sampleFileUrl)) {
            if (SD.exists(targetFileUrl)) {
              Serial.println("Target File Found!");
              filename = targetFileUrl;
            }
            else {
              Serial.println("Sample File Found But not the Target One!");
              filename = sampleFileUrl;
            }

            //Check if the file is of the right type and retrieve its timestamp
            if (isFileOk(filename)){
              Serial.println("File had the right format");

              //Compute the standard dev
              computedSdDev = computeSdDev(filename);
              Serial.println("Standard Dev");
              Serial.println(computedSdDev);
            }
            else {
              Serial.println("WRONG format");
            }
          }
          else {
            Serial.println("No File Found");
          }
      }
        
    }
    Serial.println("");

    Serial.println("Standard deviation used: ");
    Serial.println(computedSdDev);
    Serial.println("");

    //Convert the standard deviation in amount to pour
    float pcOfRum = rumSdDevMultiplier * computedSdDev;
    float rumToPour = pcOfRum * liqVol; // in ml
    float cokeToPour = (1 - pcOfRum) * liqVol; // in ml

    Serial.println("Rum to Pour in ml: ");
    Serial.println(rumToPour);
    Serial.println("");

    Serial.println("Coke to Pour in ml: ");
    Serial.println(cokeToPour);
    Serial.println("");

    float rumSeconds = rumToPour / rumFlow;
    float cokeSeconds = cokeToPour / cokeFlow;

    Serial.println("Rum in sec: ");
    Serial.println(rumSeconds);
    Serial.println("");

    Serial.println("Coke in sec: ");
    Serial.println(cokeSeconds);
    Serial.println("");
    
    //Pour the cocktail
    digitalWrite(rumValvePin, HIGH);  //Switch Rum Valve on
    delay(1000 * rumSeconds);  //Wait for rum to be poured (in milliseconds)
    digitalWrite(rumValvePin, LOW);   //Close Rum Valve
    digitalWrite(cokeValvePin, HIGH);  //Switch Rum Valve on
    delay(1000 * cokeSeconds);  //Wait for rum to be poured (in milliseconds)
    digitalWrite(cokeValvePin, LOW);   //Close Rum Valve

    //Update variables
    lastDate = now;
}


boolean isFileOk (char* filename){
  File myFile = SD.open(filename);
  char targetWord[16] = {'A','r','d','u','i','n','o','H','e','a','r','t','D','a','t','a'};
  char cur = 'm';
  int count = 0;
  while ( cur != '\n' && count < sizeof(targetWord)){
    cur = myFile.read();
    if (cur != targetWord[count])
      return false; 
    count++;
  }
  myFile.close();
  
  return true;
}

void skipLine(File myFile){
  char cur = 'm';
  while ( cur != '\n'){
    cur = myFile.read();
  }
}

float getFloatOnLine(File myFile){
  String floatString;
  char cur = 'm';
  int count = 0;
  while ( cur != '\n'){
    if (!myFile.available()){
      return 90;
    }
    cur = myFile.read();
    floatString = floatString + String(cur);
    count++;
  }
  //Serial.println("Float:");
  //Serial.println(floatString);

  return floatString.toFloat();
}

// Code inspired from https://www.programiz.com/cpp-programming/examples/standard-deviation
float computeSdDev(char* filename){

    float sum = 0.0, mean, standardDeviation = 0.0;
    int n = nbOfEntries;
  
    File myFile = SD.open(filename);
    skipLine(myFile);
    skipLine(myFile);
    skipLine(myFile);
    skipLine(myFile);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        sum += getFloatOnLine(myFile);
        //Serial.println(getFloatOnLine(myFile));
    }
    mean = sum/n;

    myFile.close();

    myFile = SD.open(filename);
    skipLine(myFile);
    skipLine(myFile);
    skipLine(myFile);
    skipLine(myFile);
    
    for(i = 0; i < n; ++i)
        standardDeviation += pow(getFloatOnLine(myFile) - mean, 2);

    myFile.close();
    
    return sqrt(standardDeviation / n);
}




