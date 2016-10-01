/*
    A0 - PWMB (speed right)
    A1 - BIN2 (direction bits)
    A2 - BIN1

    A3 - /STBY (motor enable)

    A4 - AIN1 (direction bits)
    A5 - AIN2
    DAC - PMWA (speed left)
*/
int PWM_L = DAC1;
int AIN2 = A5;
int AIN1 = A4;
int STBY = A3;
int BIN1 = A2;
int BIN2 = A1;
int PWM_R = A0;
int DEBUG_LED = D7;
bool _new_command = false;


void setup()
{
  pinMode(PWM_L, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(DEBUG_LED, OUTPUT);

  digitalWrite(PWM_L, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWM_R, LOW);
  digitalWrite(DEBUG_LED, LOW);

  Particle.function("test", test);
}

void loop()
{
  if (_new_command) {
    digitalWrite(AIN2, HIGH);
    analogWrite(PWM_L, map(100,0,100,0,255) );
    delay(3000);
    _new_command = false;
  } else {
    digitalWrite(AIN2, LOW);
  }
}

int test(String input)
{
  if (input == "go") {
    _new_command = true;
    return 0;
  } else {
    return 1;
  }
}
