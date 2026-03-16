static int glyphmatches ( SplineChar * sc , SplineChar * sc2 , int layer ) {
 RefChar * r , * r2 ;
 SplineSet * ss , * ss2 ;
 SplinePoint * sp , * sp2 ;
 if ( sc -> width != sc2 -> width ) return ( false ) ;
 if ( sc -> ttf_instrs_len != sc2 -> ttf_instrs_len ) return ( false ) ;
 if ( sc -> ttf_instrs_len != 0 && memcmp ( sc -> ttf_instrs , sc2 -> ttf_instrs , sc -> ttf_instrs_len ) != 0 ) return ( false ) ;
 for ( r = sc -> layers [ layer ] . refs , r2 = sc2 -> layers [ layer ] . refs ;
 r != NULL && r2 != NULL ;
 r = r -> next , r2 = r2 -> next ) {
 if ( r -> transform [ 0 ] != r2 -> transform [ 0 ] || r -> transform [ 1 ] != r2 -> transform [ 1 ] || r -> transform [ 2 ] != r2 -> transform [ 2 ] || r -> transform [ 3 ] != r2 -> transform [ 3 ] || r -> transform [ 4 ] != r2 -> transform [ 4 ] || r -> transform [ 5 ] != r2 -> transform [ 5 ] ) return ( false ) ;
 if ( r -> sc -> unicodeenc != r2 -> sc -> unicodeenc ) return ( false ) ;
 if ( r -> sc -> unicodeenc == - 1 && strcmp ( r -> sc -> name , r2 -> sc -> name ) != 0 ) return ( false ) ;
 }
 if ( r != NULL || r2 != NULL ) return ( false ) ;
 for ( ss = sc -> layers [ layer ] . splines , ss2 = sc2 -> layers [ layer ] . splines ;
 ss != NULL && ss2 != NULL ;
 ss = ss -> next , ss2 = ss2 -> next ) {
 for ( sp = ss -> first , sp2 = ss2 -> first ;
 sp != NULL && sp2 != NULL ;
 ) {
 if ( sp -> me . x != sp2 -> me . x || sp -> me . y != sp2 -> me . y || sp -> nextcp . x != sp2 -> nextcp . x || sp -> nextcp . y != sp2 -> nextcp . y || sp -> prevcp . x != sp2 -> prevcp . x || sp -> prevcp . y != sp2 -> prevcp . y ) return ( false ) ;
 sp = ( sp -> next ? sp -> next -> to : NULL ) ;
 sp2 = ( sp2 -> next ? sp2 -> next -> to : NULL ) ;
 if ( sp == ss -> first ) {
 if ( sp2 == ss2 -> first ) break ;
 return ( false ) ;
 }
 else if ( sp2 == ss2 -> first ) return ( false ) ;
 }
 if ( ( sp == NULL && sp2 != NULL ) || ( sp != NULL && sp2 == NULL ) ) return ( false ) ;
 }
 if ( ss == NULL && ss2 == NULL ) return ( true ) ;
 return ( false ) ;
 }