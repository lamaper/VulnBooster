static void freestuff ( struct psstack * stack , int sp , struct pskeydict * dict , GrowBuf * gb , struct garbage * tofrees ) {
 int i ;
 free ( gb -> base ) ;
 for ( i = 0 ;
 i < dict -> cnt ;
 ++ i ) {
 if ( dict -> entries [ i ] . type == ps_string || dict -> entries [ i ] . type == ps_instr || dict -> entries [ i ] . type == ps_lit ) free ( dict -> entries [ i ] . u . str ) ;
 free ( dict -> entries [ i ] . key ) ;
 }
 free ( dict -> entries ) ;
 for ( i = 0 ;
 i < sp ;
 ++ i ) {
 if ( stack [ i ] . type == ps_string || stack [ i ] . type == ps_instr || stack [ i ] . type == ps_lit ) free ( stack [ i ] . u . str ) ;
 }
 garbagefree ( tofrees ) ;
 }