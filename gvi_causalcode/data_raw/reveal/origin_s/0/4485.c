static inline ssize_t GetPixelChannelOffset ( const Image * restrict image , const PixelChannel channel ) {
 return ( image -> channel_map [ channel ] . offset ) ;
 }