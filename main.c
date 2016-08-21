/*
	Universidade Tecnol�gica Federal do Paran�
	Engenharia Eletr�nica
	Sistemas Embarcados
	Lab 1

	Testador do conversor de RGB para escala de cinza.
	19/08/2016

	F�bio Crestani
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

	// L� arquivo de imagem original ----------------------------------------------------
	if (!loadPPMFile("original.ppm", &original_data, &width, &height, 3))
		FATAL("N�o foi poss�vel abrir a imagem original.\n");

	printf("A imagem original foi lida (%u x %u):\n", width, height);

	// Mostra conte�do do arquivo original ----------------------------------------------
	printTextPPM(&original_data, width, height, 3);

	// L� arquivo de imagem processada --------------------------------------------------
	if (!loadPPMFile("processado.ppm", &processed_data, &width, &height, 1))
		FATAL("N�o foi poss�vel abrir a imagem processada.\n");

	printf("A imagem processada foi lida (%u x %u):\n", width, height);

	// Mostra conte�do do arquivo processado --------------------------------------------
	printTextPPM(&processed_data, width, height, 1);

	// Chama fun��o de convers�o de teste -----------------------------------------------
	PPMRGBToGrayscale(&test_data, &original_data, width, height);

	// Mostra conte�do do arquivo de teste ----------------------------------------------
	printf("A imagem para testar foi processada (%u x %u):\n", width, height);
	printTextPPM(&test_data, width, height, 1);

	// Salva imagem de test para compara��o visual --------------------------------------
	storePPMFile("test.ppm", &test_data, width, height, 1);

	// Compara imagem processada pelo PC e pelo ARM pixel a pixel -----------------------
	if (compareImageData(&test_data, &processed_data, width, height)) {
		printf("Passou no teste.\n\n");
	}
	else {
		printf("Nao passou no teste :(\n\n");
	}

	// Libera os espa�os de mem�ria alocados --------------------------------------------
	free(original_data);
	free(test_data);
	free(processed_data);

	system("PAUSE");
	return 0;
}