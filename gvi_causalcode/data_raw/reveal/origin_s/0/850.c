static int rtp_packetize_jpeg ( sout_stream_id_sys_t * id , block_t * in ) {
 uint8_t * p_data = in -> p_buffer ;
 int i_data = in -> i_buffer ;
 uint8_t * bufend = p_data + i_data ;
 const uint8_t * qtables = NULL ;
 int nb_qtables = 0 ;
 int off = 0 ;
 int y_sampling_factor ;
 int type ;
 int w = 0 ;
 int h = 0 ;
 int restart_interval ;
 int dri_found = 0 ;
 if ( GetWBE ( p_data ) != 0xffd8 ) goto error ;
 p_data += 2 ;
 i_data -= 2 ;
 int header_finished = 0 ;
 while ( ! header_finished && p_data + 4 <= bufend ) {
 uint16_t marker = GetWBE ( p_data ) ;
 uint8_t * section = p_data + 2 ;
 int section_size = GetWBE ( section ) ;
 uint8_t * section_body = p_data + 4 ;
 if ( section + section_size > bufend ) goto error ;
 assert ( ( marker & 0xff00 ) == 0xff00 ) ;
 switch ( marker ) {
 case 0xffdb : if ( section_body [ 0 ] ) goto error ;
 nb_qtables = section_size / 65 ;
 qtables = section_body ;
 break ;
 case 0xffc0 : {
 int height = GetWBE ( & section_body [ 1 ] ) ;
 int width = GetWBE ( & section_body [ 3 ] ) ;
 if ( width > 2040 || height > 2040 ) {
 goto error ;
 }
 w = ( ( width + 7 ) & ~ 7 ) >> 3 ;
 h = ( ( height + 7 ) & ~ 7 ) >> 3 ;
 if ( section_body [ 5 ] != 3 ) goto error ;
 for ( int j = 0 ;
 j < 3 ;
 j ++ ) {
 if ( section_body [ 6 + j * 3 ] == 1 ) {
 y_sampling_factor = section_body [ 6 + j * 3 + 1 ] ;
 }
 else if ( section_body [ 6 + j * 3 + 1 ] != 0x11 ) {
 goto error ;
 }
 }
 break ;
 }
 case 0xffdd : restart_interval = GetWBE ( section_body ) ;
 dri_found = 1 ;
 break ;
 case 0xffda : header_finished = 1 ;
 break ;
 }
 p_data += 2 + section_size ;
 i_data -= 2 + section_size ;
 }
 if ( ! header_finished ) goto error ;
 if ( ! w || ! h ) goto error ;
 switch ( y_sampling_factor ) {
 case 0x22 : type = 1 ;
 break ;
 case 0x21 : type = 0 ;
 break ;
 default : goto error ;
 }
 if ( dri_found ) type += 64 ;
 while ( i_data ) {
 int hdr_size = 8 + dri_found * 4 ;
 if ( off == 0 && nb_qtables ) hdr_size += 4 + 64 * nb_qtables ;
 int i_payload = __MIN ( i_data , ( int ) ( rtp_mtu ( id ) - hdr_size ) ) ;
 if ( i_payload <= 0 ) return VLC_EGENERIC ;
 block_t * out = block_Alloc ( 12 + hdr_size + i_payload ) ;
 if ( out == NULL ) return VLC_ENOMEM ;
 uint8_t * p = out -> p_buffer + 12 ;
 SetDWBE ( p , off & 0x00ffffff ) ;
 p += 4 ;
 * p ++ = type ;
 * p ++ = 255 ;
 * p ++ = w ;
 * p ++ = h ;
 if ( dri_found ) {
 SetWBE ( p , restart_interval ) ;
 p += 2 ;
 SetWBE ( p , 0xffff ) ;
 p += 2 ;
 }
 if ( off == 0 && nb_qtables ) {
 * p ++ = 0 ;
 * p ++ = 0 ;
 SetWBE ( p , 64 * nb_qtables ) ;
 p += 2 ;
 for ( int i = 0 ;
 i < nb_qtables ;
 i ++ ) {
 memcpy ( p , & qtables [ 65 * i + 1 ] , 64 ) ;
 p += 64 ;
 }
 }
 rtp_packetize_common ( id , out , ( i_payload == i_data ) , ( in -> i_pts > VLC_TS_INVALID ? in -> i_pts : in -> i_dts ) ) ;
 memcpy ( p , p_data , i_payload ) ;
 out -> i_dts = in -> i_dts ;
 out -> i_length = in -> i_length ;
 rtp_packetize_send ( id , out ) ;
 p_data += i_payload ;
 i_data -= i_payload ;
 off += i_payload ;
 }
 block_Release ( in ) ;
 return VLC_SUCCESS ;
 error : block_Release ( in ) ;
 return VLC_EGENERIC ;
 }