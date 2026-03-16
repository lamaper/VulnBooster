static inline void tm2_null_res_block ( TM2Context * ctx , AVFrame * pic , int bx , int by ) {
 int i ;
 int ct ;
 int left , right , diff ;
 int deltas [ 16 ] ;
 TM2_INIT_POINTERS ( ) ;
 deltas [ 0 ] = deltas [ 1 ] = deltas [ 2 ] = deltas [ 3 ] = 0 ;
 tm2_low_chroma ( U , Ustride , clast , ctx -> CD , deltas , bx ) ;
 deltas [ 0 ] = deltas [ 1 ] = deltas [ 2 ] = deltas [ 3 ] = 0 ;
 tm2_low_chroma ( V , Vstride , clast + 2 , ctx -> CD + 2 , deltas , bx ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) deltas [ i ] = 0 ;
 ct = ctx -> D [ 0 ] + ctx -> D [ 1 ] + ctx -> D [ 2 ] + ctx -> D [ 3 ] ;
 if ( bx > 0 ) left = last [ - 1 ] - ct ;
 else left = 0 ;
 right = last [ 3 ] ;
 diff = right - left ;
 last [ 0 ] = left + ( diff >> 2 ) ;
 last [ 1 ] = left + ( diff >> 1 ) ;
 last [ 2 ] = right - ( diff >> 2 ) ;
 last [ 3 ] = right ;
 {
 int tp = left ;
 ctx -> D [ 0 ] = ( tp + ( ct >> 2 ) ) - left ;
 left += ctx -> D [ 0 ] ;
 ctx -> D [ 1 ] = ( tp + ( ct >> 1 ) ) - left ;
 left += ctx -> D [ 1 ] ;
 ctx -> D [ 2 ] = ( ( tp + ct ) - ( ct >> 2 ) ) - left ;
 left += ctx -> D [ 2 ] ;
 ctx -> D [ 3 ] = ( tp + ct ) - left ;
 }
 tm2_apply_deltas ( ctx , Y , Ystride , deltas , last ) ;
 }