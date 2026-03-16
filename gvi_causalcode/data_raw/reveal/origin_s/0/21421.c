static void ffmpeg_InitCodec ( decoder_t * p_dec ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 int i_size = p_dec -> fmt_in . i_extra ;
 if ( ! i_size ) return ;
 if ( p_sys -> i_codec_id == AV_CODEC_ID_SVQ3 ) {
 uint8_t * p ;
 p_sys -> p_context -> extradata_size = i_size + 12 ;
 p = p_sys -> p_context -> extradata = av_malloc ( p_sys -> p_context -> extradata_size + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! p ) return ;
 memcpy ( & p [ 0 ] , "SVQ3" , 4 ) ;
 memset ( & p [ 4 ] , 0 , 8 ) ;
 memcpy ( & p [ 12 ] , p_dec -> fmt_in . p_extra , i_size ) ;
 if ( p_sys -> p_context -> extradata_size > 0x5a && strncmp ( ( char * ) & p [ 0x56 ] , "SMI " , 4 ) ) {
 uint8_t * psz = & p [ 0x52 ] ;
 while ( psz < & p [ p_sys -> p_context -> extradata_size - 8 ] ) {
 int i_size = GetDWBE ( psz ) ;
 if ( i_size <= 1 ) {
 break ;
 }
 if ( ! strncmp ( ( char * ) & psz [ 4 ] , "SMI " , 4 ) ) {
 memmove ( & p [ 0x52 ] , psz , & p [ p_sys -> p_context -> extradata_size ] - psz ) ;
 break ;
 }
 psz += i_size ;
 }
 }
 }
 else {
 p_sys -> p_context -> extradata_size = i_size ;
 p_sys -> p_context -> extradata = av_malloc ( i_size + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( p_sys -> p_context -> extradata ) {
 memcpy ( p_sys -> p_context -> extradata , p_dec -> fmt_in . p_extra , i_size ) ;
 memset ( p_sys -> p_context -> extradata + i_size , 0 , FF_INPUT_BUFFER_PADDING_SIZE ) ;
 }
 }
 }