#include <stdio.h>
#include <stdlib.h>
#include "airTrip.h"
#include <math.h>

int main() {

// strDuplicate

    // String vacio
    char* dup0 = strDup(NULL);
    printf("strDup(NULL) -> \"%s\"\n", dup0);
    free(dup0);
    printf("FREE DUP0\n");

    // String de un caracter
    char* dup1 = strDup("s");
    printf("strDup(\"s\") -> \"%s\"\n", dup1);
    free(dup1);
    printf("FREE DUP1\n");

    // String que incluya todos los caracteres validos distintos de cero
    char* dup2 = strDup("qwertyuiopasdfghjklzxcvbnm123456789");
    printf("strDup(\"qwertyuiopasdfghjklzxcvbnm123456789\") -> \"%s\"\n", dup2);
    free(dup2);
    printf("FREE DUP2\n");


    // String extra
    char* dup3 = strDup("steffyorigiannisere");
    printf("strDup(\"steffyorigiannisere\") -> \"%s\"\n", dup3);
    free(dup3);
    printf("\n");


// strCompare

    // Dos strings vacios
    printf("strCmp() -> %i\n", strCmp("\0","\0"));

    // Dos strings de un caracter
    printf("strCmp(\"a\",\"b\") -> %i\n", strCmp("a","b"));

    // Strings iguales hasta un caracter (hacer cmpStr(s1,s2) y cmpStr(s2,s1))
    printf("strCmp(\"juani\",\"juana\") -> %i\n", strCmp("juani","juana"));
    printf("strCmp(\"juana\",\"juani\") -> %i\n", strCmp("juana","juani"));

    // Dos strings diferentes (hacer cmpStr(s1,s2) y cmpStr(s2,s1)).
    printf("strCmp(\"hola\",\"chau\") -> %i\n", strCmp("hola","chau"));
    printf("strCmp(\"chau\",\"hola\") -> %i\n", strCmp("chau", "hola"));


// strConcatenate
    char* concat0 = strCnt("123","456");
    printf("strConcatenate(\"123\",\"456\") -> \"%s\"\n", concat0);
    free(concat0);
    printf("\n");

    // Un string vacio y un string de 3 caracteres
    char* concat1 = strCnt('\0',"abc");
    printf("strConcatenate(,\"abc\") -> \"%s\"\n", concat1);
    free(concat1);
    printf("\n");

    // Un string de 3 caracteres y un string vacio
    char* concat2 = strCnt("def",'\0');
    printf("strConcatenate(\"def\",) -> \"%s\"\n", concat2);
    free(concat2);
    printf("\n");

    // Dos strings de 1 caracter
    char* concat3 = strCnt("s","f");
    printf("strConcatenate(\"s\",\"f\") -> \"%s\"\n", concat3);
    free(concat3);
    printf("\n");

    // Dos strings de 5 caracteres
    char* concat = strCnt("01234","56789");
    printf("strConcatenate(\"01234\",\"56789\") -> \"%s\"\n", concat);
    free(concat);
    printf("\n");

// flyLength
    struct airport* a1 = (struct airport*)malloc(sizeof(struct airport));
    struct airport* a2 = (struct airport*)malloc(sizeof(struct airport));
    a1->name = strDup("a1");
    a1->latitude = 1.0;
    a1->longitude = 1.0;
    a1->next = NULL;
    a2->name = strDup("a2");
    a2->latitude = 2.0;
    a2->longitude = 2.0;
    a2->next = NULL;
    a1->next = a2;
    float len = flyLength(a1, a2);
    printf("Len %f\n\n",len);
    free(a1->name);
    free(a2->name);
    free(a1);
    free(a2);

// airTripNew
    struct airTrip* trip = airTripNew("A123");
    //trip->first = a1;

    airTripPrint(trip);
    //airTripDelete(trip);

// airTripAddLast
    // Vamos a usar el trip que acabamos de crear

    // Agregar una parada a un recorrido vacio.
    airTripAddLast(trip, "Ra3", 1.0, 1.0);

    // Agregar una parada a un recorrido de un sola parada.
    // A este recorrido le acabamos de agregar la primera parada, ahora le agregamos otra
    airTripAddLast(trip, "Ra2", 2.0, 2.0);

    // Agregar una parada a un recorrido de mas de una parada
    airTripAddLast(trip, "Ra3", 3.0, 3.0);


    // airTripPrint
   airTripPrint(trip);
   airTripDelete(trip);
   



// airTripAddBest

    // Primero creo la estructura airTrip que vamos a usar para testear
    struct airTrip* trip2= airTripNew("B1234");
    struct airport* a3 = (struct airport*)malloc(sizeof(struct airport));
    struct airport* a4 = (struct airport*)malloc(sizeof(struct airport));
    a3->name = strDup("a1");
    a3->latitude = 1.0;
    a3->longitude = 1.0;
    a3->next = a4;
    a4->name = strDup("a2");	
    a4->latitude = 2.0;
    a4->longitude = 2.0;
    a4->next = NULL;

    trip2->first = a3;

    // Agregar una parada a un recorrido vacio
    printf("INICIO ADDBEST1\n");
    airTripAddBest(trip2, "P01", 1.0, 1.0);
    airTripPrint(trip2);
    printf("INICIO ADDBEST2\n");
    // Agregar una parada a un recorrido de un sola parada.
    airTripAddBest(trip2, "P02", 2.5, 2.5);
    airTripPrint(trip2);



    printf("INICIO ADDBEST3\n");
    // Agregar una parada a un recorrido de mas de una parada tal que la parada quede en ultimo lugar
    airTripAddBest(trip2, "P04", 3.5, 3.5);
    airTripPrint(trip2);


    printf("INICIO ADDBEST4\n");
    // Agregar una parada a un recorrido de mas de una parada tal que la parada quede en segundo lugar.
    airTripAddBest(trip2, "P00", 1.25, 1.25);
    airTripPrint(trip2);


    printf("INICIO ADDBEST4\n");
    // Agregar una parada a un recorrido de mas de una parada tal que la parada quede en tercer lugar
    airTripAddBest(trip2, "P03", 3.0, 3.0);
    airTripPrint(trip2);

    airTripDelete(trip2);
 

    printf("INICIO JOIN1\n");
// airTripJoin
    struct airTrip* tripJoin;
    struct airTrip* trip_a = airTripNew("F1234");
    struct airTrip* trip_b= airTripNew("G1234");

    // Unir dos recorridos vacios
    airTripJoin(&tripJoin, trip_a, trip_b);
    airTripPrint(tripJoin);

    printf("FIN JOIN1\n");
    airTripDelete(tripJoin);

    // Unir un recorrido vacio con otro de una sola parada.
    // Le agregamos una parada a uno de los dos recorridos, el otro lo dejamos vacio
    struct airTrip* tripJoin2;
    struct airTrip* trip_a2 = airTripNew("F1234");
    struct airTrip* trip_b2= airTripNew("G1234");


    airTripAddLast(trip_a2, "Fa1", 1.0, 1.0);
    airTripJoin(&tripJoin2, trip_a2, trip_b2);
    airTripPrint(tripJoin2);

    printf("FIN JOIN2\n");

    airTripDelete(tripJoin2);


    // Unir dos recorridos con una sola parada cada uno.
    // Ahora le agregamos una parada al recorrido que estaba vacio, y tenemos dos recorridos de una sola parada, como se nos pide
    struct airTrip* tripJoin3;
    struct airTrip* trip_a3 = airTripNew("F1234");
    struct airTrip* trip_b3= airTripNew("G1234");
    airTripAddLast(trip_b3, "Ga1", 2.0, 2.0);
    airTripJoin(&tripJoin3, trip_a3, trip_b3);
    airTripPrint(tripJoin3);

    printf("FIN JOIN3\n");

    airTripDelete(tripJoin3);

    // Unir dos recorridos con mas de dos paradas cada uno.
    // Agregamos algunas paradas
    struct airTrip* tripJoin4;
    struct airTrip* trip_a4 = airTripNew("F1234");
    struct airTrip* trip_b4= airTripNew("G1234");
    airTripAddLast(trip_a4, "Fa2", 3.0, 1.4);
    airTripAddLast(trip_a4, "Fa3", 2.0, 1.8);
    airTripAddLast(trip_b4, "Ga2", 1.0, 2.5);
    airTripAddLast(trip_b4, "Ga3", 5.0, 2.6);
    airTripJoin(&tripJoin4, trip_a4, trip_b4);
    airTripPrint(tripJoin4);

    printf("FIN JOIN4\n");
    airTripDelete(tripJoin4);


// airTripDelLast
    // Creo el trip que vamos a usar para testear
    struct airTrip* trip3 = airTripNew("C234");
    struct airTrip* trip4 = airTripNew("C234");

    // Borrar el  ultimo de un recorrido vacio.
    airTripDelLast(trip3);
    airTripPrint(trip3);
    


    // Borrar el ultimo de un recorrido de exactamente una parada
    airTripAddLast(trip4, "C1", 1.0, 1.0);
    airTripPrint(trip4);
    airTripDelLast(trip4);
    airTripPrint(trip4);


    // Borrar el  ultimo de un recorrido de exactamente dos paradas
    airTripAddLast(trip3, "C1", 1.0, 1.0);
    airTripAddLast(trip3, "C2", 2.0, 2.0);
    airTripDelLast(trip3);
    airTripPrint(trip3);
    printf("DELTRIP3\n");


    // Borrar el ultimo de un recorrido de mmas de dos paradas
    airTripAddLast(trip3, "C2", 2.0, 2.0);
    airTripAddLast(trip3, "C3", 3.0, 3.0);
    airTripAddLast(trip3, "C2", 2.0, 2.0);
    airTripAddLast(trip3, "C3", 3.0, 3.0);
    airTripDelLast(trip3);
    airTripPrint(trip3);
    printf("DELTRIP4\n");
    airTripDelete(trip3);



// airTripRemoveDuplicates

    //  Borrar duplicados de un recorrido sin duplicados.
    airTripRemoveDuplicates(trip4);
    airTripPrint(trip4);
    printf("FIN DUPLICATES1\n");
    airTripDelete(trip4);

    // Borrar duplicados de un recorrido donde todos son iguales.

    printf("INIT DUPLICATES2\n");
    struct airTrip* trip6 = airTripNew("A123");
    airTripAddLast(trip6, "C1", 1.0, 1.0);
    airTripAddLast(trip6, "C1", 1.0, 1.0);
    // Ahora todas las paradas de trip6 son iguales, como nos pide la consigna
    airTripRemoveDuplicates(trip6);
    airTripPrint(trip6);
    printf("FIN DUPLICATES2\n");
    airTripDelete(trip6);

    // Borrar duplicados de un recorrido donde todos se repiten al menos una vez en cualquier orden.
    printf("INIT DUPLICATES3\n");
    struct airTrip* trip7 = airTripNew("A123");
    
    airTripAddLast(trip7, "C1", 1.0, 1.0);
    airTripAddLast(trip7, "C2", 2.0, 2.0);
    airTripAddLast(trip7, "C1", 1.0, 1.0);
    airTripAddBest(trip7, "C2", 2.0, 2.0);
    airTripAddBest(trip7, "C3", 3.0, 3.0);
    airTripAddBest(trip7, "C3", 3.0, 3.0);
    
    airTripPrint(trip7);
    
    airTripRemoveDuplicates(trip7);
    airTripPrint(trip7);
    airTripDelete(trip7);
    printf("FIN DUPLICATES3\n");

// Get trip
    printf("INIT GETTRIP\n");
    // Creo el trip que vamos a usar para testear
    struct airTrip* trip8 = airTripNew("D234");

    // Usar de paŕametro un recorrido vacio (uso el que acabamos de crear)
    char* t = airTripGetTrip(trip8);
    printf("RESULTADO GETTRIP: %s\n",t);
    //free(t);
    airTripDelete(trip8);
    printf("FIN GETTRIP\n");



    printf("INIT GETTRIP2\n");
    struct airTrip* trip9 = airTripNew("D234");
    // Usar de parametro un recorrido de una sola parada
    airTripAddLast(trip9, "D1", 1.0, 1.0);
    char* x = airTripGetTrip(trip9);
    printf("RESULTADO GETTRIP2: %s\n",x);

    airTripDelete(trip9);
    printf("FIN GETTRIP2\n");



    printf("INIT GETTRIP3\n");
    struct airTrip* trip10 = airTripNew("D234");
    // Usar de parametro un recorrido de solo dos paradas
    airTripAddLast(trip10, "D2", 2.0, 2.0);
    char* r = airTripGetTrip(trip10);
    printf("RESULTADO GETTRIP3: %s\n",r);
    //free(r);
    airTripDelete(trip10);
    printf("FIN GETTRIP3\n");

    // airTripDelete


    printf("INIT DELTRIP\n");
    //  Borrar un recorrido de mas de dos paradas.
    struct airTrip* trip11 = airTripNew("D234");
    airTripAddLast(trip11, "D3", 3.0, 3.0);
    airTripAddLast(trip11, "D4", 2.0, 3.5);
    airTripAddLast(trip11, "D5", 1.0, 1.0);
    airTripPrint(trip11);
    airTripDelete(trip11);
    printf("FIN DELTRIP\n");


    printf("INIT DELTRIP2\n");
    // Borrar un recorrido de solo una parada.
    struct airTrip* trip12 = airTripNew("D234");
    airTripAddLast(trip12, "D", 1.0, 1.0);
    airTripDelete(trip12);
    printf("FIN DELTRIP2\n");

    printf("INIT DELTRIP3\n");
    // Borrar un recorrido vacio.
    struct airTrip* trip13 = airTripNew("D234");
    airTripDelete(trip13);
    printf("FIN DELTRIP3\n");

    return 0;
}

