#include <functional>
#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;

// Usando o método "symmetric difference quotient" pra achar a derivada de uma função genérica
// Esse método é inclusive usado em diversas calculadoras científicas com h = 0.001.
// https://en.wikipedia.org/wiki/Numerical_differentiation
double derivada(std::function<double(double)> funcao, double x) {
	double h = 0.00001;
	return (funcao(x + h) - funcao(x - h)) / (2*h);
}

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
std::tuple<double, double> newton_raphson(std::function<double(double)> funcao, double d0, double precisao, int max_iteracoes){
	// Atribuindo o valor inicial para calcular a raiz
	double d = d0; // Este e o valor de d que vai sendo atualizado 
	int k = 0; // k e a quantidade de iteracoes que realizamos 

	// Adicionando os valores que vamos trabalhar
	double funcao_d = funcao(d);
	double derivada_d = derivada(funcao, d);

	// Declarando o proximo valor dado
	double d_proximo;
    double erro;

	// Loop que roda enquanto nao encontrarmos a raiz (ou atingirmos o limite de iteracoes)
	while (k < max_iteracoes && abs(funcao_d) > precisao){

		// Verificando, inicialmente, se o valor da derivada e zero (caso seja 0, nao podera ser calculado o proximo d)
		if (derivada_d == 0){
			cout << "Erro! Nao sera possivel calcular o proximo valor, pois a derivada deu 0" << endl;
			break;
		}

		// Calculando o proximo valor
		d_proximo = d - (funcao_d / derivada_d);

		// Verificando a precisao da diferenca
        erro = abs(d_proximo - d);
		if (erro <= precisao){
            // Retornando logo o valor da possivel raiz e o erro
			return std::tuple<double, double>(d_proximo, erro);
		}

		// Atualizando d e suas funcoes para a proxima iteracao
		d = d_proximo;
		funcao_d = funcao(d);
		derivada_d = derivada(funcao, d);

		// Incrementando k
		k++;


	}
    
    // Retorna o valor da possivel raiz e o erro (máximo de iterações atingido)
	return std::tuple<double, double>(d, erro);
}

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
std::tuple<double, double> newton_raphson_modificado(std::function<double(double)> funcao, double d0, double precisao, double lambda, int max_iteracoes) {
    // Atribuindo o valor inicial para calcular a raiz
    double d = d0; // Este é o valor de d que vai sendo atualizado 
    int k = 0; // k e a quantidade de iteracoes que realizamos 

    // Adicionando os valores que vamos trabalhar
    double funcao_d = funcao(d);
    double derivada_d = derivada(funcao, d);

    // Declarando o proximo valor dado
    double d_proximo, d_w; // Este dw sera o valor armazenado da ultima derivada maior que o valor adicionado em lambda
    double erro;

    // Loop que roda enquanto nao encontrarmos a raiz (ou atingirmos o limite de iteracoes)
    while (k < max_iteracoes && abs(funcao_d) > precisao) {

        // Verificando, inicialmente, se o valor da derivada atende ao limitante dado pela entrada da funcao
        if (abs(derivada_d) > lambda) { // caso sim, apenas definimos o proximo valor da mesma forma
            d_w = derivada_d;
            d_proximo = d - (funcao_d / derivada_d);
        } else {
            d_proximo = d - (funcao_d / d_w); // caso nao, usamos a derivada que atende ao requisito anterior
        }

        // Verificando a precisao da diferenca
        double erro = abs(d_proximo - d);
        if (erro <= precisao) {
            // Retornando logo o valor da possivel raiz e o erro
            return std::tuple<double, double>(d_proximo, erro);
        }

        // Atualizando d e suas funcoes para a proxima iteracao
        d = d_proximo;
        funcao_d = funcao(d);
        derivada_d = derivada(funcao, d);

        k++;
    }

    // Retorna o valor da possivel raiz e o erro (máximo de iterações atingido)
    return std::tuple<double, double>(d, erro);
}

int main() {
    double precisao = 0.001;
    int num_opcoes;

    // Testando o codigo
    std::cout << "Precisão: ";
    std::cin >> precisao;

    std::cout << "Número de opções: ";
    std::cin >> num_opcoes;

    // Os resultados pra cada opção vão ser armazenados em um array nessa ordem:
    // LAMBDA | A3 | A2 | VALOR_NR | ERRO_NR | VALOR_NRMOD | ERRO_NRMOD
    double resultados[num_opcoes][7];

    // input & processamento
    for (int i = 0; i < num_opcoes; i++) {
        // INPUT
        std::cout << "Digite o lambda, a3, e a2 da " << i+1 << "ª opção (SEPARADO POR ESPAÇOS): ";
        
        std::cin >> resultados[i][0]; // lambda
        std::cin >> resultados[i][1]; // a3
        std::cin >> resultados[i][2]; // a2

        // PROCESSAMENTO
        double lambda = resultados[i][0];
        double a3 = resultados[i][1];
        double a2 = resultados[i][2];

        // A função do pendulo dada pela questão
        std::function<double(double)> funcao = [a3, a2](double x) -> double {
            return (a3 * pow(x, 3)) - (9 * a2 * x) + 3;
        };

        double valor_nr, erro_nr;
        double valor_nrmod, erro_nrmod;
        std::tie(valor_nr, erro_nr) = newton_raphson(funcao, 0.5, precisao, 100);
        std::tie(valor_nrmod, erro_nrmod) = newton_raphson_modificado(funcao, 0.5, precisao, lambda, 100);

        resultados[i][3] = valor_nr;
        resultados[i][4] = erro_nr;
        resultados[i][5] = valor_nrmod;
        resultados[i][6] = erro_nrmod;
    }

    // PRINT FINAL
    for (int i = 0; i < num_opcoes; i++) {
        double lambda = resultados[i][0];
        double a3 = resultados[i][1];
        double a2 = resultados[i][2];
        double valor_nr = resultados[i][3];
        double erro_nr = resultados[i][4];
        double valor_nrmod = resultados[i][5];
        double erro_nrmod = resultados[i][6];

        printf("\n                              OPÇÃO Nº %d:\n", i+1);
        printf("a3: %.5f | a2: %.5f | lambda: %.5f | precisão: %.5f\n", a3, a2, lambda, precisao);
        printf("-----------------------------------------------------------------------------------\n");
        printf("Deslocamento newton_rhapson:    %.10f | Erro newton_rhapson:    %.10f\n", valor_nr, erro_nr);
        printf("Deslocamento newton_rhapson FL: %.10f | Erro newton_rhapson FL: %.10f\n", valor_nrmod, erro_nrmod);
    }
    
    return 0;
}
