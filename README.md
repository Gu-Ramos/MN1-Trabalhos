# Cálculo de Deslocamento de Pêndulo Oscilatório
Este repositório é responsável por armazenar o código-fonte do trabalho prático da disciplina de Métodos Numéricos 1. 

Esta aplicação, desenvolvida em C++ e projetada para execução em sistemas operacionais Linux, implementa algoritmos avançados baseados no **Método de Newton** para calcular o deslocamento 𝑑 de um pêndulo oscilante. O sistema utiliza uma função polinomial para determinar o deslocamento, aplicando tanto o método de Newton original quanto uma versão modificada para tratar casos em que a derivada se aproxima de zero. 

# Informações Técnicas

## Organização de pastas
O projeto está organizado da seguinte forma:

```
C:.
│   .gitignore         # Arquivo de exclusão para versionamento no Git
│   README.md          # Documentação do projeto
│
├───questões           # Implementação das questões específicas do trabalho
│       itemA.cpp      # Código para o cálculo de d pelo método de Newton original
│       itemB.cpp      # Código para o cálculo de d pelo método de Newton com FL
│       itensCD.cpp    # Código para o cálculo numérico da derivada e comparação
│
└───src                # Código principal e implementação de métodos gerais
        main.cpp       # Arquivo principal para execução do programa
        metodos.cpp    # Implementação dos métodos numéricos
        metodos.hpp    # Cabeçalhos dos métodos numéricos
```

## Dados de Entrada e Saída

### Dados de Entrada
- **n**: Número de opções para \(λ\).
- **\(λ\)**: Valor para o parâmetro de limite.
- **\(a_3\)** e **\(a_2\)**: Coeficientes polinomiais (um par para cada \(λ\)).
- **\(ε\)**: Precisão desejada.

### Dados de Saída
- **Quadros de resposta**: Apresentam \(d\) e o erro correspondente para cada valor de \(a_3\), \(a_2\), \(λ\), e método.
- **Quadro comparativo**: Detalha e compara os resultados obtidos para cada método.

## Funcionalidades

A aplicação implementa as seguintes funcionalidades:

1. **Cálculo de \(d\) pelo método de Newton original**:  
   - Implementa o algoritmo clássico para determinar o deslocamento com base na função polinomial fornecida.

2. **Cálculo de \(d\) pelo método de Newton com modificação \(FL\)**:  
   - Adiciona uma modificação ao método de Newton para lidar com situações em que a derivada se aproxima de zero, garantindo estabilidade nos cálculos.

3. **Cálculo numérico da derivada da função polinomial**:  
   - Implementa um método numérico para calcular a derivada de \(f(d)\) e aplica o resultado no método de Newton.

4. **Execução de testes com parâmetros padrão**:  
   - Avalia os métodos implementados usando os valores padrão:  
     \(a_3 = 1\), \(a_2 = 1\), \(d_0 = 0.5\), \(λ = 0.05\), e \(ε = 0.001\).

5. **Geração de quadros de resposta**:  
   - Produz tabelas detalhadas contendo os valores de deslocamento \(d\) e erros para cada conjunto de parâmetros \(a_3\), \(a_2\), \(λ\, e método).

6. **Geração de quadros comparativos**:  
   - Apresenta uma comparação consolidada dos resultados obtidos com os diferentes métodos implementados.

7. **Análise do impacto da variação dos coeficientes \(a_3\) e \(a_2\)**:  
   - Examina como a alteração desses parâmetros influencia os deslocamentos calculados e o desempenho dos métodos.


#  Como Rodar

### Pré-requisitos
- Sistema operacional Linux.
- Compilador **g++** instalado.
- Terminal para executar os comandos.

### Passos para execução

1. **Clone o repositório:**
   ```bash
   git clone <https://github.com/Gu-Ramos/MN1-Trabalhos.git>
   cd <MN1-Trabalhos>
   ```

2. Navegue até a pasta `src`:
   ```bash
   cd src
   ```

3. Compile o arquivo main.cpp junto com as implementações auxiliares:
    ```bash
    g++ main.cpp metodos.cpp -o metodos
    ```
4. Execute o programa
    ```bash
    ./metodos
    ```

