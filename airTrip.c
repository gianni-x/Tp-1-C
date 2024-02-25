#include "airTrip.h"
#include <math.h>


// hacemos una funcion auxiliar para obtener la longitud de src (luego la utilizaremos para strDup)
int len(char*s){
    if (s == NULL) {
        return 0;
    } else {
    int indice = 0;
    while (s[indice]!='\0'){
    	indice++;
    	}
    return indice;
    }
}

char* strDup(char* src) {
      int caracteres = len(src);
      char *duplicate = (char*) malloc(sizeof(char) * (caracteres + 1));
      // solicitamos memoria para el nuevo str y le sumamos 1 por el ultimo caracter
      int i = 0;
      while (i<caracteres){
      	duplicate[i] = src[i]; //copiamos los caracteres de "src" a duplicate
      	i++;
      }
      duplicate[i] = '\0'; // le agregamos el caracter nulo del str
      return duplicate;
     }

int strCmp(char* a, char* b) {
    int i=0;
    while( a[i]!=0|| b[i]!=0){
    // usamos el or en el caso de que 1 se termine antes que el otro y asi uno de los strs entre al ciclo.
    // 1) caso 1 = ambos str iguales a NULL --> 0 y no entra al ciclo.
    // 2) caso 2 = si a[i] llega al final de la lista antes que b --> 1.
    // 3) caso 3 = si b[i] llega al final de la lista antes que a --> -1
    // 4) caso 4 = a<b --> 1
    // 5) caso 5 = b<a --> -1
    	if(a[i]<b[i]){
           return 1;
    	} else if (b[i]<a[i]){
    		return -1;
    	}
    	i++;
    }
    return  0;
}


char* strCnt(char* src1, char* src2) {
	int caracteres = len(src1) + len(src2);
	char *concatena = (char*) malloc((caracteres + 1) * sizeof(char));
	// alojamos memoria para caracteres mas el ultimo caracter nulo.
	int k = 0;
	int v = 0;
	while (len(src1) > k) {
    	concatena[k] = src1[k]; // copio primero los caracteres de src1
    	k++;
	}
	while (len(src2) > v) {
    	concatena[k] = src2[v];  // luego copio los caracteres de src2
    	k++;
    	v++;
	}
	concatena[k] = '\0';
	return concatena;
}

// funciones utiles ya implementadas por nuestros profesores:
float flyLength(struct airport* a1, struct airport* a2) {
    float deltaLon = a1->longitude - a2->longitude;
    float deltaLat = a1->latitude - a2->latitude;
    return sqrt(deltaLon*deltaLon + deltaLat*deltaLat);
}

struct airTrip* airTripNew(char* plane) {
    struct airTrip* at = (struct airTrip*) malloc(sizeof(struct airTrip));
    at->plane = strDup(plane);
    at->first = 0;
    at->totalLength = 0.0;
    return at;
}

void airTripAddLast(struct airTrip* trip, char* name, float longitude, float latitude) {
    // Pido memoria para agregar un nuevo airport:
    struct airport* NewAirport = (struct airport*)malloc(sizeof(struct airport));
    // Cargo los datos del nuevo airport
    NewAirport->name = strDup(name);
    NewAirport->latitude = latitude;
    NewAirport->longitude = longitude;
    NewAirport->next = NULL; // Si solo existe un aeropuerto, el proximo del primero es nulo.

    if (trip->first == NULL) { // CASO 1: Si solo hay un viaje, agregamos ese viaje al aeropuerto.
     	trip->first = NewAirport;
       // Actualizo la distancia recorrida. Como solo tenemos una parada, la distancia recorrida es 0.0
        trip->totalLength = 0.0;
    } else { // CASO 2: Si tenemos mas de 1 airport en el trip:
        // Creo un puntero auxiliar que voy a utilizar para calcular totalLength para no perderlos.
        struct airport* aux = trip->first;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = NewAirport; //Aca me guardo todos mis viajes con las paradas recorridas.
        // Actualizo la distancia recorrida
        trip->totalLength += flyLength(aux, NewAirport); // Calculamos la distancia total del viaje.
	}
}

void airTripAddBest(struct airTrip* trip, char* name, float longitude, float latitude) {
    // Crear un nuevo aeropuerto
    struct airport* nuevo = (struct airport*)malloc(sizeof(struct airport));
    nuevo->name = strDup(name);
    nuevo->latitude = latitude;
    nuevo->longitude = longitude;
    nuevo->next = NULL;
    if (trip->first == NULL) { 
        // Si no hay aeropuertos en el viaje, asignar el nuevo como el primero
        trip->first = nuevo; 
    } else {
        struct airport* mejoranterior = trip->first;
        struct airport* curr = trip->first; 
        float mejordistancia = FLT_MAX; 
        float len_aux = 0.0; // Variable auxiliar para calcular la longitud
        // Recorrer la lista de aeropuertos existentes
        while (curr != NULL) { 
            if (curr->next != NULL) { 
                // Calcular la longitud auxiliar para aeropuertos intermedios
                float a = flyLength(curr, nuevo) + flyLength(nuevo, curr->next); 
                float b = flyLength(nuevo, curr->next); 
                float c = flyLength(curr, curr->next); 
                len_aux = a + b - c; 
            } else { 
                // Calcular la longitud auxiliar para el ultimo aeropuerto
                len_aux = flyLength(curr, nuevo); 
            }
            if (len_aux < mejordistancia) { 
                // Actualizar la mejor distancia y el aeropuerto anterior mas cercano
                mejordistancia = len_aux; 
                mejoranterior = curr; 
            }
            curr = curr->next; 
        }
        if (mejoranterior->next != NULL) { 
            // Insertar el nuevo aeropuerto entre dos aeropuertos existentes
            nuevo->next = mejoranterior->next; 
            mejoranterior->next = nuevo;  
            // Actualizar la longitud total del viaje teniendo en cuenta la insercion
            trip->totalLength = trip->totalLength - flyLength(mejoranterior, mejoranterior->next->next) 
                                + flyLength(mejoranterior, mejoranterior->next)
                                + flyLength(mejoranterior->next, mejoranterior->next->next);
        } else { 
            // Insertar el nuevo aeropuerto al final de la lista
            mejoranterior->next = nuevo;  
            // Actualizar la longitud total del viaje al agregar el nuevo aeropuerto
            trip->totalLength = trip->totalLength + flyLength(mejoranterior, nuevo);
        }
    } 
}

void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2) {
    // Creamos la nueva estructura:
    struct airTrip* nuevo = (struct airTrip*)malloc(sizeof(struct airTrip));
    if (strCmp(trip1->plane, trip2->plane) == 0) {
        // Si el nombre del avion en ambos recorridos es el mismo, nos quedamos simplemente con el primero
        nuevo->plane = strDup(trip1->plane);
    } else {
        // Si los nombres son diferentes, concatenamos el nombre del primero con el segundo separados por un guion
        char* temp = strCnt(trip1->plane, "-");
        nuevo->plane = strCnt(temp, trip2->plane);
        free(temp);
    }
    nuevo->first = trip1->first;
    if (nuevo->first == NULL) {
        nuevo->first = trip2->first;
        nuevo->totalLength = trip2->totalLength;
    } else if (trip2->first != NULL) {
        struct airport* lastAirport = nuevo->first;
        while (lastAirport->next != NULL) { 
            // Recorremos la lista enlazada del primero hasta el ultimo
            lastAirport = lastAirport->next;
        }
        // Enlazamos el ultimo aeropuerto del primer recorrido con el primer aeropuerto del segundo
        lastAirport->next = trip2->first;
        // Calculamos la longitud total del nuevo recorrido teniendo en cuenta la longitud entre el ultimo aeropuerto del primer recorrido y el primer   aeropuerto del segundo
        nuevo->totalLength = trip1->totalLength + flyLength(lastAirport, trip2->first) + trip2->totalLength;
    } else {
        nuevo->totalLength = trip1->totalLength;
    }
    // Liberamos las estructuras de los dos recorridos originales, ya que no son mas necesarias
    free(trip1->plane);
    free(trip2->plane);
    free(trip1);
    free(trip2);
    *tripJoin = nuevo; // Almacenamos la nueva estructura en el puntero tripJoin (el recorrido completo)
}

void airTripDelLast(struct airTrip* trip) {
    if(trip->first != NULL) { //Se verifica si la lista de aeropuertos no está vacía (la primera parada no es NULL).
        struct airport* aux = trip->first;
        //Se crea un puntero aux a airport y se le asigna el primer elemento de la lista de aeropuertos.
        struct airport* anterior = NULL;
     	//Se crea un puntero anterior a airport y se le asigna NULL (guardará la posición anterior a aux mientras se recorre la lista de aeropuertos).
        while(aux->next != NULL) {
        //Loopeamos mientras el puntero next del aeropuerto actual (aux) no sea NULL (mientras no lleguemos al final de la lista).
            anterior = aux;
            aux = aux->next;
        }
        
        if(anterior != NULL) {
        //Se verifica si el puntero anterior no es NULL (es decir, si la lista tiene más de un elemento).
        //En este caso, actualizamos el puntero next del aeropuerto anterior para que apunte a NULL, eliminando así el último aeropuerto de la lista.
            trip->totalLength -= flyLength(anterior,aux); // Calculamos la distancia total del viaje
            anterior->next = NULL;
            
        } else {
        //Si el puntero anterior es NULL (es decir, si la lista tiene solo un elemento).
            trip->first = NULL;
            trip->totalLength = 0.0; // Teníamos un solo airport y lo vamos a liberar, por ende la longitud del recorrido es 0.0
        }
        
        free(aux->name);
        //libera la memoria asociada al nombre del último aeropuerto (aux->name).
        free(aux);
        //Libera la memoria asociada al último aeropuerto (aux).
    }
}

void airTripRemoveDuplicates(struct airTrip* trip) {
    if (trip == NULL || trip->first == NULL) {
        // Caso vacio
        return;
    }

    struct airport* aux = trip->first;
    float new_totalLength = 0.0;

    while(aux != NULL){
        
        struct airport* current = aux-> next;
        struct airport* previo = aux;

        while(current != NULL){

            if(strCmp(aux->name,current->name) == 0){
                previo->next = current->next;
                free(current->name);
                free(current);
		current = previo->next;
            } else{
            current = current->next;
            previo = previo->next;
        	}
        }

        aux = aux ->next;  
    }
    aux = trip->first;

    while (aux != NULL && aux->next != NULL) {

        new_totalLength += flyLength(aux, aux->next);
        aux = aux->next;
    }
    // Actualizamos la longitud total del recorrido
    trip->totalLength = new_totalLength;
}

char* airTripGetTrip(struct airTrip* trip) {
    char* paradas = NULL; // Utilizaremos para ir almacenando las paradas a lo largo del recorrido
    // Creamos dos punteros auxiliares:
    char *paradas_solas;
    char *todas_paradas;
    char* nueva_parada; // Servir  para almacenar el nombre del aeropuerto actual
    struct airport *current = trip->first;
    // Creamos el puntero para recorrer la lista de aeropuertos, lo inicializamos en el primero
    while (current != 0) {
        if (paradas == NULL) { // Si estamos en la primera parada
            paradas = current-> name; // Agregamos el nombre del aeropuerto actual al str paradas
            current = current->next; // Avanzamos al proximo aeropuerto
        } else { // En el caso de que no estemos en la primera parada
            nueva_parada = current-> name; // Toma el nombre del airport en el que nos encontramos
            paradas_solas = strCnt(paradas, "-");
            todas_paradas = strCnt(paradas_solas, nueva_parada);
            // Concatenamos la(s) parada(s) existentes con las nuevas paradas separadas por un gui n
            free(paradas); // Se libera la memoria asignada a paradas
            paradas = todas_paradas; // Paradas almacena todas las paradas que tenemos hasta ahora.
            free(todas_paradas); //
            current = current-> next; // Avanzo en la lista
        }
    }
    return paradas;
}


// funciones brindadas por nuestros profesores de TD2:
void airTripPrint(struct airTrip* trip) {
    printf("%s : %.2f\n", trip->plane, trip->totalLength);
    struct airport* ap = trip->first;
    while(ap != 0) {
        printf("[%s:(%.2f,%.2f)]",ap->name,ap->latitude,ap->longitude);
        ap = ap->next;
    }
    if(trip->first != 0) {
        printf("\n");
    }
}

void airTripDelete(struct airTrip* trip) {
    struct airport* ap = trip->first;
    while(ap != 0) {
        struct airport* next = ap->next;
        free(ap->name);
        free(ap);
        ap = next;
    }
    free(trip->plane);
    free(trip);
}
