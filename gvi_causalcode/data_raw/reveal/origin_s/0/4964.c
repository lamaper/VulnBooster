static inline MagickBooleanType IsPixelMonochrome ( const Image * restrict image , const Quantum * restrict pixel ) {
 MagickRealType blue , green , red ;
 red = ( MagickRealType ) pixel [ image -> channel_map [ RedPixelChannel ] . offset ] ;
 if ( ( AbsolutePixelValue ( red ) >= MagickEpsilon ) || ( AbsolutePixelValue ( red - QuantumRange ) >= MagickEpsilon ) ) return ( MagickFalse ) ;
 green = ( MagickRealType ) pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] ;
 blue = ( MagickRealType ) pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ;
 if ( ( AbsolutePixelValue ( red - green ) < MagickEpsilon ) && ( AbsolutePixelValue ( green - blue ) < MagickEpsilon ) ) return ( MagickTrue ) ;
 return ( MagickFalse ) ;
 }