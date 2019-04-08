#include "liste.h"
#include <stdlib.h>

struct liste
{
  S element;
  struct liste* suivant;
  struct liste* precedent;
};

liste* liste_vide(void)
{
  return NULL;
}

void liste_free(liste* const l)
{
  liste* parcours = l;
  while (parcours)
  {
    liste* next = parcours->suivant;
    free(parcours);
    parcours = next;
  }
}

liste* liste_insertion(liste* l, S x)
{
  liste* const nouveau_maillon = malloc(sizeof *nouveau_maillon);

  nouveau_maillon->element = x;
  nouveau_maillon->suivant = l;
  nouveau_maillon->precedent = l ? l->precedent : NULL;
  if (l)
  {
    if (l->precedent)
      l->precedent->suivant = nouveau_maillon;
    l->precedent = l;
  }

  return nouveau_maillon;
}

liste* liste_insertion_tete(liste* l, S x)
{
  liste* const nouveau_maillon = malloc(sizeof *nouveau_maillon);

  nouveau_maillon->element = x;

  liste* const debut = liste_debut(l);
  nouveau_maillon->precedent = NULL;
  nouveau_maillon->suivant = debut;
  if (debut)
    debut->precedent = nouveau_maillon;

  return nouveau_maillon;
}

liste* liste_insertion_queue(liste* l, S x)
{
  liste* const nouveau_maillon = malloc(sizeof *nouveau_maillon);

  nouveau_maillon->element = x;

  liste* const fin = liste_fin(l);
  nouveau_maillon->precedent = fin;
  nouveau_maillon->suivant = NULL;
  if (fin)
    fin->suivant = nouveau_maillon;

  return nouveau_maillon;
}

liste* liste_suppression_tete(liste* l)
{
  if (!l)
    return NULL;

  liste* const debut = liste_debut(l);
  liste* const retour = debut->suivant;

  free(debut);
  if (retour)
    retour->precedent = NULL;

  return retour;
}

liste* liste_suppression_queue(liste* l)
{
  if (!l)
    return NULL;

  liste* const fin = liste_fin(l);
  liste* const retour = fin->precedent;

  free(fin);
  if (retour)
    retour->suivant = NULL;

  return retour;
}

liste* liste_fin(const liste* const l)
{
  if (!l)
    return NULL;

  const liste* parcours = l;
  while (parcours->suivant)
    parcours = parcours->suivant;

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) parcours;
  #pragma GCC diagnostic pop
}

liste* liste_debut(const liste* l)
{
  if (!l)
    return NULL;

  const liste* parcours = l;
  while (parcours->precedent)
    parcours = parcours->precedent;

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) parcours;
  #pragma GCC diagnostic pop
}

liste* liste_suivant(const liste* l)
{
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) (l ? l->suivant : l);
  #pragma GCC diagnostic pop
}

liste* liste_precedent(const liste* l)
{
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) (l ? l->precedent : l);
  #pragma GCC diagnostic pop
}

liste* liste_ieme(const liste* l, size_t n)
{
  liste* parcours = liste_debut(l);
  for (size_t i = 0; parcours && i < n; ++i)
    parcours = parcours->suivant;
  return parcours;
}

S liste_element(const liste* l)
{
  return l->element;
}

bool liste_est_vide(const liste* l)
{
  return l ? false : true;
}

size_t liste_longueur(const liste* l)
{
  size_t longueur = 0;
  for (const liste* parcours = l; parcours; parcours = parcours->suivant)
    longueur++;

  return longueur;
}

////////////////////////////////////////////////////////////////////////////////
// Itérateur
////////////////////////////////////////////////////////////////////////////////

static void iterateur_liste_suivant(void* infos)
{
  liste** l = infos;
  *l= liste_suivant(*l);
}

static void iterateur_liste_precedent(void* infos)
{
  liste** l = infos;
  *l=(liste_precedent(*l));
}

static S iterateur_liste_valeur(const void * infos)
{
  const liste* const* l = infos;
  return liste_element(*l);
}

static bool iterateur_liste_egal(const void* a, const void* b)
{
  const iterateur* ia=a;
  const iterateur* ib=b;
  return ia->conteneur==ib->conteneur;
}

iterateur* liste_iterateur_debut(const liste* l)
{
  const liste** const infos = malloc(sizeof *infos);
  *infos=liste_debut(l);
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_liste_suivant, iterateur_liste_precedent,
      iterateur_liste_valeur, iterateur_liste_egal);
  return it;
}

iterateur* liste_iterateur_fin(const liste* l)
{
  const liste** const infos = malloc(sizeof *infos);
  *infos=liste_fin(l);
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_liste_suivant, iterateur_liste_precedent,
      iterateur_liste_valeur, iterateur_liste_egal);
  return it;
}
