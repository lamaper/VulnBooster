static inline Quantum GetPixelIndex ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ IndexPixelChannel ] . traits == UndefinedPixelTrait ) return ( ( Quantum ) 0 ) ;
 return ( pixel [ image -> channel_map [ IndexPixelChannel ] . offset ] ) ;
 }