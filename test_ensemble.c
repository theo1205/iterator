#include <stdio.h>

#include "sorte.h"
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

static int test_ensemble_insertion(void)
{
  int erreurs = 0;

  ensemble* e = ensemble_vide();
  for (size_t i = 0; i < 20; i += 2)
    e = ensemble_insertion(e, (S) i);

  assert(ensemble_cardinal(e) == 10);
  for (size_t i = 0; i < 20; i++)
  {
    bool contient = ensemble_contient(e, (S) i);
    if (i % 2)
      erreurs += assert(!contient);
    else
      erreurs += assert(contient);
    if (contient)
      printf("%"PRI_S" ", (S) i);
  }
  printf("\n");

  ensemble_free(e);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static int test_ensemble_suppression(void)
{
  int erreurs = 0;

  ensemble* e = ensemble_vide();
  for (size_t i = 0; i < 20; i++)
    e = ensemble_insertion(e, (S) i);
  for (size_t i = 0; i < 20; i += 2)
    e = ensemble_suppression(e, (S) i);

  assert(ensemble_cardinal(e) == 10);
  for (size_t i = 0; i < 20; i++)
  {
    bool contient = ensemble_contient(e, (S) i);
    if (i % 2)
      erreurs += assert(contient);
    else
      erreurs += assert(!contient);
    if (contient)
      printf("%"PRI_S" ", (S) i);
  }
  printf("\n");

  ensemble_free(e);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

int main(int argc, char* argv[argc + 1])
{
  (void) argc; (void) argv;

  int erreurs = 0;
  erreurs += test_ensemble_insertion();
  erreurs += test_ensemble_suppression();

  return erreurs ? 1 : 0;
}
