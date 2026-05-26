#include <Arduino.h>
#include <math.h>
#include <LiquidCrystal.h>

// LCD em modo 4-bit: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pinos dos botões de dígitos 0–9
// btn10=A0(0), btn7=A1(1), btn8=A2(2), btn9=A3(3),
// btn2=A4(4), btn3=A5(5), btn6=6(6), btn1=7(7), btn4=8(8), btn5=9(9)
const int PINOS_DIGITOS[10] = { A0, A1, A2, A3, A4, A5, 6, 7, 8, 9 };

// Botão vermelho = backspace
const int PINO_BACKSPACE = 10;

// Timeout de confirmação (ms)
const unsigned long TIMEOUT_MS = 2000;

int acertos = 0;
int erros = 0;
int continuar = 1;

// ─── debounce simples ───────────────────────────────────────────────────────
bool botaoPressionado(int pino) {
    if (digitalRead(pino) == LOW) {
        delay(30);
        if (digitalRead(pino) == LOW) {
            while (digitalRead(pino) == LOW); // espera soltar
            return true;
        }
    }
    return false;
}

// ─── lê um número via botões com timeout de 4 s ────────────────────────────
// Exibe os dígitos digitados na linha 1 do LCD a partir da coluna 'col'.
// Retorna o número confirmado (ou -1 se nenhum dígito foi digitado).
long lerNumero(int linhaLCD, int colInicioLCD) {
    String entrada = "";
    unsigned long ultimoEvento = millis();

    // Limpa a área de entrada
    lcd.setCursor(colInicioLCD, linhaLCD);
    lcd.print("        "); // 8 espaços
    lcd.setCursor(colInicioLCD, linhaLCD);

    while (true) {
        // Verifica timeout
        if (entrada.length() > 0 && (millis() - ultimoEvento >= TIMEOUT_MS)) {
            break; // confirma
        }

        // Verifica botões de dígito 0–9
        for (int d = 0; d <= 9; d++) {
            if (botaoPressionado(PINOS_DIGITOS[d])) {
                if (entrada.length() < 8) {
                    entrada += String(d);
                    lcd.setCursor(colInicioLCD, linhaLCD);
                    lcd.print("        ");
                    lcd.setCursor(colInicioLCD, linhaLCD);
                    lcd.print(entrada);
                }
                ultimoEvento = millis();
            }
        }

        // Verifica backspace
        if (botaoPressionado(PINO_BACKSPACE)) {
            if (entrada.length() > 0) {
                entrada.remove(entrada.length() - 1);
                lcd.setCursor(colInicioLCD, linhaLCD);
                lcd.print("        ");
                lcd.setCursor(colInicioLCD, linhaLCD);
                lcd.print(entrada);
            }
            ultimoEvento = millis();
        }
    }

    if (entrada.length() == 0) return -1;
    return entrada.toInt();
}

// ─── potência inteira ───────────────────────────────────────────────────────
long potenciaInteira(int base, int exp) {
    long resultado = 1;
    for (int i = 0; i < exp; i++) resultado *= base;
    return resultado;
}

// ─── feedback visual ────────────────────────────────────────────────────────
void mostrarAcerto() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** ACERTOU! ***");
    acertos++;
}

void mostrarErro(long correto) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    ERROU!");
    lcd.setCursor(0, 1);
    lcd.print("Era: ");
    lcd.print(correto);
    erros++;
}

// ─── setup ──────────────────────────────────────────────────────────────────
void setup() {
    lcd.begin(16, 2);

    for (int d = 0; d <= 9; d++) pinMode(PINOS_DIGITOS[d], INPUT_PULLUP);
    pinMode(PINO_BACKSPACE, INPUT_PULLUP);

    randomSeed(analogRead(A0));

    lcd.setCursor(0, 0);
    lcd.print("  MATEMATICA!  ");
    lcd.setCursor(0, 1);
    lcd.print("   BOA SORTE!  ");
    delay(2000);
}

// ─── loop ───────────────────────────────────────────────────────────────────
void loop() {
    if (continuar == 1) {
        lcd.clear();
        int sorteio = random(1, 5); // 1 a 4

        // ── Raiz Quadrada ──────────────────────────────────────────────────
        if (sorteio == 1) {
            int nraiz = random(1, 1000);
            double raiz = sqrt(nraiz);
            while ((int)raiz * (int)raiz != nraiz) {
                nraiz = random(1, 1000);
                raiz = sqrt(nraiz);
            }
            lcd.setCursor(0, 0);
            lcd.print("Raiz de ");
            lcd.print(nraiz);
            lcd.setCursor(0, 1);
            lcd.print("R=");

            long resposta = lerNumero(1, 2);

            if (resposta == (int)raiz)  mostrarAcerto();
            else                        mostrarErro((int)raiz);
        }

        // ── Potenciação ────────────────────────────────────────────────────
        else if (sorteio == 2) {
            int npotencia = random(1, 31);
            int expoente  = (npotencia <= 10) ? random(1, 4) : random(1, 3);
            long operacao = potenciaInteira(npotencia, expoente);

            lcd.setCursor(0, 0);
            lcd.print(npotencia);
            lcd.print("^");
            lcd.print(expoente);
            lcd.print("=?");
            lcd.setCursor(0, 1);
            lcd.print("R=");

            long resposta = lerNumero(1, 2);

            if (resposta == operacao) mostrarAcerto();
            else                      mostrarErro(operacao);
        }

        // ── Logaritmo ──────────────────────────────────────────────────────
        else if (sorteio == 3) {
            int base = 2;
            int opcoes[4] = {2, 3, 5, 10};
            base = opcoes[random(0, 4)];

            int logaritimando = random(1, 1000);
            double logaritimo = log((double)logaritimando) / log((double)base);
            while (abs(logaritimo - round(logaritimo)) > 0.0001) {
                logaritimando = random(1, 1000);
                logaritimo = log((double)logaritimando) / log((double)base);
            }

            lcd.setCursor(0, 0);
            lcd.print("Log");
            lcd.print(base);
            lcd.print("(");
            lcd.print(logaritimando);
            lcd.print(")=?");
            lcd.setCursor(0, 1);
            lcd.print("R=");

            long resposta = lerNumero(1, 2);

            if (resposta == (int)round(logaritimo)) mostrarAcerto();
            else                                    mostrarErro((int)round(logaritimo));
        }

        // ── Fatorial ───────────────────────────────────────────────────────
        else if (sorteio == 4) {
            int nfatorial = random(1, 8); // 1! a 7!
            long fatorial = 1;
            for (int i = 2; i <= nfatorial; i++) fatorial *= i;

            lcd.setCursor(0, 0);
            lcd.print(nfatorial);
            lcd.print("! = ?");
            lcd.setCursor(0, 1);
            lcd.print("R=");

            long resposta = lerNumero(1, 2);

            if (resposta == fatorial) mostrarAcerto();
            else                      mostrarErro(fatorial);
        }

        delay(2000);

        // ── Continuar? ─────────────────────────────────────────────────────
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Continuar?");
        lcd.setCursor(0, 1);
        lcd.print("1=Sim  0=Nao");

        // Aguarda o usuário pressionar 1 (btn7=A1) ou 0 (btn10=A0)
        while (true) {
            if (botaoPressionado(PINOS_DIGITOS[1])) { continuar = 1; break; }
            if (botaoPressionado(PINOS_DIGITOS[0])) { continuar = 0; break; }
        }

    } else {
        // ── Tela final ─────────────────────────────────────────────────────
        lcd.clear();
        double porcentagem = (acertos + erros > 0)
            ? (100.0 * acertos) / (acertos + erros)
            : 0;

        if (porcentagem >= 70) {
            lcd.setCursor(0, 0);
            lcd.print("  Parabens!  ");
        } else if (porcentagem >= 50) {
            lcd.setCursor(0, 0);
            lcd.print("  Quase la!  ");
        } else {
            lcd.setCursor(0, 0);
            lcd.print("   Melhore!  ");
        }
        lcd.setCursor(0, 1);
        lcd.print("Nota: ");
        lcd.print((int)porcentagem);
        lcd.print("%");

        while (true) delay(1000);
    }
}