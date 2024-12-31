#include "metodos.hpp"
#include <iostream>

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