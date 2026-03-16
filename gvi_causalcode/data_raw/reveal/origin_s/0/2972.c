static inline Quantum GetPixelL ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ LPixelChannel ] . offset ] ) ;
 }