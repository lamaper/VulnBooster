static void setup_address_and_port ( const char * * address , const char * * port ) {
 if ( * address == NULL ) {
 * address = "0.0.0.0" ;
 }
 if ( * port == NULL ) {
 * port = stringify ( NBD_DEFAULT_PORT ) ;
 }
 }