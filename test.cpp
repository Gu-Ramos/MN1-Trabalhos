#include <functional>
#include <iostream>
#include <cmath>
using namespace std;

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
double newton_raphson_modificado(std::function<double(double)> funcao, std::function<double(double)> derivada, double d0, double precisao, double lambda, int max_iteracoes){

	// Atribuindo o valor inicial para calcular a raiz
	double d = d0; // Este e o valor de d que vai sendo atualizado 
	int k = 0; // k e a quantidade de iteracoes que realizamos 

	// Adicionando os valores que vamos trabalhar
	double funcao_d = funcao(d);
	double derivada_d = derivada(d);

	// Declarando o proximo valor dado
	double d_proximo, d_w; // Este dw sera o valor armazenado da ultima derivada maior que o valor adicionado em lambda

	// Loop que roda enquanto nao encontrarmos a raiz (ou atingirmos o limite de iteracoes)
	while (k < max_iteracoes && abs(funcao_d) > precisao){

		// Verificando, inicialmente, se o valor da derivada atende ao limitante dado pela entrada da funcao
		if (abs(derivada_d) > lambda){ // caso sim, apenas definimos o proximo valor da mesma forma
			d_w = derivada_d;
			d_proximo = d - (funcao_d / derivada_d);
		}

		else{
			d_proximo = d - (funcao_d / d_w); // caso nao, usamos a derivada que atende ao requisito anterior
		}

		// Verificando a precisao da diferenca
		if (abs(d_proximo - d) <= precisao){
			return d_proximo; // Retornando logo o valor da possivel raiz
		}

		// Atualizando d e suas funcoes para a proxima iteracao
		d = d_proximo;
		double funcao_d = funcao(d);
		double derivada_d = derivada(d);

		// Incrementando k
		k++;


	}

	return d;

}

int main(){
	// Definindo a3 e a2 segundo o item D
	double a3 = 1.0;
	double a2 = 1.0;

	// A funcao do pendulo dada pela questao
	std::function<double(double)> funcao = [a3, a2](double x) -> double {
		return (a3 * pow(x, 3)) - (9 * a2 * x) + 3;
	};

	// A derivada da funcao do pendulo
	std::function<double(double)> derivada = [a3, a2](double x) -> double {
		return (3 * a3 * pow(x, 2)) - (9 * a2);
	};

	// Testando o codigo
	double valor = newton_raphson_modificado(funcao, derivada, 0.5, 0.001, 0.05, 100);
	cout << valor << endl;

	return 0;
}