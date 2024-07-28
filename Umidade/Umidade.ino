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

void setup() {
  
  //solo umido é igual a:
  umidadeOk = 600;

  //Sensor
  pinMode(A0, INPUT);

  //Atuador
  pinMode(12, OUTPUT);
}

void loop() {

  leituraSensor = analogRead(A0);

  //Ao entrar no estado seco  
  if ((leituraSensor >= umidadeOk) && !(leituraAnterior <= umidadeOk)) {
     delay(5000); //5 segundos

     while (analogRead(A0) >= umidadeOk) {
        digitalWrite(12, HIGH); //rele / válvula solenoide
        delay(10000); //10 segundos de acionamento
        digitalWrite(12, LOW);  //rele / válvula solenoide

        delay(10000); //10 Segundos / Terra absorver a água
     }
  }
  
  leituraAnterior = leituraSensor;
}