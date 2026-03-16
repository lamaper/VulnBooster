static inline void allow_coredumps ( ) {

 ( void ) prctl ( PR_SET_DUMPABLE , 1 ) ;
 }
