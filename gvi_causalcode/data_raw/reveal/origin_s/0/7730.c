static inline Quantum GetPixelOpacity ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ AlphaPixelChannel ] . traits != BlendPixelTrait ) return ( QuantumRange - OpaqueAlpha ) ;
 return ( QuantumRange - pixel [ image -> channel_map [ AlphaPixelChannel ] . offset ] ) ;
 }