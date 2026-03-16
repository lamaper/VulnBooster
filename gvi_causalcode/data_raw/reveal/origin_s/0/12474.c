static inline Quantum GetPixelBlue ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ) ;
 }