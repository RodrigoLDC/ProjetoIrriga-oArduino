/* ******************** Rega Automática do Manual do Mundo ********************
   Criado por: Anderson Harayashiki Moreira
   Rev.: 01
   Data: 13.03.2019

   Guia de conexão:
   LCD I2C: 0x27
   Sensor de umidade do solo A0: Pino A0
   Módulo Relé (Válvula): Pino 8

   Este código utiliza a biblioteca LiquidCrystal_I2C

 ***************************************************************************** */

// inclui a biblioteca:
#include <LiquidCrystal_I2C.h>

// define o endereço e o tamanho do Display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// variáveis do programa
const int pinoSensor = A0;
const int pinoRele = 8; // Alterado para pinoRele
const int limiarSeco = 330;
const int tempoRega = 50; // Tempo de rega em segundos
int umidadeSolo = 0;

void setup() {
  pinMode(pinoRele, OUTPUT);
  // Desliga a válvula
  digitalWrite(pinoRele, HIGH);
  // inicializa o Display LCD
  lcd.begin(16, 2);
  lcd.backlight(); // Liga o backlight do LCD
  // Exibe a mensagem no Display LCD.
  lcd.print(" Rega do Manual ");
  Serial.begin(9600);
}

void loop() {
  // Mede a umidade a cada segundo. Faz isso durante um tempo.
  for(int i = 0; i < 5; i++) {
    // Faz a leitura do sensor de umidade do solo
    umidadeSolo = analogRead(pinoSensor);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    int umidadePercent = map(umidadeSolo, 1023, 0, 0, 100);
    
    // Atualiza a primeira linha com a umidade
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidadePercent);
    lcd.print(" %    ");

    // Exibe o nível bruto no console
    Serial.print("Nível de umidade (raw): ");
    Serial.println(umidadeSolo);
    
    // Espera um segundo
    delay(1000);
  }

  // Verifica se a umidade está abaixo do limiar
  if(umidadeSolo < limiarSeco) {
    // Exibe a mensagem no Display LCD:
    lcd.setCursor(0, 1);
    lcd.print("    Regando     ");
    // Liga a válvula
    digitalWrite(pinoRele, LOW);
    // Espera o tempo estipulado
    delay(tempoRega * 1000);
    digitalWrite(pinoRele, HIGH);
    
    // Verifica a umidade novamente após regar
    verificarUmidade();
  } else {
    // Exibe a mensagem no Display LCD:
    lcd.setCursor(0, 1);
    lcd.print("Solo Encharcado ");
    // Espera o tempo estipulado
    delay(3000);
  }
}

// Função para verificar a umidade após regar
void verificarUmidade() {
  // Lê e exibe a umidade novamente
  for (int i = 0; i < 5; i++) {
    umidadeSolo = analogRead(pinoSensor);
    int umidadePercent = map(umidadeSolo, 1023, 0, 0, 100);

    // Atualiza a primeira linha com a umidade
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidadePercent);
    lcd.print(" %    ");

    // Exibe o nível bruto no console
    Serial.print("Nível de umidade (raw): ");
    Serial.println(umidadeSolo);

    // Espera um segundo
    delay(1000);
  }
}
