static inline void SetPixelL ( const Image * restrict image , const Quantum L , Quantum * restrict pixel ) {
 if ( image -> channel_map [ LPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ LPixelChannel ] . offset ] = L ;
 }