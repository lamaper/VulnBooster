static inline MagickRealType GetPixelLuminance ( const Image * restrict image , const Quantum * restrict pixel ) {
 MagickRealType blue , green , red ;
 if ( image -> colorspace == GRAYColorspace ) return ( ( MagickRealType ) pixel [ image -> channel_map [ GrayPixelChannel ] . offset ] ) ;
 if ( image -> colorspace != sRGBColorspace ) return ( 0.212656f * pixel [ image -> channel_map [ RedPixelChannel ] . offset ] + 0.715158f * pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] + 0.072186f * pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ) ;
 red = DecodePixelGamma ( ( MagickRealType ) pixel [ image -> channel_map [ RedPixelChannel ] . offset ] ) ;
 green = DecodePixelGamma ( ( MagickRealType ) pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] ) ;
 blue = DecodePixelGamma ( ( MagickRealType ) pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ) ;
 return ( 0.212656f * red + 0.715158f * green + 0.072186f * blue ) ;
 }