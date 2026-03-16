static inline Quantum GetPixelGray ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ GrayPixelChannel ] . offset ] ) ;
 }