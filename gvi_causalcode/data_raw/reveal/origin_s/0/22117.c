static inline PixelTrait GetPixelGrayTraits ( const Image * restrict image ) {
 return ( image -> channel_map [ GrayPixelChannel ] . traits ) ;
 }