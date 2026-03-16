static inline void SetPixela ( const Image * restrict image , const Quantum a , Quantum * restrict pixel ) {
 if ( image -> channel_map [ aPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ aPixelChannel ] . offset ] = a ;
 }