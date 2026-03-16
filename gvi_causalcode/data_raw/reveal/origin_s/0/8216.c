static inline Quantum GetPixelAlpha ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ AlphaPixelChannel ] . traits == UndefinedPixelTrait ) return ( OpaqueAlpha ) ;
 return ( pixel [ image -> channel_map [ AlphaPixelChannel ] . offset ] ) ;
 }