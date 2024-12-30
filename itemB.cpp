# include <iostream>
# include <cmath>
using namespace std;

// A funcao do pendulo dada pela questao
double funcao(double d, double a2, double a3){
	return (a3 * pow(d, 3)) - (9 * a2 * d) + 3;
}

// A derivada da funcao do pendulo
double derivada(double d, double a2, double a3){
	return (3 * a3 * pow(d, 2)) - (9 * a2);
}

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
double newton_raphson_modificado(double a2, double a3, double d0, double precisao, double bruh, int max_iteracoes){

	// Atribuindo o valor inicial para calcular a raiz
	double d = d0; // Este e o valor de d que vai sendo atualizado 
	int k = 0; // k e a quantidade de iteracoes que realizamos 

	// Adicionando os valores que vamos trabalhar
	double funcao_d = funcao(d, a2, a3);
	double derivada_d = derivada(d, a2, a3);

	// Declarando o proximo valor dado
	double d_proximo, d_w; // Este dw sera o valor armazenado da ultima derivada maior que o valor adicionado em "bruh"

	// Loop que roda enquanto nao encontrarmos a raiz (ou atingirmos o limite de iteracoes)
	while (k < max_iteracoes && abs(funcao_d) > precisao){

		// Verificando, inicialmente, se o valor da derivada atende ao limitante dado pela entrada da funcao
		if (abs(derivada_d) > bruh){ // caso sim, apenas definimos o proximo valor da mesma forma
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
		funcao_d = funcao(d, a2, a3);
		derivada_d = derivada(d, a2, a3);

		// Incrementando k
		k++;


	}

	return d;

}

int main(){

	// Testando o codigo
	double valor = newton_raphson_modificado(1.0, 1.0, 0.5, 0.001, 0.05, 100);
	cout << valor << endl;

	return 0;
}
