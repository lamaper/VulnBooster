static inline Quantum GetPixelBlack ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> channel_map [ BlackPixelChannel ] . traits == UndefinedPixelTrait ) return ( ( Quantum ) 0 ) ;
 return ( pixel [ image -> channel_map [ BlackPixelChannel ] . offset ] ) ;
 }