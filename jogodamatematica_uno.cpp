#include <LiquidCrystal.h>

// --- Configuração do LCD ---
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// --- Configuração dos Botões ---
const int pinosBotoes[11] = {A0, A1, A2, A3, A4, A5, 6, 7, 8, 9, 10};

// --- Variáveis de Controle do Jogo ---
bool jogo = true;
int dificuldade = 0; 
int nivel = 1;       

// Novas variáveis para estatísticas e pontuação
int totalPerguntas = 0;
int totalAcertos = 0;

// --- Protótipos das Funções ---
int operacao(long a);
int numerosomasub99(long b);
int numerosomasub999(long b);
int numeromultB11_20(long d);
int numeromultB21_50(long d);
int numeromultB51_100(long d);
int numeromultA(int nivel, long rand_val);
void troca_se_menor(int *a, int *b);
int lerBotao();
int obterRespostaUsuario();
bool processa_pergunta(int a, int b, char operador, int resultado_correto, int *contador_progresso);
void telaFimDeJogo();

void setup() {
  lcd.begin(16, 2);
  
  for (int i = 0; i < 11; i++) {
    pinMode(pinosBotoes[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A7)); 

  lcd.print("Jogo Matematica");
  lcd.setCursor(0, 1);
  lcd.print("Prepare-se...");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (jogo) {
    long r = random(0, 2147483647);
    int opera = operacao(r);
    int a, b;

    if (opera == 1) {
      if (dificuldade < 5) { a = numerosomasub99(random(0, 10000)); b = numerosomasub99(random(0, 10000)); }
      else if (dificuldade < 10) { a = numerosomasub999(random(0, 10000)); b = numerosomasub99(random(0, 10000)); }
      else { a = numerosomasub999(random(0, 10000)); b = numerosomasub999(random(0, 10000)); }
      jogo = processa_pergunta(a, b, '+', a + b, &dificuldade);
    }
    else if (opera == 2) {
      if (dificuldade < 5) { a = numerosomasub99(random(0, 10000)); b = numerosomasub99(random(0, 10000)); }
      else if (dificuldade < 10) { a = numerosomasub999(random(0, 10000)); b = numerosomasub99(random(0, 10000)); }
      else { a = numerosomasub999(random(0, 10000)); b = numerosomasub999(random(0, 10000)); }
      troca_se_menor(&a, &b);
      jogo = processa_pergunta(a, b, '-', a - b, &dificuldade);
    }
    else if (opera == 3) {
      switch (nivel) {
        case 1:           a = numeromultA(1, random(0, 10000)); b = numeromultB11_20(random(0, 10000)); break;
        case 2: case 3:   a = numeromultA(1, random(0, 10000)); b = numeromultB21_50(random(0, 10000)); break;
        case 4: case 5:   a = numeromultA(1, random(0, 10000)); b = numeromultB51_100(random(0, 10000)); break;
        case 6: case 7:   a = numeromultA(2, random(0, 10000)); b = numeromultB11_20(random(0, 10000)); break;
        case 8:           a = numeromultA(2, random(0, 10000)); b = numeromultB21_50(random(0, 10000)); break;
        case 9: case 10:  a = numeromultA(3, random(0, 10000)); b = numeromultB11_20(random(0, 10000)); break;
        case 11: case 12: a = numeromultA(2, random(0, 10000)); b = numeromultB51_100(random(0, 10000)); break;
        case 13:          a = numeromultA(4, random(0, 10000)); b = numeromultB11_20(random(0, 10000)); break;
        case 14:          a = numeromultA(3, random(0, 10000)); b = numeromultB21_50(random(0, 10000)); break;
        case 15:          a = numeromultA(4, random(0, 10000)); b = numeromultB21_50(random(0, 10000)); break;
        case 16: case 17: a = numeromultA(3, random(0, 10000)); b = numeromultB51_100(random(0, 10000)); break;
        case 18:          a = numeromultA(4, random(0, 10000)); b = numeromultB51_100(random(0, 10000)); break;
        default:          a = numeromultA(5, random(0, 10000)); b = numeromultB21_50(random(0, 10000)); break;
      }
      jogo = processa_pergunta(a, b, '*', a * b, &nivel);
    }
    else if (opera == 4) {
      switch (nivel) {
        case 1:           b = numeromultA(1, random(0, 10000)); a = b * numeromultB11_20(random(0, 10000)); break;
        case 2: case 3:   b = numeromultA(1, random(0, 10000)); a = b * numeromultB21_50(random(0, 10000)); break;
        case 4: case 5:   b = numeromultA(1, random(0, 10000)); a = b * numeromultB51_100(random(0, 10000)); break;
        case 6: case 7:   b = numeromultA(2, random(0, 10000)); a = b * numeromultB11_20(random(0, 10000)); break;
        case 8:           b = numeromultA(2, random(0, 10000)); a = b * numeromultB21_50(random(0, 10000)); break;
        case 9: case 10:  b = numeromultA(3, random(0, 10000)); a = b * numeromultB11_20(random(0, 10000)); break;
        case 11: case 12: b = numeromultA(2, random(0, 10000)); a = b * numeromultB51_100(random(0, 10000)); break;
        case 13:          b = numeromultA(4, random(0, 10000)); a = b * numeromultB11_20(random(0, 10000)); break;
        case 14:          b = numeromultA(3, random(0, 10000)); a = b * numeromultB21_50(random(0, 10000)); break;
        case 15:          b = numeromultA(4, random(0, 10000)); a = b * numeromultB21_50(random(0, 10000)); break;
        case 16: case 17: b = numeromultA(3, random(0, 10000)); a = b * numeromultB51_100(random(0, 10000)); break;
        case 18:          b = numeromultA(4, random(0, 10000)); a = b * numeromultB51_100(random(0, 10000)); break;
        default:          b = numeromultA(5, random(0, 10000)); a = b * numeromultB21_50(random(0, 10000)); break;
      }
      jogo = processa_pergunta(a, b, '/', a / b, &nivel);
    }
  } 
  else {
    // Menu de escolha após o erro
    lcd.clear();
    lcd.print("0:Sair");
    lcd.setCursor(0, 1);
    lcd.print("1-9:Continuar");

    int escolha = -1;
    // Aguarda até que o usuário aperte uma opção válida (0 a 9)
    while (escolha == -1 || escolha == 10) { 
      escolha = lerBotao();
    }

    if (escolha == 0) {
      // Se escolheu 0, encerra definitivamente mostrando as porcentagens
      telaFimDeJogo();
    } else {
      // Se escolheu de 1 a 9, o jogo continua de onde parou (mantém nível e dificuldade atuais)
      lcd.clear();
      lcd.print("Continuando...");
      delay(1500);
      jogo = true;
    }
  }
}

// --- Funções de Leitura de Botões ---

int lerBotao() {
  for (int i = 0; i < 11; i++) {
    if (digitalRead(pinosBotoes[i]) == LOW) { 
      delay(50); // Debounce
      while(digitalRead(pinosBotoes[i]) == LOW) { delay(10); }
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
    int botaoPressionado = lerBotao();
    
    if (botaoPressionado == 10) {
      if (digitouAlgo && valorTotal > 0) {
        valorTotal = valorTotal / 10; 
        if (valorTotal == 0) {
          digitouAlgo = false;
          lcd.setCursor(0, 1);
          lcd.print("Digite...       ");
        } else {
          lcd.setCursor(0, 1);
          lcd.print("                "); 
          lcd.setCursor(0, 1);
          lcd.print(valorTotal);
        }
        tempoUltimoDigito = millis(); 
      }
    }
    else if (botaoPressionado != -1) {
      if (!digitouAlgo) {
        digitouAlgo = true;
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
      }
      valorTotal = (valorTotal * 10) + botaoPressionado;
      lcd.print(botaoPressionado);
      tempoUltimoDigito = millis(); 
    }
    
    if (digitouAlgo && (millis() - tempoUltimoDigito > 4500)) {
      break;
    }
  }
  return valorTotal;
}

bool processa_pergunta(int a, int b, char operador, int resultado_correto, int *contador_progresso) {
  totalPerguntas++; // Incrementa o total de rodadas jogadas
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(a); lcd.print(" "); lcd.print(operador); lcd.print(" "); lcd.print(b); lcd.print(" = ?");
  lcd.setCursor(0, 1);
  lcd.print("Digite...");

  int resposta = obterRespostaUsuario();

  lcd.clear();
  if (resposta == resultado_correto) {
    lcd.setCursor(0, 0);
    lcd.print("Acertou!");
    totalAcertos++; // Incrementa os acertos para a pontuação
    (*contador_progresso)++;
    delay(1500);
    return true;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Errouu!");
    lcd.setCursor(0, 1);
    lcd.print(a); lcd.print(operador); lcd.print(b); lcd.print("="); lcd.print(resultado_correto);
    delay(3000); // Exibe o resultado correto por 3 segundos antes do menu
    return false; // Retorna falso para cair na lógica do menu no loop principal
  }
}

// --- Nova Função: Exibe Pontuação Final e Trava o Jogo ---
void telaFimDeJogo() {
  lcd.clear();
  lcd.print("Jogo Encerrado!");
  
  // Calcula a porcentagem inteira com segurança contra divisão por zero
  int porcentagem = 0;
  if (totalPerguntas > 0) {
    // Multiplicamos por 100 antes de dividir para manter a precisão do valor inteiro
    porcentagem = (totalAcertos * 100) / totalPerguntas; 
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Aproveit.: ");
  lcd.print(porcentagem);
  lcd.print("%");
  
  // Loop infinito: trava aqui até que o Arduino físico/Wokwi seja reiniciado manualmente
  while(true) {
    delay(1000); 
  }
}

// --- Funções Matemáticas ---
int operacao(long a) { if (a % 4 == 1) return 1; if (a % 4 == 2) return 2; if (a % 4 == 3) return 3; return 4; }
int numerosomasub99(long b) { return (b % 99) + 1; }
int numerosomasub999(long b) { return (b % 900) + 100; }
int numeromultB11_20(long d) { return (d % 10) + 11; }
int numeromultB21_50(long d) { return (d % 30) + 21; }
int numeromultB51_100(long d) { return (d % 50) + 51; }
int numeromultA(int nivel, long rand_val) {
  if (nivel == 1) { if (rand_val % 3 == 0) return 1; if (rand_val % 3 == 1) return 2; return 10; }
  if (nivel == 2) { if (rand_val % 2 == 0) return 4; return 5; }
  if (nivel == 3) { if (rand_val % 4 == 0) return 3; if (rand_val % 4 == 1) return 6; if (rand_val % 4 == 2) return 8; return 9; }
  if (nivel == 4) return 7;
  return (rand_val % 8) + 2;
}
void troca_se_menor(int *a, int *b) { if (*a < *b) { int temp = *a; *a = *b; *b = temp; } }
