static void truespeech_filters_merge ( TSContext * dec ) {
 int i ;
 if ( ! dec -> flag ) {
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 dec -> filters [ i + 0 ] = dec -> prevfilt [ i ] ;
 dec -> filters [ i + 8 ] = dec -> prevfilt [ i ] ;
 }
 }
 else {
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 dec -> filters [ i + 0 ] = ( dec -> cvector [ i ] * 21846 + dec -> prevfilt [ i ] * 10923 + 16384 ) >> 15 ;
 dec -> filters [ i + 8 ] = ( dec -> cvector [ i ] * 10923 + dec -> prevfilt [ i ] * 21846 + 16384 ) >> 15 ;
 }
 }
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 dec -> filters [ i + 16 ] = dec -> cvector [ i ] ;
 dec -> filters [ i + 24 ] = dec -> cvector [ i ] ;
 }
 }