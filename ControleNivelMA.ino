//------------------------------------------------------------------------------
//Variaveis Sensor UltraSonico
#define SOUND_SPEED 0.034

const int trigPin = 23;
const int echoPin = 22;

long duration;
float distanceCm;
float Atotal=39; //Altura do Sensor
float erro=3;  //Erro Coller
//------------------------------------------------------------------------------
//Variavel Potenciometro
const int potPin = 32;
int potValue = 0;
//------------------------------------------------------------------------------
//Variavel PWM
const int saidaPWM = 21;
const int frequencia = 5000;
const int Channel = 0;
const int resolucao = 8; 
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT); // Seta PINO Trigger como Saida
  pinMode(echoPin, INPUT); // Seta PINO Echo como Entrada
  
  pinMode(potPin,INPUT);
  
  //Cofigura Pino PWM
  pinMode(saidaPWM, OUTPUT);

  //Seta Pwm
  ledcSetup(Channel,frequencia,resolucao);
  ledcAttachPin(saidaPWM,Channel);
  delay(1000);

}
void loop() {
  // Limpa Pino Trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Seta o pino Trigger em Alta por 10 us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Le o pino Echo, retorna o tempo de viagem da onda sonora em Microsegundos
  duration = pulseIn(echoPin, HIGH);
  
  // Calcula ´´a distancia e soma o erro 
  distanceCm = Atotal - (duration * SOUND_SPEED/2)+erro;
  
  // Imprime a distancia no Serial
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  //Le o potenciometro
  potValue = analogRead(potPin);
  
  int dutyCycle = potValue/16; // Pwm de 8bits por isso dividimos por 16
  
  //Seta o pwm com base no Potenciometro
  pwmColler(dutyCycle);

  
  Serial.print("Potenciometro: ");
  Serial.println(potValue);

  Serial.print("PWM: ");
  Serial.println(dutyCycle);
  
  delay(1000);
  

}
//Função do pwm 
void pwmColler(int dutyCycle){
    
    ledcWrite(Channel,dutyCycle);
    delay(500);  
       
    } 
