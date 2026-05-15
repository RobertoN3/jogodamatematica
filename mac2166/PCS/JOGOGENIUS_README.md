# Jogogenius - Conversão para C++ com 4 Pushbuttons

## 📋 Arquivos Criados

### 1. **jogogenius.cpp** - Versão C++ Desktop
Versão portável para compilar em qualquer máquina (Windows, Linux, macOS)

**Características:**
- Simulação de 4 pushbuttons em software
- Usa classes C++ para organização melhor
- Interface com feedback visual
- Modo de teste manual (entrada por teclado)

**Compilação:**
```bash
g++ -std=c++11 -o jogogenius jogogenius.cpp
./jogogenius
```

**Como funciona:**
- Digite uma seed para iniciar
- O jogo gera uma sequência aleatória (1-4)
- Digite cada número da sequência para repetir
- Cada acerto adiciona um novo número

---

### 2. **jogogenius_arduino.ino** - Versão Arduino
Código pronto para programar em um Arduino/microcontrolador com 4 botões reais

**Componentes necessários:**
- Arduino (Uno, Nano, Mega, etc.)
- 4 Pushbuttons
- 4 Resistores 10kΩ (pull-down)
- 4 LEDs (opcional, para feedback visual)
- 1 Buzzer/Speaker (opcional, para feedback sonoro)
- 4 Resistores 220Ω (se usar LEDs)

**Pinagem Padrão:**
```
Botões (entrada):    Pinos 2, 3, 4, 5
LEDs (saída):        Pinos 6, 7, 8, 9 (opcional)
Buzzer (saída):      Pino 10 (opcional)
```

**Esquema de Conexão do Botão:**
```
┌─────┐
│ 5V  ├─┐
└─────┘ │
        ├─[Botão]─┬─[10kΩ]─ GND
        │         │
        └─────────┤ Pino Digital (2-5)
```

**Frequências dos Tons (opcional):**
- Botão 1: 262 Hz (Dó)
- Botão 2: 294 Hz (Ré)
- Botão 3: 330 Hz (Mi)
- Botão 4: 349 Hz (Fá)

---

## 🎮 Principais Mudanças em Relação ao C Original

| Aspecto | C Original | C++ / Arduino |
|---------|-----------|--------------|
| **Entrada** | Teclado (scanf) | Pushbuttons (pinos digitais) |
| **Estrutura** | Procedural | Orientada a Objetos (C++) |
| **Organização** | Variáveis globais | Classes e encapsulamento |
| **Validação** | Mínima | Melhorada com debounce |
| **Interface** | Texto simples | Melhorada com símbolos |
| **Feedback** | Apenas texto | Visual (LEDs) + Sonoro (Buzzer) |

---

## 🚀 Como Usar

### **Teste no Desktop (C++):**
1. Compile: `g++ -std=c++11 -o jogogenius jogogenius.cpp`
2. Execute: `./jogogenius`
3. Digite a seed e depois os números 1-4

### **No Arduino:**
1. Abra a Arduino IDE
2. Copie o código de `jogogenius_arduino.ino`
3. Selecione a placa e porta serial
4. Clique em "Upload"
5. Abra o Monitor Serial para ver mensagens

---

## 💡 Dicas de Customização

### Aumentar nível de dificuldade:
```cpp
const unsigned long TIMEOUT = 3000; // Reduzir de 5 para 3 segundos
```

### Mudar número de entradas:
```cpp
const int NUM_BUTTONS = 6; // De 4 para 6 botões
const int buttonPins[6] = {2, 3, 4, 5, 12, 13};
```

### Adicionar buzzer/LEDs:
- Descomente ou use os pinos configurados
- Conecte conforme o esquema

---

## 📝 Lógica do Jogo

1. Gera um número aleatório (1-4)
2. Adiciona à sequência
3. Mostra a sequência (com sons/LEDs)
4. Aguarda o jogador repetir
5. Se correto → próxima rodada com +1 número
6. Se errado → GAME OVER

**Sequência de exemplo:**
```
Rodada 1: [1]              → Jogador digita: 1 ✓
Rodada 2: [1, 3]           → Jogador digita: 1, 3 ✓
Rodada 3: [1, 3, 2]        → Jogador digita: 1, 3, 2 ✓
Rodada 4: [1, 3, 2, 4]     → Jogador digita: 1, 3, 2, 3 ✗ GAME OVER
```

---

**Versão:** 1.0 - Maio 2026
**Compilador:** GCC/Clang (Desktop) | Arduino IDE (Microcontrolador)
