#include "tableau.h"
#include <stdlib.h>
#include <string.h>

struct tableau
{
  S* elements;
  size_t longueur;
  size_t taille_max;
};

static const size_t TABLEAU_SEUIL = 128;

tableau* tableau_vide(void)
{
  tableau* t = malloc(sizeof *t);
  if (!t)
    return t;

  t->elements = malloc(sizeof *t->elements * TABLEAU_SEUIL);
  if (!t->elements)
  {
    free(t);
    return NULL;
  }

  t->taille_max = TABLEAU_SEUIL;
  t->longueur = 0;

  return t;
}

void tableau_free(tableau* t)
{
  if (!t)
    return;
  free(t->elements);
  free(t);
}

static inline tableau* tableau_agrandir(tableau* t, size_t taille)
{
  const size_t nouvealle_taille = sizeof *t->elements * taille;
  S* elements = realloc(t->elements, nouvealle_taille);
  if (elements)
  {
    t->elements = elements;
    t->taille_max = nouvealle_taille;
  }
  return t;
}

tableau* tableau_insertion_debut(tableau* t, S x)
{
  if (t->longueur >= t->taille_max)
    t = tableau_agrandir(t, t->taille_max + TABLEAU_SEUIL);

  memmove(t->elements + 1, t->elements, sizeof *t->elements * t->longueur);
  if (t->longueur < t->taille_max)
  {
    t->elements[0] = x;
    t->longueur++;
  }

  return t;
}

tableau* tableau_insertion_fin(tableau* t, S x)
{
  if (t->longueur >= t->taille_max)
    t = tableau_agrandir(t, t->taille_max + TABLEAU_SEUIL);
  if (t->longueur < t->taille_max)
    t->elements[t->longueur++] = x;

  return t;
}

tableau* tableau_modification(tableau* t, size_t position, S x)
{
  t->elements[position] = x;
  return t;
}

size_t tableau_longueur(const tableau* t)
{
  return t->longueur;
}

size_t tableau_taille_maximale(const tableau* t)
{
  return t->taille_max;
}

const S* tableau_elements(const tableau* t)
{
  return t->elements;
}

S tableau_element(const tableau* t, size_t position)
{
  return t->elements[position];
}

////////////////////////////////////////////////////////////////////////////////
// Itérateur
////////////////////////////////////////////////////////////////////////////////

typedef struct iterateur_tableau
{
  const tableau* t;
  size_t position;
} iterateur_tableau;

static void iterateur_tableau_suivant(void* infos)
{
  iterateur_tableau* const it = infos;
 it->position=it->position+1;
 
}

static void iterateur_tableau_precedent(void* infos)
{
  /* (Peut-être) À modifier ou compléter. */
  iterateur_tableau* const it = infos;
  it->position=it->position-1;
}

static S iterateur_tableau_valeur(const void * infos)
{
  const iterateur_tableau* const it = infos;
  return tableau_element(it->t,it->position);
  return (S) { 0 };
}

static bool iterateur_tableau_egal(const void* a, const void* b)
{
  const iterateur_tableau* const ita = a;
  const iterateur_tableau* const itb = b;
  return (ita->position==itb->position);
}

iterateur* tableau_iterateur_debut(const tableau* t)
{
  iterateur_tableau* const infos = malloc(sizeof *infos);
  infos->t=t;
  infos->position=0;
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_tableau_suivant, iterateur_tableau_precedent,
      iterateur_tableau_valeur, iterateur_tableau_egal);
  
  return it;
}

iterateur* tableau_iterateur_fin(const tableau* t)
{
  iterateur_tableau* const infos = malloc(sizeof *infos);
  infos->t=t;
  infos->position=tableau_longueur(t)-1;
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_tableau_suivant, iterateur_tableau_precedent,
      iterateur_tableau_valeur, iterateur_tableau_egal);
  
  return it;
}
