static inline void tm2_still_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i , j ;
 TM2_INIT_POINTERS_2 ( ) ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) {
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 U [ i ] = Uo [ i ] ;
 V [ i ] = Vo [ i ] ;
 }
 U += Ustride ;
 V += Vstride ;
 Uo += oUstride ;
 Vo += oVstride ;
 }
 U -= Ustride * 2 ;
 V -= Vstride * 2 ;
 TM2_RECALC_BLOCK ( U , Ustride , clast , ctx -> CD ) ;
 TM2_RECALC_BLOCK ( V , Vstride , ( clast + 2 ) , ( ctx -> CD + 2 ) ) ;
 ctx -> D [ 0 ] = Yo [ 3 ] - last [ 3 ] ;
 ctx -> D [ 1 ] = Yo [ 3 + oYstride ] - Yo [ 3 ] ;
 ctx -> D [ 2 ] = Yo [ 3 + oYstride * 2 ] - Yo [ 3 + oYstride ] ;
 ctx -> D [ 3 ] = Yo [ 3 + oYstride * 3 ] - Yo [ 3 + oYstride * 2 ] ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 Y [ i ] = Yo [ i ] ;
 last [ i ] = Yo [ i ] ;
 }
 Y += Ystride ;
 Yo += oYstride ;
 }
 }