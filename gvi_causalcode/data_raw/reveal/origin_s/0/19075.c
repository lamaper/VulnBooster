static int ogg_probe ( AVProbeData * p ) {
 if ( ! memcmp ( "OggS" , p -> buf , 5 ) && p -> buf [ 5 ] <= 0x7 ) return AVPROBE_SCORE_MAX ;
 return 0 ;
 }