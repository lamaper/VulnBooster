static gint dissect_aptx ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_item * aptx_item ;
 proto_tree * aptx_tree ;
 proto_item * pitem ;
 bta2dp_codec_info_t * info ;
 gdouble cumulative_frame_duration = 0 ;
 info = ( bta2dp_codec_info_t * ) data ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "APT-X" ) ;
 switch ( pinfo -> p2p_dir ) {
 case P2P_DIR_SENT : col_set_str ( pinfo -> cinfo , COL_INFO , "Sent " ) ;
 break ;
 case P2P_DIR_RECV : col_set_str ( pinfo -> cinfo , COL_INFO , "Rcvd " ) ;
 break ;
 case P2P_DIR_UNKNOWN : col_clear ( pinfo -> cinfo , COL_INFO ) ;
 break ;
 default : col_add_fstr ( pinfo -> cinfo , COL_INFO , "Unknown direction %d " , pinfo -> p2p_dir ) ;
 break ;
 }
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "APT-X" ) ;
 aptx_item = proto_tree_add_item ( tree , proto_aptx , tvb , 0 , - 1 , ENC_NA ) ;
 aptx_tree = proto_item_add_subtree ( aptx_item , ett_aptx ) ;
 proto_tree_add_item ( aptx_tree , hf_aptx_data , tvb , 0 , - 1 , ENC_NA ) ;
 if ( info && info -> configuration && info -> configuration_length >= 9 ) {
 gboolean fail = FALSE ;
 gdouble expected_speed_data ;
 gdouble frame_duration ;
 gdouble frame_length = 2 * 2 * 4 ;
 gint number_of_channels ;
 gint frequency ;
 gint sample_bits ;
 switch ( info -> configuration [ 8 ] >> 4 ) {
 case 0x01 : frequency = 48000 ;
 break ;
 case 0x02 : frequency = 44100 ;
 break ;
 case 0x04 : frequency = 32000 ;
 break ;
 case 0x08 : frequency = 16000 ;
 break ;
 default : fail = TRUE ;
 }
 if ( fail ) return tvb_reported_length ( tvb ) ;
 switch ( info -> configuration [ 8 ] & 0x0F ) {
 case 0x01 : case 0x02 : case 0x04 : number_of_channels = 2 ;
 break ;
 case 0x08 : number_of_channels = 1 ;
 break ;
 default : fail = TRUE ;
 }
 if ( fail ) return tvb_reported_length ( tvb ) ;
 sample_bits = 16 ;
 expected_speed_data = frequency * ( sample_bits / 8.0 ) * number_of_channels ;
 frame_duration = ( ( ( double ) frame_length / ( double ) expected_speed_data ) * 1000.0 ) ;
 cumulative_frame_duration = ( tvb_reported_length ( tvb ) / 4.0 ) * frame_duration ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_cumulative_frame_duration , tvb , 0 , 0 , cumulative_frame_duration ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 if ( info && info -> previous_media_packet_info && info -> current_media_packet_info ) {
 nstime_t delta ;
 nstime_delta ( & delta , & pinfo -> abs_ts , & info -> previous_media_packet_info -> abs_ts ) ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_delta_time , tvb , 0 , 0 , nstime_to_msec ( & delta ) ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_avrcp_song_position , tvb , 0 , 0 , info -> previous_media_packet_info -> avrcp_song_position ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 nstime_delta ( & delta , & pinfo -> abs_ts , & info -> previous_media_packet_info -> first_abs_ts ) ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_delta_time_from_the_beginning , tvb , 0 , 0 , nstime_to_msec ( & delta ) ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 if ( ! pinfo -> fd -> flags . visited ) info -> current_media_packet_info -> cumulative_frame_duration += cumulative_frame_duration ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_cumulative_duration , tvb , 0 , 0 , info -> previous_media_packet_info -> cumulative_frame_duration ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_double ( aptx_tree , hf_aptx_diff , tvb , 0 , 0 , info -> previous_media_packet_info -> cumulative_frame_duration - nstime_to_msec ( & delta ) ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 }
 return tvb_reported_length ( tvb ) ;
 }