static int64_t ogg_read_timestamp ( AVFormatContext * s , int stream_index , int64_t * pos_arg , int64_t pos_limit ) {
 struct ogg * ogg = s -> priv_data ;
 AVIOContext * bc = s -> pb ;
 int64_t pts = AV_NOPTS_VALUE ;
 int64_t keypos = - 1 ;
 int i ;
 int pstart , psize ;
 avio_seek ( bc , * pos_arg , SEEK_SET ) ;
 ogg_reset ( s ) ;
 while ( avio_tell ( bc ) <= pos_limit && ! ogg_packet ( s , & i , & pstart , & psize , pos_arg ) ) {
 if ( i == stream_index ) {
 struct ogg_stream * os = ogg -> streams + stream_index ;
 if ( ( os -> flags & OGG_FLAG_EOS ) && ! ( os -> flags & OGG_FLAG_BOS ) && os -> codec == & ff_ogm_video_codec ) continue ;
 pts = ogg_calc_pts ( s , i , NULL ) ;
 ogg_validate_keyframe ( s , i , pstart , psize ) ;
 if ( os -> pflags & AV_PKT_FLAG_KEY ) {
 keypos = * pos_arg ;
 }
 else if ( os -> keyframe_seek ) {
 if ( keypos >= 0 ) * pos_arg = keypos ;
 else pts = AV_NOPTS_VALUE ;
 }
 }
 if ( pts != AV_NOPTS_VALUE ) break ;
 }
 ogg_reset ( s ) ;
 return pts ;
 }