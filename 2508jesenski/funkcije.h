#pragma once

#include "podatci.h"

extern int brojBMW;

void kreirajDatoteku(const char* imeDatoteke);
int izlazIzPrograma(BMW* nizPodataka);
int izbornik(const char* const);
void unosBMW(const char* const imeDatoteke, const BMW* nizPodataka);
BMW* ispisBMW(const char* const imeDatoteke);
void urediBMW(const BMW* nizPodataka, const char* const imeDatoteke);
void obrisiBMW(const char* const imeDatoteke);
void sortirajBMWpoCijeniPadajuce(BMW* nizPodataka, int brojBMW);
int getBrojBMW(const char* const imeDatoteke);
void sortirajBMWpoCijeniRastuce(BMW* nizPodataka, int brojBMW);
int usporedbaSilazno(const void* a, const void* b);
int usporedbaUzlazno(const void* a, const void* b);
void sortirajBMWpoSnaziOpadajuce(BMW* nizPodataka, int brojBMW);
int snagaSilazno(const void* a, const void* b);
void sortirajBMWpoSnaziRastuce(BMW* nizPodataka, int brojBMW);
void obrisiDatoteku(const char* imeDatoteke);
void preimenujDatoteku(const char* staroIme, const char* novoIme);
int snagaUzlazno(const void* a, const void* b);