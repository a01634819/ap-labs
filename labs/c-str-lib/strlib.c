int mystrlen(char *str) {
    if (*str == '\0')
        return 0;
    
    return (1 + mystrlen(++str));
}

char *mystradd(char *origin, char *addition){
    char *str = origin + mystrlen(origin);
    while (*addition != '\0'){
        *str++ = *addition++;
    }
    *str = '\0';
    return origin;
}

int mystrfind(char *origin, char *substr){
    int x = mystrlen(substr);
    int a = 0, b = 0,c = 0;
    while (origin[a] != '\0') {
        c = a;
        while (origin[a] == substr[b] && origin[a] != '\0') {      
            b++;
            a++;           
        }
        if (b == x) {
            return c;
        }
        b = 0;
        a++;    
    }
    return 0;
}