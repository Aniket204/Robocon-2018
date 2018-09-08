#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include <Cytron_SmartDriveDuo.h>

#define gripper1 48             // IN4 of relay                             // Pin number for gripper1 on arduino
#define gripper2 52             // IN3 of relay                             // Pin number for gripper2 on arduino
#define gripper3 50             // IN2 of relay                             // Pin number for gripper3 on arduino
#define randomrelay 4           // IN1 of relay                             // Pin number for a substitute relay on arduino

SoftwareSerial Driver_2_4 (2, 3);        // RX (not use), TX
SoftwareSerial Driver_1_3 (4, 13);

Cytron_PS2Shield ps2(10, 11);            // SoftwareSerial: Rx and Tx pin

int H1 = 63;                             // This value gives highest RPM in clockwise direction, change this if the motor is spinning in undesired direction
int L1 = 127;                            // This value gives highest RPM in anti-clockwise direction, number indicates the wheel

int H2 = 63;
int L2 = 127;

int H3 = 191;
int L3 = 255;

int H4 = 191;
int L4 = 255;

int tweak = 35;                            // Increase this to Decrease the overall speed of MANU
int slow = 0;                              // Used in fine tuning                     ### Keep in mind that (slow+tweak) should not be greater than 55 ###
int tune_speed = 15;                       // To tweak twist speeds
int tune_slow = 0;                         // To tweak twist speeds in fine tuning    ### Keep in mind that (tune_speed+tune_slow) should not be greater than 55 ###

bool Twist_left, Twist_right, Hold, gripper = false ;
// Booleans representing various buttons

void setup()
{
  ps2.begin(9600);                         // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);
  Driver_1_3.begin(9600);                  // Initialize serial
  Driver_2_4.begin(9600);
  pinMode(gripper1, OUTPUT);
  pinMode(gripper2, OUTPUT);
  pinMode(gripper3, OUTPUT);
  pinMode(randomrelay, OUTPUT);
  digitalWrite(gripper1, HIGH);
  digitalWrite(gripper2, HIGH);
  digitalWrite(gripper3, HIGH);
  digitalWrite(randomrelay, HIGH);
}

void loop()
{
  Twist_left = ps2.readButton(PS2_LEFT_1);
  Twist_right = ps2.readButton(PS2_RIGHT_1);

  Hold = ps2.readButton(PS2_LEFT_2);

  int X = ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS);
  int Y = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);

  if ( Y < 100 )
  {
    front();
  }

  if ( Y > 160 )
  {
    reverse();
  }

  if ( X < 100 )
  {
    left();
  }

  if ( X > 160 )
  {
    right();
  }

  if ( X < 100 && Y < 100 )
  {
    front_left();
  }

  if ( X > 160 && Y < 100 )
  {
    front_right();
  }

  if ( X < 100 && Y > 160 )
  {
    bottom_left();
  }

  if ( X > 160 && Y > 160 )
  {
    bottom_right();
  }

  if ((Y < 100) && (Hold == 0))
  {
    slow_front();
  }

  if ((Y > 160) && (Hold == 0))
  {
    slow_reverse();
  }

  if ((X < 100) && (Hold == 0))
  {
    slow_left();
  }

  if ((X > 160) && (Hold == 0))
  {
    slow_right();
  }

  if ((X < 100) && (Y < 100) && (Hold == 0))
  {
    slow_front_left();
  }

  if ((X > 160) && (Y < 100) && (Hold == 0))
  {
    slow_front_right();
  }

  if ((X < 100) && (Y > 160) && (Hold == 0))
  {
    slow_bottom_left();
  }

  if ((X > 160) && (Y > 160) && (Hold == 0))
  {
    slow_bottom_right();
  }

  if ((X > 100 && X < 160) && (Y > 100 && Y < 160))
  {
    wait();
  }

  if (Twist_left == 0)
  {
    twist_left();
  }

  if (Twist_right == 0)
  {
    twist_right();
  }

  if (Twist_left == 0 && (Hold == 0))
  {
    twist_left_slow();
  }

  if (Twist_right == 0 && (Hold == 0))
  {
    twist_right_slow();
  }

  if (ps2.readButton(PS2_RIGHT_2) == 1)
  {
    if (ps2.readButton(PS2_LEFT) == 0)
    {
      digitalWrite(gripper1, LOW);
    }
    else
    {
      digitalWrite(gripper1, HIGH);
    }

    if (ps2.readButton(PS2_RIGHT) == 0)
    {
      digitalWrite(gripper2, LOW);
    }
    else
    {
      digitalWrite(gripper2, HIGH);
    }

    if (ps2.readButton(PS2_UP) == 0)
    {
      digitalWrite(gripper3, LOW);
    }
    else
    {
      digitalWrite(gripper3, HIGH);
    }

    if (ps2.readButton(PS2_DOWN) == 0)
    {
      digitalWrite(randomrelay, LOW);
    }
    else
    {
      digitalWrite(randomrelay, HIGH);
    }
  }
  else
  {
    digitalWrite(gripper1, LOW);
    digitalWrite(gripper2, LOW);
  }
}

void front()
{
  Driver_1_3.write(H1 - tweak);
  Driver_2_4.write(H2 - tweak);
  Driver_1_3.write(H3 - tweak);
  Driver_2_4.write(H4 - tweak);
}

void reverse()
{
  Driver_1_3.write(L1 - tweak);
  Driver_2_4.write(L2 - tweak);
  Driver_1_3.write(L3 - tweak);
  Driver_2_4.write(L4 - tweak);
}

void left()
{
  Driver_1_3.write(L1 - tweak);
  Driver_2_4.write(H2 - tweak);
  Driver_1_3.write(L3 - tweak);
  Driver_2_4.write(H4 - tweak);
}

void right()
{
  Driver_1_3.write(H1 - tweak);
  Driver_2_4.write(L2 - tweak);
  Driver_1_3.write(H3 - tweak);
  Driver_2_4.write(L4 - tweak);
}

void front_left()
{
  Driver_1_3.write((byte)0);
  Driver_2_4.write(H2 - tweak);
  Driver_1_3.write(128);
  Driver_2_4.write(H4 - tweak);
}

void front_right()
{
  Driver_1_3.write(H1 - tweak);
  Driver_2_4.write((byte)0);
  Driver_1_3.write(H3 - tweak);
  Driver_2_4.write(128);
}

void bottom_left()
{
  Driver_1_3.write(L1 - tweak);
  Driver_2_4.write((byte)0);
  Driver_1_3.write(L3 - tweak);
  Driver_2_4.write(128);
}

void bottom_right()
{
  Driver_1_3.write((byte)0);
  Driver_2_4.write(L2 - tweak);
  Driver_1_3.write(128);
  Driver_2_4.write(L4 - tweak);
}

void twist_left()
{
  Driver_1_3.write(L1 - (tweak + tune_speed));
  Driver_2_4.write(L2 - (tweak + tune_speed));
  Driver_1_3.write(H3 - (tweak + tune_speed));
  Driver_2_4.write(H4 - (tweak + tune_speed));
}

void twist_right()
{
  Driver_1_3.write(H1 - tweak - tune_speed);
  Driver_2_4.write(H2 - tweak - tune_speed);
  Driver_1_3.write(L3 - tweak - tune_speed);
  Driver_2_4.write(L4 - tweak - tune_speed);
}

void twist_left_slow()
{
  Driver_1_3.write(L1 - tweak - tune_speed - tune_slow);
  Driver_2_4.write(L2 - tweak - tune_speed - tune_slow);
  Driver_1_3.write(H3 - tweak - tune_speed - tune_slow);
  Driver_2_4.write(H4 - tweak - tune_speed - tune_slow);
}

void twist_right_slow()
{
  Driver_1_3.write(H1 - tweak - tune_speed - tune_slow);
  Driver_2_4.write(H2 - tweak - tune_speed - tune_slow);
  Driver_1_3.write(L3 - tweak - tune_speed - tune_slow);
  Driver_2_4.write(L4 - tweak - tune_speed - tune_slow);
}

void wait()
{
  Driver_1_3.write((byte)0);
  Driver_2_4.write((byte)0);
  Driver_1_3.write(128);
  Driver_2_4.write(128);
}

void slow_front()
{
  Driver_1_3.write(H1 - tweak - slow);
  Driver_2_4.write(H2 - tweak - slow);
  Driver_1_3.write(H3 - tweak - slow);
  Driver_2_4.write(H4 - tweak - slow);
}

void slow_reverse()
{
  Driver_1_3.write(L1 - tweak - slow);
  Driver_2_4.write(L2 - tweak - slow);
  Driver_1_3.write(L3 - tweak - slow);
  Driver_2_4.write(L4 - tweak - slow);
}

void slow_left()
{
  Driver_1_3.write(L1 - tweak - slow);
  Driver_2_4.write(H2 - tweak - slow);
  Driver_1_3.write(L3 - tweak - slow);
  Driver_2_4.write(H4 - tweak - slow);
}

void slow_right()
{
  Driver_1_3.write(H1 - tweak - slow);
  Driver_2_4.write(L2 - tweak - slow);
  Driver_1_3.write(H3 - tweak - slow);
  Driver_2_4.write(L4 - tweak - slow);
}

void slow_front_right()
{
  Driver_1_3.write(H1 - tweak - slow);
  Driver_2_4.write((byte)0);
  Driver_1_3.write(H3 - tweak - slow);
  Driver_2_4.write(128);
}

void slow_front_left()
{
  Driver_1_3.write((byte)0);
  Driver_2_4.write(H2 - tweak - slow);
  Driver_1_3.write(128);
  Driver_2_4.write(H4 - tweak - slow);
}

void slow_bottom_right()
{
  Driver_1_3.write((byte)0);
  Driver_2_4.write(L2 - tweak - slow);
  Driver_1_3.write(128);
  Driver_2_4.write(L4 - tweak - slow);
}

void slow_bottom_left()
{
  Driver_1_3.write(L1 - tweak - slow);
  Driver_2_4.write((byte)0);
  Driver_1_3.write(L3 - tweak - slow);
  Driver_2_4.write(128);
}
