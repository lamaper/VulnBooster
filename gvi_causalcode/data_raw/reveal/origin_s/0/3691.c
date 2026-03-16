void validate_positive_rational ( const char * msg , struct vpx_rational * rat ) {
 if ( rat -> den < 0 ) {
 rat -> num *= - 1 ;
 rat -> den *= - 1 ;
 }
 if ( rat -> num < 0 ) die ( "Error: %s must be positive\n" , msg ) ;
 if ( ! rat -> den ) die ( "Error: %s has zero denominator\n" , msg ) ;
 }