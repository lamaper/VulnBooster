static inline void SetPixelb ( const Image * restrict image , const Quantum b , Quantum * restrict pixel ) {
 if ( image -> channel_map [ bPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ bPixelChannel ] . offset ] = b ;
 }