static inline Quantum GetPixelY ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ YPixelChannel ] . offset ] ) ;
 }