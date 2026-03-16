void usage_exit ( ) {
 int i ;
 fprintf ( stderr , "Usage: %s <options> filename\n\n" "Options:\n" , exec_name ) ;
 arg_show_usage ( stderr , all_args ) ;

 arg_show_usage ( stderr , vp8_pp_args ) ;

 fprintf ( stderr , "\n\t%%w - Frame width" "\n\t%%h - Frame height" "\n\t%%<n> - Frame number, zero padded to <n> places (1..9)" "\n\n Pattern arguments are only supported in conjunction " "with the --yv12 and\n --i420 options. If the -o option is " "not specified, the output will be\n directed to stdout.\n" ) ;
 fprintf ( stderr , "\nIncluded decoders:\n\n" ) ;
 for ( i = 0 ;
 i < get_vpx_decoder_count ( ) ;
 ++ i ) {
 const VpxInterface * const decoder = get_vpx_decoder_by_index ( i ) ;
 fprintf ( stderr , " %-6s - %s\n" , decoder -> name , vpx_codec_iface_name ( decoder -> codec_interface ( ) ) ) ;
 }
 exit ( EXIT_FAILURE ) ;
 }