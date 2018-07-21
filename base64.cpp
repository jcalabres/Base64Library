#include "base64.h"

/* inicia un vector binario dinamico
* @return: puntero al vector binario */
uint32_t *Base64::IniciarVectorBinario(uint32_t longitudVectorBinario){
	uint32_t *vectorBinario = (uint32_t*) calloc(longitudVectorBinario, sizeof(uint32_t));
	return vectorBinario;
}

/* inicia un vector alfanumerico dinamico
* @return: puntero al vector alfanumerico */
char *Base64::IniciarVectorAlfanumerico(uint32_t longitudVectorAlfanumerico){
	char *vectorAlfanumerico = (char*) malloc(longitudVectorAlfanumerico*sizeof(char));
	return vectorAlfanumerico;
}

/* imprime un vector binario */
void Base64::MostrarVectorBinario(uint32_t *vectorBinario, uint32_t longitudVectorBinario){
	for(uint32_t i=0; i<longitudVectorBinario; i++){
		cout << vectorBinario[i];
	}
}

/* imprime un vector alfanumerico */
void Base64::MostrarVectorAlfanumerico(char *vectorAlfanumerico, uint32_t longitudVectorAlfanumerico){
	for(uint32_t i=0; i<longitudVectorAlfanumerico ; i++){
		cout << vectorAlfanumerico[i];
	}
}

/* escribe el vector binario a partir de un texto dado, tanto ascii como alfanumerico */
void Base64::EscribirVectorBinario(uint32_t *vectorBinario, char *textoCodificar, uint32_t longitudTexto, uint32_t bloque){
	uint32_t posicionEscritura = 0;
	for(uint32_t i=0; i<longitudTexto; i++){
		uint32_t *vectorTemporal;
		if(bloque == BITS_LETRA){
			vectorTemporal = EnteroABinario(uint32_t(textoCodificar[i]), bloque);
		}else if(bloque == BITS_LETRA_B64){
			vectorTemporal = EnteroABinario(BuscarIndiceB64(textoCodificar[i]), bloque);
		}
		for(uint32_t i=0; i<bloque;i++){
			vectorBinario[posicionEscritura] = vectorTemporal[i];
			posicionEscritura++;
		}
		free(vectorTemporal);
	}
}

/* escribe un vector alfanumerico a partir de un vector binario dado */
void Base64::EscribirVectorAlfanumerico(uint32_t *vectorBinario, char *vectorAlfanumerico, uint32_t longitudVectorBinario, uint32_t bloque){
	uint32_t posicionLectura = 0;
	uint32_t indiceAlfanumerico = 0;
	char letra =' ';
	uint32_t *temporal = IniciarVectorBinario(bloque);
	for(uint32_t i=0; i<longitudVectorBinario; i++){
		temporal[posicionLectura] = vectorBinario[i];
		if(posicionLectura == bloque-1){
			uint32_t letraEntero = BinarioAEntero(temporal, bloque);
			if(bloque == BITS_LETRA){
				letra = char(letraEntero);
			}else if(bloque == BITS_LETRA_B64){
				letra = CODI_B64[letraEntero];
			}
			vectorAlfanumerico[indiceAlfanumerico] = letra;
			indiceAlfanumerico++;
			posicionLectura = 0;
		}else{
			posicionLectura++;
		}
	}
	free(temporal);
}

/* transforma el numero entero a numero binario
* @return: puntero al array que contiene el entero dado en binario */
uint32_t *Base64::EnteroABinario(uint32_t numero, uint32_t bloque){
	uint32_t indice = 0;
	//numero de 0's por delante del binario calculado
	uint32_t zeros = 0;
	uint32_t *binario = IniciarVectorBinario(bloque);
	//vector temporal para almacenar la secuencia binaria
	uint32_t *temporal = IniciarVectorBinario(bloque);
  while(numero >= BASE_BINARIA){
		temporal[indice] = numero % BASE_BINARIA;
		numero /= BASE_BINARIA;
		indice++;
	}
	temporal[indice] = numero;
	zeros = bloque - (indice+1);
	uint32_t pos = 1;
	for(int32_t i=indice; i>=0; i--){
	 if(temporal[i]==1){
			binario[(zeros-1)+pos] = 1;
		}
		pos++;
	}
	free(temporal);
	return binario;
}

/* transforma un numero binario a un numero entero
* @return: devuelve un entero*/
uint32_t Base64::BinarioAEntero(uint32_t *binario, uint32_t bits_letra){
	uint32_t numero = 0;
	for(uint32_t i=0; i<bits_letra ; i++){
		if (binario[i]==1){
			numero += pow(BASE_BINARIA, (bits_letra-i-1));
		}
	}
	return numero;
}

/* calcula la longitud de un vector alfanumerico a partir de su tamaño binario
* @return: longitud del vector alfanumerico */
uint32_t Base64::CalcularLongitudVectorAlfanumerico(uint32_t longitudTexto, uint32_t bitsLetra, uint32_t bitsLetraCod){
	uint32_t longitudAlfanumerico = (longitudTexto * bitsLetra)  / bitsLetraCod;
	return longitudAlfanumerico;
}

/* busca el indice de un caracter representado en base64
* @return: retorna ese indice */
uint32_t Base64::BuscarIndiceB64(char letra){
	bool encontrado = false;
	uint32_t indice = 0;
	while(!encontrado){
			if(CODI_B64[indice] == letra){
				encontrado = true;
			}
			indice++;
	}
	return indice-1;
}

/* procedimiento para la codificacion
* @return: devuelve puntero al string codificado */
char *Base64::Codificar(char *textoCodificar){
	longitudTexto= strlen(textoCodificar);
	longitudVectorBinario = longitudTexto*BITS_LETRA;
	vectorBinario = IniciarVectorBinario(longitudVectorBinario);
	EscribirVectorBinario(vectorBinario, textoCodificar, longitudTexto, BITS_LETRA);
	longitudVectorAlfanumerico = CalcularLongitudVectorAlfanumerico(longitudTexto, BITS_LETRA, BITS_LETRA_B64);
	vectorAlfanumerico = IniciarVectorAlfanumerico(longitudVectorAlfanumerico);
	EscribirVectorAlfanumerico(vectorBinario, vectorAlfanumerico, longitudVectorBinario, BITS_LETRA_B64);
	//MostrarVectorBinario(vectorBinario, longitudVectorBinario);
	free(vectorBinario);
	return vectorAlfanumerico;
}

/* procedimiento para la descodificación
* @return: devuelve puntero al string descodificado */
char *Base64::Descodificar(char *textoCodificado){
	longitudTextoAlfanumerico = strlen(textoCodificado);
	longitudVectorBinario = longitudTextoAlfanumerico*BITS_LETRA_B64;
	uint32_t *vectorBinarioo = IniciarVectorBinario(longitudVectorBinario);
	EscribirVectorBinario(vectorBinario, textoCodificado, longitudTextoAlfanumerico, BITS_LETRA_B64);
	//MostrarVectorBinario(vectorBinario, longitudVectorBinario);
	longitudVectorAlfanumerico = CalcularLongitudVectorAlfanumerico(longitudTextoAlfanumerico, BITS_LETRA_B64, BITS_LETRA);
	vectorAlfanumerico = IniciarVectorAlfanumerico(longitudVectorAlfanumerico);
	EscribirVectorAlfanumerico(vectorBinario, vectorAlfanumerico, longitudVectorBinario, BITS_LETRA);
	free(vectorBinario);
	//MostrarVectorAlfanumerico(vectorAlfanumerico, longitudVectorAlfanumerico);
	return vectorAlfanumerico;
}
