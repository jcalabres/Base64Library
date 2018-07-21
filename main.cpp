#include <stdio.h>
#include "base64.h"

int main(){
  char textoCodificar[50] = "I'm killing your brain like a poisonous mushroom";
  cout << "Sin codificar: \n" << textoCodificar << "\n";
  Base64 base64;
  char *textoCodificado = base64.Codificar(textoCodificar);
  cout << "Codificado: \n" << textoCodificado << "\n";
  char *textoDescodificado = base64.Descodificar(textoCodificado);
  cout << "Descodificado: \n" << textoDescodificado << "\n";
}
