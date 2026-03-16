static inline void SetPixelCr ( const Image * restrict image , const Quantum cr , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ CrPixelChannel ] . offset ] = cr ;
 }