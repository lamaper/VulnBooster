static void open_output_file ( struct stream_state * stream , struct VpxEncoderConfig * global ) {
 const char * fn = stream -> config . out_fn ;
 const struct vpx_codec_enc_cfg * const cfg = & stream -> config . cfg ;
 if ( cfg -> g_pass == VPX_RC_FIRST_PASS ) return ;
 stream -> file = strcmp ( fn , "-" ) ? fopen ( fn , "wb" ) : set_binary_mode ( stdout ) ;
 if ( ! stream -> file ) fatal ( "Failed to open output file" ) ;
 if ( stream -> config . write_webm && fseek ( stream -> file , 0 , SEEK_CUR ) ) fatal ( "WebM output to pipes not supported." ) ;

 stream -> ebml . stream = stream -> file ;
 write_webm_file_header ( & stream -> ebml , cfg , & global -> framerate , stream -> config . stereo_fmt , global -> codec -> fourcc ) ;
 }

 ivf_write_file_header ( stream -> file , cfg , global -> codec -> fourcc , 0 ) ;
 }
 }