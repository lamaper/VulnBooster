static inline PixelTrait GetPixelReadMaskTraits ( const Image * restrict image ) {
 return ( image -> channel_map [ ReadMaskPixelChannel ] . traits ) ;
 }