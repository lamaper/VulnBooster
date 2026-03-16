static inline MagickBooleanType IsPixelInfoEquivalent ( const PixelInfo * restrict p , const PixelInfo * restrict q ) {
 if ( ( p -> alpha_trait != UndefinedPixelTrait ) && ( q -> alpha_trait == UndefinedPixelTrait ) && ( AbsolutePixelValue ( p -> alpha - OpaqueAlpha ) >= MagickEpsilon ) ) return ( MagickFalse ) ;
 if ( ( q -> alpha_trait != UndefinedPixelTrait ) && ( p -> alpha_trait == UndefinedPixelTrait ) && ( AbsolutePixelValue ( q -> alpha - OpaqueAlpha ) ) >= MagickEpsilon ) return ( MagickFalse ) ;
 if ( ( p -> alpha_trait != UndefinedPixelTrait ) && ( q -> alpha_trait != UndefinedPixelTrait ) ) {
 if ( AbsolutePixelValue ( p -> alpha - q -> alpha ) >= MagickEpsilon ) return ( MagickFalse ) ;
 if ( AbsolutePixelValue ( p -> alpha - TransparentAlpha ) < MagickEpsilon ) return ( MagickTrue ) ;
 }
 if ( AbsolutePixelValue ( p -> red - q -> red ) >= MagickEpsilon ) return ( MagickFalse ) ;
 if ( AbsolutePixelValue ( p -> green - q -> green ) >= MagickEpsilon ) return ( MagickFalse ) ;
 if ( AbsolutePixelValue ( p -> blue - q -> blue ) >= MagickEpsilon ) return ( MagickFalse ) ;
 if ( ( p -> colorspace == CMYKColorspace ) && ( AbsolutePixelValue ( p -> black - q -> black ) >= MagickEpsilon ) ) return ( MagickFalse ) ;
 return ( MagickTrue ) ;
 }