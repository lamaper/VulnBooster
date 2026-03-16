void usage_exit ( ) {
 int i ;
 fprintf ( stderr , "Usage: %s <options> -o dst_filename src_filename \n" , exec_name ) ;
 fprintf ( stderr , "\nOptions:\n" ) ;
 arg_show_usage ( stderr , main_args ) ;
 fprintf ( stderr , "\nEncoder Global Options:\n" ) ;
 arg_show_usage ( stderr , global_args ) ;
 fprintf ( stderr , "\nRate Control Options:\n" ) ;
 arg_show_usage ( stderr , rc_args ) ;
 fprintf ( stderr , "\nTwopass Rate Control Options:\n" ) ;
 arg_show_usage ( stderr , rc_twopass_args ) ;
 fprintf ( stderr , "\nKeyframe Placement Options:\n" ) ;
 arg_show_usage ( stderr , kf_args ) ;

 arg_show_usage ( stderr , vp8_args ) ;

 arg_show_usage ( stderr , vp9_args ) ;

 fprintf ( stderr , "\nIncluded encoders:\n\n" ) ;
 for ( i = 0 ;
 i < get_vpx_encoder_count ( ) ;
 ++ i ) {
 const VpxInterface * const encoder = get_vpx_encoder_by_index ( i ) ;
 fprintf ( stderr , " %-6s - %s\n" , encoder -> name , vpx_codec_iface_name ( encoder -> codec_interface ( ) ) ) ;
 }
 exit ( EXIT_FAILURE ) ;
 }