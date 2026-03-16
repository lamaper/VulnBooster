static inline void SetPixelYellow ( const Image * restrict image , const Quantum yellow , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ YellowPixelChannel ] . offset ] = yellow ;
 }