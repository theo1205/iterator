#include <stdio.h>

#include "sorte.h"
#include "liste.h"
#include "tableau.h"
#include "iterateur.h"
#include "ensemble.h"

#ifndef NDEBUG
  #define assert(expr) \
    (expr) ? \
    0 : \
    (fprintf( \
        stderr, "erreur: %s: %s(): l.%d: "#expr"\n", __FILE__, \
        __func__, __LINE__), 1)
#else
  #define assert(expr) (void) 0
#endif

#define iterateur_debut(x) \
  _Generic((x), \
      liste*: liste_iterateur_debut, \
      tableau*: tableau_iterateur_debut, \
      ensemble*: ensemble_iterateur_debut \
      )(x)
#define iterateur_fin(x) \
  _Generic((x), \
      liste*: liste_iterateur_fin, \
      tableau*: tableau_iterateur_fin, \
      ensemble*: ensemble_iterateur_fin \
      )(x)

static inline int test_tableau(void)
{
  int erreurs = 0;
  tableau* t = tableau_vide();
  for (size_t i = 0; i < 20; ++i)
    t = tableau_insertion_fin(t, (S) i);
  iterateur* debut = iterateur_debut(t);
  iterateur* fin = iterateur_fin(t);
  iterateur* it;
  S x = 0;
  for (it = debut; !iterateur_egal(it, fin); it = iterateur_suivant(it))
  {
    const S valeur = iterateur_valeur(it);
    printf("%"PRI_S" ", x);
    erreurs = assert(valeur == x++);
  }
  printf("\n");
  iterateur_free(it);
  iterateur_free(fin);
  tableau_free(t);
  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste(void)
{
  int erreurs = 0;
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_debut(l);
  S x = 0;
  iterateur* it;
  iterateur* const fin = liste_iterateur_fin(l);
  for (it = iterateur_debut(l); !iterateur_egal(it, fin); it = iterateur_suivant(it))
  {
    const S valeur = iterateur_valeur(it);
    printf("%"PRI_S" ", valeur);
    erreurs = assert(valeur == x++);
  }
  printf("\n");
  iterateur_free(it);
  iterateur_free(fin);
  liste_free(l);
  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_ensemble(void)
{
  int erreurs = 0;
  ensemble* e = ensemble_vide();
  for (size_t i = 0; i < 20; ++i)
    e = ensemble_insertion(e, (S) i);
  S x = 0;
  iterateur* it;
  iterateur* const fin = ensemble_iterateur_fin(e);
  for (it = iterateur_debut(e); !iterateur_egal(it, fin); it = iterateur_suivant(it))
  {
    const S valeur = iterateur_valeur(it);
    printf("%"PRI_S" ", valeur);
    erreurs = assert(valeur == x++);
  }
  printf("\n");
  iterateur_free(it);
  iterateur_free(fin);
  ensemble_free(e);
  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

int main(int argc, char* argv[argc + 1])
{
  (void) argc; (void) argv;
  int erreurs = 0;
  erreurs += test_tableau();
  erreurs += test_liste();
  erreurs += test_ensemble();
  return erreurs;
}
