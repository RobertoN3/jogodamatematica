#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ── Pinos ─────────────────────────────────────────────────────────────────────
const int BTN_CIMA     = A1;
const int BTN_BAIXO    = A0;
const int BTN_CONFIRMA = 10;
const int PINOS_DIGITOS[10] = { A0, A1, A2, A3, A4, A5, 6, 7, 8, 9 };
const int PINO_BACKSPACE    = 10;
const unsigned long TIMEOUT_MS = 2000;

// ── Menu ──────────────────────────────────────────────────────────────────────
const char* itens[] = {
  "Teste de Reacao",
  "Math Avancada",
  "Math"
};
const int NUM_ITENS = 3;
int selecionado = 0;

// ── Protótipos ────────────────────────────────────────────────────────────────
void exibirMenu();
void jogoTesteReacao();
void jogoMathAvancada();
void jogoMath();

// ── Auxiliares Math Avançada ──────────────────────────────────────────────────
bool   botaoPressionado(int pino);
long   lerNumero(int linhaLCD, int colInicioLCD);
long   potenciaInteira(int base, int exp);
void   mostrarAcerto(int &acertos);
void   mostrarErro(long correto, int &erros);

// ── Auxiliares Math ───────────────────────────────────────────────────────────
int  operacao(long a);
int  numeromasub99(long b);
int  numeromasub999(long b);
int  numeromultB11_20(long d);
int  numeromultB21_50(long d);
int  numeromultB51_100(long d);
int  numeromultA(int nivel, long rand_val);
void troca_se_menor(int *a, int *b);
int  lerBotaoMath();
int  obterRespostaUsuario();
bool processa_pergunta(int a, int b, char operador, int resultado_correto,
                       int *contador_progresso, int &totalPerguntas, int &totalAcertos);

void (*jogos[])() = { jogoTesteReacao, jogoMathAvancada, jogoMath };

// ── Menu ──────────────────────────────────────────────────────────────────────
void exibirMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("> ");
  lcd.print(itens[selecionado]);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  lcd.print(itens[(selecionado + 1) % NUM_ITENS]); // Corrigido aqui (selecionado)
}

// ── Setup / Loop ──────────────────────────────────────────────────────────────
void setup() {
  lcd.begin(16, 2);
  pinMode(BTN_CIMA,     INPUT_PULLUP);
  pinMode(BTN_BAIXO,    INPUT_PULLUP);
  pinMode(BTN_CONFIRMA, INPUT_PULLUP);
  for (int d = 0; d <= 9; d++) pinMode(PINOS_DIGITOS[d], INPUT_PULLUP);
  randomSeed(analogRead(A5));
  exibirMenu();
}

void loop() {
  if (digitalRead(BTN_CIMA) == LOW) {
    while (digitalRead(BTN_CIMA) == LOW);
    selecionado = (selecionado - 1 + NUM_ITENS) % NUM_ITENS;
    exibirMenu();
  }
  if (digitalRead(BTN_BAIXO) == LOW) {
    while (digitalRead(BTN_BAIXO) == LOW);
    selecionado = (selecionado + 1) % NUM_ITENS;
    exibirMenu();
  }
  if (digitalRead(BTN_CONFIRMA) == LOW) {
    while (digitalRead(BTN_CONFIRMA) == LOW);
    jogos[selecionado]();
    exibirMenu();
  }
}

// ═════════════════════════════════════════════════════════════════════════════
// JOGO 1 — Teste de Reação
// ═════════════════════════════════════════════════════════════════════════════
void jogoTesteReacao() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Teste de Reacao");
  lcd.setCursor(0, 1); lcd.print("SIM (1) NAO (0)");

  while (true) {
    if (digitalRead(BTN_CIMA) == LOW) {
      while (digitalRead(BTN_CIMA) == LOW);
      break;
    }
    if (digitalRead(BTN_BAIXO) == LOW) {
      while (digitalRead(BTN_BAIXO) == LOW);
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("    Ate logo!   ");
      lcd.setCursor(0, 1); lcd.print("                ");
      delay(3000);
      lcd.clear();
      return;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Aguarde o sinal");
  lcd.setCursor(0, 1); lcd.print("                ");
  delay(random(3000, 10001));

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("*** AGORA!!! ***");
  lcd.setCursor(0, 1); lcd.print(" Pressione btn! ");

  unsigned long inicio = millis();
  while (digitalRead(BTN_CONFIRMA) == HIGH);
  unsigned long fim = millis();
  while (digitalRead(BTN_CONFIRMA) == LOW);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Seu tempo:");
  lcd.setCursor(0, 1); lcd.print(fim - inicio); lcd.print(" ms");
  delay(3000);
}

// ═════════════════════════════════════════════════════════════════════════════
// JOGO 2 — Math Avançada
// ═════════════════════════════════════════════════════════════════════════════
bool botaoPressionado(int pino) {
  if (digitalRead(pino) == LOW) {
    delay(30);
    if (digitalRead(pino) == LOW) {
      while (digitalRead(pino) == LOW);
      return true;
    }
  }
  return false;
}

long lerNumero(int linhaLCD, int colInicioLCD) { // Corrigido aqui (linhaLCD)
  String entrada = "";
  unsigned long ultimoEvento = millis();
  lcd.setCursor(colInicioLCD, linhaLCD);
  lcd.print("        ");
  lcd.setCursor(colInicioLCD, linhaLCD);

  while (true) {
    if (entrada.length() > 0 && (millis() - ultimoEvento >= TIMEOUT_MS)) break;
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

long potenciaInteira(int base, int exp) {
  long resultado = 1;
  for (int i = 0; i < exp; i++) resultado *= base;
  return resultado;
}

void mostrarAcerto(int &acertos) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("*** ACERTOU! ***");
  acertos++;
}

void mostrarErro(long correto, int &erros) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("    ERROU!");
  lcd.setCursor(0, 1); lcd.print("Era: "); lcd.print(correto);
  erros++;
}

void jogoMathAvancada() {
  int acertos = 0, erros = 0;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("  MATEMATICA!  ");
  lcd.setCursor(0, 1); lcd.print("   BOA SORTE!  ");
  delay(2000);

  while (true) {
    lcd.clear();
    int sorteio = random(1, 5);

    if (sorteio == 1) {
      int nraiz = random(1, 1000);
      double raiz = sqrt(nraiz);
      while ((int)raiz * (int)raiz != nraiz) { nraiz = random(1, 1000); raiz = sqrt(nraiz); }
      lcd.setCursor(0, 0); lcd.print("Raiz de "); lcd.print(nraiz);
      lcd.setCursor(0, 1); lcd.print("R=");
      long resposta = lerNumero(1, 2);
      if (resposta == (int)raiz) mostrarAcerto(acertos);
      else                       mostrarErro((int)raiz, erros);
    }
    else if (sorteio == 2) {
      int npotencia = random(1, 31);
      int expoente  = (npotencia <= 10) ? random(1, 4) : random(1, 3);
      long operacao = potenciaInteira(npotencia, expoente);
      lcd.setCursor(0, 0);
      lcd.print(npotencia); lcd.print("^"); lcd.print(expoente); lcd.print("=?");
      lcd.setCursor(0, 1); lcd.print("R=");
      long resposta = lerNumero(1, 2);
      if (resposta == operacao) mostrarAcerto(acertos);
      else                      mostrarErro(operacao, erros);
    }
    else if (sorteio == 3) {
      int opcoes[4] = {2, 3, 5, 10};
      int base = opcoes[random(0, 4)];
      int logaritimando = random(1, 1000);
      double logaritimo = log((double)logaritimando) / log((double)base);
      while (abs(logaritimo - round(logaritimo)) > 0.0001) {
        logaritimando = random(1, 1000);
        logaritimo    = log((double)logaritimando) / log((double)base);
      }
      lcd.setCursor(0, 0);
      lcd.print("Log"); lcd.print(base);
      lcd.print("(");   lcd.print(logaritimando); lcd.print(")=?");
      lcd.setCursor(0, 1); lcd.print("R=");
      long resposta = lerNumero(1, 2);
      if (resposta == (int)round(logaritimo)) mostrarAcerto(acertos);
      else                                    mostrarErro((int)round(logaritimo), erros);
    }
    else {
      int nfatorial = random(1, 8);
      long fatorial = 1;
      for (int i = 2; i <= nfatorial; i++) fatorial *= i;
      lcd.setCursor(0, 0); lcd.print(nfatorial); lcd.print("! = ?");
      lcd.setCursor(0, 1); lcd.print("R=");
      long resposta = lerNumero(1, 2);
      if (resposta == fatorial) mostrarAcerto(acertos);
      else                      mostrarErro(fatorial, erros);
    }

    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Continuar?");
    lcd.setCursor(0, 1); lcd.print("1=Sim  0=Nao");

    bool decisao = false;
    while (true) {
      if (botaoPressionado(PINOS_DIGITOS[1])) { decisao = true;  break; }
      if (botaoPressionado(PINOS_DIGITOS[0])) { decisao = false; break; }
    }
    if (!decisao) break;
  }

  lcd.clear();
  double porcentagem = (acertos + erros > 0) ? (100.0 * acertos) / (acertos + erros) : 0;
  lcd.setCursor(0, 0);
  if      (porcentagem >= 70) lcd.print("  Parabens!    ");
  else if (porcentagem >= 50) lcd.print("  Quase la!    ");
  else                        lcd.print("    Melhore!    ");
  lcd.setCursor(0, 1);
  lcd.print("Nota: "); lcd.print((int)porcentagem); lcd.print("%");
  delay(3000);
}

// ═════════════════════════════════════════════════════════════════════════════
// JOGO 3 — Math (Normal)
// ═════════════════════════════════════════════════════════════════════════════
int lerBotaoMath() {
  const int pinosBotoes[11] = { A0, A1, A2, A3, A4, A5, 6, 7, 8, 9, 10 };
  for (int i = 0; i < 11; i++) {
    if (digitalRead(pinosBotoes[i]) == LOW) {
      delay(50);
      while (digitalRead(pinosBotoes[i]) == LOW) delay(10);
      delay(50);
      return i;
    }
  }
  return -1;
}

int obterRespostaUsuario() {
  int valorTotal = 0;
  bool digitouAlgo = false;
  unsigned long tempoUltimoDigito = millis();

  while (true) {
    int botaoPressionado = lerBotaoMath();

    if (botaoPressionado == 10) {
      if (digitouAlgo && valorTotal > 0) {
        valorTotal = valorTotal / 10;
        if (valorTotal == 0) {
          digitouAlgo = false;
          lcd.setCursor(0, 1); lcd.print("Digite...       ");
        } else {
          lcd.setCursor(0, 1); lcd.print("                ");
          lcd.setCursor(0, 1); lcd.print(valorTotal);
        }
        tempoUltimoDigito = millis();
      }
    }
    else if (botaoPressionado != -1) {
      if (!digitouAlgo) {
        digitouAlgo = true;
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(0, 1);
      }
      valorTotal = (valorTotal * 10) + botaoPressionado;
      lcd.print(botaoPressionado);
      tempoUltimoDigito = millis();
    }

    if (digitouAlgo && (millis() - tempoUltimoDigito > 4500)) break;
  }
  return valorTotal;
}

bool processa_pergunta(int a, int b, char operador, int resultado_correto,
                       int *contador_progresso, int &totalPerguntas, int &totalAcertos) {
  totalPerguntas++;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(a); lcd.print(" "); lcd.print(operador);
  lcd.print(" "); lcd.print(b); lcd.print(" = ?");
  lcd.setCursor(0, 1); lcd.print("Digite...");

  int resposta = obterRespostaUsuario();

  lcd.clear();
  if (resposta == resultado_correto) {
    lcd.setCursor(0, 0); lcd.print("Acertou!");
    totalAcertos++;
    (*contador_progresso)++;
    delay(1500);
    return true;
  } else {
    lcd.setCursor(0, 0); lcd.print("Errouu!");
    lcd.setCursor(0, 1);
    lcd.print(a); lcd.print(operador); lcd.print(b);
    lcd.print("="); lcd.print(resultado_correto);
    delay(3000);
    return false;
  }
}

void jogoMath() {
  int dificuldade    = 0;
  int nivel          = 1;
  int totalPerguntas = 0;
  int totalAcertos   = 0;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Jogo Matematica");
  lcd.setCursor(0, 1); lcd.print("Prepare-se...");
  delay(2000);

  while (true) {
    long r    = random(0, 2147483647L);
    int opera = operacao(r);
    int a, b;

    if (opera == 1) {
      if      (dificuldade < 5)  { a = numerosomasub99(random(0,10000));  b = numerosomasub99(random(0,10000)); }
      else if (dificuldade < 10) { a = numerosomasub999(random(0,10000)); b = numerosomasub99(random(0,10000)); }
      else                       { a = numerosomasub999(random(0,10000)); b = numerosomasub999(random(0,10000)); }
      processa_pergunta(a, b, '+', a+b, &dificuldade, totalPerguntas, totalAcertos);
    }
    else if (opera == 2) {
      if      (dificuldade < 5)  { a = numerosomasub99(random(0,10000));  b = numerosomasub99(random(0,10000)); }
      else if (dificuldade < 10) { a = numerosomasub999(random(0,10000)); b = numerosomasub99(random(0,10000)); }
      else                       { a = numerosomasub999(random(0,10000)); b = numerosomasub999(random(0,10000)); }
      troca_se_menor(&a, &b);
      processa_pergunta(a, b, '-', a-b, &dificuldade, totalPerguntas, totalAcertos);
    }
    else if (opera == 3) {
      switch (nivel) {
        case 1:            a = numeromultA(1,random(0,10000)); b = numeromultB11_20(random(0,10000)); break;
        case 2: case 3:    a = numeromultA(1,random(0,10000)); b = numeromultB21_50(random(0,10000)); break;
        case 4: case 5:    a = numeromultA(1,random(0,10000)); b = numeromultB51_100(random(0,10000)); break;
        case 6: case 7:    a = numeromultA(2,random(0,10000)); b = numeromultB11_20(random(0,10000)); break;
        case 8:            a = numeromultA(2,random(0,10000)); b = numeromultB21_50(random(0,10000)); break;
        case 9: case 10:   a = numeromultA(3,random(0,10000)); b = numeromultB11_20(random(0,10000)); break;
        case 11: case 12:  a = numeromultA(2,random(0,10000)); b = numeromultB51_100(random(0,10000)); break;
        case 13:           a = numeromultA(4,random(0,10000)); b = numeromultB11_20(random(0,10000)); break;
        case 14:           a = numeromultA(3,random(0,10000)); b = numeromultB21_50(random(0,10000)); break;
        case 15:           a = numeromultA(4,random(0,10000)); b = numeromultB21_50(random(0,10000)); break;
        case 16: case 17:  a = numeromultA(3,random(0,10000)); b = numeromultB51_100(random(0,10000)); break;
        case 18:           a = numeromultA(4,random(0,10000)); b = numeromultB51_100(random(0,10000)); break;
        default:           a = numeromultA(5,random(0,10000)); b = numeromultB21_50(random(0,10000)); break;
      }
      processa_pergunta(a, b, '*', a*b, &nivel, totalPerguntas, totalAcertos);
    }
    else {
      switch (nivel) {
        case 1:            b = numeromultA(1,random(0,10000)); a = b*numeromultB11_20(random(0,10000)); break;
        case 2: case 3:    b = numeromultA(1,random(0,10000)); a = b*numeromultB21_50(random(0,10000)); break;
        case 4: case 5:    b = numeromultA(1,random(0,10000)); a = b*numeromultB51_100(random(0,10000)); break;
        case 6: case 7:    b = numeromultA(2,random(0,10000)); a = b*numeromultB11_20(random(0,10000)); break;
        case 8:            b = numeromultA(2,random(0,10000)); a = b*numeromultB21_50(random(0,10000)); break;
        case 9: case 10:   b = numeromultA(3,random(0,10000)); a = b*numeromultB11_20(random(0,10000)); break;
        case 11: case 12:  b = numeromultA(2,random(0,10000)); a = b*numeromultB51_100(random(0,10000)); break;
        case 13:           b = numeromultA(4,random(0,10000)); a = b*numeromultB11_20(random(0,10000)); break;
        case 14:           b = numeromultA(3,random(0,10000)); a = b*numeromultB21_50(random(0,10000)); break;
        case 15:           b = numeromultA(4,random(0,10000)); a = b*numeromultB21_50(random(0,10000)); break;
        case 16: case 17:  b = numeromultA(3,random(0,10000)); a = b*numeromultB51_100(random(0,10000)); break;
        case 18:           b = numeromultA(4,random(0,10000)); a = b*numeromultB51_100(random(0,10000)); break;
        default:           b = numeromultA(5,random(0,10000)); a = b*numeromultB21_50(random(0,10000)); break;
      }
      processa_pergunta(a, b, '/', a/b, &nivel, totalPerguntas, totalAcertos);
    }

    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Continuar?");
    lcd.setCursor(0, 1); lcd.print("1=Sim  0=Nao");

    bool decisao = false;
    while (true) {
      if (botaoPressionado(PINOS_DIGITOS[1])) { decisao = true;  break; }
      if (botaoPressionado(PINOS_DIGITOS[0])) { decisao = false; break; }
    }
    if (!decisao) break;
  }

  lcd.clear();
  double porcentagem = (totalPerguntas > 0) ? (100.0 * totalAcertos) / totalPerguntas : 0;
  lcd.setCursor(0, 0);
  if      (porcentagem >= 70) lcd.print("  Parabens!    ");
  else if (porcentagem >= 50) lcd.print("  Quase la!    ");
  else                        lcd.print("    Melhore!    ");
  lcd.setCursor(0, 1);
  lcd.print("Nota: "); lcd.print((int)porcentagem); lcd.print("%");
  delay(3000);
}

// ── Funções matemáticas (Math) ────────────────────────────────────────────────
int operacao(long a)          { if (a%4==1) return 1; if (a%4==2) return 2; if (a%4==3) return 3; return 4; }
int numerosomasub99(long b)   { return (b % 99) + 1; }
int numerosomasub999(long b)  { return (b % 900) + 100; }
int numeromultB11_20(long d)  { return (d % 10) + 11; }
int numeromultB21_50(long d)  { return (d % 30) + 21; }
int numeromultB51_100(long d) { return (d % 50) + 51; }
int numeromultA(int nivel, long rand_val) {
  if (nivel==1) { if (rand_val%3==0) return 1; if (rand_val%3==1) return 2; return 10; }
  if (nivel==2) { if (rand_val%2==0) return 4; return 5; }
  if (nivel==3) { if (rand_val%4==0) return 3; if (rand_val%4==1) return 6; if (rand_val%4==2) return 8; return 9; }
  if (nivel==4) return 7;
  return (rand_val % 8) + 2;
}
void troca_se_menor(int *a, int *b) { if (*a < *b) { int temp=*a; *a=*b; *b=temp; } }