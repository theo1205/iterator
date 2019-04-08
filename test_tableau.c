#include <stdio.h>

#include "sorte.h"
#include "tableau.h"

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

static inline int test_tableau_insertion_debut(void)
{
  int erreurs = 0;

  tableau* t = tableau_vide();
  for (size_t i = 0; i < 20; ++i)
    t = tableau_insertion_debut(t, (S) i);

  const size_t taille = tableau_longueur(t);
  erreurs += assert(taille == 20);
  for (size_t i = 0; i < taille; ++i)
  {
    const S element = tableau_element(t, i);
    erreurs += assert(element == (S) (taille - i - 1));
    printf("%"PRI_S" ", element);
  }
  printf("\n");

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_tableau_insertion_fin(void)
{
  int erreurs = 0;

  tableau* t = tableau_vide();
  for (size_t i = 0; i < 20; ++i)
    t = tableau_insertion_fin(t, (S) i);

  const size_t taille = tableau_longueur(t);
  erreurs += assert(taille == 20);
  for (size_t i = 0; i < taille; ++i)
  {
    const S element = tableau_element(t, i);
    erreurs += assert(element == (S) i);
    printf("%"PRI_S" ", element);
  }
  printf("\n");

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

int main(int argc, char* argv[argc + 1])
{
  (void) argc; (void) argv;

  int erreurs = 0;
  erreurs += test_tableau_insertion_debut();
  erreurs += test_tableau_insertion_fin();

  return erreurs ? 1 : 0;
}
