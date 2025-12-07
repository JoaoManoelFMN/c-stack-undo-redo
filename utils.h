#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de cores para o console
#define COR_VERMELHO "\x1b[31m"
#define COR_VERDE "\x1b[32m"
#define COR_AMARELO "\x1b[33m"
#define COR_AZUL "\x1b[34m"
#define COR_MAGENTA "\x1b[35m"
#define COR_CYAN "\x1b[36m"
#define COR_RESET "\x1b[0m"

// Definição para limpar a tela (compatível com Linux/Windows)
#ifdef _WIN32
#define LIMPAR_TELA "cls"
#else
#define LIMPAR_TELA "clear"
#endif

// Protótipo da função para limpar o buffer de entrada
void limpar_buffer();

#endif