static inline Quantum GetPixelChannel ( const Image * restrict image , const PixelChannel channel , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ channel ] . traits == UndefinedPixelTrait ) return ( ( Quantum ) 0 ) ;
 return ( pixel [ image -> channel_map [ channel ] . offset ] ) ;
 }