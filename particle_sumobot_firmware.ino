/* Motors */
int PWM_L = A6;
int AIN1 = A5;
int AIN2 = A4;
int STBY = A3;
int BIN2 = A2;
int BIN1 = A1;
int PWM_R = A0;

/* Reflective Sensor*/
int SENSE_LED = D7;
int SENSE_PWR = D6;
int SENSE_READ = A7;

/* Control */
int full_rotation = 2400;
int _activated = 0;
int reading = 0;

void setup()
{
  pinMode(PWM_L, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(SENSE_LED, OUTPUT);
  pinMode(SENSE_PWR, OUTPUT);
  pinMode(SENSE_READ, INPUT);

  digitalWrite(PWM_L, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWM_R, LOW);
  digitalWrite(SENSE_LED, HIGH);
  digitalWrite(SENSE_PWR, HIGH);

  Particle.function("active", active);
  Particle.function("read", readSensor);
}

void loop()
{
  if (_activated > 0) {
    reading = analogRead(SENSE_READ);
    if (reading >= 3500) {
      forward();
    } else {
      reverse();
      delay(100);
      if ((reading % 2) == 1) {
        left();
      } else {
        right();
      }
      delay(random(800, 1600));
      forward();
    }
  } else {
    stop();
  }
}

int active(String activate)
{
  _activated = activate.toInt();
  return 0;
}

int readSensor(String read)
{
  return reading;
}

void forward()
{
  digitalWrite(BIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWM_R, HIGH);
  digitalWrite(PWM_L, HIGH);
}

void reverse()
{
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(PWM_R, HIGH);
  digitalWrite(PWM_L, HIGH);
}

void stop()
{
  digitalWrite(BIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWM_R, LOW);
  digitalWrite(PWM_L, LOW);
}

void left()
{
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWM_R, HIGH);
  digitalWrite(PWM_L, HIGH);
}

void right()
{
  digitalWrite(BIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(PWM_R, HIGH);
  digitalWrite(PWM_L, HIGH);
}
