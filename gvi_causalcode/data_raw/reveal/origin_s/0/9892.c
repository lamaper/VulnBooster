static int ogg_new_buf ( struct ogg * ogg , int idx ) {
 struct ogg_stream * os = ogg -> streams + idx ;
 uint8_t * nb = av_malloc ( os -> bufsize + AV_INPUT_BUFFER_PADDING_SIZE ) ;
 int size = os -> bufpos - os -> pstart ;
 if ( ! nb ) return AVERROR ( ENOMEM ) ;
 if ( os -> buf ) {
 memcpy ( nb , os -> buf + os -> pstart , size ) ;
 av_free ( os -> buf ) ;
 }
 os -> buf = nb ;
 os -> bufpos = size ;
 os -> pstart = 0 ;
 return 0 ;
 }