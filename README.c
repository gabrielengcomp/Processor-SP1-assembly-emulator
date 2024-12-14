# Assembly Virtual Simplificado 🖥️

## Descrição do Projeto 📘
Este programa em **C** implementa um **interpretador de Assembly** simplificado. Ele simula a execução de instruções em uma arquitetura hipotética, utilizando um acumulador (*ACC*), memória e um contador de programa (*PC*).  

O programa lê instruções de um **arquivo binário** contendo opcodes e operandos, executa os comandos e retorna o estado final do acumulador e das flags (*Overflow, Carry e Zero*).

---

## Funcionalidades 🔧
1. **Leitura de arquivo binário**: Interpreta opcodes e operandos armazenados.
2. **Execução de instruções Assembly**:
   - Operações aritméticas: `ADD`, `SUB`, `MUL`, `DIV`, `INC`, `DEC`.
   - Operações lógicas: `AND`, `OR`, `NOT`.
   - Controle de fluxo: `JMP`, `JZ`, `JG`, `JL`, etc.
   - Carregamento e armazenamento: `LOAD_M`, `LOAD_V`, `STORE`.
3. **Flags**:
   - **O (Overflow)**: Resultado fora do intervalo permitido.
   - **C (Carry)**: Indica a necessidade de "carry" para soma/subtração.
   - **Z (Zero)**: Acumulador igual a zero.
4. **Parada do programa**: Instrução `HLT` finaliza a execução.

---

## Estrutura das Instruções 🗂️
Cada instrução é formada por:
- **Opcode** (8 bits): Código da operação.
- **Operando** (8 bits): Endereço ou valor imediato.

| Opcode | Instrução | Descrição                           |
|--------|-----------|-------------------------------------|
| 0      | LOAD_M    | Carrega valor da memória no ACC.    |
| 1      | LOAD_V    | Carrega valor imediato no ACC.      |
| 2      | STORE     | Armazena valor do ACC na memória.   |
| 3      | ADD       | Soma valor da memória ao ACC.       |
| 4      | SUB       | Subtrai valor da memória do ACC.    |
| 5      | MUL       | Multiplica valor da memória pelo ACC.|
| 6      | DIV       | Divide ACC pelo valor da memória.   |
| 7      | INC       | Incrementa ACC.                    |
| 8      | DEC       | Decrementa ACC.                    |
| 9      | AND       | Operação lógica AND com memória.    |
| 10     | OR        | Operação lógica OR com memória.     |
| 11     | NOT       | Operação lógica NOT no ACC.         |
| 12     | JMP       | Desvio incondicional.               |
| 13     | JZ        | Desvio se ACC == 0.                 |
| 14     | JNZ       | Desvio se ACC != 0.                 |
| 15     | JG        | Desvio se ACC > 0.                  |
| 16     | JL        | Desvio se ACC < 0.                  |
| 17     | JGE       | Desvio se ACC >= 0.                 |
| 18     | JLE       | Desvio se ACC <= 0.                 |
| 19     | HLT       | Encerra a execução do programa.     |

---

## Compilação e Execução ▶️

### Pré-requisitos
- **Sistema operacional**: Linux, Windows ou MacOS.
- **Compilador**: `gcc`.

### Compilação
Para compilar o programa, utilize o comando:

```bash
gcc -o assembly_virtual assembly_virtual.c
```

### Execução
O programa espera um arquivo binário chamado **programa.exe** contendo as instruções. Execute com:

```bash
./assembly_virtual
```

---

## Formato do Arquivo Binário 📄
O arquivo de entrada **programa.exe** contém as instruções no formato binário (2 bytes por instrução):
- **Byte 1**: Opcode.
- **Byte 2**: Operando (valor ou endereço).

### Exemplo:
| Byte 1 (Opcode) | Byte 2 (Operando) | Descrição         |
|-----------------|------------------|------------------|
| `01`           | `0A`             | LOAD_V 10        |
| `03`           | `05`             | ADD [Mem[5]]     |
| `12`           | `04`             | JMP para endereço 4 |

---

## Exemplo de Saída 💻
Entrada (programa.exe com instruções):
```
01 0A   ; LOAD_V 10
03 00   ; ADD Mem[0]
07      ; INC
19      ; HLT
```

Saída esperada:
```
ACC: 11
STAT: xxxxx001   ; Apenas flag Z está ativa
```

---

## Funções Principais 🛠️
1. **jmp**: Atualiza o contador de programa (*PC*) para um endereço específico.
   ```c
   void jmp(int operando, int *pnt) {
       *pnt = operando++/2;
   }
   ```

2. **accStat**: Atualiza as **flags** `O`, `C` e `Z` com base no valor do acumulador.
   ```c
   void accStat(int acc, int *statPnt, int operação) { 
       *statPnt = 0;	
       if(acc == 0) *statPnt = 1;
       if((acc > 255) || (acc < -256)) *statPnt = operação + 2;
   }
   ```

---

## Possíveis Erros ⚠️
1. **Arquivo não encontrado**: Certifique-se de que o arquivo `programa.exe` está no mesmo diretório que o executável.
2. **Divisão por zero**: O opcode `DIV` pode gerar erro se o operando for 0.
3. **Opcode inválido**: Caso o opcode não seja reconhecido, o programa retorna uma mensagem de erro.
