static inline MagickRealType GetPixelLuma ( const Image * restrict image , const Quantum * restrict pixel ) {
 if ( image -> colorspace == GRAYColorspace ) return ( ( MagickRealType ) pixel [ image -> channel_map [ GrayPixelChannel ] . offset ] ) ;
 return ( 0.212656f * pixel [ image -> channel_map [ RedPixelChannel ] . offset ] + 0.715158f * pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] + 0.072186f * pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ) ;
 }