#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXLINES 10000
#define ALLOCSIZE 100000 
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *lineptr[MAXLINES];
int lines;

char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >= n ){
		allocp += n;
		return allocp - n;
	}else{
		return 0;
	}
}

void writelines(char *lineptr[], int nlines, char *name){
	FILE *fp;
	char *newname = malloc(sizeof(name) + 9);
	char *prefix = "sorted_";
	strcpy(newname, prefix);
	strcat(newname, name);
	printf("... Results file can be found at ./%s \n", newname);
	fp = fopen(newname, "w");
	if(fp == NULL)
		exit(-1);
	for(int i = 0; i < nlines; i++){
		fprintf(fp,"%s", lineptr[i]);
	}
	fclose(fp);
}

int readlines(char *lineptr[], int maxlines, char *file){
	char *p;
	int lines = 0;
	FILE *fp = fopen(file, "r");
	if(fp == NULL){
		printf("ERROR \n");
		return 1;
	}
	char *line = NULL;
	size_t len = 0;
	while(getline(&line, &len, fp) != -1 )
		if(lines >= maxlines || (p = alloc(len)) == NULL){
			return -1;
		}else{
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[lines++] = p;
		}

	fclose(fp);
	free(line);
	return lines;
}

int numcmp(char *s1, char *s2){
	double v1,v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if(v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else 
		return 0;
}

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int main(int argc, char **argv)
{
	int algorithm;
	int nlines;
	int numeric = 0; 
	char *filename, *algorithmname;
	int argname;
	if(argc > 1 && strcmp(argv[1], "-n") == 0){ 
		numeric = 1;
		argname = 2;
		algorithm = 3;
	}else{
		argname = 1;
		algorithm = 2;
	}
	filename = argv[argname];
	algorithmname = argv[algorithm];
	char * quick = strstr(algorithmname, "quick");
	char * merge = strstr(algorithmname, "merge");
	if(quick){
		printf("sorting %s file with quicksort\n", filename);

		if((nlines = readlines(lineptr, MAXLINES, argv[argname])) >= 0){
			if (numeric){
				quicksort((void**) lineptr, 0, nlines-1, (int (*) (void*, void*)) (numcmp));
				mergesort((void**) lineptr, 0, nlines-1, (int (*) (void*, void*)) (numcmp));
			}else{
				quicksort((void**) lineptr, 0, nlines-1, (int (*) (void*, void*)) (strcmp));
				mergesort((void**) lineptr, 0, nlines-1, (int (*) (void*, void*)) (strcmp));
			}
		
		writelines(lineptr, nlines, filename);
		return 0;
		}else{
			printf("Error \n");
			return 1;
		}
		
	}else if (merge){
		printf("sorting %s file with mergesort\n", filename);
		if((nlines = readlines(lineptr, MAXLINES, argv[argname])) >= 0){
			if(numeric){
				mergesort((void**) lineptr, 0, nlines, (int (*) (void*, void*)) (numcmp));
			}else{
				mergesort((void**) lineptr, 0, nlines, (int (*) (void*, void*)) (strcmp));
			}
		writelines(lineptr, nlines, filename);
		return 0;
		}else{
			printf("ERROR\n");
			return 1;
		}
	}else{
		printf("ERROR\n");
		return -1;
	}
	
			
	return 0; 

}