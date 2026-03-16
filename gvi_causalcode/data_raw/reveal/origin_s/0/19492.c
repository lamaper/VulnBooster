static inline void SetPixelGray ( const Image * restrict image , const Quantum gray , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ GrayPixelChannel ] . offset ] = gray ;
 }