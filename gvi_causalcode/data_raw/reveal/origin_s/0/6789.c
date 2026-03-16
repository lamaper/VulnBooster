static void OS2WeightCheck ( struct pfminfo * pfminfo , char * weight ) {
 if ( weight == NULL ) {
 }
 else if ( strstrmatch ( weight , "medi" ) != NULL ) {
 pfminfo -> weight = 500 ;
 pfminfo -> panose [ 2 ] = 6 ;
 }
 else if ( strstrmatch ( weight , "demi" ) != NULL || strstrmatch ( weight , "halb" ) != NULL || ( strstrmatch ( weight , "semi" ) != NULL && strstrmatch ( weight , "bold" ) != NULL ) ) {
 pfminfo -> weight = 600 ;
 pfminfo -> panose [ 2 ] = 7 ;
 }
 else if ( strstrmatch ( weight , "bold" ) != NULL || strstrmatch ( weight , "fett" ) != NULL || strstrmatch ( weight , "gras" ) != NULL ) {
 pfminfo -> weight = 700 ;
 pfminfo -> panose [ 2 ] = 8 ;
 }
 else if ( strstrmatch ( weight , "heavy" ) != NULL ) {
 pfminfo -> weight = 800 ;
 pfminfo -> panose [ 2 ] = 9 ;
 }
 else if ( strstrmatch ( weight , "black" ) != NULL ) {
 pfminfo -> weight = 900 ;
 pfminfo -> panose [ 2 ] = 10 ;
 }
 else if ( strstrmatch ( weight , "nord" ) != NULL ) {
 pfminfo -> weight = 950 ;
 pfminfo -> panose [ 2 ] = 11 ;
 }
 else if ( strstrmatch ( weight , "thin" ) != NULL ) {
 pfminfo -> weight = 100 ;
 pfminfo -> panose [ 2 ] = 2 ;
 }
 else if ( strstrmatch ( weight , "extra" ) != NULL || strstrmatch ( weight , "light" ) != NULL ) {
 pfminfo -> weight = 200 ;
 pfminfo -> panose [ 2 ] = 3 ;
 }
 else if ( strstrmatch ( weight , "light" ) != NULL ) {
 pfminfo -> weight = 300 ;
 pfminfo -> panose [ 2 ] = 4 ;
 }
 }