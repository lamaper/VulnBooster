static int ogg_new_stream ( AVFormatContext * s , uint32_t serial ) {
 struct ogg * ogg = s -> priv_data ;
 int idx = ogg -> nstreams ;
 AVStream * st ;
 struct ogg_stream * os ;
 size_t size ;
 if ( ogg -> state ) {
 av_log ( s , AV_LOG_ERROR , "New streams are not supposed to be added " "in between Ogg context save/restore operations.\n" ) ;
 return AVERROR_BUG ;
 }
 if ( av_size_mult ( ogg -> nstreams + 1 , sizeof ( * ogg -> streams ) , & size ) < 0 || ! ( os = av_realloc ( ogg -> streams , size ) ) ) return AVERROR ( ENOMEM ) ;
 ogg -> streams = os ;
 os = ogg -> streams + idx ;
 memset ( os , 0 , sizeof ( * os ) ) ;
 os -> serial = serial ;
 os -> bufsize = DECODER_BUFFER_SIZE ;
 os -> buf = av_malloc ( os -> bufsize + AV_INPUT_BUFFER_PADDING_SIZE ) ;
 os -> header = - 1 ;
 os -> start_granule = OGG_NOGRANULE_VALUE ;
 if ( ! os -> buf ) return AVERROR ( ENOMEM ) ;
 st = avformat_new_stream ( s , NULL ) ;
 if ( ! st ) {
 av_freep ( & os -> buf ) ;
 return AVERROR ( ENOMEM ) ;
 }
 st -> id = idx ;
 avpriv_set_pts_info ( st , 64 , 1 , 1000000 ) ;
 ogg -> nstreams ++ ;
 return idx ;
 }