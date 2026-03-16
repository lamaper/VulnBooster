static inline void tm2_hi_res_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i ;
 int deltas [ 16 ] ;
 TM2_INIT_POINTERS ( ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 deltas [ i ] = GET_TOK ( ctx , TM2_C_HI ) ;
 deltas [ i + 4 ] = GET_TOK ( ctx , TM2_C_HI ) ;
 }
 tm2_high_chroma ( U , Ustride , clast , ctx -> CD , deltas ) ;
 tm2_high_chroma ( V , Vstride , clast + 2 , ctx -> CD + 2 , deltas + 4 ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) deltas [ i ] = GET_TOK ( ctx , TM2_L_HI ) ;
 tm2_apply_deltas ( ctx , Y , Ystride , deltas , last ) ;
 }