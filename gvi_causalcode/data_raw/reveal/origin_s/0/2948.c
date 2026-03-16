static void garbagefree ( struct garbage * all ) {
 struct garbage * junk , * next ;
 int i , j ;
 for ( junk = all ;
 junk != NULL ;
 junk = next ) {
 next = junk -> next ;
 for ( j = 0 ;
 j < junk -> cnt ;
 ++ j ) {
 for ( i = 0 ;
 i < junk -> cnts [ j ] ;
 ++ i ) {
 if ( junk -> entries [ j ] [ i ] . type == ps_string || junk -> entries [ j ] [ i ] . type == ps_instr || junk -> entries [ j ] [ i ] . type == ps_lit ) free ( junk -> entries [ j ] [ i ] . u . str ) ;
 }
 free ( junk -> entries [ j ] ) ;
 }
 if ( junk != all ) chunkfree ( junk , sizeof ( struct garbage ) ) ;
 }
 }