static inline Quantum GetPixelCyan ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ CyanPixelChannel ] . offset ] ) ;
 }