void proto_register_aptx ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_aptx_data , {
 "Data" , "aptx.data" , FT_BYTES , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_cumulative_frame_duration , {
 "Cumulative Frame Duration" , "aptx.cumulative_frame_duration" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_delta_time , {
 "Delta time" , "aptx.delta_time" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_avrcp_song_position , {
 "AVRCP Song Position" , "aptx.avrcp_song_position" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_delta_time_from_the_beginning , {
 "Delta time from the beginning" , "aptx.delta_time_from_the_beginning" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_cumulative_duration , {
 "Cumulative Music Duration" , "aptx.cumulative_music_duration" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , {
 & hf_aptx_diff , {
 "Diff" , "aptx.diff" , FT_DOUBLE , BASE_NONE | BASE_UNIT_STRING , & units_milliseconds , 0x00 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_aptx }
 ;
 proto_aptx = proto_register_protocol ( "APT-X Codec" , "APT-X" , "aptx" ) ;
 proto_register_field_array ( proto_aptx , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 aptx_handle = register_dissector ( "aptx" , dissect_aptx , proto_aptx ) ;
 }