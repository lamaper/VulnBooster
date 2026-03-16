static inline void SetPixelBlack ( const Image * restrict image , const Quantum black , Quantum * restrict pixel ) {
 if ( image -> channel_map [ BlackPixelChannel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ BlackPixelChannel ] . offset ] = black ;
 }