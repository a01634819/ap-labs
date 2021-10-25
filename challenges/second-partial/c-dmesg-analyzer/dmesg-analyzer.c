#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define REPORT_FILE "report.txt"
#define HASHSIZE 500000

struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];
struct nlist* item;

unsigned hash(char *s){

    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval%HASHSIZE;
}

struct nlist *lookup(char *s){

    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next){
        if(strcmp(s, np->name) == 0){
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL){
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup(name))==NULL){
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }else{     
        char *tam;
        tam = np->defn;
        np->defn = malloc(strlen(np->defn) + strlen(defn) + 500000);
        strcpy(np->defn, tam);
        strcat(np->defn, "    ");
        strcat(np->defn, defn);
        return NULL;
    }
    if((np->defn = strdup(defn)) == NULL){
        return NULL;
    }
    return np; 
}

void analizeLog(char *logFile, char *report);


int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {

    printf("Generating Report from: [%s] log file\n", logFile);
    
    FILE *txt;
    char *a;
    char *b;
    char *time;
    char *temp;
    char *write;
    char *line = NULL;
    char *copy01;
    char *copy02;
    size_t s = 0;
    ssize_t r;

    txt = fopen(logFile, "r");

    if (txt == NULL){
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    while ((r = getline(&line, &s, txt) != -1)){
        copy01 = strdup(line);
        copy02 = strdup(line);
        a = strtok(line, "]");
        time = strdup(a);
        a = strtok(NULL, ":");
        temp = strtok(NULL, "");
        if (temp == NULL){
            temp = a;
        }
        b = strtok(copy02, "]");
        b = strtok(NULL, "");
        if(a != NULL){
            write = malloc(strlen(time) + strlen(temp) +4);
            strcpy(write,time);
            strcat(write,"]");
            strcat(write,temp);
            if(strcmp(a, b) == 0){
                install("General", copy01);
            }else{
                install(a, write);
            }
        }   
    }   

    fclose(txt);
    txt = fopen(REPORT_FILE, "w");

    for (int i = 0; i < HASHSIZE; i++){
        if(hashtab[i]!=NULL){
            fprintf(txt, "%s\n", hashtab[i]->name);
            fprintf(txt, "    %s\n", hashtab[i]->defn);
        }
    }

    printf("Report is generated at: [%s]\n", report);
}