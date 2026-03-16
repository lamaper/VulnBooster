static subpicture_t * ParseText ( decoder_t * p_dec , block_t * p_block ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 subpicture_t * p_spu = NULL ;
 char * psz_subtitle = NULL ;
 if ( p_block -> i_pts <= VLC_TS_INVALID ) {
 msg_Warn ( p_dec , "subtitle without a date" ) ;
 return NULL ;
 }
 if ( p_block -> i_buffer < 1 ) {
 msg_Warn ( p_dec , "no subtitle data" ) ;
 return NULL ;
 }
 psz_subtitle = malloc ( p_block -> i_buffer + 1 ) ;
 if ( psz_subtitle == NULL ) return NULL ;
 memcpy ( psz_subtitle , p_block -> p_buffer , p_block -> i_buffer ) ;
 psz_subtitle [ p_block -> i_buffer ] = '\0' ;
 if ( p_sys -> iconv_handle == ( vlc_iconv_t ) - 1 ) {
 if ( EnsureUTF8 ( psz_subtitle ) == NULL ) {
 msg_Err ( p_dec , "failed to convert subtitle encoding.\n" "Try manually setting a character-encoding " "before you open the file." ) ;
 }
 }
 else {
 if ( p_sys -> b_autodetect_utf8 ) {
 if ( IsUTF8 ( psz_subtitle ) == NULL ) {
 msg_Dbg ( p_dec , "invalid UTF-8 sequence: " "disabling UTF-8 subtitles autodetection" ) ;
 p_sys -> b_autodetect_utf8 = false ;
 }
 }
 if ( ! p_sys -> b_autodetect_utf8 ) {
 size_t inbytes_left = strlen ( psz_subtitle ) ;
 size_t outbytes_left = 6 * inbytes_left ;
 char * psz_new_subtitle = xmalloc ( outbytes_left + 1 ) ;
 char * psz_convert_buffer_out = psz_new_subtitle ;
 const char * psz_convert_buffer_in = psz_subtitle ;
 size_t ret = vlc_iconv ( p_sys -> iconv_handle , & psz_convert_buffer_in , & inbytes_left , & psz_convert_buffer_out , & outbytes_left ) ;
 * psz_convert_buffer_out ++ = '\0' ;
 free ( psz_subtitle ) ;
 if ( ( ret == ( size_t ) ( - 1 ) ) || inbytes_left ) {
 free ( psz_new_subtitle ) ;
 msg_Err ( p_dec , "failed to convert subtitle encoding.\n" "Try manually setting a character-encoding " "before you open the file." ) ;
 return NULL ;
 }
 psz_subtitle = realloc ( psz_new_subtitle , psz_convert_buffer_out - psz_new_subtitle ) ;
 if ( ! psz_subtitle ) psz_subtitle = psz_new_subtitle ;
 }
 }
 p_spu = decoder_NewSubpictureText ( p_dec ) ;
 if ( ! p_spu ) {
 free ( psz_subtitle ) ;
 return NULL ;
 }
 p_spu -> i_start = p_block -> i_pts ;
 p_spu -> i_stop = p_block -> i_pts + p_block -> i_length ;
 p_spu -> b_ephemer = ( p_block -> i_length == 0 ) ;
 p_spu -> b_absolute = false ;
 subpicture_updater_sys_t * p_spu_sys = p_spu -> updater . p_sys ;
 p_spu_sys -> align = SUBPICTURE_ALIGN_BOTTOM | p_sys -> i_align ;
 p_spu_sys -> text = StripTags ( psz_subtitle ) ;
 if ( var_InheritBool ( p_dec , "subsdec-formatted" ) ) p_spu_sys -> html = CreateHtmlSubtitle ( & p_spu_sys -> align , psz_subtitle ) ;
 free ( psz_subtitle ) ;
 return p_spu ;
 }