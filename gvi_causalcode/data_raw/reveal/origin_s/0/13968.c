static inline void tm2_apply_deltas ( TM2Context * ctx , int * Y , int stride , int * deltas , int * last ) {
 int ct , d ;
 int i , j ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 ct = ctx -> D [ j ] ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 d = deltas [ i + j * 4 ] ;
 ct += d ;
 last [ i ] += ct ;
 Y [ i ] = av_clip_uint8 ( last [ i ] ) ;
 }
 Y += stride ;
 ctx -> D [ j ] = ct ;
 }
 }