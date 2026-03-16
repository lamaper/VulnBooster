static void ogg_validate_keyframe ( AVFormatContext * s , int idx , int pstart , int psize ) {
 struct ogg * ogg = s -> priv_data ;
 struct ogg_stream * os = ogg -> streams + idx ;
 int invalid = 0 ;
 if ( psize ) {
 switch ( s -> streams [ idx ] -> codec -> codec_id ) {
 case AV_CODEC_ID_THEORA : invalid = ! ! ( os -> pflags & AV_PKT_FLAG_KEY ) != ! ( os -> buf [ pstart ] & 0x40 ) ;
 break ;
 case AV_CODEC_ID_VP8 : invalid = ! ! ( os -> pflags & AV_PKT_FLAG_KEY ) != ! ( os -> buf [ pstart ] & 1 ) ;
 }
 if ( invalid ) {
 os -> pflags ^= AV_PKT_FLAG_KEY ;
 av_log ( s , AV_LOG_WARNING , "Broken file, %skeyframe not correctly marked.\n" , ( os -> pflags & AV_PKT_FLAG_KEY ) ? "" : "non-" ) ;
 }
 }
 }