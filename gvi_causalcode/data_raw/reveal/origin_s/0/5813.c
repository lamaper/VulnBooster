static inline void SetPixelRed ( const Image * restrict image , const Quantum red , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ RedPixelChannel ] . offset ] = red ;
 }