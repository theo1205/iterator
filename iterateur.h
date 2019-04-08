#ifndef _ITERATEUR_H_
#define _ITERATEUR_H_

#include <stdbool.h>

#include "sorte.h"
struct iterateur
{
  void* conteneur;
  void (*suivant)(void*);
  void (*precedent)(void*);
  S (*valeur)(const void*);
  bool (*egal)(const void*, const void*);
};

typedef struct iterateur iterateur;

iterateur* iterateur_nouveau(
    void* conteneur, void (*suivant)(void*), void (*precedent)(void*),
    S (*valeur)(const void*), bool (*egal)(const void*, const void*));

iterateur* iterateur_suivant(iterateur* i);
iterateur* iterateur_precedent(iterateur* i);
bool iterateur_egal(const iterateur* a, const iterateur* b);
S iterateur_valeur(const iterateur* it);
void iterateur_free(iterateur* i);

#endif
