#include <Arduino.h>
#include <math.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PIN_BUZZER 8

int acertos = 0;
int erros = 0;
int continuar = 1;

// ✅ Função definida FORA do loop()
long potenciaInteira(int base, int exp) {
    long resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }
    return resultado;
}

void tocarSomAcerto() {
    tone(PIN_BUZZER, 1500, 150);
    delay(150);
    tone(PIN_BUZZER, 2000, 250);
}

void tocarSomErro() {
    tone(PIN_BUZZER, 300, 500);
}

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(115200);
    pinMode(PIN_BUZZER, OUTPUT);
    randomSeed(analogRead(0));
    
    lcd.setCursor(0, 0);
    lcd.print("MATEMÁTICA .");
    lcd.setCursor(0, 1);
    lcd.print("BOA SORTE!");
    delay(2000);
}

void loop() {
    if (continuar == 1) {
        lcd.clear();
        int sorteio = (random(0, 4)) + 1;

        if (sorteio == 1) {
            lcd.setCursor(0, 0);
            lcd.print("Raiz Quadrada:");
            int nraiz = (random(0, 1000)) + 1;
            double raiz = sqrt(nraiz);
            while ((int)raiz * (int)raiz != nraiz) {
                nraiz = (random(0, 1000)) + 1;
                raiz = sqrt(nraiz);
            }
            lcd.setCursor(0, 1);
            lcd.print("Raiz de "); lcd.print(nraiz);
            while (Serial.available() == 0);
            int resposta1 = Serial.parseInt();
            while(Serial.available()) Serial.read();
            if (resposta1 == (int)raiz) {
                lcd.clear();
                lcd.print("ACERTOU!");
                acertos++; tocarSomAcerto();
            } else {
                lcd.clear();
                lcd.print("ERROU!");
                lcd.setCursor(0, 1);
                lcd.print("Era: "); lcd.print((int)raiz);
                erros++; tocarSomErro();
            }
        }
        else if (sorteio == 2) {
            lcd.setCursor(0, 0);
            lcd.print("Potenciacao:");
            int npotencia = (random(0, 30)) + 1;
            int expoente = (npotencia <= 10) ? (random(0, 3)) + 1 : (random(0, 2)) + 1;
            long operacao = potenciaInteira(npotencia, expoente); // ✅ chamada correta
            lcd.setCursor(0, 1);
            lcd.print(npotencia); lcd.print("^"); lcd.print(expoente);
            while (Serial.available() == 0);
            long resposta2 = Serial.parseInt();
            while(Serial.available()) Serial.read();
            if (resposta2 == operacao) {
                lcd.clear();
                lcd.print("ACERTOU!");
                acertos++; tocarSomAcerto();
            } else {
                lcd.clear();
                lcd.print("ERROU!");
                lcd.setCursor(0, 1);
                lcd.print("Era: "); lcd.print(operacao);
                erros++; tocarSomErro();
            }
        }
        else if (sorteio == 3) {
            lcd.setCursor(0, 0);
            lcd.print("Logaritmo:");
            int base = (random(0, 10)) + 1;
            while (base != 2 && base != 3 && base != 5 && base != 10) base = (random(0, 10)) + 1;
            int logaritimando = (random(0, 1000)) + 1;
            double logaritimo = log(logaritimando) / log(base);
            while (abs(logaritimo - round(logaritimo)) > 0.0001) {
                logaritimando = (random(0, 1000)) + 1;
                logaritimo = log(logaritimando) / log(base);
            }
            lcd.setCursor(0, 1);
            lcd.print("Log"); lcd.print(base); lcd.print("("); lcd.print(logaritimando); lcd.print(")");
            while (Serial.available() == 0);
            int resposta3 = Serial.parseInt();
            while(Serial.available()) Serial.read();
            if (resposta3 == (int)round(logaritimo)) {
                lcd.clear();
                lcd.print("ACERTOU!");
                acertos++; tocarSomAcerto();
            } else {
                lcd.clear();
                lcd.print("ERROU!");
                lcd.setCursor(0, 1);
                lcd.print("Era: "); lcd.print((int)round(logaritimo));
                erros++; tocarSomErro();
            }
        }
        else if (sorteio == 4) {
            lcd.setCursor(0, 0);
            lcd.print("Fatorial:");
            int nfatorial = (random(0, 7)) + 1;
            long fatorial = nfatorial;
            for (int proximo = nfatorial - 1; proximo > 1; proximo--) {
                fatorial = fatorial * proximo;
            }
            lcd.setCursor(0, 1);
            lcd.print(nfatorial); lcd.print("!");
            while (Serial.available() == 0);
            long resposta4 = Serial.parseInt();
            while(Serial.available()) Serial.read();
            if (resposta4 == fatorial) {
                lcd.clear();
                lcd.print("ACERTOU!");
                acertos++; tocarSomAcerto();
            } else {
                lcd.clear();
                lcd.print("ERROU!");
                lcd.setCursor(0, 1);
                lcd.print("Era: "); lcd.print(fatorial);
                erros++; tocarSomErro();
            }
        }

        delay(2000);
        lcd.clear();
        lcd.print("Continuar?");
        lcd.setCursor(0, 1);
        lcd.print("1=Sim 0=Nao");
        while (Serial.available() == 0);
        continuar = Serial.parseInt();
        while(Serial.available()) Serial.read();
    } else {
        lcd.clear();
        double porcentagem = (100.0 * acertos) / (acertos + erros);
        if (porcentagem >= 70) {
            lcd.print("Parabens!");
            lcd.setCursor(0, 1);
            lcd.print("Nota: "); lcd.print(porcentagem, 0); lcd.print("%");
        } else if (porcentagem >= 50 && porcentagem < 70) {
            lcd.print("Quase la!");
            lcd.setCursor(0, 1);
            lcd.print("Nota: "); lcd.print(porcentagem, 0); lcd.print("%");
        } else {
            lcd.print("Melhore!");
            lcd.setCursor(0, 1);
            lcd.print("Nota: "); lcd.print(porcentagem, 0); lcd.print("%");
        }
        while (true) delay(1000);
    }
}