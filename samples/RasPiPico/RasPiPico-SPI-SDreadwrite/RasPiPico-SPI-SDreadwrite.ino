#include <SPI.h>
#include <SD.h>

const int _MISO = 4;
const int _MOSI = 7;
const int _CS = 5;
const int _SCK = 6;

File myFile;

SPISettings spisttings(10000000, MSBFIRST, SPI_MODE3);

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1);
  }

  Serial.print("Initializing SD card...");
  bool sdInitialized = false;

  // setup SPI
  SPI.setCS(_CS);
  SPI.setRX(_MISO);
  SPI.setSCK(_SCK);
  SPI.setTX(_MOSI);
  SPI.begin();

  sdInitialized = SD.begin(_CS);

  if (!SD.begin(_CS))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop()
{
  // write loop!
}

void SDwrite()
{
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile)
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    Serial.println("error opening test.txt");
  }
}

void SDread()
{
  myFile = SD.open("test.txt");
  if (myFile)
  {
    Serial.println("test.txt:");

    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  }
  else
  {
    Serial.println("error opening test.txt");
  }
}
