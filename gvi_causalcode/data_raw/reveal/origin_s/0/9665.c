static inline void GetPixelInfoPixel ( const Image * restrict image , const Quantum * restrict pixel , PixelInfo * restrict pixel_info ) {
 pixel_info -> colorspace = image -> colorspace ;
 pixel_info -> fuzz = image -> fuzz ;
 pixel_info -> red = ( MagickRealType ) pixel [ image -> channel_map [ RedPixelChannel ] . offset ] ;
 pixel_info -> green = ( MagickRealType ) pixel [ image -> channel_map [ GreenPixelChannel ] . offset ] ;
 pixel_info -> blue = ( MagickRealType ) pixel [ image -> channel_map [ BluePixelChannel ] . offset ] ;
 pixel_info -> black = 0.0f ;
 if ( image -> channel_map [ BlackPixelChannel ] . traits != UndefinedPixelTrait ) pixel_info -> black = ( MagickRealType ) pixel [ image -> channel_map [ BlackPixelChannel ] . offset ] ;
 pixel_info -> alpha = ( MagickRealType ) OpaqueAlpha ;
 pixel_info -> alpha_trait = UndefinedPixelTrait ;
 if ( image -> channel_map [ AlphaPixelChannel ] . traits != UndefinedPixelTrait ) {
 pixel_info -> alpha = ( MagickRealType ) pixel [ image -> channel_map [ AlphaPixelChannel ] . offset ] ;
 pixel_info -> alpha_trait = BlendPixelTrait ;
 }
 pixel_info -> index = 0.0f ;
 if ( image -> channel_map [ IndexPixelChannel ] . traits != UndefinedPixelTrait ) pixel_info -> index = ( MagickRealType ) pixel [ image -> channel_map [ IndexPixelChannel ] . offset ] ;
 }