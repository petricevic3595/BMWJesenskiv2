#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funkcije.h"
#include "podatci.h"

#define PROVJERA 3  

int brojBMW = 0;

void kreirajDatoteku(const char* imeDatoteke) {
    FILE* datoteka = fopen(imeDatoteke, "rb+");
    if (datoteka == NULL) {
        printf("Datoteka %s ne postoji. Kreiranje datoteke...\n", imeDatoteke);
        datoteka = fopen(imeDatoteke, "wb");
        if (datoteka == NULL) {
            perror("Greska prilikom kreiranja datoteke");           //zastita prilikom otvaranja datoteke
            exit(EXIT_FAILURE);
        }
        int tmp = 0;                                        // deklariranje pomocne varijable za pocetak brojanja
        fwrite(&tmp, sizeof(int), 1, datoteka);             // postavljanje broja bmwova na nulu 
        fclose(datoteka);
        printf("Datoteka %s uspjesno kreirana!\n\n", imeDatoteke);
    }
    else {
        printf("Datoteka %s vec postoji!\n\n", imeDatoteke);
        fclose(datoteka);
    }
}

int getBrojBMW(const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb");
    if (pF == NULL) {
        perror("Error opening file");
        return -1;
    }

    int numBMW;
    fread(&numBMW, sizeof(int), 1, pF);     // provjerava koliko bmw vozila ima zapisanih u datoteci
    fclose(pF);

    return numBMW;
}

void unosBMW(const char* const fileName, const BMW* nizPodataka) {
    printf("Dodavanje BMW:\n\n");
    bool validInput = false;

    FILE* pF = fopen(fileName, "rb+");

    if (pF == NULL) {
        perror("Dodavanje BMWa u BMW.bin");
        exit(EXIT_FAILURE);
    }
    printf("Broj dodanih BMW-ova: %d\n\n", brojBMW);

    BMW temp;               // inicijalizacija privremene varijable za unos BMW vozila
    temp.id = brojBMW;      // privremeni id uzima brojBMW koji se nakon svakog unosa uvecava
    printf("Unesite model (do 30 znakova):\n");
    char model[MODLEN];
    scanf(" %30[^\n]", model);
    if (strlen(model) <= MODLEN) {          // ako model ima vise znakova od dopustenog unos ce se ponovit
        strcpy(temp.model, model);
        printf("Model unesen: %s\n", temp.model);
    }
    else {
        printf("Previše znakova. Unos odbijen.\n");
        while (getchar() != '\n');
    }

    getchar();
    while (!validInput) {           // petlja se izvrsava dok unos ne bude ispravan
        printf("Cijena:\n ");
        if (scanf("%f", &temp.cijena) == 1) {
            validInput = true;          // ako je unos ispravan varijable se mijenja na true i zavrsava petlja
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;         // ponovno postavljanje varijable na false kako bi iznova mogli provjeriti uvjet
    while (!validInput) {
        printf("Potrosnja (litara na 100km):\n ");
        if (scanf("%f", &temp.potrosnja) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Ubrzanje u sec(0-100km/h):\n ");
        if (scanf("%f", &temp.ubrzanje) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Snaga(HP):\n ");
        if (scanf("%d", &temp.snaga) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Godina proizvodnje:\n");
        if (scanf("%d", &temp.godinaProizvodnje) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Kilometraza:\n");
        if (scanf("%d", &temp.kilometraza) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    fread(&brojBMW, sizeof(int), 1, pF);           // citanje broja zapisanih bmw vozila u datoteci 
    fseek(pF, sizeof(BMW) * brojBMW, SEEK_CUR);     // pomicanje pokazivaca na kraj datoteke    
    fwrite(&temp, sizeof(BMW), 1, pF);              // zapis o novom bmw vozilu
    rewind(pF);                                     // vracanje pokazivaca na pocetak
    brojBMW++;
    fwrite(&brojBMW, sizeof(int), 1, pF);              // zapisuje novi broj bmw vozila nakon sto je varijabla uvecana
    fclose(pF);
    printf("\n");
    printf("BMW uspjesno dodan!\n\n");
}

BMW* ispisBMW(const char* const imeDatoteke) {
    printf("Ucitavanje podataka...\n\n");
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Ucitavanje podataka iz datoteke");          // zastita parametara
        return NULL;
    }

    fread(&brojBMW, sizeof(int), 1, pF);        // citanje koliko ima pohranjenih bmw vozila
    printf("Broj BMW automobila: %d\n\n", brojBMW);
    BMW* nizBMW = (BMW*)calloc(brojBMW, sizeof(BMW));       // alociranje memorije za kasniji ispis pohranjenih vozila
    if (nizBMW == NULL) {
        perror("Alokacija memorije za BMW automobile");
        return NULL;
    }

    fread(nizBMW, sizeof(BMW), brojBMW, pF);    // citanje podataka o bmw vozilima i pohrana u nizBMW
    if (nizBMW == NULL) {
        printf("Polje BMW automobila je prazno!\n");
        return NULL;
    }

    int i;
    for (i = 0; i < brojBMW; i++) {     // ispis svih pohranjenih vozila
        printf("BMW automobil %d:\n", i + 1);
        printf("ID: %d\n", nizBMW[i].id);
        printf("Model: %s\n", nizBMW[i].model);
        printf("Cijena: %.2f $\n", nizBMW[i].cijena);
        printf("Potrosnja: %.2f l/100km\n", nizBMW[i].potrosnja);
        printf("Ubrzanje: %.2f s\n", nizBMW[i].ubrzanje);
        printf("Snaga: %d hp\n", nizBMW[i].snaga);
        printf("Godina proizvodnje: %d\n", nizBMW[i].godinaProizvodnje);
        printf("Kilometraza: %d km\n\n", nizBMW[i].kilometraza);
    }

    printf("Uspjesno ucitano!\n");
    fclose(pF);

    return nizBMW;
}
void cistacZnakova() {
    while (getchar() != '\n');
}
void urediBMW(BMW* nizPodataka, const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Otvaranje datoteke nije uspjelo");
        exit(EXIT_FAILURE);
    }

    int brojBMW;
    fread(&brojBMW, sizeof(int), 1, pF);
    if (brojBMW == 0) {
        printf("Nema unesenih vozila, ne mozete koristiti funkciju azuriranja vozila.\n");
        fclose(pF);
        return;
    }

    BMW* temp = (BMW*)calloc(brojBMW, sizeof(BMW));
    if (!temp) {
        perror("Memorijska greska prilikom alokacije");
        fclose(pF);
        exit(EXIT_FAILURE);
    }

    fread(temp, sizeof(BMW), brojBMW, pF);

    printf("\nNa stanju su vozila s ovim ID-evima: ");
    for (int i = 0; i < brojBMW; i++) {
        printf("%d", temp[i].id);
        if (i != (brojBMW - 1)) {
            printf(", ");
        }
    }

    int id, index = -1;
    do {
        printf("\nUnesite ID BMW-a koji zelite urediti: ");
        if (scanf("%d", &id) != 1) {
            printf("Neispravan unos. Molimo unesite broj.\n");
            cistacZnakova();
            continue;
        }

        for (int i = 0; i < brojBMW; i++) {
            if (temp[i].id == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("Nepostojeci ID, ponovite unos.\n");
        }
    } while (index == -1);


    char provjera;
    printf("Jeste li sigurni?\nAko jeste, unesite Y, a ako niste, unesite n: ");
    do {
        scanf(" %c", &provjera);
        if (provjera != 'Y' && provjera != 'n') {
            printf("Krivi unos, unesite Y za da ili unesite n za ne: ");
        }
    } while (provjera != 'Y' && provjera != 'n');

    if (provjera == 'Y') {
        printf("\nUkoliko ne zelite naciniti promjene u odredenom kriteriju vozila, unesite vrijednost 0.\n");

        printf("\nUnesite novi model vozila (do 30 znakova, moze sadrzavati razmake): ");
        char model[MODLEN];
        scanf(" %30[^\n]", model);
        cistacZnakova();
        if (strcmp(model, "0") != 0) {
            strncpy(temp[index].model, model, MODLEN - 1);  // izbjegavamo overflow
            temp[index].model[MODLEN - 1] = '\0';  
        }

        // ponavlja se sve odozgor za ostala polja
        printf("Unesite novu cijenu vozila: ");
        float cijena;
        if (scanf("%f", &cijena) == 1 && cijena != 0) {
            temp[index].cijena = cijena;
        }

        printf("Unesite novu potrosnju (litara na 100km): ");
        float potrosnja;
        if (scanf("%f", &potrosnja) == 1 && potrosnja != 0) {
            temp[index].potrosnja = potrosnja;
        }

        printf("Unesite novo ubrzanje (0-100km/h): ");
        float ubrzanje;
        if (scanf("%f", &ubrzanje) == 1 && ubrzanje != 0) {
            temp[index].ubrzanje = ubrzanje;
        }

        printf("Unesite novu snagu motora (HP): ");
        int snaga;
        if (scanf("%d", &snaga) == 1 && snaga != 0) {
            temp[index].snaga = snaga;
        }

        printf("Unesite novu godinu proizvodnje: ");
        int godinaProizvodnje;
        if (scanf("%d", &godinaProizvodnje) == 1 && godinaProizvodnje >= 1920 && godinaProizvodnje <= 2025) {
            temp[index].godinaProizvodnje = godinaProizvodnje;
        }

        printf("Unesite novu kilometrazu: ");
        int kilometraza;
        if (scanf("%d", &kilometraza) == 1 && kilometraza != 0) {
            temp[index].kilometraza = kilometraza;
        }

        fseek(pF, sizeof(int) + sizeof(BMW) * index, SEEK_SET);
        fwrite(&temp[index], sizeof(BMW), 1, pF);

        printf("BMW s ID-om %d uspjesno uredjen!\n", id);
    }
    else {
        printf("Azuriranje otkazano.\n");
    }

    free(temp);
    if (fclose(pF) != 0) {
        perror("Greska pri zatvaranju datoteke");
        exit(EXIT_FAILURE);
    }
    return;
}

void obrisiBMW(const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Brisanje BMW-a iz BMW.bin");
        exit(EXIT_FAILURE);
    }

    fseek(pF, sizeof(int), SEEK_SET);   // postavljanje pokazivaca na pocetak

    int obrisiBMW;
    printf("Unesite ID BMW-a koji zelite obrisati: ");
    if (scanf("%d", &obrisiBMW) != 1) {         // unos ID-a za brisanje uz zastitu parametara
        printf("Neispravan unos ID-a BMW-a.\n");
        fclose(pF);
        return;
    }


    int pronadeniIndex = -1;
    BMW temp;       // sluzi nam za pretrazivanje datoteke 
    while (fread(&temp, sizeof(BMW), 1, pF) == 1) {
        if (temp.id == obrisiBMW) {
            pronadeniIndex = ftell(pF) / sizeof(BMW) - 1; // postavljanje indeksa na poziciju gdje se nalazi bmw koji zelimo obrisat
            break;
        }
    }

    if (pronadeniIndex == -1) {
        printf("BMW s ID-om %d nije pronaden!\n", obrisiBMW);
        fclose(pF);
        return;
    }
    char potvrda[PROVJERA];
    printf("Jeste li sigurni da zelite izbrisati BMW s ID-om %d? (da/ne): ", obrisiBMW);
    if (scanf("%2s", potvrda) != 1) {       // provjera korisnikovog unosa zeli li obrisati navedeni bmw
        printf("Neispravan unos. Brisanje prekinuto.\n");
        fclose(pF);
        return;
    }
    if (strcmp(potvrda, "da") != 0) {
        printf("Brisanje prekinuto.\n");
        fclose(pF);
        return;
    }

    fseek(pF, -(long)sizeof(BMW), SEEK_END);    // postavlja pokazivac na kraj datoteke 


    BMW lastBMW;    // pravi se nova privremena struktura
    fread(&lastBMW, sizeof(BMW), 1, pF);    // procitaju se sva vozila osim ovog obrisanog


    fseek(pF, sizeof(int) + pronadeniIndex * sizeof(BMW), SEEK_SET);    // trazi indeks vozila kojeg brisemo   
    fwrite(&lastBMW, sizeof(BMW), 1, pF);       // zapisuje sva vozila osim obrisanog


    fseek(pF, 0, SEEK_SET);     // postavljanje pokazivaca na pocetak
    int brojBMW; // privremena varijabla za novi brojac
    fread(&brojBMW, sizeof(int), 1, pF);    // procita trenutni broj vozila
    brojBMW--;
    fseek(pF, 0, SEEK_SET); // vracanje pokazivaca na pocetak
    fwrite(&brojBMW, sizeof(int), 1, pF);   // upisuje broj vozila umanjen za jedan

    fclose(pF);
    printf("BMW s ID-om %d uspjesno obrisan!\n", obrisiBMW);
}

int usporedbaSilazno(const void* a, const void* b) {
    const BMW* BMWa = (const BMW*)a;
    const BMW* BMWb = (const BMW*)b;
    if (BMWa->cijena < BMWb->cijena) return 1;
    if (BMWa->cijena > BMWb->cijena) return -1;
    return 0;
}

void sortirajBMWpoCijeniPadajuce(BMW* nizPodataka, int brojBMW) {

    qsort(nizPodataka, brojBMW, sizeof(BMW), usporedbaSilazno);     //rekurzija pozivanjem druge funkcije u qsort


    printf("Sortirani BMW automobili po cijeni (od najvise do najnize):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int usporedbaUzlazno(const void* a, const void* b) {
    const BMW* bmw1 = (const BMW*)a;
    const BMW* bmw2 = (const BMW*)b;
    if (bmw1->cijena < bmw2->cijena) return -1;
    if (bmw1->cijena > bmw2->cijena) return 1;
    return 0;
}

void sortirajBMWpoCijeniRastuce(BMW* nizPodataka, int brojBMW) {

    qsort(nizPodataka, brojBMW, sizeof(BMW), usporedbaUzlazno);     // rekurzija pozivanjem druge funkcije u qsort


    printf("BMW sortirannje od najnize do najvise cijene:\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobile %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Price: %.2f\n", nizPodataka[i].cijena);
        printf("Consumption: %.2f\n", nizPodataka[i].potrosnja);
        printf("Acceleration: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Power: %d\n", nizPodataka[i].snaga);
        printf("Year of production: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Mileage: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int snagaUzlazno(const void* a, const void* b) {
    const BMW* bmw1 = (const BMW*)a;
    const BMW* bmw2 = (const BMW*)b;
    if (bmw1->snaga < bmw2->snaga) return -1;
    if (bmw1->snaga > bmw2->snaga) return 1;
    return 0;
}

void sortirajBMWpoSnaziRastuce(BMW* nizPodataka, int brojBMW) {

    qsort(nizPodataka, brojBMW, sizeof(BMW), snagaUzlazno);


    printf("BMW automobili sortirani po snazi (Uzlazno):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int snagaSilazno(const void* a, const void* b) {
    return snagaUzlazno(b, a);
}

void sortirajBMWpoSnaziOpadajuce(BMW* nizPodataka, int brojBMW) {
    qsort(nizPodataka, brojBMW, sizeof(BMW), snagaSilazno);


    printf("BMW automobili sortirani po snazi (silazno):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}
void obrisiDatoteku(const char* imeDatoteke) {
    int status = 0;
   
    status = remove(imeDatoteke);
    if (status == 0) {
        printf("Uspjesno obrisana datoteka!\n");
    }
    else {
        printf("Nemogucnost brisanja datoteke!\n");
    }


}

void preimenujDatoteku(const char* staroIme, const char* novoIme) {
    int status = 0;
    status = rename(staroIme, novoIme);
    if (status == 0) {
        printf("Datoteka %s je uspjesno preimenovana u %s!\n", staroIme, novoIme);
    }
    else {
        perror("Greska prilikom preimenovanja datoteke");
    }
}
int izlazIzPrograma(BMW* nizPodataka) {
    getchar();
    char potvrda[PROVJERA];
    while (1) {
        printf("Zaista zelite izaci iz programa?\n");
        printf("Upisite \"da\" ako zaista zelite izaci, inace upisite \"ne\"!\n");

        if (fgets(potvrda, sizeof(potvrda), stdin)) {

            size_t len = strlen(potvrda);
            if (len > 0 && potvrda[len - 1] == '\n') {      // ako je nesto uneseno u len i potvrdjen unos s enterom
                potvrda[len - 1] = '\0';
            }

            if (strcmp("da", potvrda) == 0) {       // usporedba sa da
                free(nizPodataka);
                nizPodataka = NULL;
                return 0;
            }
            else if (strcmp("ne", potvrda) == 0) {      // usporedba sa ne
                return 1;
            }
            else {
                printf("Neispravan unos. Molimo upisite \"da\" ili \"ne\".\n");
            }
        }
        else {

            while (getchar() != '\n');
            printf("Neispravan unos. Molimo upisite \"da\" ili \"ne\".\n");
        }
    }
}


