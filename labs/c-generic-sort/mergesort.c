#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void mergesort(void *lineptr[], int left, int right, int (*comp)(void *, void *)) {
	char *aux[10000];
	copyarray(lineptr, left, right, aux);
	split(aux, left, right,lineptr, comp);
}

void copyarray(char *lineptr[], int left, int right, char *aux[]){
	for(int x = left; x < right; x++){
		aux[x] = lineptr[x];
	}
}

void split(char *aux[], int left, int right, char *lineptr[],int (*comp)(void *, void *)){
	if(right - left <= 1) 
		return;
	
	int mid = (right + left) / 2;
	split(lineptr, left, mid, aux, comp);
	split(lineptr, mid, right, aux, comp);
	merge(aux, left, mid, right, lineptr, comp);
}

void merge(char *lineptr[], int left, int mid, int right, char *aux[], int (*comp)(void *, void *)){
	int a = left;
	int b = mid;
	for(int x = left; x < right; x++){
		if(a < mid && (b >= right || (*comp)(lineptr[a], lineptr[b]) <= 0)){
			aux[x] = lineptr[a];
			a++;
		}else{
			aux[x] = lineptr[b];
			b++;
		}
	}
}