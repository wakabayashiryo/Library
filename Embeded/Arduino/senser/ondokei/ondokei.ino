

void setup() {
  Serial.begin(9600);
}

void loop() {
  long int sensorReading = 0,Volte;

  for (unsigned int samp = 0; samp < 1000; samp++)
    {
      sensorReading += ((analogRead(0) * (49400 / 1024)/10)-400)/19.5;
    } 
    Volte = (analogRead(0) * (49400 / 1024)/10);
  Serial.print("Temperature is ");
  Serial.print(sensorReading/1000);
  Serial.print(".");
  Serial.print(sensorReading%1000/100);
  Serial.print("SensorVoltage is ");
  Serial.print(Volte/1000);
  Serial.print(".");
  Serial.print(Volte%1000);
  Serial.print("V");
  Serial.println("");
}
