static inline Quantum GetPixelYellow ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ YellowPixelChannel ] . offset ] ) ;
 }