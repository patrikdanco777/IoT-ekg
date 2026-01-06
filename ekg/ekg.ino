int ekgPin = 34;

float filtered = 0;
float prevFiltered = 0;

unsigned long lastBeatTime = 0;
int bpm = 0;

const int threshold = 150;   // prah R-vlny (budeš ladiť)

void setup() {
  Serial.begin(115200);
}

void loop() {
  int raw = analogRead(ekgPin);   // 0–4095
  int value = raw - 2048;         // centrovanie

  // low-pass filter
  filtered = 0.9 * filtered + 0.1 * value;

  // DERIVÁCIA (zvýrazní QRS)
  float diff = filtered - prevFiltered;
  prevFiltered = filtered;

  unsigned long now = millis();

  // DETEKCIA R-VLNY
 if (abs(diff) > threshold && now - lastBeatTime > 300) {
    bpm = 60000 / (now - lastBeatTime);
    lastBeatTime = now;
  }

  // Výstup pre Python / Plotter
  Serial.print(-filtered);
  Serial.print(",");
  Serial.println(bpm);

  delay(2);  // ~500 Hz
}

