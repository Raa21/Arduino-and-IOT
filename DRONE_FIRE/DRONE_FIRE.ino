int pwm_pin = 9;
int pwm_recv;

int state = 0;
int fire = 8;

int i = 0;
int fireCond = 0;

int rest_state_PWM_start = 900;
int rest_state_PWM_end = 1500;

int fire_state_PWM_start = 1600;
int fire_state_PWM_end = 2200;

void setup()
{
  Serial.begin(9600);
  pinMode(pwm_pin, INPUT);
  pinMode(fire, OUTPUT);

}
void dronemode1()
{
  digitalWrite(fire, !LOW);
}

void dronemode2()
{
  digitalWrite(fire, !HIGH);
  delay(1000);
  fireCond = 1;
}
void loop() {
  Serial.print("pulse");
  Serial.println(pwm_recv);
  delay(100);
  pwm_recv = pulseIn(pwm_pin, !HIGH);

  if (pwm_recv > rest_state_PWM_start && pwm_recv < rest_state_PWM_end)
  {
    dronemode1();
    fireCond = 0;
  }

  else if (pwm_recv >= fire_state_PWM_start && pwm_recv < fire_state_PWM_end) {
    if (fireCond == 0)
    {
      dronemode2();
    }
    else
    {
      dronemode1();
    }
  }
  else
  {
    digitalWrite(fire, !LOW);
  }
}
