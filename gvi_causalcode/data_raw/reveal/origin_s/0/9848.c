static int ogg_save ( AVFormatContext * s ) {
 struct ogg * ogg = s -> priv_data ;
 struct ogg_state * ost = av_malloc ( sizeof ( * ost ) + ( ogg -> nstreams - 1 ) * sizeof ( * ogg -> streams ) ) ;
 int i ;
 int ret = 0 ;
 if ( ! ost ) return AVERROR ( ENOMEM ) ;
 ost -> pos = avio_tell ( s -> pb ) ;
 ost -> curidx = ogg -> curidx ;
 ost -> next = ogg -> state ;
 ost -> nstreams = ogg -> nstreams ;
 memcpy ( ost -> streams , ogg -> streams , ogg -> nstreams * sizeof ( * ogg -> streams ) ) ;
 for ( i = 0 ;
 i < ogg -> nstreams ;
 i ++ ) {
 struct ogg_stream * os = ogg -> streams + i ;
 os -> buf = av_mallocz ( os -> bufsize + AV_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( os -> buf ) memcpy ( os -> buf , ost -> streams [ i ] . buf , os -> bufpos ) ;
 else ret = AVERROR ( ENOMEM ) ;
 os -> new_metadata = NULL ;
 os -> new_metadata_size = 0 ;
 }
 ogg -> state = ost ;
 if ( ret < 0 ) ogg_restore ( s , 0 ) ;
 return ret ;
 }