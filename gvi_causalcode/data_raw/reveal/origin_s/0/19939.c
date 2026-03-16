static void DoMatTransform ( int tok , int sp , struct psstack * stack ) {
 real invt [ 6 ] , t [ 6 ] ;
 if ( stack [ sp - 1 ] . u . dict . cnt == 6 && stack [ sp - 1 ] . u . dict . entries [ 0 ] . type == ps_num ) {
 double x = stack [ sp - 3 ] . u . val , y = stack [ sp - 2 ] . u . val ;
 -- sp ;
 t [ 5 ] = stack [ sp ] . u . dict . entries [ 5 ] . u . val ;
 t [ 4 ] = stack [ sp ] . u . dict . entries [ 4 ] . u . val ;
 t [ 3 ] = stack [ sp ] . u . dict . entries [ 3 ] . u . val ;
 t [ 2 ] = stack [ sp ] . u . dict . entries [ 2 ] . u . val ;
 t [ 1 ] = stack [ sp ] . u . dict . entries [ 1 ] . u . val ;
 t [ 0 ] = stack [ sp ] . u . dict . entries [ 0 ] . u . val ;
 dictfree ( & stack [ sp ] . u . dict ) ;
 if ( tok == pt_itransform || tok == pt_idtransform ) {
 MatInverse ( invt , t ) ;
 memcpy ( t , invt , sizeof ( t ) ) ;
 }
 stack [ sp - 2 ] . u . val = t [ 0 ] * x + t [ 1 ] * y ;
 stack [ sp - 1 ] . u . val = t [ 2 ] * x + t [ 3 ] * y ;
 if ( tok == pt_transform || tok == pt_itransform ) {
 stack [ sp - 2 ] . u . val += t [ 4 ] ;
 stack [ sp - 1 ] . u . val += t [ 5 ] ;
 }
 }
 }