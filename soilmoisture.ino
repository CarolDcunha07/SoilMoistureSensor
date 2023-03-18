// define the analog input pin for the sensor
const int sensorPin = A0;

// define the threshold value to determine if the soil is wet or dry
const int thresholdValue = 500;

void setup() {
  // initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // read the sensor value
  int sensorValue = analogRead(sensorPin);

  // check if the soil is wet or dry based on the threshold value
  if (sensorValue >= thresholdValue) {
    Serial.println("Soil is dry");
  } else {
    Serial.println("Soil is wet");
  }

  // wait for a second before taking another reading
  delay(1000);
}
