#ifndef METODOS_H
#define METODOS_H

#include <functional>
#include <tuple>
#include <cmath>

// Usando o método "symmetric difference quotient" pra achar a derivada de uma função genérica
// Esse método é inclusive usado em diversas calculadoras científicas com h = 0.001.
// https://en.wikipedia.org/wiki/Numerical_differentiation
double derivada(std::function<double(double)> funcao, double x);

// Desenvolvendo o metodo de newton original, pedido pelo item a da questao
std::tuple<double, double, std::vector<std::tuple<int, double, double, double, double, double>>> newton_raphson(std::function<double(double)> funcao, double d0, double precisao, int max_iteracoes);

// Desenvolvendo o metodo de newton modificado, pedido pelo item b da questao
std::tuple<double, double, std::vector<std::array<double, 6>>> newton_raphson_modificado(std::function<double(double)> funcao, double d0, double precisao, double lambda, int max_iteracoes);

#endif
