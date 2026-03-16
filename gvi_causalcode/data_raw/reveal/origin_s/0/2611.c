static void copyarray ( struct pskeydict * to , struct pskeydict * from , struct garbage * tofrees ) {
 int i ;
 struct pskeyval * oldent = from -> entries ;
 * to = * from ;
 to -> entries = calloc ( to -> cnt , sizeof ( struct pskeyval ) ) ;
 for ( i = 0 ;
 i < to -> cnt ;
 ++ i ) {
 to -> entries [ i ] = oldent [ i ] ;
 if ( to -> entries [ i ] . type == ps_string || to -> entries [ i ] . type == ps_instr || to -> entries [ i ] . type == ps_lit ) to -> entries [ i ] . u . str = copy ( to -> entries [ i ] . u . str ) ;
 else if ( to -> entries [ i ] . type == ps_array || to -> entries [ i ] . type == ps_dict ) copyarray ( & to -> entries [ i ] . u . dict , & oldent [ i ] . u . dict , tofrees ) ;
 }
 collectgarbage ( tofrees , to ) ;
 }