static void dictfree ( struct pskeydict * dict ) {
 int i ;
 for ( i = 0 ;
 i < dict -> cnt ;
 ++ i ) {
 if ( dict -> entries [ i ] . type == ps_string || dict -> entries [ i ] . type == ps_instr || dict -> entries [ i ] . type == ps_lit ) free ( dict -> entries [ i ] . u . str ) ;
 else if ( dict -> entries [ i ] . type == ps_array || dict -> entries [ i ] . type == ps_dict ) dictfree ( & dict -> entries [ i ] . u . dict ) ;
 }
 }