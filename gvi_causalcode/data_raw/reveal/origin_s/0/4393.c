static inline MagickRealType GetPixelInfoLuma ( const PixelInfo * restrict pixel ) {
 MagickRealType blue , green , red ;
 if ( pixel -> colorspace == GRAYColorspace ) return ( pixel -> red ) ;
 if ( pixel -> colorspace == sRGBColorspace ) return ( 0.212656f * pixel -> red + 0.715158f * pixel -> green + 0.072186f * pixel -> blue ) ;
 red = EncodePixelGamma ( pixel -> red ) ;
 green = EncodePixelGamma ( pixel -> green ) ;
 blue = EncodePixelGamma ( pixel -> blue ) ;
 return ( 0.212656f * red + 0.715158f * green + 0.072186f * blue ) ;
 }