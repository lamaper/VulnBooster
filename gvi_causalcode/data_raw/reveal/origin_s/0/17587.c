static inline void SetPixelCb ( const Image * restrict image , const Quantum cb , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ CbPixelChannel ] . offset ] = cb ;
 }