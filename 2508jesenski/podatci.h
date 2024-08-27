#pragma once

#define MODLEN 50
#define FILLEN 14


typedef struct {
    char model[MODLEN];
    float cijena;
    float potrosnja;
    float ubrzanje;
    int id;
    int snaga;
    int godinaProizvodnje;
    int kilometraza;
} BMW;

typedef enum {
    DODAJ_BMW = 1,
    ISPISI_BMW,
    UREDI_BMW,
    OBRISI_BMW,
    SORTIRAJ_CIJENA_PADAJUCE,
    SORTIRAJ_CIJENA_RASTUCE,
    SORTIRAJ_SNAZI_RASTUCE,
    SORTIRAJ_SNAZI_OPADAJUCE,
    OBRISI_DATOTEKU,
    PREIMENUJ_DATOTEKU,
    IZADJI
} IzbornikOpcija;