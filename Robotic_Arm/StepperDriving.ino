void stepper4quarterrot()
{
  digitalWrite(dirPin4, HIGH);               // 200 steps for rotation
  for (int x = 0; x < 500; x++)
  {
    digitalWrite(stepPin4, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin4, LOW);
    delayMicroseconds(1500);
  }
  delay(1000);

  /* digitalWrite(dirPin4, LOW);
    for (int x = 0; x < 200; x++)
    {
     digitalWrite(stepPin4, HIGH);
     delayMicroseconds(1500);
     digitalWrite(stepPin4, LOW);
     delayMicroseconds(1500);
    }
    delay(1000);*/
}

void stepper1initial()
{
  digitalWrite(dirPin1, LOW);               // 200 steps for rotation
  for (int x = 0; x < 10000; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(50);
  }
}

void stepper2down()
{
  digitalWrite(dirPin2, HIGH);               // 200 steps for rotation
  for (int x = 0; x < 10000; x++)
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
}

void stepper1fast()
{
  digitalWrite(dirPin1, HIGH);               // 200 steps for rotation
  for (int x = 0; x < 100000; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(50);
  }
}
