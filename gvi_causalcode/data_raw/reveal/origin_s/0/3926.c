static inline Quantum GetPixelCr ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ CrPixelChannel ] . offset ] ) ;
 }