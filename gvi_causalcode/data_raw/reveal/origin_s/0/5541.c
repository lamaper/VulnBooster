static inline int ivi_scale_mv ( int mv , int mv_scale ) {
 return ( mv + ( mv > 0 ) + ( mv_scale - 1 ) ) >> mv_scale ;
 }