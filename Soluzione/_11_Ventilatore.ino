const byte PIN_TERMORESISTENZA = A0;
const float RESISTENZAFISSA    = 10.0; 
const float Bcoeff             = 3435;
const float RESISTENZA25       = 10.0;

const byte PIN_MOTORE          = 5;

const float TEMPERATURA_FONDOSCALA = 35;
const float TEMPERATURA_MINIMA     = 10;

void setup() {
  pinMode(PIN_TERMORESISTENZA, INPUT);
  pinMode(PIN_MOTORE, OUTPUT);
}

void loop() {
  int   lettura     = analogRead(PIN_TERMORESISTENZA);
  float resistenzaSensore = RESISTENZAFISSA / ( 1024.0 / lettura - 1 );
  float temperatura;
  
  temperatura = log(resistenzaSensore / RESISTENZA25);
  temperatura = temperatura / Bcoeff + 1/298.15;
  temperatura = 1/temperatura + 273.15;


  // Si imposta un range finito di temperature
  if (temperatura > TEMPERATURA_FONDOSCALA) {
    temperatura = TEMPERATURA_FONDOSCALA;
  }
  else if (temperatura < TEMPERATURA_MINIMA) {
    temperatura = TEMPERATURA_MINIMA;
  }

  // temperatura = 10 --> PWM = 0
  // temperatura = 35 --> PWM = 255
  // Valori intermedi proporzionali
  byte velocita = (temperatura - TEMPERATURA_MINIMA) * 255.0 / (TEMPERATURA_FONDOSCALA - TEMPERATURA_MINIMA);
  analogWrite(PIN_MOTORE, velocita);
  delay(10);
}
