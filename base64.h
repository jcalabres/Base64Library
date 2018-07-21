#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <iostream>
using namespace std;

const uint32_t BASE_BINARIA = 2;
const uint32_t BASE64 = 64;
const uint32_t BITS_LETRA = 8;
const uint32_t BITS_LETRA_B64 = 6;
const char CODI_B64[BASE64] = {'A', 'B', 'C', 'D','E','F','G','H','I','J','K','L','M',
'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b', 'c', 'd','e','f',
'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

class Base64{
	private:
	/* vectores */
	uint32_t *vectorBinario;
	char *vectorAlfanumerico;
	/* longitudes */
	uint32_t longitudTexto;
	uint32_t longitudTextoAlfanumerico;
	uint32_t longitudVectorBinario;
	uint32_t longitudVectorAlfanumerico;
	/* inicio de vectores */
	uint32_t *IniciarVectorBinario(uint32_t longitudVectorBinario);
	char *IniciarVectorAlfanumerico(uint32_t longitudVectorAlfanumerico);
	/* imprimir vectores */
	void MostrarVectorBinario(uint32_t *vectorBinario, uint32_t longitudVector);
	void MostrarVectorAlfanumerico(char *vectorAlfanumerico, uint32_t longitudVector);
	/* escribir vectores */
	void EscribirVectorBinario(uint32_t *vectorBinario, char *textoCodificar, uint32_t longitudTexto, uint32_t bloque);
	void EscribirVectorAlfanumerico(uint32_t *vectorBinario, char *vectorAlfanumerico, uint32_t longitudVectorBinario, uint32_t bloque);
	/* transformar de entero a binario y viceversa */
	uint32_t *EnteroABinario(uint32_t numero, uint32_t bloque);
	uint32_t BinarioAEntero(uint32_t *binario, uint32_t bits_letra);
	/* otros */
	uint32_t CalcularLongitudVectorAlfanumerico(uint32_t longitudTexto, uint32_t bitsLetra, uint32_t bitsLetraCod);
	uint32_t BuscarIndiceB64(char letra);
	public:
	char *Codificar(char *textoCodificar);
	char *Descodificar(char *textoCodificado);
};
