static inline void SetPixelChannelAttributes ( const Image * restrict image , const PixelChannel channel , const PixelTrait traits , const ssize_t offset ) {
 image -> channel_map [ offset ] . channel = channel ;
 image -> channel_map [ channel ] . offset = offset ;
 image -> channel_map [ channel ] . traits = traits ;
 }