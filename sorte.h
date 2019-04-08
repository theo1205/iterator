#ifndef _SORTE_H
#define _SORTE_H

#include <inttypes.h>

#ifndef TYPE_S
  #define TYPE_S intmax_t
  #ifndef PRI_S
    #define PRI_S PRIdMAX
  #endif
  #ifndef SCN_S
    #define SCN_S SCNdMAX
  #endif
#endif

/*
 * PRI_S et SCN_S ont une valeur par défaut si et seulement si
 * TYPE_S est défini à sa valeur par défaut.
 * On exige que PRI_S et SCN_S soient manuellement définis
 * lorsque TYPE_S est manuellement défini, car ces deux macros doivent
 * être adaptés à TYPE_S.
 */
#ifndef PRI_S
  #error "PRI_S macro not found"
#endif
#ifndef SCN_S
  #error "SCN_S macro not found"
#endif

typedef TYPE_S S;

#endif
