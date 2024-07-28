//O estado umido para o sensor digital é indicado pelo 0
//quanto mais perto de 0 mais umido está o solo na escala analogica

//O estado seco para o sensor digital é indicado pelo 1
//Quanto mais perto do 1023 mais seco está o solo na escala analogica

//Variavel que guardará a leitura do sensor atual
int leituraSensor;
//Variavel que guardará a leitura do sensor anterior
int leituraAnterior;
//Variavel que indicará a umidade adequada escolhiada pelo o usuario
int umidadeOk;

int IntervalOn = 15000; //30 Segundos de acionamento //Irrigar
int IntervalOff = 10000; //10 Segundos de desacionamento //Absorver a água
unsigned long starTime = 0;

double calculoVazao; //Calcular a vazão
volatile int contador; //Contador de pulsos do sensor de fluxo
float fluxoAcumulado = 0; //Armazea o fluxo que passou pelo sensor

void setup() {
  
  pinMode(2, INPUT);
  attachInterrupt(0, Vazao, RISING);
  Serial.begin(9600);

  //solo umido é igual a:
  umidadeOk = 500;

  //Sensor
  pinMode(A0, INPUT);

  //Atuador
  pinMode(12, OUTPUT);
}

void loop() {

  Serial.println("A terra está úmida");

  leituraSensor = analogRead(A0);

  //Ao entrar no estado seco  
  if ((leituraSensor >= umidadeOk) && !(leituraAnterior <= umidadeOk)) {

    starTime = millis();
    
    while(millis() - starTime < IntervalOn){
      digitalWrite(12, LOW); //rele / válvula solenoide

      contador = 0;
      interrupts();
      delay(1000);
      noInterrupts();

      /*O calculoVazao leva em consideração o giro do sensor, que cada vez que ele
      for de low à high, ou seja, der um giro, ele contabiliza 2,40 ml de vazão*/
      calculoVazao = (contador * 2.40);

      //O fluxoAcumulado registra valores de volume na unidade de Litro
      fluxoAcumulado = fluxoAcumulado + (calculoVazao/1000);

      //Essa conta traz o resultado do vazão por minuto(mL/Min)
      calculoVazao = calculoVazao * 60; 
      calculoVazao = calculoVazao / 1000;

      //Vazão em litros por minuto
      Serial.println("Vazão: ");
      Serial.print(calculoVazao);
      Serial.println(" L/Min");

      //Gasto total de litros
      Serial.println("consumo total: ");
      Serial.print(fluxoAcumulado);
      Serial.println(" Litros");
      
    } 
    
    digitalWrite(12, HIGH);  //rele / válvula solenoide

    Serial.println("Código pausado para a terra absorver a água");
    interrupts();
    delay(IntervalOff);
    noInterrupts();

  }
  
  leituraAnterior = leituraSensor;
}
void Vazao() {

  contador++;
}