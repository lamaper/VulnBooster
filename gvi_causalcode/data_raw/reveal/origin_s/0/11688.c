static inline void store_mvs ( AVSContext * h ) {
 h -> col_mv [ h -> mbidx * 4 + 0 ] = h -> mv [ MV_FWD_X0 ] ;
 h -> col_mv [ h -> mbidx * 4 + 1 ] = h -> mv [ MV_FWD_X1 ] ;
 h -> col_mv [ h -> mbidx * 4 + 2 ] = h -> mv [ MV_FWD_X2 ] ;
 h -> col_mv [ h -> mbidx * 4 + 3 ] = h -> mv [ MV_FWD_X3 ] ;
 }