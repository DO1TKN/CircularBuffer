#include <CircularBuffer.h>

CircularBuffer<int, 400> buffer;

unsigned long noticed_time = 0;

#define SAMPLE_PIN A0

void setup() {
	Serial.begin(9600);
	pinMode(SAMPLE_PIN, INPUT);
	noticed_time = millis();
}

void loop() {
	// samples A0 and prints the average of the latest hundred samples to console every 500ms
	int reading = analogRead(A0);
	buffer.push(reading);

	if (millis() - noticed_time >= 500) {
		noticed_time = millis();
		float avg = 0.0;
		// the following ensures using the right type for the index variable
		using index_t = decltype(buffer)::index_t;
		for (index_t i = 0; i < buffer.size(); i++) {
			avg += buffer[i] / (float)buffer.size();
		}
		Serial.print("Average is ");
		Serial.println(avg);
	}
}
