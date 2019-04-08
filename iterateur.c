#include "iterateur.h"

#include <stdlib.h>



iterateur* iterateur_nouveau(
    void* conteneur, void (*suivant)(void*), void (*precedent)(void*),
    S (*valeur)(const void*), bool (*egal)(const void*, const void*))
{
  iterateur* const it = malloc(sizeof *it);
  if (!it)
    return it;
    else{
    it->conteneur=conteneur;
    it->suivant=suivant;
    it->precedent=precedent;
    it->valeur=valeur;
    it->egal=egal;
  return it;
    }
}

iterateur* iterateur_suivant(iterateur* it)
{
  it->suivant(it->conteneur);
  return it;
}

iterateur* iterateur_precedent(iterateur* it)
{
  it->precedent(it->conteneur);
  return it;
}

bool iterateur_egal(const iterateur* a, const iterateur* b)
{
  return a->egal(a->conteneur, b->conteneur);
}

S iterateur_valeur(const iterateur* it)
{
  return it->valeur(it->conteneur);
  return (S) { 0 };
}

void iterateur_free(iterateur* it)
{
  if (!it)
    return;

  if (it->conteneur)
    free(it->conteneur);
  free(it);
}
