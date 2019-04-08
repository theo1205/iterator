#ifndef _LISTE_H_
#define _LISTE_H_

#include <stddef.h>
#include <stdbool.h>

#include "sorte.h"
#include "iterateur.h"

typedef struct liste liste;

liste* liste_vide(void);
void liste_free(liste* l);
liste* liste_insertion(liste* l, S x);
liste* liste_insertion_tete(liste* l, S x);
liste* liste_insertion_queue(liste* l, S x);
liste* liste_suppression_tete(liste* l);
liste* liste_suppression_queue(liste* l);

liste* liste_fin(const liste* l);
liste* liste_debut(const liste* l);
liste* liste_suivant(const liste* l);
liste* liste_precedent(const liste* l);
liste* liste_ieme(const liste* l, size_t i);

S liste_element(const liste* l);
bool liste_est_vide(const liste* l);
size_t liste_longueur(const liste* l);

iterateur* liste_iterateur_debut(const liste* l);
iterateur* liste_iterateur_fin(const liste* l);

#endif
