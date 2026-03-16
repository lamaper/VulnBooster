static int aload ( unsigned sp , struct psstack * stack , size_t stacktop , struct garbage * tofrees ) {
 int i ;
 if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 struct pskeydict dict ;
 -- sp ;
 dict = stack [ sp ] . u . dict ;
 for ( i = 0 ;
 i < dict . cnt ;
 ++ i ) {
 if ( sp < stacktop ) {
 stack [ sp ] . type = dict . entries [ i ] . type ;
 stack [ sp ] . u = dict . entries [ i ] . u ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) stack [ sp ] . u . str = copy ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array ) copyarray ( & stack [ sp ] . u . dict , & stack [ sp ] . u . dict , tofrees ) ;
 ++ sp ;
 }
 }
 }
 return ( sp ) ;
 }