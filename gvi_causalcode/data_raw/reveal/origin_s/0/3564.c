static inline void SetPixelAlpha ( const Image * restrict image , const Quantum alpha , Quantum * restrict pixel ) {
 if ( image -> channel_map [ AlphaPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ AlphaPixelChannel ] . offset ] = alpha ;
 }