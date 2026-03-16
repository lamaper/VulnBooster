static inline PixelTrait GetPixelChannelTraits ( const Image * restrict image , const PixelChannel channel ) {
 return ( image -> channel_map [ channel ] . traits ) ;
 }