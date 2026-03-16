static void HintsRenumber ( SplineChar * sc ) {
 int mapping [ 96 ] ;
 int i , max ;
 StemInfo * h ;
 SplineSet * spl ;
 SplinePoint * sp ;
 for ( i = 0 ;
 i < 96 ;
 ++ i ) mapping [ i ] = i ;
 i = 0 ;
 for ( h = sc -> hstem ;
 h != NULL ;
 h = h -> next ) {
 if ( h -> hintnumber < 96 && i < 96 ) {
 mapping [ h -> hintnumber ] = i ;
 h -> hintnumber = i ++ ;
 }
 chunkfree ( h -> u . unblended , sizeof ( real [ 2 ] [ MmMax ] ) ) ;
 h -> u . unblended = NULL ;
 }
 for ( h = sc -> vstem ;
 h != NULL ;
 h = h -> next ) {
 if ( h -> hintnumber < 96 && i < 96 ) {
 mapping [ h -> hintnumber ] = i ;
 h -> hintnumber = i ++ ;
 }
 chunkfree ( h -> u . unblended , sizeof ( real [ 2 ] [ MmMax ] ) ) ;
 h -> u . unblended = NULL ;
 }
 max = i ;
 for ( i = 0 ;
 i < max ;
 ++ i ) if ( mapping [ i ] != i ) break ;
 if ( i == max ) return ;
 for ( i = 0 ;
 i < sc -> countermask_cnt ;
 ++ i ) RemapHintMask ( & sc -> countermasks [ i ] , mapping , max ) ;
 for ( spl = sc -> layers [ ly_fore ] . splines ;
 spl != NULL ;
 spl = spl -> next ) {
 for ( sp = spl -> first ;
 ;
 ) {
 RemapHintMask ( sp -> hintmask , mapping , max ) ;
 if ( sp -> next == NULL ) break ;
 sp = sp -> next -> to ;
 if ( sp == spl -> first ) break ;
 }
 }
 }