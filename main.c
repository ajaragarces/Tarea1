#include <stdio.h>
#include <stdlib.h>

struct Nodo{

    char info;
    struct Nodo *next;

};

struct Lista{

    struct Nodo *head;
    int length;

};

struct Cadena{

    struct Lista *superior;
    struct Lista *central;
    struct Lista *inferior;

};

struct Nodo *crearNodo(char i){

    struct Nodo *node = (struct Nodo *)malloc(sizeof(struct Nodo));
    node->info = i;
    node->next = NULL;

    return node;

}

//MÃ©todos Lista

struct Lista *crearLista(){

    struct Lista *lista = (struct Lista *)malloc(sizeof(struct Lista));
    lista->head = NULL;
    lista->length = 0;

    return lista;

}

void imprimirLista(struct Lista *list){

    struct Nodo *aux = list->head;

    while(aux != NULL){

        printf("%c->", aux->info);
        aux = aux->next;

    }

    printf("\n");

}

void insertarLista(struct Lista *lista, char info){

    if(lista->head == NULL){

        lista->head = crearNodo(info);
        lista->length++;
        return;

    }

    struct Nodo *aux = lista->head;

    while(aux->next != NULL){

        aux = aux->next;

    }

    aux->next = crearNodo(info);
    lista->length++;

}

void borrarLista(struct Lista *lista){

    if(lista->head == NULL) return;

    struct Nodo *next = lista->head->next;

    while(next != NULL){

        free(lista->head);
        lista->head = NULL;
        lista->head = next;
        next = next->next;

    }

    free(lista->head);
    lista->head = NULL;

}

char get(struct Lista *lista, int index){

    struct Nodo *aux = lista->head;
    int i = 0;
    
    for(; i < index && aux != NULL; i++){

        aux = aux->next;

    }

    if(i == index) return aux->info;

    return '0';

}

struct Nodo *getNodo(struct Lista *lista, int index){

    struct Nodo *aux = lista->head;
    int i = 0;

    for(; i < index && aux != NULL; i++)
        aux = aux->next;

    if(i == index) return aux;

    return NULL;

}

int indexLista(struct Lista *lista, struct Nodo *nodo){

    struct Nodo *aux = lista->head;
    int i = 0;

    while(aux != NULL){

        if(aux == nodo) return i;

        aux = aux->next;

    }

    return -1;

}

int largoLista(struct Lista *lista){

    struct Nodo *aux = lista->head;
    int i = 0;

    while(aux != NULL){

        if(aux->info != ' ') i++;
        aux = aux->next;

    }

    return i;

}

int largoTrayecto(struct Lista *lista, int index){

    int i = 0;

    for(i = index; i < lista->length && get(lista, i) != ' '; i++);

    return i - index + 1;

}

//MÃ©todo Cadena

struct Cadena *crearCadena(){
    
    struct Cadena *chain = (struct Cadena *)malloc(sizeof(struct Cadena));
    chain->superior = NULL;
    chain->central = NULL;
    chain->inferior = NULL;

    return chain;

}

char *alcano(int length){

    switch(length){

        case 1: return "met";
        case 2: return "et";
        case 3: return "prop";
        case 4: return "but";
        case 5: return "pent";
        case 6: return "hex";
        case 7: return "hept";
        case 8: return "oct";
        case 9: return "non";
        case 10: return "dec";
        case 11: return "undec";
        case 12: return "dodec";
        case 13: return "tridec";
        case 14: return "tetradec";
        case 15: return "pentadec";
        case 16: return "hexadec";
        case 17: return "heptadec";
        case 18: return "octadec";
        case 19: return "nonedec";
        case 20: return "eicos";
        case 21: return "heneicos";
        case 22: return "docos";
        case 23: return "tricos";
        case 24: return "tetracos";
        case 30: return "tricont";
        case 40: return "tetracont";
        default: return NULL;

    }

}

char *nombrarAlcano(struct Cadena *chain){

    if(chain->central == NULL) return NULL;

    int length = largoLista(chain->central);

    for(int i = 0; i < chain->central->length; i++){

        if(get(chain->central, i) == ' '){
            
            int lSup = largoLista(chain->superior, i), lInf = largoLista(chain->inferior, i);
            
            int nlen = lSup > lInf ? lSup : lInf;
            
            if(i + 1 + nlen > length)
                length = i + 1 + nlen;
            
            
        }

    }

    return strncat(alcano(length), "ano", 3 * sizeof(char));

}

void borrarCadena(struct Cadena *chain){

    if(chain == NULL) return;

    borrarLista(chain->inferior);
    borrarLista(chain->central);
    borrarLista(chain->superior);

    free(chain->inferior);
    free(chain->central);
    free(chain->superior);

    chain->inferior = NULL;
    chain->central = NULL;
    chain->superior = NULL;
    

}

void estructurarCadena(struct Cadena *chain, const char *str){

    chain->superior = crearLista();
    chain->central = crearLista();
    chain->inferior = crearLista();

    short sup = 0, inf = 0, gato = 0;

    for(int i = 0; str[i] != '\0'; i++){

        if(str[i] == '-') inf = 1;
        else if(str[i] == '+') sup = 1;
        else if(str[i] == '#'){

            if(gato == 1){

                inf = 0;
                sup = 0;

            }

            gato++;
            gato %= 2;

        }else{

            if(sup == 1){

                insertarLista(chain->superior, str[i]);
                insertarLista(chain->central, ' ');
                insertarLista(chain->inferior, ' ');


            }else if(inf == 1){

                insertarLista(chain->inferior, str[i]);
                insertarLista(chain->superior, ' ');
                insertarLista(chain->central, ' ');


            }else{

                insertarLista(chain->central, str[i]);
                insertarLista(chain->superior, ' ');
                insertarLista(chain->inferior, ' ');

            }

        }

    }

}

void salida(struct Cadena *chain){
    
    FILE *archivo = fopen("./salida.txt", "a");
    fputs(strncat(nombrarAlcano(chain), "\n", 1), archivo);
    
    fclose(archivo);
    
}

void diagrama(struct Cadena *chain){
    
    FILE *archivo = fopen("./diagramas.txt", "a");
    
    for(int i = 0; i < chain->superior->length; i++){
        
        char c = get(chain->superior, i);
        
        if(c != ' ')
            fputs("CH", archivo);
            
        fputc(c, archivo);
        
    }
    
    fputc('\n', archivo);
    
    short p = 0;
    
    for(int i = 0; i < chain->superior->length; i++){
        
        char c = get(chain->superior, i);
        
        if(c != ' ' && p == 0){
            
            fputc('|', archivo);
            p = 1;
            
        }else if(p == 1 && c == ' '){
            
            p = 0;
            fputc(c, archivo);
            
        }else
            fputc(c, archivo);
        
    }
    
    fputc('\n', archivo);
    
    for(int i = 0; i < chain->central->length; i++){
        
        char c = get(chain->central, i);
        
        if(c != ' '){
            
            fputs("CH", archivo);
            fputc(c, archivo);
            
        }
        
    }
    
    fputc('\n', archivo);
    
    for(int i = 0; i < chain->inferior->length; i++){
        
        char c = get(chain->inferior, i);
        
        if(c != ' ' && p == 0){
            
            fputc('|', archivo);
            p = 1;
            
        }else if(p == 1 && c == ' '){
            
            p = 0;
            fputc(c, archivo);
            
        }else
            fputc(c, archivo);
        
    }
    
    fputc('\n', archivo);
    
    for(int i = 0; i < chain->inferior->length; i++){
        
        char c = get(chain->inferior, i);
        
        if(c != ' ')
            fputs("CH", archivo);
            
        fputc(c, archivo);
        
    }
    
    fputc('\n', archivo);
    
    fclose(archivo);
    
}

int main(){

    FILE *archivo = fopen("./alcanos.txt", "r");

    int length;
    char *str;
    struct Cadena *chain = crearCadena();

    fscanf(archivo, "%d", &length);

    while(!feof(archivo)){

        fscanf(archivo, "%s", str);
        estructurarCadena(chain, str);
        salida(chain);
        diagrama(chain);

    }
    
    borrarCadena(chain);

    fclose(archivo);

    return 0;

}
