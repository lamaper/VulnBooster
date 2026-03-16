static void printusage ( struct xcmd * xcp , FILE * fp ) {
 register int i ;
 ( void ) fprintf ( fp , "usage: %s" , xcp -> keyword ) ;
 for ( i = 0 ;
 i < MAXARGS && xcp -> arg [ i ] != NO ;
 i ++ ) {
 if ( xcp -> arg [ i ] & OPT ) ( void ) fprintf ( fp , " [ %s ]" , xcp -> desc [ i ] ) ;
 else ( void ) fprintf ( fp , " %s" , xcp -> desc [ i ] ) ;
 }
 ( void ) fprintf ( fp , "\n" ) ;
 }