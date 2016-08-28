#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PPMREADBUFLEN 100
#define SHOW_FILE_DATA 1

/*
loadPPMFile

Carrega um arquivo PPM em formato de texto.
image_data retorna apenas o vetor contendo os dados da imagem em si.
Use channels = 1 para escala de cinza, ou channels = 3 para RGB.

Retorna 1 se carregou corretamente.

*/
int loadPPMFile(char filename[],
	unsigned char **image_data,
	unsigned int *width,
	unsigned int *height,
	unsigned int channels) {

	if (!(channels == 3 || channels == 1)) return 0;

	int dim_x;
	int dim_y;
	char buf[PPMREADBUFLEN], *t;
	unsigned int w, h, d;
	unsigned int r, g, b;
	int ret;

	// Opens PPM file
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) return 0;

	// Gets first line
	t = fgets(buf, PPMREADBUFLEN, fp);

	// If it has 3 channels, code fails if the white space following "P3" is not '\n'								
	if (channels == 3) {
		if ((t == NULL) || (strncmp(buf, "P3\n", 3) != 0)) return 0;
	}
	// If it has 1 channel, code fails if the white space following "P2" is not '\n'								
	else if (channels == 1) {
		if ((t == NULL) || (strncmp(buf, "P2\n", 3) != 0)) return 0;
	}

	// Px formats can have # comments after first line
	do {
		t = fgets(buf, PPMREADBUFLEN, fp);
		if (t == NULL) return 0;
	} while (strncmp(buf, "#", 1) == 0);

	// Gets width and height or fails
	ret = sscanf(buf, "%u %u", &w, &h);
	if (ret < 2) return 0;

	// Gets max value
	ret = fscanf(fp, "%u\n", &d);
	if ((ret < 1) || (d != 255)) return 0;

	// Allocates memory for image data
	*image_data = malloc(channels * w * h * sizeof(unsigned char));
	unsigned int i = 0;

	// Reads image data
	while (i < channels * w * h) {

		// If it is a RGB file
		if (channels == 3) {

			if (fscanf(fp, "%u %u %u", &r, &g, &b) == EOF) break;
			(*image_data)[i] = (unsigned char)r;
			(*image_data)[i + 1] = (unsigned char)g;
			(*image_data)[i + 2] = (unsigned char)b;
			i = i + 3;

		}
		// If it is a grayscale file
		else if (channels == 1) {

			if (fscanf(fp, "%u ", &g) == EOF) break;
			(*image_data)[i] = (unsigned char)g;
			i = i + 1;

		}

	}

	// Closes file
	fclose(fp);

	// Returns data to pointers
	*width = w;
	*height = h;

	return 1;
}


/*
storePPMFile

Salva um arquivo PPM em formato de texto.
Use channels = 1 para escala de cinza, ou channels = 3 para RGB.

Retorna 1 se salvou corretamente.

*/
int storePPMFile(char filename[],
	unsigned char **data,
	unsigned int width,
	unsigned int height,
	unsigned int channels) {

	// Opens PPM file
	FILE *fp = fopen(filename, "w+");
	if (fp == NULL) return 0;

	// Writes file header
	if (channels == 1)
		fprintf(fp, "P2\n# arquivo de teste.pgm\n%u %u\n255\n", width, height);
	else if (channels == 3)
		fprintf(fp, "P3\n# arquivo de teste.ppm\n%u %u\n255\n", width, height);
	else
		return 0;

	// Writes array to file
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width * channels; j = j + channels) {
			for (unsigned int k = 0; k < channels; k++) {
				fprintf(fp, "%u ", (*data)[i * width * channels + j + k]);
			}
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	return 1;
}


/*
PPMRGBToGrayscale

Converte um arquivo de imagem RGB para escala de cinza fazendo a média dos canais:
Nível de Cinza = (R + G + B) / 3

Retorna 1 em caso de sucesso.

*/
int PPMRGBToGrayscale(unsigned char **output,
	unsigned char **input,
	unsigned int width,
	unsigned int height) {

	*output = malloc(width * height * sizeof(unsigned char));

	if (output == NULL) return 0;

	unsigned int index_j = 0;
	unsigned int i = 0;

	while (i < width * height) {
		(*output)[i] = ((*input)[index_j + 0] +
			(*input)[index_j + 1] +
			(*input)[index_j + 2]) / 3;

		i++;
		index_j = index_j + 3;
	}

	return 1;
}


/*
compareImageData

Recebe dois vetores de imagem em escala de cinza (1 canal) e compara pixel a pixel.

Retorna 1 se os vetores forem iguais.

*/
int compareImageData(unsigned char **test,
	unsigned char **input,
	unsigned int width,
	unsigned int height) {

	for (unsigned int i = 0; i < width * height; i++) {
		if ((*test)[i] != (*input)[i])
			return 0;
	}

	return 1;
}

/*
printTextPPM

Imprime um vetor de imagem em format de texto.
Use channels = 1 para escala de cinza, ou channels = 3 para RGB.

*/
void printTextPPM(unsigned char **data,
	unsigned int width,
	unsigned int height,
	unsigned int channels) {

#if SHOW_FILE_DATA == 1
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width * channels; j = j + channels) {
			for (unsigned int k = 0; k < channels; k++) {
				printf("%u ", (*data)[i * width * channels + j + k]);
			}
		}
		printf("\n");
	}

	printf("\n");
#endif
}


/*
FATAL

Função usada para mostrar mensagem e encerrar programa em caso de erro.

*/
void FATAL(char msg[]) {
	printf("%s", msg);
	system("PAUSE");
	exit(0);
}


/*
allocateImageMemory

Aloca espaço na memória para um vetor de imagem PPM.
Retorna 1 em caso de sucesso.

*/
int allocateImageMemory(unsigned char **output,
	unsigned int width,
	unsigned int height,
	unsigned int channels) {

	*output = malloc(width * height * channels * sizeof(unsigned char));

	if (output == NULL)
		return 0;
	else
		return 1;
}

/*
newRandomImage

Gera uma imagem aleatoriamente para fins de teste.
Valores de 0 a 255.
!!Nota: Não gera um arquivo PPM, apenas o vetor de imagem
Retorna 1 em caso de sucesso.

*/
int newRandomImage(unsigned char **output,
	unsigned int width,
	unsigned int height,
	unsigned int channels) {

	*output = malloc(width * height * channels * sizeof(unsigned char));

	if (output == NULL)
		return 0;

	srand(time(NULL));

	for(unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width * channels; j = j + channels) {
			for (unsigned int k = 0; k < channels; k++) {

				int r = rand() % 255;

				(*output)[i * width * channels + j + k] = r;

			}
		}
	}

	return 1;

}