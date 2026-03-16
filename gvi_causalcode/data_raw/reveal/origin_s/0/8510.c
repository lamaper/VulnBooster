int ff_msmpeg4_decode_picture_header ( MpegEncContext * s ) {
 int code ;
 if ( s -> msmpeg4_version == 1 ) {
 int start_code = get_bits_long ( & s -> gb , 32 ) ;
 if ( start_code != 0x00000100 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "invalid startcode\n" ) ;
 return - 1 ;
 }
 skip_bits ( & s -> gb , 5 ) ;
 }
 s -> pict_type = get_bits ( & s -> gb , 2 ) + 1 ;
 if ( s -> pict_type != AV_PICTURE_TYPE_I && s -> pict_type != AV_PICTURE_TYPE_P ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "invalid picture type\n" ) ;
 return - 1 ;
 }

 static int had_i = 0 ;
 if ( s -> pict_type == AV_PICTURE_TYPE_I ) had_i = 1 ;
 if ( ! had_i ) return - 1 ;
 }

 if ( s -> qscale == 0 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "invalid qscale\n" ) ;
 return - 1 ;
 }
 if ( s -> pict_type == AV_PICTURE_TYPE_I ) {
 code = get_bits ( & s -> gb , 5 ) ;
 if ( s -> msmpeg4_version == 1 ) {
 if ( code == 0 || code > s -> mb_height ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "invalid slice height %d\n" , code ) ;
 return - 1 ;
 }
 s -> slice_height = code ;
 }
 else {
 if ( code < 0x17 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "error, slice code was %X\n" , code ) ;
 return - 1 ;
 }
 s -> slice_height = s -> mb_height / ( code - 0x16 ) ;
 }
 switch ( s -> msmpeg4_version ) {
 case 1 : case 2 : s -> rl_chroma_table_index = 2 ;
 s -> rl_table_index = 2 ;
 s -> dc_table_index = 0 ;
 / ot used break ;
 case 3 : s -> rl_chroma_table_index = decode012 ( & s -> gb ) ;
 s -> rl_table_index = decode012 ( & s -> gb ) ;
 s -> dc_table_index = get_bits1 ( & s -> gb ) ;
 break ;
 case 4 : ff_msmpeg4_decode_ext_header ( s , ( 2 + 5 + 5 + 17 + 7 ) / 8 ) ;
 if ( s -> bit_rate > MBAC_BITRATE ) s -> per_mb_rl_table = get_bits1 ( & s -> gb ) ;
 else s -> per_mb_rl_table = 0 ;
 if ( ! s -> per_mb_rl_table ) {
 s -> rl_chroma_table_index = decode012 ( & s -> gb ) ;
 s -> rl_table_index = decode012 ( & s -> gb ) ;
 }
 s -> dc_table_index = get_bits1 ( & s -> gb ) ;
 s -> inter_intra_pred = 0 ;
 break ;
 }
 s -> no_rounding = 1 ;
 if ( s -> avctx -> debug & FF_DEBUG_PICT_INFO ) av_log ( s -> avctx , AV_LOG_DEBUG , "qscale:%d rlc:%d rl:%d dc:%d mbrl:%d slice:%d \n" , s -> qscale , s -> rl_chroma_table_index , s -> rl_table_index , s -> dc_table_index , s -> per_mb_rl_table , s -> slice_height ) ;
 }
 else {
 switch ( s -> msmpeg4_version ) {
 case 1 : case 2 : if ( s -> msmpeg4_version == 1 ) s -> use_skip_mb_code = 1 ;
 else s -> use_skip_mb_code = get_bits1 ( & s -> gb ) ;
 s -> rl_table_index = 2 ;
 s -> rl_chroma_table_index = s -> rl_table_index ;
 s -> dc_table_index = 0 ;
 / ot used s -> mv_table_index = 0 ;
 break ;
 case 3 : s -> use_skip_mb_code = get_bits1 ( & s -> gb ) ;
 s -> rl_table_index = decode012 ( & s -> gb ) ;
 s -> rl_chroma_table_index = s -> rl_table_index ;
 s -> dc_table_index = get_bits1 ( & s -> gb ) ;
 s -> mv_table_index = get_bits1 ( & s -> gb ) ;
 break ;
 case 4 : s -> use_skip_mb_code = get_bits1 ( & s -> gb ) ;
 if ( s -> bit_rate > MBAC_BITRATE ) s -> per_mb_rl_table = get_bits1 ( & s -> gb ) ;
 else s -> per_mb_rl_table = 0 ;
 if ( ! s -> per_mb_rl_table ) {
 s -> rl_table_index = decode012 ( & s -> gb ) ;
 s -> rl_chroma_table_index = s -> rl_table_index ;
 }
 s -> dc_table_index = get_bits1 ( & s -> gb ) ;
 s -> mv_table_index = get_bits1 ( & s -> gb ) ;
 s -> inter_intra_pred = ( s -> width * s -> height < 320 * 240 && s -> bit_rate <= II_BITRATE ) ;
 break ;
 }
 if ( s -> avctx -> debug & FF_DEBUG_PICT_INFO ) av_log ( s -> avctx , AV_LOG_DEBUG , "skip:%d rl:%d rlc:%d dc:%d mv:%d mbrl:%d qp:%d \n" , s -> use_skip_mb_code , s -> rl_table_index , s -> rl_chroma_table_index , s -> dc_table_index , s -> mv_table_index , s -> per_mb_rl_table , s -> qscale ) ;
 if ( s -> flipflop_rounding ) {
 s -> no_rounding ^= 1 ;
 }
 else {
 s -> no_rounding = 0 ;
 }
 }
 av_dlog ( s -> avctx , "%d %d %d %d %d\n" , s -> pict_type , s -> bit_rate , s -> inter_intra_pred , s -> width , s -> height ) ;
 s -> esc3_level_length = 0 ;
 s -> esc3_run_length = 0 ;
 return 0 ;
 }