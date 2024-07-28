double calculoVazao; //Calcular a vazão
volatile int contador; //Contador de pulsos do sensor de fluxo
float fluxoAcumulado = 0; //Armazea o fluxo que passou pelo sensor
unsigned long Tempo = 0;
unsigned long intervalo = 10000;


void setup() {

  pinMode(2, INPUT);
  attachInterrupt(0, Vazao, RISING);
  Serial.begin(9600);

}
void loop() {

  contador = 0;
  interrupts();
  // delay(1000);
    if ( (Tempo + intervalo) >  millis()){
		  Tempo = millis();
		  
		  noInterrupts();

		  /*O calculoVazao leva em consideração o giro do sensor, que cada vez que ele
		  for de low à high, ou seja, der um giro, ele contabiliza 2,25 ml de vazão*/
		  calculoVazao = (contador * 2.25);

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

  

}
void Vazao() {

  contador++;
}