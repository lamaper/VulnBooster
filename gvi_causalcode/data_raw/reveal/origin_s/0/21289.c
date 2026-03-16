static inline Quantum GetPixelb ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ bPixelChannel ] . offset ] ) ;
 }