#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define REPORT_FILE "report.txt"

struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
}

#define HASHSIZE 50000;
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s){
    unsigned hashval;
    for(hashval =0; *s != '\0';s++){
        hashval=*s+31*hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s){
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NUULL; np =np->next){
        if (strcmp(s, np->name)== 0){
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL){
        np=(struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL){
            return Null;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval]=np;
    }else{
        free((void *)np->defn);
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

    // Implement your solution here.

    printf("Report is generated at: [%s]\n", report);
}
