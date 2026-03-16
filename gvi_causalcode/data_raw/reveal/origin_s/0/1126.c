static inline void SetPixelMagenta ( const Image * restrict image , const Quantum magenta , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ MagentaPixelChannel ] . offset ] = magenta ;
 }