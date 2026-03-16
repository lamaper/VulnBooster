static inline void SetPixelIndex ( const Image * restrict image , const Quantum index , Quantum * restrict pixel ) {
 if ( image -> channel_map [ IndexPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ IndexPixelChannel ] . offset ] = index ;
 }