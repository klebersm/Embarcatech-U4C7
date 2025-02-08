# Embarcatech-U4C7

Este projeto demonstra o funcionamento de um servo motor controlado por uma saída do RP2040 usando um sinal PWM.

O princípio de funcionamento do servo motor se baseia num sinal PWM de 50Hz (20ms de período), com posições estabelecidas de acordo com o duty cycle

Para conseguir um sinal de 50Hz, a frequência padrão do RP2040 (125Mhz), precisa ser dividida por 125000000 / 50 = 2500000
Ou seja, o valor do WRAP multiplicado pelo Divisor precisa ser igual a 2500000. Visando melhorar a resolução no caso de porcentagens com casas decimais, optei por maximizar o valor do WRAP, diminuindo o valor do divisor. Portanto os valores obtidos foram:

- Divisor 25
- WRAP 100000

## Tabela de duty cycle

Aplicando as porcentagens no WRAP para obter o level de cada posição, obtém-se a segunte tabela:

| Posição | Periodo | Porcentagem de 20ms | level                 |
| ------- | ------- | ------------------- | --------------------- |
| 180º    | 2400us  | 12%                 | 12,0% \* WRAP = 12000 |
| 90º     | 1470us  | 7,35%               | 7,35% \* WRAP = 7350  |
| 0º      | 500us   | 2,5%                | 2,50% \* WRAP = 2500  |

Por isso, os valores foram definidos no código como macros:

```
#define POS_180 12000
#define POS_90 7350
#define POS_0 2500
```

Já para a movimentação contínua do motor, a tarefa indica o uso de passos de 5us de duty cycle a cada incremento/decremento da posição. Com base nessa informação, pode-se obter a quantidade total de passos que existem dentro da onda de 20ms fazendo 20000us/5us = 4000, ou seja o WRAP total seria dividido em 4000 partes. Para isto, cada passo deve ter 100000 / 4000 = 25. Por isso foi definida no código uma macro

```
#define STEP        25
```

## Comportamento de um led

Conforme solicitado na tarefa, o sinal PWM foi aplicado a um led utilizando a plataforma BitdogLab e setando o PWM para o pino 12, que corresponde ao led Azul. Nos 15 primeiros segundos de execução, o led apresentou pequenos saltos de luminosidade, correspondentes às posições de 180º, 90º e 0º, respectivamente. Importante salientar que o led não apaga totalmente na posição 0º, dado que o duty cycle para essa posição ainda é de 2,5% do valor total.
Ao entrar no modo ciclico, é possível ver a luminosidade do led variar gradativamente para mais e para menos, mas sempre com uma luminosidade baixa. Isso ocorre porque a luminosidade sempre se apresenta entre 2,5% e 12% da luminosidade total do led, valores que correspondem ao duty cycle mínimo e máximo para controle do motor.

## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico).
- Servomotor

## Software 💻

- **SDK do Raspberry Pi Pico:** O SDK (Software Development Kit) do Pico, que inclui as bibliotecas e ferramentas necessárias para desenvolver e compilar o código. [Instruções de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
- **CMake:** Um sistema de construção multiplataforma usado para gerar os arquivos de construção do projeto.
- **Compilador C/C++:** Um compilador C/C++ como o GCC (GNU Compiler Collection).
- **Git:** (Opcional) Para clonar o repositório do projeto.

### O código está dividido em vários arquivos para melhor organização:

- **`U4T7.C`**: Inicializa o pino e os parâmetros e faz o motor se mover de acordo com o especificado.
- **`CMakeLists.txt`:** Define a estrutura do projeto para o CMake.
- **`diagram.json`:** Diagramas de conexões.
  |

## Como Compilar e Executar ⚙️

1. **Instale o SDK do Raspberry Pi Pico:** Siga as instruções no site oficial do Raspberry Pi.
2. **Clone este repositório:** `git clone git@github.com:klebersm/embarcatech-U4C7.git`
3. **Navegue até o diretório do projeto:** `cd Embarcatech-U4C7`
4. **Compile o projeto:** `cmake -B build && cmake --build build`
5. **Copie para o Pico:** Copie o arquivo `U4C7.uf2` da pasta `build` (gerada após a compilação) para o Raspberry Pi Pico. O programa iniciará automaticamente.

## 🔗 Link do Vídeo de Funcionamento:

https://drive.google.com/file/d/1118dtAJuiiKRs1i7EShtLsdd9D56enlQ/view?usp=drive_link

## 📞 Contato

- 👤 **Autor**: Kleber Marçal

- 📧 **E-mail**:kleber.sm@gmail.com

---
