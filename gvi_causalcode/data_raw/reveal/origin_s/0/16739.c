static void set_rate_control_metrics ( struct RateControlMetrics * rc , vpx_codec_enc_cfg_t * cfg ) {
 unsigned int i = 0 ;
 const double framerate = cfg -> g_timebase . den / cfg -> g_timebase . num ;
 rc -> layer_framerate [ 0 ] = framerate / cfg -> ts_rate_decimator [ 0 ] ;
 rc -> layer_pfb [ 0 ] = 1000.0 * cfg -> ts_target_bitrate [ 0 ] / rc -> layer_framerate [ 0 ] ;
 for ( i = 0 ;
 i < cfg -> ts_number_layers ;
 ++ i ) {
 if ( i > 0 ) {
 rc -> layer_framerate [ i ] = framerate / cfg -> ts_rate_decimator [ i ] ;
 rc -> layer_pfb [ i ] = 1000.0 * ( cfg -> ts_target_bitrate [ i ] - cfg -> ts_target_bitrate [ i - 1 ] ) / ( rc -> layer_framerate [ i ] - rc -> layer_framerate [ i - 1 ] ) ;
 }
 rc -> layer_input_frames [ i ] = 0 ;
 rc -> layer_enc_frames [ i ] = 0 ;
 rc -> layer_tot_enc_frames [ i ] = 0 ;
 rc -> layer_encoding_bitrate [ i ] = 0.0 ;
 rc -> layer_avg_frame_size [ i ] = 0.0 ;
 rc -> layer_avg_rate_mismatch [ i ] = 0.0 ;
 }
 }