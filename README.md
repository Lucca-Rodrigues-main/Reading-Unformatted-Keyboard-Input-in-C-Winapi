# Reading-Unformatted-Keyboard-Input-in-C-Winapi
A set of C functions to read unformatted (keyboard) input. Provides safe, validated reading for every data type, replaces unsafe scanf with portable alternatives using PeekConsoleInput and custom scanning. Features character filtering, buffer overflow protection, and real-time validation.

---

## Introdução

### **O que são dados formatados?**
- **Definição:** Organização de informações conforme especificações pré-definidas (geralmente para processamento computacional).
- **Em C:** Funções como `scanf()` foram projetadas para ler entrada formatada (*scan formatted input*).

### **Problemas com `scanf()`**
- **Objetivo original:** Ler entrada formatada (ex: arquivos estruturados), **não** entrada do teclado (que é livre).
- **Riscos:**
  - Não valida a entrada — usuário pode digitar qualquer coisa (105+ teclas de liberdade).
  - Pode corromper memória se a entrada não corresponder ao esperado.
  - Retorna um `int` (número de itens lidos) — ignorar esse retorno é um erro comum.
- **Uso prático:**
  - Pode ser útil em casos controlados, mas **não** é adequado para aplicações robustas que exigem validação.

### **Desafios com Entrada de Teclado**
- Necessidade de ler caracteres sem esperar por Enter
- Validação em tempo real de entrada
- Controle preciso de tipos e intervalos
- Manipulação segura de strings

---

## Soluções propostas

### 1. **Leitura de Caracteres Avançada**
- `LerChar()`, `LerSChar()`, `LerUChar()`: Leitura direta sem buffer
- A implementação é baseada nas funções `WaitForSingleObject()`, que apenas aguarda por um evento no buffer de entrada, e `PeekConsoleInput`, que apenas "espia" o que há na stdin para poder validar um evento do teclado, sem de fato tentar ler e consumir desnecessariamente como a maioria das funções de leitura fazem.
- Solução portável alternativa ao `getch()` da `conio.h`, mas esta biblioteca não é portável e não faz parte de padrão nenhum.

### 2. **Leitura de Strings Configurável**
- `LerString()`, `LerSString()`, `LerUString()`
- Parâmetros `scanset` (caracteres permitidos) e `nscanset` (caracteres proibidos) para filtragem:
  - `scanset` != NULL && `nscanset` == NULL: somente os caracteres apontados por `scanset` são permitidos.
  - `scanset` == NULL && `nscanset` != NULL: somente os caracteres não apontados por `nscanset` são permitidos.
  - `scanset` == NULL && `nscanset` == NULL: quaisquer caracteres são permitidos.
- Controle de tamanho máximo para prevenção de overflow.

### 3. **Leitura Numérica com Validação**
- Funções para todos os tipos numéricos padrão C.
- Validação de intervalos (`minval`, `maxval`) em tempo real, ou seja, o usuário é impedido de digitar qualquer valor fora do intervalo. Valores fora do intervalo não serão impressos na stdout.
- Conversão segura de strings para valores numéricos.

### 4. **Bonus**
- Macro `gets()`, baseada em `fgets()`, porém mais segura e com limpeza do buffer de entrada.
- Função `Getch()`, que desabilita Line Input para que não seja necessário teclar Enter e Echo Input para que o caractere não seja impresso, e então lê com `ReadConsole()`. Tem o mesmo efeito da `getch()` da `conio.h`, mas usa a WinAPI.
- Função `LerStr()`, com mesma implementação da `gets()`, porém retorna um ponteiro.

---

## Exemplo
O exemplo a seguir segue a implementação encontrada nesse repositório.

<img width="792" height="784" alt="image" src="https://github.com/user-attachments/assets/1870385c-62eb-4d93-9474-d08f9faf479e" />
