
//Declaracao do pino conectado ao sensor
const int SENSOR = **;

//Declaracao do pino conectado ao rele
const int PINO_RELE = **;

//Declaracao da variavel que armazena as leituras do sensor
int leitura_sensor = 0;

//Declaracao da variavel auxiliar para o "delay" de 10 segundos
bool pausa = true;

//Declaracao das variaveis que armazenam os valores de calibracao
const int VALOR_MAXIMO = 600; //Valor com solo seco
const int VALOR_MINIMO = 300; //Valor com solo umido
//Altere o valor das variaveis acima de acordo com as medias obtidas atraves do codigo do projeto anterior

//Declaracao das variaveis que armazenam a concentracao maxima e minima desejada
const int CONCENTRACAO_MINIMA = 30;
const int CONCENTRACAO_MAXIMA = 50;
//Altere as variaveis acima com os valores ideais para a sua planta

void setup() {

  //Define o pino conectado ao sensor como uma entrada do sistema
  pinMode(SENSOR, INPUT);
  
  //Define o pino conectado ao rele como uma saida do sistema
  pinMode(RELE, OUTPUT);

  //Inicia o pino conectado ao rele com nivel logico baixo
  digitalWrite(RELE, LOW);
  
}

void loop() {

  //Realiza a leitura do sensor, a mapeia entre 0 e 100 % e exibe o valor no LCD
  leitura_sensor = analogRead(SENSOR);
  leitura_sensor = map(leitura_sensor, VALOR_MINIMO, VALOR_MAXIMO, 100, 0);

  //Verifica se a leitura esta abaixo da concetracao minima desejada
  if(leitura_sensor < CONCENTRACAO_MINIMA){ //Se sim
    digitalWrite(RELE, HIGH); //Acionamos o rele
    pausa = false; //Configura a variavel "pausa" como falsa
  } else if (leitura_sensor > CONCENTRACAO_MAXIMA) { //Caso contrario
    digitalWrite(RELE, LOW); //O rele se mantem desligado
    pausa = true; //Configura a variavel "pausa" como verdadeira
  }

  //Verifica se a variavel "pausa" e verdadeira
  if(pausa){ //Se sim
    delay(10000); //Aguarda 10 segundos para nova leitura
  } 

}