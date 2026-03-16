static inline Quantum GetPixela ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ aPixelChannel ] . offset ] ) ;
 }