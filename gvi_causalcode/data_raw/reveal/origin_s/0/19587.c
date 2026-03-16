static inline void SetPixelReadMask ( const Image * restrict image , const Quantum mask , Quantum * restrict pixel ) {
 if ( image -> channel_map [ ReadMaskPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ ReadMaskPixelChannel ] . offset ] = mask ;
 }