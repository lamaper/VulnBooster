static void output_stats ( FIRSTPASS_STATS * stats , struct vpx_codec_pkt_list * pktlist ) {
 struct vpx_codec_cx_pkt pkt ;
 pkt . kind = VPX_CODEC_STATS_PKT ;
 pkt . data . twopass_stats . buf = stats ;
 pkt . data . twopass_stats . sz = sizeof ( FIRSTPASS_STATS ) ;
 vpx_codec_pkt_list_add ( pktlist , & pkt ) ;

 FILE * fpfile ;
 fpfile = fopen ( "firstpass.stt" , "a" ) ;
 fprintf ( fpfile , "%12.0f %12.0f %12.0f %12.0f %12.4f %12.4f" "%12.4f %12.4f %12.4f %12.4f %12.4f %12.4f %12.4f" "%12.0f %12.0f %12.4f %12.0f %12.0f %12.4f\n" , stats -> frame , stats -> intra_error , stats -> coded_error , stats -> sr_coded_error , stats -> pcnt_inter , stats -> pcnt_motion , stats -> pcnt_second_ref , stats -> pcnt_neutral , stats -> MVr , stats -> mvr_abs , stats -> MVc , stats -> mvc_abs , stats -> MVrv , stats -> MVcv , stats -> mv_in_out_count , stats -> new_mv_count , stats -> count , stats -> duration ) ;
 fclose ( fpfile ) ;
 }
