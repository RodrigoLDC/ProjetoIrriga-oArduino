#include <LiquidCrystal_I2C.h> // Inclui a biblioteca para controle de display LCD via I2C

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos
const int pinoSensor = A0; // Pino analógico para o sensor de umidade
const int pinoRele = 8;     // Pino digital para controle do relé (bomba)
const int pinoLed = 9;      // Pino digital para controle do LED

// Limites de umidade
const int limiteSeco = 227;     // Limite para solo seco (menor valor)
const int limiteUmedecido = 50;  // Limite para solo úmido (maior valor)

void setup() {
  lcd.begin(16, 2);                   // Inicializa o display LCD
  lcd.backlight();              // Liga a luz de fundo do LCD
  pinMode(pinoRele, OUTPUT);    // Configura o pino do relé como saída
  pinMode(pinoLed, OUTPUT);      // Configura o pino do LED como saída
  digitalWrite(pinoRele, LOW);  // Garante que a bomba esteja desligada no início
  digitalWrite(pinoLed, LOW);    // Garante que o LED esteja apagado no início
  Serial.begin(9600);           // Inicializa a comunicação serial a 9600 bps
}

void loop() {
  int nivelUmidade = analogRead(pinoSensor); // Lê o nível de umidade do sensor
  int porcentagemUmidade = map(nivelUmidade, limiteUmedecido, limiteSeco, 0, 100); // Mapeia o nível de umidade para uma porcentagem de 0 a 100
  
  // Evitar valores negativos: garante que a porcentagem não seja menor que 0
  porcentagemUmidade = constrain(porcentagemUmidade, 0, 100);
  
  // Debugging: exibe o nível de umidade lido
  Serial.print("Nivel Umidade: ");
  Serial.println(nivelUmidade);
  Serial.print("Porcentagem Umidade: ");
  Serial.println(porcentagemUmidade);

  // Atualizar LCD
  lcd.setCursor(0, 0);         // Move o cursor para a primeira linha
  lcd.print("Umidade: ");      // Exibe o texto "Umidade: "
  lcd.print(porcentagemUmidade); // Exibe o nível de umidade em porcentagem
  lcd.print("%");               // Exibe o símbolo de porcentagem

  // Verificar se o solo precisa de irrigação
  if (porcentagemUmidade < 70) { // Irrigar se a umidade estiver abaixo de 70%
    lcd.setCursor(0, 1);            
    lcd.print("Irrigando..."); // Exibe que está irrigando
    digitalWrite(pinoRele, HIGH);   // Liga a bomba de água
    digitalWrite(pinoLed, HIGH);      // Acende o LED
  } else if (nivelUmidade < limiteSeco) { // Solo seco
    lcd.setCursor(0, 1);            
    lcd.print("Desidratado"); // Exibe que o solo está desidratado
    digitalWrite(pinoRele, LOW);   // Desliga a bomba de água
    digitalWrite(pinoLed, LOW);      // Apaga o LED
  } else if (nivelUmidade > limiteUmedecido) { // Solo úmido
    lcd.setCursor(0, 1);            
    lcd.print("Hidratado"); // Exibe que o solo está hidratado
    digitalWrite(pinoRele, LOW);    // Desliga a bomba de água
    digitalWrite(pinoLed, LOW);      // Apaga o LED
  } else { // Se o nível de umidade estiver entre os limites
    lcd.setCursor(0, 1);            
    lcd.print("Estado: OK        "); // Exibe que o solo está em estado OK
    digitalWrite(pinoRele, LOW);    // Garante que a bomba esteja desligada
    digitalWrite(pinoLed, LOW);      // Apaga o LED
  }

  delay(2000); // Espera 2 segundos antes da próxima leitura
}
