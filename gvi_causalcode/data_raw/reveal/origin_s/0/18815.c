static void SetupOutput ( decoder_t * p_dec , block_t * p_block ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 if ( p_dec -> fmt_out . audio . i_rate != p_sys -> i_rate ) {
 msg_Info ( p_dec , "AAC channels: %d samplerate: %d" , p_sys -> i_channels , p_sys -> i_rate ) ;
 const mtime_t i_end_date = date_Get ( & p_sys -> end_date ) ;
 date_Init ( & p_sys -> end_date , p_sys -> i_rate , 1 ) ;
 date_Set ( & p_sys -> end_date , i_end_date ) ;
 }
 p_dec -> fmt_out . audio . i_rate = p_sys -> i_rate ;
 p_dec -> fmt_out . audio . i_channels = p_sys -> i_channels ;
 p_dec -> fmt_out . audio . i_bytes_per_frame = p_sys -> i_frame_size ;
 p_dec -> fmt_out . audio . i_frame_length = p_sys -> i_frame_length ;

 p_dec -> fmt_out . audio . i_physical_channels = p_sys -> i_channels_conf ;

 p_block -> i_length = date_Increment ( & p_sys -> end_date , p_sys -> i_frame_length ) - p_block -> i_pts ;
 }