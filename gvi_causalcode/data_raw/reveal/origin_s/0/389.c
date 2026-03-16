static void truespeech_save_prevvec ( TSContext * c ) {
 int i ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) c -> prevfilt [ i ] = c -> cvector [ i ] ;
 }