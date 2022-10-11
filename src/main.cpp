#include <Arduino.h>

#include <VarSpeedServo.h>

// create servo objects
VarSpeedServo myservo1;
VarSpeedServo myservo2;
VarSpeedServo myservo3;

String data;
String get_data[3];
byte a;
int x = 0;
int y = 0;
int z = 0;

int stringData;
String per_data;

void runServo(int valX, int valY, int valZ)
{
  Serial.println("X:" + String(valX) + " Y:" + String(valY) + " Z:" + String(valZ));

  myservo1.write(valX, 30, false);
  myservo2.write(valY, 30, false);
  myservo3.write(valZ, 30, true);

  delay(1000);
}

String split(String data, char character, int pos)
{
  stringData = 0;
  per_data = "";

  for (int i = 0; i < data.length() - 1; i++)
  {

    if (data[i] == character)
    {
      stringData++;
    }

    else if (stringData == pos)
    {
      per_data.concat(data[i]);
    }

    else if (stringData > pos)
    {
      return per_data;
      break;
    }
  }

  return per_data;
}

void getSerial()
{
  while (Serial.available() != 0)
  {
    data = Serial.readString();

    for (a = 0; a < 3; a++)
    {

      get_data[a] = split(data, ' ', a);

      if (get_data[a] != NULL)
      {

        if (a == 0)
        {
          x = get_data[0].toInt();
        }

        if (a == 1)
        {
          y = get_data[1].toInt();
        }

        if (a == 2)
        {
          z = get_data[2].toInt();
        }
      }
    }
    runServo(x, y, z);
  }
}

void setup()
{
  Serial.begin(9600);
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
}

void loop()
{
  getSerial();
}
