static inline void tm2_med_res_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i ;
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
 i ++ ) deltas [ i ] = GET_TOK ( ctx , TM2_L_HI ) ;
 tm2_apply_deltas ( ctx , Y , Ystride , deltas , last ) ;
 }