#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 200

/*functions*/
int readFile(char *filename, char **array, int maxLineLength);


int main(){
    char *dizi[MAX_LINE_LENGTH]; // Maksimum 200 satir saklamak için bir dizi
    int i,j,lineLength;

    lineLength = readFile("data.txt", dizi, MAX_LINE_LENGTH);

    if (lineLength == -1) {
        return 1; // Hata durumunda programi sonlandir
    }

    // Diziyi yazdir
    for (j = 0; j < lineLength; j++) {
        printf("[%d]: %s\n", j + 1, dizi[j]);
    }

    // Bellegi serbest birak
    for (j = 0; j < lineLength; j++) {
        free(dizi[j]);
    }

    return 1;
}

int readFile(char *filename, char **array, int maxLineLength){
    FILE *file;
    char *line;
    int i;

    line = (char*) calloc(MAX_LINE_LENGTH,sizeof(char));
    file = fopen(filename, "r"); // filename dosyasini okuma modunda ac

    if (file == NULL) {
        perror("File opening error");
        return -1; // Hata durumunda -1 dondur
    }

    i = 0;
    
    // Maksimum satir sayisini astiysa donguden cik
    while ( (fgets(line, MAX_LINE_LENGTH, file) != NULL) || i >= maxLineLength) {
        // Satir sonundaki new line karakterini kaldir
        line[strcspn(line, "\n")] = '\0';

        // Satiri diziye ekle
        array[i] = strdup(line);
        i++;
    }

    fclose(file);

    return i; // Okunan satir sayisini dondur
}
