#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
//#define EDEBUG
//#define AUTOCOMPILE

#ifdef AUTORUN
# define csystem(y) system(y)
#else
# define csystem(y) ;
#endif

#ifdef EDEBUG
# define eprintf(x...) printf(x)
#else
# define eprintf(x...) ; 
#endif

#ifdef DEBUG
# define dprintf(x...) printf(x)
#else
# define dprintf(x...) ; 
#endif

