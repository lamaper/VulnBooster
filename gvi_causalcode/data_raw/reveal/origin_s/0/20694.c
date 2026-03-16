static inline Quantum GetPixelReadMask ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ ReadMaskPixelChannel ] . traits == UndefinedPixelTrait ) return ( ( Quantum ) QuantumRange ) ;
 return ( pixel [ image -> channel_map [ ReadMaskPixelChannel ] . offset ] ) ;
 }