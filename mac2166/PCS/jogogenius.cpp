// Genius Game - Versão C++ com 4 Pushbuttons
// Sequência aleatória de 1 a 4 é gerada
// Um novo dígito é adicionado a cada acerto
// O jogador deve repetir a sequência inteira usando os 4 botões

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// Simulação de pushbuttons - em Arduino seria leitura de pinos digitais
class PushButton {
private:
    int pinNumber;
    bool pressed;
    
public:
    PushButton(int pin) : pinNumber(pin), pressed(false) {}
    
    // Simula leitura do botão (em Arduino seria digitalRead)
    int read() {
        return pressed ? 1 : 0;
    }
    
    // Simula pressão do botão (para testes)
    void setPressed(bool state) {
        pressed = state;
    }
    
    int getPinNumber() const {
        return pinNumber;
    }
};

// Classe para gerenciar o jogo
class GeniusGame {
private:
    const int NUM_BUTTONS = 4;
    const int MAX_SEQUENCE = 100;
    
    vector<int> sequence;
    vector<int> playerInput;
    int score;
    bool gameActive;
    
    PushButton buttons[4];
    int buttonPins[4] = {2, 3, 4, 5}; // Pinos exemplo para Arduino
    
public:
    GeniusGame() : score(0), gameActive(true), 
                   buttons{PushButton(2), PushButton(3), PushButton(4), PushButton(5)} {
        sequence.reserve(MAX_SEQUENCE);
        playerInput.reserve(MAX_SEQUENCE);
    }
    
    // Inicializa o jogo com uma seed
    void initialize(unsigned int seed) {
        srand(seed);
        sequence.clear();
        playerInput.clear();
        score = 0;
        gameActive = true;
    }
    
    // Gera um novo dígito aleatório (1-4) e adiciona à sequência
    void generateNewDigit() {
        int newDigit = (rand() % NUM_BUTTONS) + 1;
        sequence.push_back(newDigit);
    }
    
    // Exibe a sequência atual (com delays para visualização)
    void displaySequence() {
        cout << "\n--- Sequência a repetir: ";
        for (int digit : sequence) {
            cout << digit << " ";
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        cout << "\n";
    }
    
    // Aguarda entrada do jogador via pushbuttons
    // Retorna -1 se timeout, caso contrário retorna o número do botão (1-4)
    int waitForButtonPress(int timeoutMs = 5000) {
        auto startTime = chrono::steady_clock::now();
        
        while (true) {
            auto currentTime = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime);
            
            if (elapsed.count() > timeoutMs) {
                return -1; // Timeout
            }
            
            // Verifica cada botão (em Arduino seria digitalRead)
            for (int i = 0; i < NUM_BUTTONS; i++) {
                if (buttons[i].read()) {
                    // Aguarda soltar o botão
                    this_thread::sleep_for(chrono::milliseconds(50));
                    while (buttons[i].read() && elapsed.count() < timeoutMs) {
                        this_thread::sleep_for(chrono::milliseconds(10));
                    }
                    return i + 1; // Retorna botão 1-4
                }
            }
            
            this_thread::sleep_for(chrono::milliseconds(20));
        }
    }
    
    // Obtém entrada do jogador manualmente (para teste sem Arduino)
    int getPlayerInput() {
        int button;
        cout << "Digite o número do botão (1-4): ";
        cin >> button;
        
        if (button < 1 || button > 4) {
            cout << "Entrada inválida! Digite entre 1 e 4.\n";
            return -1;
        }
        return button;
    }
    
    // Verifica se a entrada do jogador está correta
    bool checkPlayerInput(int inputValue) {
        if (inputValue == sequence[playerInput.size()]) {
            playerInput.push_back(inputValue);
            cout << "✓ Correto! (" << inputValue << ")\n";
            
            // Se completou a sequência, próxima rodada
            if (playerInput.size() == sequence.size()) {
                score++;
                playerInput.clear();
                return true; // Sequência completa corretamente
            }
            return true; // Entrada correta, aguarda próxima
        } else {
            cout << "✗ Errado! Era " << sequence[playerInput.size()] 
                 << " e você digitou " << inputValue << "\n";
            gameActive = false;
            return false;
        }
    }
    
    // Executa uma rodada do jogo
    void playRound() {
        generateNewDigit();
        displaySequence();
        
        cout << "Sua vez! Repita a sequência:\n";
        
        while (!playerInput.empty() && playerInput.size() < sequence.size()) {
            int input = getPlayerInput(); // Para teste sem Arduino
            // Para usar com Arduino real: int input = waitForButtonPress();
            
            if (input > 0 && !checkPlayerInput(input)) {
                break; // Erro - jogo termina
            }
        }
    }
    
    // Exibe o resultado final
    void showGameOver() {
        cout << "\n╔════════════════════╗\n";
        cout << "║    GAME OVER       ║\n";
        cout << "║ Pontuação: " << (score < 10 ? " " : "") << score << "        ║\n";
        cout << "╚════════════════════╝\n";
    }
    
    // Retorna se o jogo ainda está ativo
    bool isActive() const {
        return gameActive;
    }
    
    int getScore() const {
        return score;
    }
    
    // Simula pressão de botão (para testes)
    void simulateButtonPress(int buttonNumber) {
        if (buttonNumber >= 1 && buttonNumber <= NUM_BUTTONS) {
            buttons[buttonNumber - 1].setPressed(true);
        }
    }
    
    void simulateButtonRelease(int buttonNumber) {
        if (buttonNumber >= 1 && buttonNumber <= NUM_BUTTONS) {
            buttons[buttonNumber - 1].setPressed(false);
        }
    }
};

int main() {
    GeniusGame game;
    unsigned int seed;
    
    cout << "╔════════════════════╗\n";
    cout << "║   GENIUS GAME      ║\n";
    cout << "║  4 Pushbuttons     ║\n";
    cout << "╚════════════════════╝\n\n";
    
    cout << "Digite a seed (ou 0 para usar o relógio): ";
    cin >> seed;
    
    if (seed == 0) {
        seed = time(nullptr);
    }
    
    game.initialize(seed);
    
    cout << "\nBotões: 1, 2, 3, 4\n";
    cout << "Repita a sequência exibida!\n";
    cout << "═════════════════════════════════════\n";
    
    while (game.isActive()) {
        game.playRound();
    }
    
    game.showGameOver();
    
    return 0;
}
