static inline PixelChannel GetPixelChannelChannel ( const Image * restrict image , const ssize_t offset ) {
 return ( image -> channel_map [ offset ] . channel ) ;
 }