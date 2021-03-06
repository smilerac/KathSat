#include <SD.h>
#include <SPI.h>

int CS_PIN = 10;

File file;
void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}


int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(double temp, double alt)
{
  if (file)
  {
//    file.println(text);
    Serial.println("Writing to file: ");
//    Serial.println(text);
    file.println(temp);
    Serial.println(temp);
    file.println(alt);
//    if(file.println(temp)==200){Serial.println("hellyeaaaa");}
//    else{Serial.println("noooooo, couldnot write");}
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine()
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}

void sd_setup()
{

  Serial.begin(9600);

  initializeSD();
  createFile("test.txt");
//  writeToFile("This is sample text!");
  closeFile();

  openFile("test.txt");
  Serial.println(readLine());
  Serial.println(readLine());
  closeFile();

//  
  
}
