static inline void SetPixelCyan ( const Image * restrict image , const Quantum cyan , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ CyanPixelChannel ] . offset ] = cyan ;
 }