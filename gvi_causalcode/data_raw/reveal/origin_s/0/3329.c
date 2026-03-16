static block_t * PacketizeStreamBlock ( decoder_t * p_dec , block_t * * pp_block ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 uint8_t p_header [ ADTS_HEADER_SIZE + LOAS_HEADER_SIZE ] ;
 block_t * p_out_buffer ;
 uint8_t * p_buf ;
 if ( ! pp_block || ! * pp_block ) return NULL ;
 if ( ( * pp_block ) -> i_flags & ( BLOCK_FLAG_DISCONTINUITY | BLOCK_FLAG_CORRUPTED ) ) {
 if ( ( * pp_block ) -> i_flags & BLOCK_FLAG_CORRUPTED ) {
 p_sys -> i_state = STATE_NOSYNC ;
 block_BytestreamEmpty ( & p_sys -> bytestream ) ;
 }
 date_Set ( & p_sys -> end_date , 0 ) ;
 block_Release ( * pp_block ) ;
 return NULL ;
 }
 if ( ! date_Get ( & p_sys -> end_date ) && ( * pp_block ) -> i_pts <= VLC_TS_INVALID ) {
 block_Release ( * pp_block ) ;
 return NULL ;
 }
 block_BytestreamPush ( & p_sys -> bytestream , * pp_block ) ;
 for ( ;
 ;
 ) {
 switch ( p_sys -> i_state ) {
 case STATE_NOSYNC : while ( block_PeekBytes ( & p_sys -> bytestream , p_header , 2 ) == VLC_SUCCESS ) {
 if ( p_header [ 0 ] == 0xff && ( p_header [ 1 ] & 0xf6 ) == 0xf0 ) {
 if ( p_sys -> i_type != TYPE_ADTS ) msg_Dbg ( p_dec , "detected ADTS format" ) ;
 p_sys -> i_state = STATE_SYNC ;
 p_sys -> i_type = TYPE_ADTS ;
 break ;
 }
 else if ( p_header [ 0 ] == 0x56 && ( p_header [ 1 ] & 0xe0 ) == 0xe0 ) {
 if ( p_sys -> i_type != TYPE_LOAS ) msg_Dbg ( p_dec , "detected LOAS format" ) ;
 p_sys -> i_state = STATE_SYNC ;
 p_sys -> i_type = TYPE_LOAS ;
 break ;
 }
 block_SkipByte ( & p_sys -> bytestream ) ;
 }
 if ( p_sys -> i_state != STATE_SYNC ) {
 block_BytestreamFlush ( & p_sys -> bytestream ) ;
 return NULL ;
 }
 case STATE_SYNC : p_sys -> i_pts = p_sys -> bytestream . p_block -> i_pts ;
 if ( p_sys -> i_pts > VLC_TS_INVALID && p_sys -> i_pts != date_Get ( & p_sys -> end_date ) ) date_Set ( & p_sys -> end_date , p_sys -> i_pts ) ;
 p_sys -> i_state = STATE_HEADER ;
 break ;
 case STATE_HEADER : if ( p_sys -> i_type == TYPE_ADTS ) {
 if ( block_PeekBytes ( & p_sys -> bytestream , p_header , ADTS_HEADER_SIZE ) != VLC_SUCCESS ) return NULL ;
 p_sys -> i_frame_size = ADTSSyncInfo ( p_dec , p_header , & p_sys -> i_channels , & p_sys -> i_rate , & p_sys -> i_frame_length , & p_sys -> i_header_size ) ;
 }
 else {
 assert ( p_sys -> i_type == TYPE_LOAS ) ;
 if ( block_PeekBytes ( & p_sys -> bytestream , p_header , LOAS_HEADER_SIZE ) != VLC_SUCCESS ) return NULL ;
 p_sys -> i_frame_size = LOASSyncInfo ( p_header , & p_sys -> i_header_size ) ;
 }
 if ( p_sys -> i_frame_size <= 0 ) {
 msg_Dbg ( p_dec , "emulated sync word" ) ;
 block_SkipByte ( & p_sys -> bytestream ) ;
 p_sys -> i_state = STATE_NOSYNC ;
 break ;
 }
 p_sys -> i_state = STATE_NEXT_SYNC ;
 case STATE_NEXT_SYNC : if ( p_sys -> bytestream . p_block == NULL ) {
 p_sys -> i_state = STATE_NOSYNC ;
 block_BytestreamFlush ( & p_sys -> bytestream ) ;
 return NULL ;
 }
 if ( block_PeekOffsetBytes ( & p_sys -> bytestream , p_sys -> i_frame_size + p_sys -> i_header_size , p_header , 2 ) != VLC_SUCCESS ) return NULL ;
 assert ( ( p_sys -> i_type == TYPE_ADTS ) || ( p_sys -> i_type == TYPE_LOAS ) ) ;
 if ( ( ( p_sys -> i_type == TYPE_ADTS ) && ( p_header [ 0 ] != 0xff || ( p_header [ 1 ] & 0xf6 ) != 0xf0 ) ) || ( ( p_sys -> i_type == TYPE_LOAS ) && ( p_header [ 0 ] != 0x56 || ( p_header [ 1 ] & 0xe0 ) != 0xe0 ) ) ) {
 msg_Dbg ( p_dec , "emulated sync word " "(no sync on following frame)" ) ;
 p_sys -> i_state = STATE_NOSYNC ;
 block_SkipByte ( & p_sys -> bytestream ) ;
 break ;
 }
 p_sys -> i_state = STATE_SEND_DATA ;
 break ;
 case STATE_GET_DATA : if ( block_WaitBytes ( & p_sys -> bytestream , p_sys -> i_frame_size + p_sys -> i_header_size ) != VLC_SUCCESS ) return NULL ;
 p_sys -> i_state = STATE_SEND_DATA ;
 case STATE_SEND_DATA : p_out_buffer = block_Alloc ( p_sys -> i_frame_size ) ;
 if ( ! p_out_buffer ) {
 return NULL ;
 }
 p_buf = p_out_buffer -> p_buffer ;
 block_SkipBytes ( & p_sys -> bytestream , p_sys -> i_header_size ) ;
 if ( p_sys -> i_type == TYPE_ADTS ) {
 block_GetBytes ( & p_sys -> bytestream , p_buf , p_sys -> i_frame_size ) ;
 }
 else {
 assert ( p_sys -> i_type == TYPE_LOAS ) ;
 block_GetBytes ( & p_sys -> bytestream , p_buf , p_sys -> i_frame_size ) ;
 p_out_buffer -> i_buffer = LOASParse ( p_dec , p_buf , p_sys -> i_frame_size ) ;
 if ( p_out_buffer -> i_buffer <= 0 ) {
 if ( ! p_sys -> b_latm_cfg ) msg_Warn ( p_dec , "waiting for header" ) ;
 block_Release ( p_out_buffer ) ;
 p_out_buffer = NULL ;
 p_sys -> i_state = STATE_NOSYNC ;
 break ;
 }
 }
 SetupOutput ( p_dec , p_out_buffer ) ;
 if ( p_sys -> i_pts == p_sys -> bytestream . p_block -> i_pts ) p_sys -> i_pts = p_sys -> bytestream . p_block -> i_pts = VLC_TS_INVALID ;
 * pp_block = block_BytestreamPop ( & p_sys -> bytestream ) ;
 p_sys -> i_state = STATE_NOSYNC ;
 return p_out_buffer ;
 }
 }
 return NULL ;
 }