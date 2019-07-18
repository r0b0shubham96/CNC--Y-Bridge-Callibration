/*
   Pin 1 -- reset
   Pin 2 --  D3
   Pin 3 --  D4
   Pin 4 -- gnd
   pin 5 -- D0
   pin 6 -- D1
   pin 7 -- D2
   pin 8 -- 5V
*/

/*
    D3, D4 -- LIMITS Y1, Y2 -- EXTERNAL PULL UPS
    D0, D1 -- ENABLE Y1, Y2 -- EXTERNAL PULL DOWNS
    D2     -- LIMIT Y PIN TO GRBL EXTERNAL PULL UP
*/

void setup()
{
  pinMode(3, INPUT);  pinMode(4, INPUT);  // limit inputs for y1 and y2
  pinMode(0, OUTPUT);  pinMode(1, OUTPUT); //Enable outputs for y1 and y2
  pinMode(2, OUTPUT); // grbl limit y pin

}

void loop()
{
  int count = 0;
  byte state_3 = digitalRead(3);
  while (count < 20)
  {
    if (digitalRead(3) == state_3)
    {
      count++;
    }
    else
    {
      count--;
      if (count < -20)
      {
        break;
      }
    }
    delay(5);
  }
  if (count < 20)
  {
    return;
  }

  count = 0;
  byte state_4 = digitalRead(4);
  while (count < 20)
  {
    if (digitalRead(4) == state_4)
    {
      count++;
    }
    else
    {
      count--;
      if (count < -20)
      {
        break;
      }
    }
    delay(5);
  }
  if (count < 20)
  {
    return;
  }


  if (state_3 == 1 && state_4 == 0)
  {
    digitalWrite(0, 1); // enable 1 high
    digitalWrite(1, 0);  // enable 2 low
    digitalWrite(2, 0); // grbl y low
  }

  if (state_3 == 0 && state_4 == 1) {
    digitalWrite(1, 1); // enable 2 high
    digitalWrite(0, 0); // enable 1 low
    digitalWrite(2, 0); // grbl y low
  }

  if (state_3 == 1 && state_4 == 1)
  {
    digitalWrite(0, 0);  digitalWrite(1, 0);  // both enables low
    digitalWrite(2, 1); // grbl y high
    delay(2000); // delay to give timw for debounce

  }


  digitalWrite(2, 0); // keeps grbl y low in idle state

}
