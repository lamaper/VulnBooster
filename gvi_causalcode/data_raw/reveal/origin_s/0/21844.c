static int encode_frame ( VC2EncContext * s , AVPacket * avpkt , const AVFrame * frame , const char * aux_data , const int header_size , int field ) {
 int i , ret ;
 int64_t max_frame_bytes ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 s -> transform_args [ i ] . ctx = s ;
 s -> transform_args [ i ] . field = field ;
 s -> transform_args [ i ] . plane = & s -> plane [ i ] ;
 s -> transform_args [ i ] . idata = frame -> data [ i ] ;
 s -> transform_args [ i ] . istride = frame -> linesize [ i ] ;
 }
 s -> avctx -> execute ( s -> avctx , dwt_plane , s -> transform_args , NULL , 3 , sizeof ( TransformArgs ) ) ;
 max_frame_bytes = header_size + calc_slice_sizes ( s ) ;
 if ( field < 2 ) {
 ret = ff_alloc_packet2 ( s -> avctx , avpkt , max_frame_bytes << s -> interlaced , max_frame_bytes << s -> interlaced ) ;
 if ( ret ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "Error getting output packet.\n" ) ;
 return ret ;
 }
 init_put_bits ( & s -> pb , avpkt -> data , avpkt -> size ) ;
 }
 encode_parse_info ( s , DIRAC_PCODE_SEQ_HEADER ) ;
 encode_seq_header ( s ) ;
 if ( aux_data ) {
 encode_parse_info ( s , DIRAC_PCODE_AUX ) ;
 avpriv_put_string ( & s -> pb , aux_data , 1 ) ;
 }
 encode_parse_info ( s , DIRAC_PCODE_PICTURE_HQ ) ;
 encode_picture_start ( s ) ;
 encode_slices ( s ) ;
 encode_parse_info ( s , DIRAC_PCODE_END_SEQ ) ;
 return 0 ;
 }