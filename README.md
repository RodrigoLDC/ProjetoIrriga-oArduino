🌱 Sistema de Irrigação Automática com Arduino

Este projeto implementa um sistema de irrigação automática utilizando Arduino, sensores de umidade do solo e uma bomba d’água controlada por relé. O objetivo é manter a umidade ideal para as plantas de forma automática e eficiente, reduzindo o desperdício de água e melhorando o cuidado com o cultivo.

📸 Demonstração (opcional)

Adicione aqui fotos do sistema montado, esquemas ou vídeos — posso gerar um modelo para você, se quiser.

📌 Funcionalidades

Monitoramento contínuo da umidade do solo.

Acionamento automático da bomba quando o solo estiver seco.

Exibição do status no display LCD (umidade, irrigando etc.).

Controle via relé para maior segurança elétrica.

Lógica personalizável para diferentes condições de cultivo.

📦 Componentes Utilizados

Arduino Uno

Sensor de umidade do solo (capacitivo recomendado)

Bomba submersível 5V / 12V

Módulo Relé 5V

Display LCD 16x2 com interface I2C

Fonte de alimentação

Jumpers e cabos

Tubulação para irrigação

🔌 Esquema de Funcionamento

O sensor lê constantemente a umidade do solo.

O Arduino converte a leitura para porcentagem.

Se a umidade estiver abaixo do limite definido (ex.: 70%), a bomba é acionada.

O display LCD mostra o nível de umidade e o status da irrigação.

A bomba é desligada automaticamente quando a umidade ideal é atingida.

💻 Código (trecho principal)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinoSensor = A0; 
const int pinoRele = 8; 
const int pinoLed = 9;

void setup() {
  pinMode(pinoRele, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  digitalWrite(pinoRele, LOW);
  
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int umidade = analogRead(pinoSensor);
  float umidadePorcentagem = map(umidade, 540, 380, 0, 100);
  umidadePorcentagem = constrain(umidadePorcentagem, 0, 100);

  Serial.print("Umidade: ");
  Serial.println(umidadePorcentagem);

  if (umidadePorcentagem < 70) {
    lcd.clear();
    lcd.print("Desidratado: ");
    lcd.print(umidadePorcentagem);
    lcd.print("%");

    digitalWrite(pinoLed, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Irrigando...");

    digitalWrite(pinoRele, LOW);
    delay(3000);
    digitalWrite(pinoRele, HIGH);
    delay(2000);
  } else {
    lcd.clear();
    lcd.print("Hidratado: ");
    lcd.print(umidadePorcentagem);
    lcd.print("%");

    digitalWrite(pinoLed, LOW);
  }

  delay(1000);
}

🛠️ Montagem

Posicione o sensor no solo, próximo às raízes.

Conecte a bomba a um reservatório de água.

Use o relé entre a bomba e o Arduino para controlar a alimentação da bomba.

Alimente o Arduino e a bomba com fontes adequadas.

📈 Resultados Esperados

Redução significativa do desperdício de água.

Automatização completa da irrigação.

Solução prática para jardins, hortas ou vasos.

🚀 Possíveis Melhorias

Conexão Wi-Fi para monitoramento remoto.

Dashboard móvel ou web.

Integração de sensores adicionais (luminosidade, temperatura).

Programação por horário (RTC).