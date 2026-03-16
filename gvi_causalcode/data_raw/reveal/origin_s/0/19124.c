static inline void SetPixelBlue ( const Image * restrict image , const Quantum blue , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ BluePixelChannel ] . offset ] = blue ;
 }