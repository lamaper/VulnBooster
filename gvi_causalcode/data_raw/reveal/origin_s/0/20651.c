static inline void SetPixelGreen ( const Image * restrict image , const Quantum green , Quantum * restrict pixel ) {
 pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] = green ;
 }