static int forgetstack ( struct psstack * stack , int forgets , int sp ) {
 int i ;
 for ( i = 0 ;
 i < forgets ;
 ++ i ) {
 if ( stack [ i ] . type == ps_string || stack [ i ] . type == ps_instr || stack [ i ] . type == ps_lit ) free ( stack [ i ] . u . str ) ;
 else if ( stack [ i ] . type == ps_array || stack [ i ] . type == ps_dict ) dictfree ( & stack [ i ] . u . dict ) ;
 }
 for ( i = forgets ;
 i < sp ;
 ++ i ) stack [ i - forgets ] = stack [ i ] ;
 return ( sp - forgets ) ;
 }