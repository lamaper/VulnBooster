static int AddEntry ( struct pskeydict * dict , struct psstack * stack , int sp ) {
 int i ;
 if ( dict -> cnt >= dict -> max ) {
 if ( dict -> cnt == 0 ) {
 dict -> max = 30 ;
 dict -> entries = malloc ( dict -> max * sizeof ( struct pskeyval ) ) ;
 }
 else {
 dict -> max += 30 ;
 dict -> entries = realloc ( dict -> entries , dict -> max * sizeof ( struct pskeyval ) ) ;
 }
 }
 if ( sp < 2 ) return ( sp ) ;
 if ( stack [ sp - 2 ] . type != ps_string && stack [ sp - 2 ] . type != ps_lit ) {
 LogError ( _ ( "Key for a def must be a string or name literal\n" ) ) ;
 return ( sp - 2 ) ;
 }
 for ( i = 0 ;
 i < dict -> cnt ;
 ++ i ) if ( strcmp ( dict -> entries [ i ] . key , stack [ sp - 2 ] . u . str ) == 0 ) break ;
 if ( i != dict -> cnt ) {
 free ( stack [ sp - 2 ] . u . str ) ;
 if ( dict -> entries [ i ] . type == ps_string || dict -> entries [ i ] . type == ps_instr || dict -> entries [ i ] . type == ps_lit ) free ( dict -> entries [ i ] . u . str ) ;
 }
 else {
 memset ( & dict -> entries [ i ] , '\0' , sizeof ( struct pskeyval ) ) ;
 dict -> entries [ i ] . key = stack [ sp - 2 ] . u . str ;
 ++ dict -> cnt ;
 }
 dict -> entries [ i ] . type = stack [ sp - 1 ] . type ;
 dict -> entries [ i ] . u = stack [ sp - 1 ] . u ;
 return ( sp - 2 ) ;
 }