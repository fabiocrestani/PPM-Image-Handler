/*
	Universidade Tecnológica Federal do Paraná
	Engenharia Eletrônica
	Sistemas Embarcados
	Lab 1

	Testador do conversor de RGB para escala de cinza.
	19/08/2016

	Fábio Crestani
	Cezar Henrique Conrado
	Matheus Angelo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PPM.h"


int main() {

	unsigned int width;
	unsigned int height;
	unsigned char * original_data;
	unsigned char * processed_data;
	unsigned char * test_data;

	// Lê arquivo de imagem original ----------------------------------------------------
	if (!loadPPMFile("original.ppm", &original_data, &width, &height, 3))
		FATAL("Não foi possível abrir a imagem original.\n");

	printf("A imagem original foi lida (%u x %u):\n", width, height);

	// Mostra conteúdo do arquivo original ----------------------------------------------
	printTextPPM(&original_data, width, height, 3);

	// Lê arquivo de imagem processada --------------------------------------------------
	if (!loadPPMFile("processado.ppm", &processed_data, &width, &height, 1))
		FATAL("Não foi possível abrir a imagem processada.\n");

	printf("A imagem processada foi lida (%u x %u):\n", width, height);

	// Mostra conteúdo do arquivo processado --------------------------------------------
	printTextPPM(&processed_data, width, height, 1);

	// Chama função de conversão de teste -----------------------------------------------
	PPMRGBToGrayscale(&test_data, &original_data, width, height);

	// Mostra conteúdo do arquivo de teste ----------------------------------------------
	printf("A imagem para testar foi processada (%u x %u):\n", width, height);
	printTextPPM(&test_data, width, height, 1);

	// Salva imagem de test para comparação visual --------------------------------------
	storePPMFile("test.ppm", &test_data, width, height, 1);

	// Compara imagem processada pelo PC e pelo ARM pixel a pixel -----------------------
	if (compareImageData(&test_data, &processed_data, width, height)) {
		printf("Passou no teste.\n\n");
	}
	else {
		printf("Nao passou no teste :(\n\n");
	}

	// Libera os espaços de memória alocados --------------------------------------------
	free(original_data);
	free(test_data);
	free(processed_data);

	system("PAUSE");
	return 0;
}