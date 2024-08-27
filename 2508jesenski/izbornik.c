#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "podatci.h"
#include "funkcije.h"
#define LOGIN 20

static bool adminLogin() {
    char password[LOGIN];

    printf("Admin Login\n");
    printf("Password: ");
    scanf("%19s", password);            // trazi verifikaciju korisnika pomocu lozinke 

    if (strcmp(password, "admin123") == 0) {
        printf("Uspjesno logiranje\n");
        return true;
    }
    else {
        printf("Kriva lozinka\n");
        return false;
    }
}


int izbornik(const char* imeDatoteke) {
    static BMW* nizPodataka = NULL;
    static BMW* pModel = NULL;
    int izbor;

    nizPodataka = ispisBMW(imeDatoteke);
    if (nizPodataka == NULL) {
        printf("Error: Unable to read BMW data from file.\n");
        return -1;
    }

    brojBMW = getBrojBMW(imeDatoteke);
    if (brojBMW < 0) {
        printf("Error: Invalid number of BMWs.\n");      // dohvacanje trenutno pohranjenih vozila
        return -1;
    }

    while (1) {
        system("cls");
        printf("\t\t\t\t\t \033[0;34m ____  __  ____        __\n");
        printf("\t\t\t\t\t\033[0;34m| __ )|  \\/  \\ \\      / /\n");
        printf("\t\t\t\t\t\033[0;34m|  _ \\| |\\/| |\\ \\ /\\ / / \n");
        printf("\t\t\t\t\t\033[0;34m| |_) | |  | | \\ V  V /  \n");
        printf("\t\t\t\t\t\033[0;34m|____/|_|  |_|  \\_/\\_/   \n");
        printf("\033[0m");  // vracanje na klasicnu boju
        printf("\n\n\t\t\t\t\tIzbornik:\n");
        printf("\t\t\t\t\t1. Dodaj novi BMW(ADMIN)\n");
        printf("\t\t\t\t\t2. Ispisi sve BMW automobile\n");
        printf("\t\t\t\t\t3. Uredi BMW(ADMIN)\n");
        printf("\t\t\t\t\t4. Obrisi BMW(ADMIN)\n");
        printf("\t\t\t\t\t5. Sortiraj BMW-ove po cijeni (od najvise do najnize)\n");
        printf("\t\t\t\t\t6. Sortiraj BMW-ove po cijeni (od najnize do najvise)\n");
        printf("\t\t\t\t\t7. Sortiraj BMW-ove po snazi (uzlazno)\n");
        printf("\t\t\t\t\t8. Sortiraj BMW-ove po snazi (silazno)\n");
        printf("\t\t\t\t\t9. Obrisi datoteku (ADMIN)\n");
        printf("\t\t\t\t\t10. Preimenuj datoteku (ADMIN)\n");
        printf("\t\t\t\t\t11. Izadji iz programa\n");
        printf("\t\t\t\t\tOdabir: ");

        if (scanf("%d", &izbor) != 1) {     // petlja provjerava da je korisnicki unos tipa int
            printf("Krivi odabir!\n");
            while (getchar() != '\n');
            continue;                       // continue nas vraca na pocetak unosa izbora za izbornik
        }

        IzbornikOpcija opcija = (IzbornikOpcija)izbor;      // castovanje izbora u enum IzbornikOpcija
        switch (opcija) {
        case DODAJ_BMW:
            if (nizPodataka != NULL && adminLogin()) {
                unosBMW(imeDatoteke, nizPodataka);
                free(nizPodataka);
                nizPodataka = ispisBMW(imeDatoteke);
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano.\n");
            }
            break;

        case ISPISI_BMW:
            if (nizPodataka != NULL && brojBMW > 0) {
                ispisBMW(imeDatoteke);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case UREDI_BMW:
            if (nizPodataka != NULL && brojBMW > 0 && adminLogin()) {
                urediBMW((BMW*)nizPodataka, imeDatoteke);
                free(nizPodataka);
                nizPodataka = ispisBMW(imeDatoteke);  // Re-read the updated data after editing a car.
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case OBRISI_BMW:
            if (nizPodataka != NULL && brojBMW > 0 && adminLogin()) {
                obrisiBMW(imeDatoteke);
                free(nizPodataka);
                nizPodataka = ispisBMW(imeDatoteke);  // Re-read the updated data after editing a car.
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;
        case SORTIRAJ_CIJENA_PADAJUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoCijeniPadajuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_CIJENA_RASTUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoCijeniRastuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_SNAZI_RASTUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoSnaziRastuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_SNAZI_OPADAJUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoSnaziOpadajuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;
        case OBRISI_DATOTEKU:
            obrisiDatoteku(imeDatoteke);
            break;

        case PREIMENUJ_DATOTEKU:
            if (adminLogin()) {
                char novoIme[FILLEN];
                printf("Unesite novo ime za datoteku: ");
                scanf("%s", novoIme);
                preimenujDatoteku(imeDatoteke, novoIme);
            }
            break;

        case IZADJI:
            if (izlazIzPrograma(nizPodataka) == 0) {
                return 0;
            }
            break;

        default:
            printf("Nepostojeci izbor.\n");
            break;
        }

        system("pause");
    }

    free(nizPodataka);                  //oslobadjanje memorije i vracanje pokazivaca na NULL vrijednost
    nizPodataka = NULL;

    return izbor;
}
