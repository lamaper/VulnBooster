static int ogg_replace_stream ( AVFormatContext * s , uint32_t serial , int nsegs ) {
 struct ogg * ogg = s -> priv_data ;
 struct ogg_stream * os ;
 const struct ogg_codec * codec ;
 int i = 0 ;
 if ( s -> pb -> seekable ) {
 uint8_t magic [ 8 ] ;
 int64_t pos = avio_tell ( s -> pb ) ;
 avio_skip ( s -> pb , nsegs ) ;
 avio_read ( s -> pb , magic , sizeof ( magic ) ) ;
 avio_seek ( s -> pb , pos , SEEK_SET ) ;
 codec = ogg_find_codec ( magic , sizeof ( magic ) ) ;
 if ( ! codec ) {
 av_log ( s , AV_LOG_ERROR , "Cannot identify new stream\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 for ( i = 0 ;
 i < ogg -> nstreams ;
 i ++ ) {
 if ( ogg -> streams [ i ] . codec == codec ) break ;
 }
 if ( i >= ogg -> nstreams ) return ogg_new_stream ( s , serial ) ;
 }
 else if ( ogg -> nstreams != 1 ) {
 avpriv_report_missing_feature ( s , "Changing stream parameters in multistream ogg" ) ;
 return AVERROR_PATCHWELCOME ;
 }
 os = & ogg -> streams [ i ] ;
 os -> serial = serial ;
 return i ;

 bufsize = os -> bufsize ;
 codec = os -> codec ;
 if ( ! ogg -> state || ogg -> state -> streams [ i ] . private != os -> private ) av_freep ( & ogg -> streams [ i ] . private ) ;
 memset ( os , 0 , sizeof ( * os ) ) ;
 os -> serial = serial ;
 os -> bufsize = bufsize ;
 os -> buf = buf ;
 os -> header = - 1 ;
 os -> codec = codec ;
 return i ;
