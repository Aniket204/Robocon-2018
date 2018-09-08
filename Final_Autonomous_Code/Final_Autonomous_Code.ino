//editors note  lsa1 and lsa2 pins have been interchanged and please check the b_tz1,b_tz2 and b_tz3 connections....this is a working code for 24 feb afternoon with pid

#define DIR_1 23
#define PWM_1 2

#define DIR_2 10
#define PWM_2 11

#define DIR_3 8
#define PWM_3 9

#define DIR_4 6
#define PWM_4 7

#define b_tz1 49 //b_tz1    
#define b_tz2 51
#define b_tz3 53   //b_tz3 

#define throw_tz1 22   //green
#define throw_tz2 26   //blue
#define throw_tz3 24  //yellow

#define junction2 50  //junction1 earlier
#define junction1 48  //junction2 earlier
#define junction3 52

#define analog2 A6    //analog1 earlier
#define analog1 A7  //analog2 earlier
#define analog3 A2

#define proxy1 45
#define proxy2 47

#define flasher 28

bool jc ;
bool j3 = true;

bool drift_enable = true;
int counter = 0;

bool firsttrace_counter2 = true ;
bool counter1_slippage = false ;

bool tz1_enable = false;
bool tz1_counter5 = true ;
bool tz1_counter6 = false ;
bool tz1_drift_enable = false;
bool tz1_trigger_slipage = true;

bool tz2_enable = false; //booleans used for tz2
bool tz2_start = false ;
bool tz2_counter2 = false ;
bool tz2_counter3 = false;
bool tz2_counter6 = true ;
bool tz2_counter8 = false;
bool tz2_counter9 = false ;
bool tz2_counter10 = false ;
bool tz2_trigger_slippage = true;

bool tz3_enable = false;  //booleans used for tz3
bool tz3_start = false;
bool tz3_counter3 = false;
bool tz3_counter9 = true;
bool tz3_counter13 = false;
bool tz3_counter16 = false;
bool tz3_trigger_slippage = true;
bool tz3_counter15 = false;
bool tz3_counter15_j3 = false;

int delaytime = 1000;
long int currenttime, previoustime;

int readval1, posval1, readval2, posval2, readval3, posval3;
int speed1, speed2, speed3, speed4;

const int Kp2 = 3;  //2
const float Kd2 = 30; //25

const int Kp1 = 3;  //2
const float Kd1 = 20; //25

const int setPoint = 35;
int baseSpeed;   //100
int maxSpeed;   //200

int leftMotorSpeed , rightMotorSpeed , motorSpeed1, motorSpeed2, error1, error2 ;
int lastError1 = 0 , lastError2 = 0 , positionVal;

void setup() {
  pinMode(DIR_1 , OUTPUT);
  pinMode(DIR_2 , OUTPUT);
  pinMode(DIR_3 , OUTPUT);
  pinMode(DIR_4 , OUTPUT);

  pinMode(PWM_1 , OUTPUT);
  pinMode(PWM_2 , OUTPUT);
  pinMode(PWM_3 , OUTPUT);
  pinMode(PWM_4 , OUTPUT);

  pinMode(analog1 , INPUT);
  pinMode(junction1 , INPUT);

  pinMode(analog2 , INPUT);
  pinMode(junction2 , INPUT);

  pinMode(analog3 , INPUT);
  pinMode(junction3 , INPUT);

  pinMode(b_tz1 , INPUT);
  pinMode(b_tz2 , INPUT);
  pinMode(b_tz3, INPUT);

  pinMode(throw_tz1, OUTPUT);
  pinMode(throw_tz2, OUTPUT);
  pinMode(throw_tz3, OUTPUT);

  pinMode(flasher , OUTPUT);
  digitalWrite(flasher , HIGH);


  digitalWrite(throw_tz1 , HIGH);
  digitalWrite(throw_tz2 , HIGH);
  digitalWrite(throw_tz3, HIGH);

  digitalWrite(DIR_1 , HIGH);
  digitalWrite(DIR_2 , LOW);
  digitalWrite(DIR_3 , LOW);
  digitalWrite(DIR_4 , HIGH);


  analogWrite(PWM_1, 0);
  analogWrite(PWM_2, 0);
  analogWrite(PWM_3, 0);
  analogWrite(PWM_4, 0);
  Serial.begin(9600);
}

void readsensor1()
{
  readval1 = analogRead(analog1);
  posval1 = (((float)readval1 / 921) * 70);

  error1 = posval1 - setPoint;
  motorSpeed1 = Kp1 * error1 + Kd1 * (error1 - lastError1);
  lastError1 = error1;

  rightMotorSpeed = baseSpeed - motorSpeed1;
  leftMotorSpeed = baseSpeed + motorSpeed1;

  if (rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
  if (leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;
}

void readsensor2()
{
  readval2 = analogRead(analog2);
  posval2 = (((float)readval2 / 921) * 70);

  error2 = posval2 - setPoint;
  motorSpeed2 = Kp2 * error2 + Kd2 * (error2 - lastError2);
  lastError2 = error2;

  rightMotorSpeed = baseSpeed - motorSpeed2;
  leftMotorSpeed = baseSpeed + motorSpeed2;

  if (rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
  if (leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;
}

void countercount()
{
  readsensor1();
  readsensor2();
  while ((digitalRead(junction1) == HIGH || digitalRead(junction2) == HIGH))
  {
    readsensor1();
    readsensor2();
    jc = true;

  }

  /*currenttime = millis();                                         //debouncing for junction
    if (currenttime - previoustime > delaytime)
    {
    previoustime = currenttime;
    }
    else
    {
    jc == false;
    }*/

  if (jc == true)
  {
    counter++;
    jc = false;
  }
}

void readzone()
{
  if ((digitalRead(b_tz1) == HIGH) && (digitalRead(b_tz2) == LOW) && (digitalRead(b_tz3) == LOW))
  {
    tz1_enable = true;
    delay(3000);
  }

  else if ((digitalRead(b_tz1) == LOW) && (digitalRead(b_tz2) == HIGH) && (digitalRead(b_tz3) == LOW))
  {
    tz2_enable = true;
    delay(5000);
  }

  else if ((digitalRead(b_tz1) == LOW) && (digitalRead(b_tz2) == LOW) && (digitalRead(b_tz3) == HIGH))
  {
    tz3_enable = true;
    delay(5000);
  }

  else if ((digitalRead(b_tz1) == LOW) && (digitalRead(b_tz2) == LOW) && (digitalRead(b_tz3) == LOW))
  {
    wait();
  }
}

void loop()
{
  readsensor1();
  readsensor2();
  countercount();
  if (posval1 > 70 && posval2 > 70)
  {
    wait();
  }
  else
  {
    if (tz1_enable == false && tz2_enable == false && tz3_enable == false && firsttrace_counter2 == false)
    {
      if (drift_enable == true)
      {
        set_speed_slow();
        move_right();
      }
      if (drift_enable == false)
      {
        readzone();
      }
      while (digitalRead(junction3) == HIGH)
      {
        drift_enable = false;
        if (tz1_drift_enable == true)
        {
          wait();
          delay(500);
          set_speed_slow();
          readsensor1();
          //readsensor2();

          digitalWrite(DIR_1 , HIGH);
          digitalWrite(DIR_2 , HIGH);
          digitalWrite(DIR_3 , LOW);
          digitalWrite(DIR_4 , LOW);

          analogWrite(PWM_1, 100);
          analogWrite(PWM_2, 100 );
          analogWrite(PWM_3, 100);
          analogWrite(PWM_4, 100);
          delay(400);                                 //to be changed according to the surface
          tz1_drift_enable = false;
        }
        continue;
      }
    }
    if (tz1_enable == true)
    {
      tz1();
    }

    if (tz2_enable == true)
    {
      tz2();
    }

    if (tz3_enable == true)
    {
      tz3();
    }

    if (counter ==  0 )                             //first_trace
    {

      set_speed_slow();
      move_right();
      counter1_slippage = true ;
    }
    if (counter == 1)
    {
      if (counter1_slippage == true)
      {
        wait();
        delay(500);
        counter1_slippage = false;
      }
      set_speed_medium();
      move_back();
    }
    if (counter == 2)
    {
      if (firsttrace_counter2 == true)
      {
        wait();
        delay(500);
        drift_enable = true;
        firsttrace_counter2 = false ;
      }
    }
  }
}
