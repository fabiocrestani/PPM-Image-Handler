#pragma once

/* 
  PPM.h

  Funções para trata de arquivos de imagem no formato PPM e PGM.

  Exemplos de uso:

  Ler um arquivo:
    if (!loadPPMFile("original.ppm", &original_data, &width, &height, 3))
	FATAL("Não foi possível abrir a imagem original.\n");

  Exibir o conteudo da imagem:
    printTextPPM(&original_data, width, height, 3);

  Escrever um arquivo:
    storePPMFile("test.ppm", &test_data, width, height, 1);
*/


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
	unsigned int channels);


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
	unsigned int channels);


/*
PPMRGBToGrayscale

Converte um arquivo de imagem RGB para escala de cinza fazendo a média dos canais:
Nível de Cinza = (R + G + B) / 3

Retorna 1 em caso de sucesso.

*/
int PPMRGBToGrayscale(unsigned char **output,
	unsigned char **input,
	unsigned int width,
	unsigned int height);


/*
compareImageData

Recebe dois vetores de imagem em escala de cinza (1 canal) e compara pixel a pixel.

Retorna 1 se os vetores forem iguais.

*/
int compareImageData(unsigned char **test,
	unsigned char **input,
	unsigned int width,
	unsigned int height);


/*
printTextPPM

Imprime um vetor de imagem em format de texto.
Use channels = 1 para escala de cinza, ou channels = 3 para RGB.

*/
void printTextPPM(unsigned char **data,
	unsigned int width,
	unsigned int height,
	unsigned int channels);


/*
FATAL

Função usada para mostrar mensagem e encerrar programa em caso de erro.

*/
void FATAL(char msg[]);


/*
allocateImageMemory

Aloca espaço na memória para um vetor de imagem PPM

*/
int allocateImageMemory(unsigned char **output,
                        unsigned int width,
                        unsigned int height,
                        unsigned int channels);