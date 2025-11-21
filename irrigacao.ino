#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configurações do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço do I2C pode variar, verifique com um scanner I2C

const int pinoSensor = A0;  // Pino do sensor de umidade
const int pinoRele = 8;     // Pino do relé
const int pinoLed = 9;      // Pino do LED

void setup() {
  pinMode(pinoRele, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoRele, LOW); // Garantir que a bomba esteja desligada
  lcd.begin(16,2);
  lcd.backlight(); // Ativar a luz de fundo
  Serial.begin(9600);
}

void loop() {
  int umidade = analogRead(pinoSensor);
  float umidadePorcentagem = map(umidade, 540, 380, 0, 100); // Mapeia a leitura para porcentagem
  umidadePorcentagem = constrain(umidadePorcentagem, 0, 100); // Garante que o valor fique entre 0 e 100
  Serial.print("Umidade (bruta): ");
  Serial.println(umidade); // Imprime o nível de umidade do sensor
  Serial.print("Umidade (porcentagem): ");
  Serial.print(umidadePorcentagem);
  Serial.println("%");

  // Verifica se a leitura do sensor é abaixo de 330
  if (umidadePorcentagem < 70) {
    lcd.clear();
    lcd.print("Desidratado: ");
    lcd.print(umidadePorcentagem);
    lcd.print("%");
    digitalWrite(pinoLed, HIGH); // Liga o LED
    lcd.setCursor(0, 1);
    lcd.print("Irrigando...");

    // Liga a bomba
    Serial.println("Bomba ligada");
    digitalWrite(pinoRele, LOW);
    delay(3000); // Irriga por 3 segundos
    Serial.println("Bomba desligada");
    digitalWrite(pinoRele, HIGH); // Desliga a bomba

    delay(2000); // Aguarda 2 segundos antes de verificar novamente
  } else {
    lcd.clear();
    lcd.print("Hidratado: ");
    lcd.print(umidadePorcentagem);
    lcd.print("%");
    digitalWrite(pinoLed, LOW); // Desliga o LED
  }
    if (umidadePorcentagem >= 70) {
              digitalWrite(pinoRele, HIGH); // Garante que a bomba esteja desligada
              Serial.println("Bomba desligada (suficiente)");
          } 

  delay(1000); // Aguarda 1 segundo antes de nova leitura


}