static inline Quantum GetPixelRed ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ RedPixelChannel ] . offset ] ) ;
 }