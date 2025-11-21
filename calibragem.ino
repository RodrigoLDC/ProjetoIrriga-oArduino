void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0); // Lê o valor do sensor
  Serial.println(sensorValue); // Imprime o valor no Monitor Serial
  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}

//void loop() {
// int sensorValue = analogRead(A0);
// int humidity = map(sensorValue, valor_0, valor_100, 0, 100);
//humidity = constrain(humidity, 0, 100); // Garante que o valor fique entre 0 e 100
//Serial.println(humidity);
//delay(1000);
//}