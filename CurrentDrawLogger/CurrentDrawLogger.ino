//This code is a moddification of the SD labrary Datalogger Example

#include <SPI.h>
#include <SD.h>

// This must be pin 10 to work with our sheild
const int chipSelect = 10;

void setup()
{
  Serial.begin(9600);
//make chipselect pin output
  pinMode(10, OUTPUT);

  // check for errors
  if (!SD.begin(chipSelect)) {
    Serial.println("Failed to communicate with SD card");
  }
  Serial.println("Initialized");
}

void loop()
{
  // make a string for assembling the data
  String dataString = "";

  // read sensors for voltage and current and space data logs with tabs for excel imports
  for (int analogPin = 0; analogPin < 2; analogPin++) {
    //read sensor
    int sensor = analogRead(analogPin);
    //add data to string
    dataString += String(sensor);
      //here is where we tab for easy excel import
      dataString += "\t";
  }

  // open the file
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  //write to file
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // To serial for testing
    Serial.println(dataString);
  }
  // if file fails to open, print error
  else {
    Serial.println("Error");
  }
  
  //We doon't need that many data points
  delay(2500);
}


