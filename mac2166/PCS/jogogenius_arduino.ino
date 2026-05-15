// Genius Game - Versão Arduino com 4 Pushbuttons
// Conecte os botões aos pinos digitais: 2, 3, 4, 5
// Adicione LEDs aos pinos: 6, 7, 8, 9 (opcional para feedback visual)

const int NUM_BUTTONS = 4;
const int MAX_SEQUENCE = 100;

// Configuração de pinos
const int buttonPins[4] = {2, 3, 4, 5};      // Pinos dos botões
const int ledPins[4] = {6, 7, 8, 9};         // Pinos dos LEDs (opcional)
const int buzzerPin = 10;                     // Buzzer para feedback sonoro (opcional)

// Variáveis do jogo
int sequence[MAX_SEQUENCE];
int playerInput[MAX_SEQUENCE];
int sequenceLength = 0;
int playerInputLength = 0;
int score = 0;
bool gameActive = true;

// Configuração
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0)); // Usa entrada analógica como seed aleatória
  
  // Configura pinos dos botões como entrada
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  pinMode(buzzerPin, OUTPUT);
  
  Serial.println("╔════════════════════╗");
  Serial.println("║   GENIUS GAME      ║");
  Serial.println("║  4 Pushbuttons     ║");
  Serial.println("╚════════════════════╝");
  Serial.println("\nPressione os botões para começar!");
}

// Loop principal
void loop() {
  if (gameActive) {
    // Gera novo dígito
    int newDigit = random(1, NUM_BUTTONS + 1);
    sequence[sequenceLength] = newDigit;
    sequenceLength++;
    
    Serial.print("\nSequência (");
    Serial.print(sequenceLength);
    Serial.println(" dígitos):");
    displaySequence();
    
    Serial.println("Sua vez! Repita a sequência:");
    playerInputLength = 0;
    
    // Aguarda entrada do jogador
    while (playerInputLength < sequenceLength && gameActive) {
      int pressedButton = waitForButtonPress();
      
      if (pressedButton > 0) {
        playerInput[playerInputLength] = pressedButton;
        playFeedback(pressedButton);
        Serial.print(pressedButton);
        Serial.print(" ");
        
        // Verifica se a entrada está correta
        if (playerInput[playerInputLength] != sequence[playerInputLength]) {
          Serial.println("\n✗ ERRADO!");
          playErrorSound();
          gameOver();
          gameActive = false;
        } else {
          Serial.println("✓");
        }
        
        playerInputLength++;
      }
    }
    
    if (gameActive) {
      score++;
      Serial.print("\nAcerto! Pontuação: ");
      Serial.println(score);
      playSuccessSound();
      delay(2000);
    }
  }
}

// Aguarda pressão de um dos botões e retorna o número (1-4)
int waitForButtonPress() {
  int lastButtonState[NUM_BUTTONS] = {LOW, LOW, LOW, LOW};
  unsigned long startTime = millis();
  const unsigned long TIMEOUT = 5000; // 5 segundos de timeout
  
  while (millis() - startTime < TIMEOUT) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
      int currentButtonState = digitalRead(buttonPins[i]);
      
      if (currentButtonState == HIGH && lastButtonState[i] == LOW) {
        // Botão pressionado
        delay(20); // Debounce
        
        if (digitalRead(buttonPins[i]) == HIGH) {
          // Aguarda soltar o botão
          while (digitalRead(buttonPins[i]) == HIGH) {
            delay(10);
          }
          delay(20); // Debounce ao soltar
          return i + 1; // Retorna 1-4
        }
      }
      
      lastButtonState[i] = currentButtonState;
    }
    delay(20);
  }
  
  Serial.println("Timeout!");
  return 0;
}

// Exibe a sequência com feedback visual e sonoro
void displaySequence() {
  delay(1000);
  
  for (int i = 0; i < sequenceLength; i++) {
    int buttonNum = sequence[i];
    
    // Acende LED
    digitalWrite(ledPins[buttonNum - 1], HIGH);
    playTone(buttonNum);
    Serial.print(buttonNum);
    Serial.print(" ");
    
    delay(600);
    
    // Apaga LED
    digitalWrite(ledPins[buttonNum - 1], LOW);
    noTone(buzzerPin);
    
    delay(400);
  }
  
  Serial.println();
}

// Feedback ao pressionar botão
void playFeedback(int buttonNumber) {
  // Acende LED
  digitalWrite(ledPins[buttonNumber - 1], HIGH);
  playTone(buttonNumber);
  
  delay(200);
  
  // Apaga LED
  digitalWrite(ledPins[buttonNumber - 1], LOW);
  noTone(buzzerPin);
}

// Toca tom de sucesso (3 bips)
void playSuccessSound() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000, 200);
    delay(250);
  }
}

// Toca som de erro (1 bip longo)
void playErrorSound() {
  tone(buzzerPin, 300, 500);
}

// Toca frequência baseada no botão
void playTone(int buttonNumber) {
  int frequencies[4] = {262, 294, 330, 349}; // C, D, E, F
  tone(buzzerPin, frequencies[buttonNumber - 1], 200);
}

// Exibe game over
void gameOver() {
  Serial.println("\n╔════════════════════╗");
  Serial.println("║    GAME OVER       ║");
  Serial.print("║ Pontuação: ");
  Serial.print(score);
  if (score < 10) Serial.print(" ");
  Serial.println("        ║");
  Serial.println("╚════════════════════╝");
  
  // Pisca todos os LEDs
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(200);
    for (int i = 0; i < NUM_BUTTONS; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(200);
  }
  
  Serial.println("\nPressione RESET para jogar novamente!");
}
