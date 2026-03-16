static inline MagickBooleanType IsPixelEquivalent ( const Image * restrict image , const Quantum * restrict p , const PixelInfo * restrict q ) {
 MagickRealType blue , green , red ;
 red = ( MagickRealType ) p [ image -> channel_map [ RedPixelChannel ] . offset ] ;
 green = ( MagickRealType ) p [ image -> channel_map [ GreenPixelChannel ] . offset ] ;
 blue = ( MagickRealType ) p [ image -> channel_map [ BluePixelChannel ] . offset ] ;
 if ( ( AbsolutePixelValue ( red - q -> red ) < MagickEpsilon ) && ( AbsolutePixelValue ( green - q -> green ) < MagickEpsilon ) && ( AbsolutePixelValue ( blue - q -> blue ) < MagickEpsilon ) ) return ( MagickTrue ) ;
 return ( MagickFalse ) ;
 }