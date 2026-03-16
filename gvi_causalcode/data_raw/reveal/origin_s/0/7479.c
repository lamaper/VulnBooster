static void printout_rate_control_summary ( struct RateControlMetrics * rc , vpx_codec_enc_cfg_t * cfg , int frame_cnt ) {
 unsigned int i = 0 ;
 int tot_num_frames = 0 ;
 printf ( "Total number of processed frames: %d\n\n" , frame_cnt - 1 ) ;
 printf ( "Rate control layer stats for %d layer(s):\n\n" , cfg -> ts_number_layers ) ;
 for ( i = 0 ;
 i < cfg -> ts_number_layers ;
 ++ i ) {
 const int num_dropped = ( i > 0 ) ? ( rc -> layer_input_frames [ i ] - rc -> layer_enc_frames [ i ] ) : ( rc -> layer_input_frames [ i ] - rc -> layer_enc_frames [ i ] - 1 ) ;
 tot_num_frames += rc -> layer_input_frames [ i ] ;
 rc -> layer_encoding_bitrate [ i ] = 0.001 * rc -> layer_framerate [ i ] * rc -> layer_encoding_bitrate [ i ] / tot_num_frames ;
 rc -> layer_avg_frame_size [ i ] = rc -> layer_avg_frame_size [ i ] / rc -> layer_enc_frames [ i ] ;
 rc -> layer_avg_rate_mismatch [ i ] = 100.0 * rc -> layer_avg_rate_mismatch [ i ] / rc -> layer_enc_frames [ i ] ;
 printf ( "For layer#: %d \n" , i ) ;
 printf ( "Bitrate (target vs actual): %d %f \n" , cfg -> ts_target_bitrate [ i ] , rc -> layer_encoding_bitrate [ i ] ) ;
 printf ( "Average frame size (target vs actual): %f %f \n" , rc -> layer_pfb [ i ] , rc -> layer_avg_frame_size [ i ] ) ;
 printf ( "Average rate_mismatch: %f \n" , rc -> layer_avg_rate_mismatch [ i ] ) ;
 printf ( "Number of input frames, encoded (non-key) frames, " "and perc dropped frames: %d %d %f \n" , rc -> layer_input_frames [ i ] , rc -> layer_enc_frames [ i ] , 100.0 * num_dropped / rc -> layer_input_frames [ i ] ) ;
 printf ( "\n" ) ;
 }
 if ( ( frame_cnt - 1 ) != tot_num_frames ) die ( "Error: Number of input frames not equal to output! \n" ) ;
 }