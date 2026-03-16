static int DoMatOp ( int tok , int sp , struct psstack * stack ) {
 real temp [ 6 ] , t [ 6 ] ;
 int nsp = sp ;
 if ( stack [ sp - 1 ] . u . dict . cnt == 6 && stack [ sp - 1 ] . u . dict . entries [ 0 ] . type == ps_num ) {
 t [ 5 ] = stack [ sp - 1 ] . u . dict . entries [ 5 ] . u . val ;
 t [ 4 ] = stack [ sp - 1 ] . u . dict . entries [ 4 ] . u . val ;
 t [ 3 ] = stack [ sp - 1 ] . u . dict . entries [ 3 ] . u . val ;
 t [ 2 ] = stack [ sp - 1 ] . u . dict . entries [ 2 ] . u . val ;
 t [ 1 ] = stack [ sp - 1 ] . u . dict . entries [ 1 ] . u . val ;
 t [ 0 ] = stack [ sp - 1 ] . u . dict . entries [ 0 ] . u . val ;
 switch ( tok ) {
 case pt_translate : if ( sp >= 3 ) {
 stack [ sp - 1 ] . u . dict . entries [ 5 ] . u . val += stack [ sp - 3 ] . u . val * t [ 0 ] + stack [ sp - 2 ] . u . val * t [ 2 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 4 ] . u . val += stack [ sp - 3 ] . u . val * t [ 1 ] + stack [ sp - 2 ] . u . val * t [ 3 ] ;
 nsp = sp - 2 ;
 }
 break ;
 case pt_scale : if ( sp >= 2 ) {
 stack [ sp - 1 ] . u . dict . entries [ 0 ] . u . val *= stack [ sp - 3 ] . u . val ;
 stack [ sp - 1 ] . u . dict . entries [ 1 ] . u . val *= stack [ sp - 3 ] . u . val ;
 stack [ sp - 1 ] . u . dict . entries [ 2 ] . u . val *= stack [ sp - 2 ] . u . val ;
 stack [ sp - 1 ] . u . dict . entries [ 3 ] . u . val *= stack [ sp - 2 ] . u . val ;
 nsp = sp - 2 ;
 }
 break ;
 case pt_rotate : if ( sp >= 1 ) {
 -- sp ;
 temp [ 0 ] = temp [ 3 ] = cos ( stack [ sp ] . u . val ) ;
 temp [ 1 ] = sin ( stack [ sp ] . u . val ) ;
 temp [ 2 ] = - temp [ 1 ] ;
 temp [ 4 ] = temp [ 5 ] = 0 ;
 MatMultiply ( temp , t , t ) ;
 stack [ sp - 1 ] . u . dict . entries [ 5 ] . u . val = t [ 5 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 4 ] . u . val = t [ 4 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 3 ] . u . val = t [ 3 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 2 ] . u . val = t [ 2 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 1 ] . u . val = t [ 1 ] ;
 stack [ sp - 1 ] . u . dict . entries [ 0 ] . u . val = t [ 0 ] ;
 nsp = sp - 1 ;
 }
 break ;
 default : break ;
 }
 stack [ nsp - 1 ] = stack [ sp - 1 ] ;
 }
 return ( nsp ) ;
 }