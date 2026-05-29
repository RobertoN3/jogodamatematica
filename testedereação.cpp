#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int BTN_REACAO = 10;
const int BTN_SIM    = A1;  // invertido
const int BTN_NAO    = A0;  // invertido

void setup() {
  lcd.begin(16, 2);
  pinMode(BTN_REACAO, INPUT_PULLUP);
  pinMode(BTN_SIM,    INPUT_PULLUP);
  pinMode(BTN_NAO,    INPUT_PULLUP);
  randomSeed(analogRead(A5));
}

void loop() {
  // --- Tela inicial ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Teste de Reacao");
  lcd.setCursor(0, 1);
  lcd.print("SIM (1) NAO (0)");

  while (true) {
    if (digitalRead(BTN_SIM) == LOW) {
      while (digitalRead(BTN_SIM) == LOW);
      break; // SIM → começa
    }
    if (digitalRead(BTN_NAO) == LOW) {
      while (digitalRead(BTN_NAO) == LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Ate logo!   ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(3000);
      lcd.clear(); // apaga tela e trava
      while (true); // "encerra" o programa
    }
  }

  // --- Aguardando sinal ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguarde o sinal");

  long esperaMs = random(3000, 10001);
  delay(esperaMs);

  // --- AGORA! ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*** AGORA!!! ***");
  lcd.setCursor(0, 1);
  lcd.print(" Pressione btn! ");

  unsigned long inicio = millis();
  while (digitalRead(BTN_REACAO) == HIGH);
  unsigned long fim = millis();
  while (digitalRead(BTN_REACAO) == LOW);

  // --- Resultado ---
  unsigned long reacao = fim - inicio;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seu tempo:");
  lcd.setCursor(0, 1);
  lcd.print(reacao);
  lcd.print(" ms");

  delay(4000);
}