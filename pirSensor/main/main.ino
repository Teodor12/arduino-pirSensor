
#define pirInput 3
#define pwmOutput 5
#define steps 255
#define calibrationTime 5

float R;

void calibration()
{
  Serial.print("Calibrating the sensor");
  delay(50);
  for (int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void pwmDown(int *pwm, int *factor)
{
  *pwmValue = pow(2, ((*factor) / R)) - 1;
  (*factor)--;
  delay(10);
}

void reset(int *value1, int *value2)
{
  *value1 = 255;
  *value2 = 255;
}

void setup()
{
  pinMode(pirInput, INPUT);
  pinMode(pwmOutput, OUTPUT);
  digitalWrite(pirInput, LOW);
  Serial.begin(9600);
  calibration();
  R = (steps * log10(2)) / (log10(255));
}

void loop()
{

  static int fadeValue = 0;
  static int step = 0;

  if (digitalRead(pirInput) == HIGH)
  {
    analogWrite(pwmOutput, 255);
    reset(&fadeValue, &step);
    delay(10);
  }
  else if(digitalRead(pirInput) == LOW)
  {
    if (fadeValue > 0)
    {
      pwmDown(&fadeValue, &step);
      analogWrite(pwmOutput, fadeValue);
      delay(10);
    }
  }
}
