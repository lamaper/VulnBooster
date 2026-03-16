static inline void tm2_motion_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i , j ;
 int mx , my ;
 TM2_INIT_POINTERS_2 ( ) ;
 mx = GET_TOK ( ctx , TM2_MOT ) ;
 my = GET_TOK ( ctx , TM2_MOT ) ;
 mx = av_clip ( mx , - ( bx * 4 + 4 ) , ctx -> avctx -> width - bx * 4 ) ;
 my = av_clip ( my , - ( by * 4 + 4 ) , ctx -> avctx -> height - by * 4 ) ;
 Yo += my * oYstride + mx ;
 Uo += ( my >> 1 ) * oUstride + ( mx >> 1 ) ;
 Vo += ( my >> 1 ) * oVstride + ( mx >> 1 ) ;
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
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 Y [ i ] = Yo [ i ] ;
 }
 Y += Ystride ;
 Yo += oYstride ;
 }
 Y -= Ystride * 4 ;
 ctx -> D [ 0 ] = Y [ 3 ] - last [ 3 ] ;
 ctx -> D [ 1 ] = Y [ 3 + Ystride ] - Y [ 3 ] ;
 ctx -> D [ 2 ] = Y [ 3 + Ystride * 2 ] - Y [ 3 + Ystride ] ;
 ctx -> D [ 3 ] = Y [ 3 + Ystride * 3 ] - Y [ 3 + Ystride * 2 ] ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) last [ i ] = Y [ i + Ystride * 3 ] ;
 }