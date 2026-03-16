static inline void SetPixelWriteMask ( const Image * restrict image , const Quantum mask , Quantum * restrict pixel ) {
 if ( image -> channel_map [ WriteMaskPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ WriteMaskPixelChannel ] . offset ] = mask ;
 }