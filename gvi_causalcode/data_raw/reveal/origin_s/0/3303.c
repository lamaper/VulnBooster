static inline Quantum GetPixelWriteMask ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ WriteMaskPixelChannel ] . traits == UndefinedPixelTrait ) return ( ( Quantum ) QuantumRange ) ;
 return ( pixel [ image -> channel_map [ WriteMaskPixelChannel ] . offset ] ) ;
 }