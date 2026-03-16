static inline void SetPixelChannel ( const Image * restrict image , const PixelChannel channel , const Quantum quantum , Quantum * restrict pixel ) {
 if ( image -> channel_map [ channel ] . traits != UndefinedPixelTrait ) pixel [ image -> channel_map [ channel ] . offset ] = quantum ;
 }