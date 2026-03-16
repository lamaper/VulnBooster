static int rtp_packetize_spx ( sout_stream_id_sys_t * id , block_t * in ) {
 uint8_t * p_buffer = in -> p_buffer ;
 int i_data_size , i_payload_size , i_payload_padding ;
 i_data_size = i_payload_size = in -> i_buffer ;
 i_payload_padding = 0 ;
 block_t * p_out ;
 if ( in -> i_buffer > rtp_mtu ( id ) ) {
 block_Release ( in ) ;
 return VLC_SUCCESS ;
 }
 if ( i_payload_size % 4 ) {
 i_payload_padding = 4 - ( i_payload_size % 4 ) ;
 i_payload_size += i_payload_padding ;
 }
 p_out = block_Alloc ( 12 + i_payload_size ) ;
 if ( i_payload_padding ) {
 char c_first_pad , c_remaining_pad ;
 c_first_pad = 0x7F ;
 c_remaining_pad = 0xFF ;
 p_out -> p_buffer [ 12 + i_data_size ] = c_first_pad ;
 switch ( i_payload_padding ) {
 case 2 : p_out -> p_buffer [ 12 + i_data_size + 1 ] = c_remaining_pad ;
 break ;
 case 3 : p_out -> p_buffer [ 12 + i_data_size + 1 ] = c_remaining_pad ;
 p_out -> p_buffer [ 12 + i_data_size + 2 ] = c_remaining_pad ;
 break ;
 }
 }
 rtp_packetize_common ( id , p_out , 0 , ( in -> i_pts > VLC_TS_INVALID ? in -> i_pts : in -> i_dts ) ) ;
 memcpy ( & p_out -> p_buffer [ 12 ] , p_buffer , i_data_size ) ;
 p_out -> i_dts = in -> i_dts ;
 p_out -> i_length = in -> i_length ;
 block_Release ( in ) ;
 rtp_packetize_send ( id , p_out ) ;
 return VLC_SUCCESS ;
 }