#define stepPin1 2
#define dirPin1 24
#define enPin1 3
#define stepPin2 4
#define dirPin2 26
#define enPin2 5
#define stepPin3 6
#define dirPin3 28
#define enPin3 7
#define stepPin4 8
#define dirPin4 30
#define enPin4 9
#define IR1 32
#define IR2 34
#define S0 36
#define S1 38
#define S2 40
#define S3 42
#define sensorOut 8
int frequency = 0;
int color = 0;                     // Color sensor's

void setup()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(enPin1, OUTPUT);
  digitalWrite(enPin1, LOW);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enPin2, OUTPUT);
  digitalWrite(enPin2, LOW);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(enPin3, OUTPUT);
  digitalWrite(enPin3, LOW);

  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
  pinMode(enPin4, OUTPUT);
  digitalWrite(enPin4, LOW);

  Serial.begin(9600);
}

void loop()
{
  bool IR1detect = LOW;
  if (digitalRead(IR1) == LOW)
  {
    IR1detect = HIGH;
  }
  if (IR1detect == HIGH)
  {
    stepper1initial();
  }

  bool IR2detect = LOW;
  if (digitalRead(IR2) == LOW)
  {
    IR2detect = HIGH;
  }
  if (IR2detect == HIGH)
  {
    stepper4quarterrot();
  }
}
