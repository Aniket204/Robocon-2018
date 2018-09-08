void set_speed_slow()
{
  baseSpeed = 60;   //100
  maxSpeed = 160;   //200
}

void set_speed_medium()
{
  baseSpeed = 73;
  maxSpeed = 170;   //200
}

void set_speed_fast()
{
  baseSpeed = 100;   //100
  maxSpeed = 200;   //200
}
void set_speed_tz2()
{
  baseSpeed = 60;   //100
  maxSpeed = 130;   //200


}
void move_front()
{
  //readsensor1();
  readsensor2();

  digitalWrite(DIR_1 , HIGH);
  digitalWrite(DIR_2 , LOW);
  digitalWrite(DIR_3 , LOW);
  digitalWrite(DIR_4 , HIGH);

  analogWrite(PWM_1, rightMotorSpeed);
  analogWrite(PWM_2, leftMotorSpeed);
  analogWrite(PWM_3, rightMotorSpeed);
  analogWrite(PWM_4, leftMotorSpeed);
}

void move_back()
{
  //readsensor1();
  readsensor2();

  digitalWrite(DIR_1 , LOW);
  digitalWrite(DIR_2 , HIGH);
  digitalWrite(DIR_3 , HIGH);
  digitalWrite(DIR_4 , LOW);

  analogWrite(PWM_1, leftMotorSpeed);
  analogWrite(PWM_2, rightMotorSpeed);
  analogWrite(PWM_3, leftMotorSpeed);
  analogWrite(PWM_4, rightMotorSpeed);
}


void move_right()
{
  readsensor1();
  //readsensor2();

  digitalWrite(DIR_1 , HIGH);
  digitalWrite(DIR_2 , HIGH);
  digitalWrite(DIR_3 , LOW);
  digitalWrite(DIR_4 , LOW);

  analogWrite(PWM_1, rightMotorSpeed + 5 ); //+ 10);
  analogWrite(PWM_2, leftMotorSpeed + 5 ); //+ 10);
  analogWrite(PWM_3, rightMotorSpeed);
  analogWrite(PWM_4, leftMotorSpeed);
}

void move_left()
{
  readsensor1();
  // readsensor2();

  digitalWrite(DIR_1 , LOW);
  digitalWrite(DIR_2 , LOW);
  digitalWrite(DIR_3 , HIGH);
  digitalWrite(DIR_4 , HIGH);

  analogWrite(PWM_1, leftMotorSpeed); //+ 15);
  analogWrite(PWM_2, rightMotorSpeed); //+ 15);
  analogWrite(PWM_3, leftMotorSpeed ); //+ 10);
  analogWrite(PWM_4, rightMotorSpeed ); //+ 10);
}

void wait()
{
  digitalWrite(DIR_1 , LOW);
  digitalWrite(DIR_2 , LOW);
  digitalWrite(DIR_3 , LOW);
  digitalWrite(DIR_4 , LOW);

  analogWrite(PWM_1 , 0);
  analogWrite(PWM_2 , 0);
  analogWrite(PWM_3 , 0);
  analogWrite(PWM_4 , 0);
}
