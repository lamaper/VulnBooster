static inline PixelTrait GetPixelCbTraits ( const Image * restrict image ) {
 return ( image -> channel_map [ CbPixelChannel ] . traits ) ;
 }