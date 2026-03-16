static int yop_copy_previous_block ( YopDecContext * s , int linesize , int copy_tag ) {
 uint8_t * bufptr ;
 bufptr = s -> dstptr + motion_vector [ copy_tag ] [ 0 ] + linesize * motion_vector [ copy_tag ] [ 1 ] ;
 if ( bufptr < s -> dstbuf ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "YOP: cannot decode, file probably corrupt\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 s -> dstptr [ 0 ] = bufptr [ 0 ] ;
 s -> dstptr [ 1 ] = bufptr [ 1 ] ;
 s -> dstptr [ linesize ] = bufptr [ linesize ] ;
 s -> dstptr [ linesize + 1 ] = bufptr [ linesize + 1 ] ;
 return 0 ;
 }