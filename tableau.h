#ifndef _TABLEAU_H_
#define _TABLEAU_H_

#include <stddef.h>
#include "sorte.h"
#include "iterateur.h"

typedef struct tableau tableau;

tableau* tableau_vide(void);
void tableau_free(tableau* t);

tableau* tableau_insertion_debut(tableau* t, S x);
tableau* tableau_insertion_fin(tableau* t, S x);
tableau* tableau_modification(tableau* t, size_t position, S x);

size_t tableau_longueur(const tableau* t);
size_t tableau_taille_maximale(const tableau* t);
const S* tableau_elements(const tableau* t);
S tableau_element(const tableau* t, size_t position);

iterateur* tableau_iterateur_debut(const tableau* t);
iterateur* tableau_iterateur_fin(const tableau* t);

#endif
