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
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1); // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  bool sdInitialized = false;

  // setup SPI
  // pinMode(_CS, OUTPUT);
  // digitalWrite(_CS, LOW);
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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
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
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile)
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
