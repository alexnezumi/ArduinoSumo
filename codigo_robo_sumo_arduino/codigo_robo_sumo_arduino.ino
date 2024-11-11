//Programa: Robô sumô
//Autor: Alex
//Versão: 1.0

//********************Inclusão das bibliotecas**************

#include <AFMotor.h>//Biblioteca do motor shield
#include <Ultrasonic.h>//Bibloteca do sensor ultrassônico

//********************Definição dos pinos********************

#define trigger A2
#define echo   A3
#define sensor2 A4
#define sensor1 A5

//********************Criação dos objetos********************

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Ultrasonic ultrasonic(trigger, echo);

//********************Função de configuração******************

void setup() {
  //Configuração de velocidade dos motores
  motor1.setSpeed(255);//Velocidade vai de 0 a 255
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  Serial.begin(9600);//Habilita a comunicação serial
  pinMode(sensor1, INPUT);//Configura o pino do sensor 1 como entrada
  pinMode(sensor2, INPUT);//Configura o pino do sensor 2 como entrada
}
//********************Função de principal********************

void loop() {
  //Cálculo e conversão da leitura do sensor ultrassônico
  long microsec = ultrasonic.timing();
  float distancia = ultrasonic.convert(microsec, Ultrasonic::CM);

  //Mostra as leitura dos sensores
  
    Serial.print("A distancia: ");
    Serial.println(distancia);
    Serial.print("Sensor da frente: ");
    Serial.println(digitalRead(sensor1));
    Serial.print("Sensor da tras: ");
    Serial.println(digitalRead(sensor2));
    delay(1000);
  
  
  //Verifica se tem alguma coisa na sua frente e se os sensor estão no branco
  if (distancia > 20 && digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0) {
    Serial.println("procurando oponente");
    //Duas formas de procurar o oponente na arena
    procura();//Procura em forma de quadrado
    //esquerda();//Fica girando
  }
  //Se caso encontrar algo na sua frente
  if (distancia < 20 && distancia > 0 && digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0) {
    while (digitalRead(sensor1) == 0) { //Prende na condição até o sensor encotrar a borda da arena
      Serial.println("achei o oponente");
      frente();//Movimenta para frente
    }
    parada();
    delay(1000);
    tras();
    delay(1000);
  }
  //Se caso encontre a borda e não o oponente
  if (digitalRead(sensor1) == 1 && digitalRead(sensor2) == 0) {
    Serial.println("Sensor da frente achou borda");
    tras();
    delay(500);
  }
  if (digitalRead(sensor1) == 0 && digitalRead(sensor2) == 1) {
    Serial.println("Sensor de tras achou borda");
    frente();
    delay(500);
  }
}
//********************Movimenta o robô para frente********************

void tras() {
  motor1.run(FORWARD); //Motor traseiro esquerdo
  motor2.run(FORWARD); //Motor dianteiro esquerdo
  motor3.run(FORWARD); //Motor dianteiro direito
  motor4.run(FORWARD); //Motor traseiro direito
}
//********************Movimenta o robô para trás********************

void frente() {
  motor1.run(BACKWARD); //Motor traseiro esquerdo
  motor2.run(BACKWARD); //Motor dianteiro esquerdo
  motor3.run(BACKWARD); //Motor dianteiro direito
  motor4.run(BACKWARD); //Motor traseiro direito
}
//********************Parada dos motores********************

void parada() {
  motor1.run(RELEASE); //Motor traseiro esquerdo
  motor2.run(RELEASE); //Motor dianteiro esquerdo
  motor3.run(RELEASE); //Motor dianteiro direito
  motor4.run(RELEASE); //Motor traseiro direito
}
//********************Movimenta o robô para esquerda********************

void esquerda() {
  motor1.run(FORWARD); //Motor traseiro esquerdo
  motor2.run(FORWARD); //Motor dianteiro esquerdo
  motor3.run(BACKWARD); //Motor dianteiro direito
  motor4.run(BACKWARD); //Motor traseiro direito
}
//********************Movimenta o robô em forma de quadrado********************

void procura() {
  frente();
  delay(400);
  esquerda();
  delay(200);
}