#include <functional>
#include <iostream>
#include <cmath>
using namespace std;

// Usando o método "symmetric difference quotient" pra achar a derivada de uma função genérica
// Esse método é inclusive usado em diversas calculadoras científicas com h = 0.001.
// https://en.wikipedia.org/wiki/Numerical_differentiation
double derivada(std::function<double(double)> funcao, double x) {
	double h = 0.00001;
	return (funcao(x + h) - funcao(x - h)) / (2*h);
}

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
double newton_raphson(std::function<double(double)> funcao, double d0, double precisao, int max_iteracoes){
	// Atribuindo o valor inicial para calcular a raiz
	double d = d0; // Este e o valor de d que vai sendo atualizado 
	int k = 0; // k e a quantidade de iteracoes que realizamos 

	// Adicionando os valores que vamos trabalhar
	double funcao_d = funcao(d);
	double derivada_d = derivada(funcao, d);

	// Declarando o proximo valor dado
	double d_proximo;

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
		if (abs(d_proximo - d) <= precisao){
			return d_proximo; // Retornando logo o valor da possivel raiz
		}

		// Atualizando d e suas funcoes para a proxima iteracao
		d = d_proximo;
		funcao_d = funcao(d);
		derivada_d = derivada(funcao, d);

		// Incrementando k
		k++;


	}

	return d;

}

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
double newton_raphson_modificado(std::function<double(double)> funcao, double d0, double precisao, double lambda, int max_iteracoes) {
    // Atribuindo o valor inicial para calcular a raiz
    double d = d0; // Este é o valor de d que vai sendo atualizado 
    int k = 0; // k e a quantidade de iteracoes que realizamos 

    // Adicionando os valores que vamos trabalhar
    double funcao_d = funcao(d);
    double derivada_d = derivada(funcao, d);

    // Declarando o proximo valor dado
    double d_proximo, d_w; // Este dw sera o valor armazenado da ultima derivada maior que o valor adicionado em lambda

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
        if (abs(d_proximo - d) <= precisao) {
            return d_proximo; // Retornando logo o valor da possivel raiz
        }

        // Atualizando d e suas funcoes para a proxima iteracao
        d = d_proximo;
        funcao_d = funcao(d);
        derivada_d = derivada(funcao, d);

        k++;
    }

    return d;
}

int main() {
    // Definindo a3 e a2 segundo o item D
    double a3 = 1.0;
    double a2 = 1.0;

    // A funcao do pendulo dada pela questao
    std::function<double(double)> funcao = [a3, a2](double x) -> double {
        return (a3 * pow(x, 3)) - (9 * a2 * x) + 3;
    };

    // Testando o codigo
    double valor_nr = newton_raphson(funcao, 0.5, 0.001, 100);
    double valor_nrmod = newton_raphson_modificado(funcao, 0.5, 0.001, 0.05, 100);

    printf("Valor usando método de newton_rhapson: %.10f\n", valor_nr);
    printf("Valor usando método de newton_rhapson modificado com lambda = 0.05: %.10f\n", valor_nrmod);
    
    return 0;
}
