
#define steps 255
#define scale 100
#define pwmPin 5
#define pirPin 3
#define callibrationTime 6
#define max_fade_value 200

float R;

void callibration()
{
  Serial.print("Callibrating");
  for (int i = 0; i <= callibrationTime; i++)
  {
    Serial.print(". ");
    delay(1000);
  }
  Serial.println();
  Serial.println("Sensor active!");
}
void pwmDown(int *pwmValue, int *factor)
{
  *pwmValue = pow(2, ((*factor) / R)) - 1;
  (*factor)--;
  delay(5);
}

void pwmUp(int *pwmValue, int *factor)
{
  *pwmValue = pow(2, ((*factor) / R)) - 1;
  (*factor)++;
  delay(5);
}

void setup()
{

  pinMode(pwmPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  R = (scale * log10(2)) / (log10(255));
  callibration();
}

void loop()
{
  static int fadeValue = 0;
  static int step = 0;

  if (digitalRead(pirPin) == HIGH)
  {
    if(fadeValue < max_fade_value){
      pwmUp(&fadeValue, &step);
      analogWrite(pwmPin, fadeValue);
      delay(30);
    }
    
   
  }
  else if (digitalRead(pirPin) == LOW)
  {
    if (fadeValue > 0)
    {
      pwmDown(&fadeValue, &step);
      analogWrite(pwmPin, fadeValue);
      delay(45);
    }
  }
}
