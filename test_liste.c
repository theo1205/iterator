#include <stdio.h>
#include <stdbool.h>

#include "sorte.h"
#include "liste.h"

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

static inline int test_liste_insertion_tete(void)
{
  int erreurs = 0;

  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_tete(l, (S) i);
  l = liste_debut(l);

  S x = 19;
  for (const liste* parcours = l; parcours; parcours = liste_suivant(parcours))
  {
    const S element = liste_element(parcours);
    erreurs += assert(element == x);
    x--;

    printf("%"PRI_S" ", element);
  }
  erreurs += assert(liste_longueur(l) == 20);
  printf("\n");

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_insertion_queue(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_debut(l);

  S x = 0;
  for (const liste* parcours = l; parcours; parcours = liste_suivant(parcours))
  {
    const S element = liste_element(parcours);
    erreurs += assert(element == x);
    x++;

    printf("%"PRI_S" ", element);
  }
  erreurs += assert(liste_longueur(l) == 20);
  printf("\n");

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_suppression_tete(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_suppression_tete(l);
  l = liste_debut(l);

  erreurs += assert(liste_longueur(l) == 19);
  erreurs += assert(liste_element(liste_debut(l)) == 1);
  erreurs += assert(liste_element(liste_fin(l)) == 19);

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_suppression_queue(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_suppression_queue(l);
  l = liste_debut(l);

  erreurs += assert(liste_longueur(l) == 19);
  erreurs += assert(liste_element(liste_debut(l)) == 0);
  erreurs += assert(liste_element(liste_fin(l)) == 18);

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

int main(int argc, char* argv[argc + 1])
{
  (void) argc; (void) argv;

  int erreurs = 0;

  erreurs += test_liste_insertion_tete();
  erreurs += test_liste_insertion_queue();
  erreurs += test_liste_suppression_tete();
  erreurs += test_liste_suppression_queue();

  return erreurs ? 1 : 0;
}
