static inline Quantum GetPixelCb ( const Image * restrict image , const Quantum * restrict pixel ) {
 return ( pixel [ image -> channel_map [ CbPixelChannel ] . offset ] ) ;
 }