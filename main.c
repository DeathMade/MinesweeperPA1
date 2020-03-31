#include <stdio.h>
#include <stdlib.h>

#define START_LENGTH 10
#define START_DEPTH 10

/* function that frees up allocated 2D array */
void free2D (char **arr,int depth){
    for (int i = 0; i < depth; i++){
        free(arr[i]);
    }
    free(arr);
}

/* function for loading individual characters, checks if it's * or . or if reached EOF */
int loadChar(char * helper){

    char tmp = '0';

    int eof = scanf("%c", &tmp);

    if ( eof == EOF ){
        return EOF;
    } else if (eof != 1 || ( tmp != '.' && tmp != '*' && tmp != '\n')){
        return 1;
    } else if ( tmp == '\n'){
        return 2;
    }
    *helper = tmp;
    return 0;
}

/* Increases value of each tile if it's next to a mine */
void increaseNeighbors(char **arr,int h_pos, int v_pos, int depth, int length){

    int v_pos_1 = 1;
    int v_pos_2 = 1;
    int h_pos_1 = 1;
    int h_pos_2 = 1;

	if (arr[v_pos][h_pos] != '*'){
		return;
	}

    if (v_pos - 1 < 0){
        v_pos_1 = 0;
    }

    if (v_pos + 1 >= depth){
        v_pos_2 = 0;
    }

    if (h_pos - 1 < 0){
        h_pos_1 = 0;
    }

    if (h_pos + 1 >= length){
        h_pos_2 = 0;
    }

    for (int i = v_pos - v_pos_1; i <= v_pos + v_pos_2; i++){
        for (int n = h_pos - h_pos_1; n <= h_pos + h_pos_2; n++){

            if ( arr[i][n] == '.' ){
                arr[i][n] = '1';
            } else if (arr[i][n] == '*'){
            } else {
                arr[i][n]++;
            }
        }
    }

}

int main() {

    int eof = 0;
    int lineLength = 0;
    int lineLength_max = START_LENGTH;
    int lineDepth = 0;
    int lineDepth_max = START_DEPTH;

    char **lines;
    char helper = '0';

    /* Creating 2D array, first we allocate 10 lines, and then allocate length of the first line */
    lines = (char**)malloc(lineDepth_max*sizeof(char*));
    lines[0] = (char*) malloc(lineLength_max*sizeof(char));

    printf("Zadejte hraci plochu:\n");

    /* load first line only to determine the length of the line */
    while (eof != EOF){

        eof = loadChar(&helper);

        if (eof == EOF) {
            if(lineLength == 0){
		free2D(lines, lineDepth+1);
                printf("Nespravny vstup.\n");
                return 0;
            }
            break;
        } else if (eof == 1){
		free2D(lines, lineDepth+1);
            printf("Nespravny vstup.\n");
            return 0;
        } else if (eof == 2){
	if(lineLength == 0){
		free2D(lines, lineDepth+1);
                printf("Nespravny vstup.\n");
                return 0;
            }
            break;
        }

        lines[0][lineLength] = helper;

        lineLength++;

        /* Extending array if we reach allocated size */
        if (lineLength >= lineLength_max){
            lineLength_max = 2*lineLength_max;
            lines[0] = (char*)realloc(lines[0],lineLength_max* sizeof(char));
        }
    }

    lineDepth++;
	int eof_helper = 0;
    while (eof != EOF){
        lines[lineDepth] = (char*)malloc(lineLength*sizeof(char));

        for (int i = 0; i < lineLength+1; i++){

            eof = loadChar(&helper);

            /* Here we check for invalid inputs.
             * If we reached allowed number of chars in line but it still doesnt end then invalid input
             * If we reached EOF or newline before the allowed number of chars it also means invalid input */
            if ((i == lineLength && !(eof == 2 || eof == EOF)) || (eof == 2 && i != lineLength && i!=0) || eof == 1){
		free(lines[lineDepth]);
		free2D(lines, lineDepth);
                printf("Nespravny vstup.\n");
                return 0;
            /* Here we check for end of the line
             * If we reached allowed number of chars and next symbol is new line then exit the cycle
             * Same for if we reach EOF */
            } else if ((eof == 2 && (i == lineLength || i==0)) || (eof == EOF && (i == lineLength || i == 0))){

		if (eof == 2 && i ==0){
			eof_helper = 1;
			break;
		}

		if (eof == EOF && i == 0 && !eof_helper){
			free(lines[lineDepth]);
		} else if (eof == EOF && i == 0 && eof_helper){
			free(lines[lineDepth]);
			lineDepth--;
			free(lines[lineDepth]);
		}
                break;
            } 
            lines[lineDepth][i] = helper;
        }
	
        if (eof == EOF ){
            break;
        }

        lineDepth++;
        if (lineDepth >= lineDepth_max){
            lineDepth_max = 2*lineDepth_max;
            lines = (char**) realloc(lines,lineDepth_max* sizeof(char*));
        }

    }
	
    for (int i = 0; i < lineDepth; i++){
        for (int n = 0; n < lineLength; n++){
            increaseNeighbors(lines, n, i, lineDepth, lineLength);
        }
    }

printf("Vyplnena hraci plocha:\n");

    for (int i = 0; i < lineDepth; i++){
        for (int n = 0; n < lineLength; n++){
            printf("%c", lines[i][n]);
        }
        printf("\n");
    }

free2D(lines, lineDepth);

    return 0;
}
