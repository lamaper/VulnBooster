static uint32_t ffmpeg_CodecTag ( vlc_fourcc_t fcc ) {
 uint8_t * p = ( uint8_t * ) & fcc ;
 return p [ 0 ] | ( p [ 1 ] << 8 ) | ( p [ 2 ] << 16 ) | ( p [ 3 ] << 24 ) ;
 }