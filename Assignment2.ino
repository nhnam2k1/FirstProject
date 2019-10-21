#define K1 8  // Confirm button
#define K2 9  // Input button
#define Buzzer 3
#define LIGHT_SENSOR A2
#define TEMP_SENSOR A1

bool makeAlarm;
bool AlarmIsOn;
long long pivotTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(TEMP_SENSOR, INPUT);
  AlarmIsOn = false;
  makeAlarm = false;
}

void Heat_Calc(){
  long double heat = analogRead(TEMP_SENSOR);
  long double temp = heat * 0.48828125;
  if (heat > 100) makeAlarm = true;
}

void Light_Calc(){
  int density = analogRead(LIGHT_SENSOR);
  if (density > 150) makeAlarm = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  int k1 = digitalRead(k1); // Heat check
  int k2 = digitalRead(k2); // Light check

  if(!makeAlarm && AlarmIsOn){
    if(millis() - pivotTime > 10000) // 10 second for alarming
      digitalWrite(Buzzer, LOW); // Turn off the alarm
    AlarmIsOn = false;
  }

  makeAlarm = false;
  if (k1 == LOW){
    Heat_Calc();
    if (makeAlarm) digitalWrite(Buzzer,HIGH);
    delay(100);
    Light_Calc();
    if (makeAlarm) digitalWrite(Buzzer,HIGH);
  }
  else{
    Light_Calc();
    if (makeAlarm) digitalWrite(Buzzer,HIGH);
    delay(100);
    Heat_Calc();
    if (makeAlarm) digitalWrite(Buzzer,HIGH);
  }
  if (makeAlarm && !AlarmIsOn){
    pivotTime = millis();
    AlarmIsOn = true;
  }
}
