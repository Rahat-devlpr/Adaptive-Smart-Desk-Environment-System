int led = 9;
int buzzer = 8;
int motion = 2;
int ldr = A0;
int sound = A1;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motion, INPUT);

  Serial.begin(9600);
  Serial.println("=== Smart Desk Environment System Started ===");
}

void loop() {
  // Read inputs
  int motionState = digitalRead(motion);
  int lightValue = analogRead(ldr);
  int soundValue = analogRead(sound);

  // Process data
  int brightness = map(lightValue, 0, 1023, 255, 0);

  // Decision + Output
  String status = "";

  if (motionState == LOW) {
    analogWrite(led, 0);
    digitalWrite(buzzer, LOW);
    status = "No Motion → System OFF";
  } 
  else {
    analogWrite(led, brightness);

    if (soundValue > 600) {
      digitalWrite(buzzer, HIGH);
      status = "Motion + Noisy → ALERT!";
    } 
    else {
      digitalWrite(buzzer, LOW);

      if (lightValue < 400) {
        status = "Motion + Dark → Bright Light";
      } else {
        status = "Motion + Good Environment";
      }
    }
  }

  // Serial Monitor Output
  Serial.println("--------------------------------------------------");
  Serial.print("Motion: ");
  Serial.print(motionState == HIGH ? "Detected" : "None");

  Serial.print(" | Light: ");
  Serial.print(lightValue);

  Serial.print(" | Sound: ");
  Serial.print(soundValue);

  Serial.print(" | LED Brightness: ");
  Serial.print(brightness);

  Serial.print(" | Status: ");
  Serial.println(status);

  delay(400);
}