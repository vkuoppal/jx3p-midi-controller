// Simple setup for controlling JX-3P VCF low pass cutoff via potentiometer

int potentioMeter0Pin = 0; 
int potentioMeter0Val = 0;
int earlierVcfCutoffMidiVal = 0;
int ledPin = 11; // PWM Output

// JX-3P kiwi mod midi bytes
int vcfLowPassCutoff = 41;
int continuousController = 176;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(31250); // Midi baudrate needs to be 31250
}

void loop()
{
  potentioMeter0Val = analogRead(potentioMeter0Pin);
  
  delay(10);

  int midiVal = potentioMeter0Val / 8;
  if (midiVal != earlierVcfCutoffMidiVal) {
    Serial.println(midiVal);

    // Approximate midi value 0 - 127 (and led 0 - 255)
    // TODO: convert to use more precise multiMap or use linear potentiometer
    analogWrite(ledPin, potentioMeter0Val / 4);
    int midiVal = potentioMeter0Val / 8;
    midiMessage(continuousController, vcfLowPassCutoff, midiVal);
    earlierVcfCutoffMidiVal = midiVal;
  }
}

void midiMessage(int statusByte, int secondByte, int thirdByte) {
  Serial.write(statusByte);
  Serial.write(secondByte);
  Serial.write(thirdByte);
}
