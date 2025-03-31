#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt_decrypt(char* input, char* output, int key) {
	int i;
	for (i = 0; i < strlen(input); i++) {
		output[i] = input[i] ^ key;
	}
	output[i] = '\0';
}

int readFile(FILE*f,char* fileName, char* buffer) {
	if (!f || ferror(f)) {
		printf("Error with file -> %s\n", fileName);
		return 0;
	}
	fread(buffer, 1, 1024, f);
	printf("File read successfully\n");
	return 1;
}
int writeFile(FILE*f,char* fileName, char* buffer) {
	if (!f || ferror(f)) {
		printf("Error with file -> %s\n", fileName);
		return 0;
	}
	fwrite(buffer, 1, strlen(buffer), f);
	printf("File written successfully\n");
	return 1;
}
char* inputFilePath() {
	char* path;
	printf("Enter file file path: ");
	char element;
	int offset = 0, flag = 0, size = 10;
	path = (char*)malloc(10);
	while (!flag) {
		scanf("%c", &element);
		if (element == '\n') {
			flag = 1;
			element = '\0';
		}
		path[offset++] = element;

		if (offset == size - 1) {
			size += size;
			path = (char*)realloc(path, size);
		}
	}
	path = (char*)realloc(path, offset + 1);
	return path;
}

int main() {
	char* inputFile;
	char* outputFile;
	char* buffer;
	char* encryptedBuffer;

	char key = 'A';

	inputFile = inputFilePath();
	outputFile = inputFilePath();

	FILE* input = fopen(inputFile, "r");
	FILE* output = fopen(outputFile, "a");

	if (!input || !output) {
		printf("Error opening file\n");
		return 0;
	}
	while (feof(input)) {
		buffer = (char*)malloc(1024);
		encryptedBuffer = (char*)malloc(1024);

		if (!readFile(input,inputFile, buffer)) {
			printf("Error\n");
			return 0;
		}

		encrypt_decrypt(buffer, encryptedBuffer, key);

		if (!writeFile(output,outputFile, encryptedBuffer)) {
			printf("Error\n");
			return 0;
		}

		free(buffer);
		free(encryptedBuffer);
	}

	return 0;
}