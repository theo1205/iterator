
#ifndef _ENSEMBLE_H_
#define _ENSEMBLE_H_

#include <stddef.h>
#include <stdbool.h>

#include "sorte.h"
#include "iterateur.h"

typedef struct ensemble ensemble;

ensemble* ensemble_vide(void);
void ensemble_free(ensemble* e);

ensemble* ensemble_insertion(ensemble* e, S x);
ensemble* ensemble_suppression(ensemble* e, S x);

bool ensemble_contient(const ensemble* e, S x);
size_t ensemble_cardinal(const ensemble * e);
bool ensemble_est_vide(const ensemble * e);

iterateur* ensemble_iterateur_debut(const ensemble* e);
iterateur* ensemble_iterateur_fin(const ensemble* e);

#endif
