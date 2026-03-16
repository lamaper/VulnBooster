static inline void tm2_low_res_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i ;
 int t1 , t2 ;
 int deltas [ 16 ] ;
 TM2_INIT_POINTERS ( ) ;
 deltas [ 0 ] = GET_TOK ( ctx , TM2_C_LO ) ;
 deltas [ 1 ] = deltas [ 2 ] = deltas [ 3 ] = 0 ;
 tm2_low_chroma ( U , Ustride , clast , ctx -> CD , deltas , bx ) ;
 deltas [ 0 ] = GET_TOK ( ctx , TM2_C_LO ) ;
 deltas [ 1 ] = deltas [ 2 ] = deltas [ 3 ] = 0 ;
 tm2_low_chroma ( V , Vstride , clast + 2 , ctx -> CD + 2 , deltas , bx ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) deltas [ i ] = 0 ;
 deltas [ 0 ] = GET_TOK ( ctx , TM2_L_LO ) ;
 deltas [ 2 ] = GET_TOK ( ctx , TM2_L_LO ) ;
 deltas [ 8 ] = GET_TOK ( ctx , TM2_L_LO ) ;
 deltas [ 10 ] = GET_TOK ( ctx , TM2_L_LO ) ;
 if ( bx > 0 ) last [ 0 ] = ( last [ - 1 ] - ctx -> D [ 0 ] - ctx -> D [ 1 ] - ctx -> D [ 2 ] - ctx -> D [ 3 ] + last [ 1 ] ) >> 1 ;
 else last [ 0 ] = ( last [ 1 ] - ctx -> D [ 0 ] - ctx -> D [ 1 ] - ctx -> D [ 2 ] - ctx -> D [ 3 ] ) >> 1 ;
 last [ 2 ] = ( last [ 1 ] + last [ 3 ] ) >> 1 ;
 t1 = ctx -> D [ 0 ] + ctx -> D [ 1 ] ;
 ctx -> D [ 0 ] = t1 >> 1 ;
 ctx -> D [ 1 ] = t1 - ( t1 >> 1 ) ;
 t2 = ctx -> D [ 2 ] + ctx -> D [ 3 ] ;
 ctx -> D [ 2 ] = t2 >> 1 ;
 ctx -> D [ 3 ] = t2 - ( t2 >> 1 ) ;
 tm2_apply_deltas ( ctx , Y , Ystride , deltas , last ) ;
 }