#include <functional>
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include "metodos.hpp"

using namespace std;

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
    std::vector<std::tuple<std::vector<std::array<double, 5>>, std::vector<std::array<double, 6>>>> tabelas;

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
        std::vector<std::array<double, 5>> tabela_nr;

        double valor_nrmod, erro_nrmod;
        std::vector<std::array<double, 6>> tabela_nrmod;
        
        std::tie(valor_nr, erro_nr, tabela_nr) = newton_raphson(funcao, 0.5, precisao, 100);
        std::tie(valor_nrmod, erro_nrmod, tabela_nrmod) = newton_raphson_modificado(funcao, 0.5, precisao, lambda, 100);

        resultados[i][3] = valor_nr;
        resultados[i][4] = erro_nr;
        resultados[i][5] = valor_nrmod;
        resultados[i][6] = erro_nrmod;
        
        tabelas.push_back(make_tuple(tabela_nr, tabela_nrmod));
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

        std::vector<std::array<double, 5>> tabela_nr;
        std::vector<std::array<double, 6>> tabela_nrmod;
        std::tie(tabela_nr, tabela_nrmod) = tabelas[i];

        printf("\n                              OPÇÃO Nº %d:\n", i+1);

        printf("Iterações newton_rhapson:\n");
        printf(" k   | d            | f(d)          | f'(d)         | d k+1        | erro abs     | erro rel\n");
        for (int iteracao = 0; iteracao < (int) tabela_nr.size(); iteracao++) {
            printf(" %-3d | %.10f | %.10f | %.10f | %.10f | %.10f | %.10f\n", (int) iteracao, tabela_nr[iteracao][0], tabela_nr[iteracao][1], tabela_nr[iteracao][2], tabela_nr[iteracao][3], tabela_nr[iteracao][4], tabela_nr[iteracao][4]/tabela_nr[iteracao][3]);
        }

        printf("\n");

        printf("Iterações newton_rhapson_mod:\n");
        printf(" k   | d            | f(d)          | f'(d)         | d k+1        | d w          | erro abs     | erro rel\n");
        for (int iteracao = 0; iteracao < (int) tabela_nrmod.size(); iteracao++) {
            printf(" %-3d | %.10f | %.10f | %.10f | %.10f | %.10f | %.10f | %.10f\n", (int) iteracao, tabela_nrmod[iteracao][0], tabela_nrmod[iteracao][1], tabela_nrmod[iteracao][2], tabela_nrmod[iteracao][3], tabela_nrmod[iteracao][4], tabela_nrmod[iteracao][5], tabela_nrmod[iteracao][5]/tabela_nrmod[iteracao][3]);
        }

        printf("\n");

        printf("a3: %.5f | a2: %.5f | lambda: %.5f | precisão: %.5f\n", a3, a2, lambda, precisao);
        printf("-----------------------------------------------------------------------------------\n");
        printf("Deslocamento newton_rhapson:    %.10f | Erro absoluto newton_rhapson:    %.10f\n", valor_nr, erro_nr);
        printf("Deslocamento newton_rhapson FL: %.10f | Erro absoluto newton_rhapson FL: %.10f\n", valor_nrmod, erro_nrmod);
        printf("Erro relativo newton_rhapson:   %.10f | Erro relativo newton_rhapson FL: %.10f\n", erro_nr / valor_nr, erro_nrmod / valor_nrmod);
        printf("Iterações newton_rhapson FL:    %.10f | Iterações newton_rhapson FL:     %.10f\n", (double) tabela_nr.size(), (double) tabela_nrmod.size());
    }
    
    return 0;
}
