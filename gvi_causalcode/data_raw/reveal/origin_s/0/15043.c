static inline void SetPixelY ( const Image * restrict image , const Quantum y , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ YPixelChannel ] . offset ] = y ;
 }