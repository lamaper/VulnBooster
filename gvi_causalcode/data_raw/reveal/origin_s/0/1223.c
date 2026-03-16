void ff_h263_encode_picture_header ( MpegEncContext * s , int picture_number ) {
 int format , coded_frame_rate , coded_frame_rate_base , i , temp_ref ;
 int best_clock_code = 1 ;
 int best_divisor = 60 ;
 int best_error = INT_MAX ;
 if ( s -> h263_plus ) {
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 int div , error ;
 div = ( s -> avctx -> time_base . num * 1800000LL + 500LL * s -> avctx -> time_base . den ) / ( ( 1000LL + i ) * s -> avctx -> time_base . den ) ;
 div = av_clip ( div , 1 , 127 ) ;
 error = FFABS ( s -> avctx -> time_base . num * 1800000LL - ( 1000LL + i ) * s -> avctx -> time_base . den * div ) ;
 if ( error < best_error ) {
 best_error = error ;
 best_divisor = div ;
 best_clock_code = i ;
 }
 }
 }
 s -> custom_pcf = best_clock_code != 1 || best_divisor != 60 ;
 coded_frame_rate = 1800000 ;
 coded_frame_rate_base = ( 1000 + best_clock_code ) * best_divisor ;
 avpriv_align_put_bits ( & s -> pb ) ;
 s -> ptr_lastgob = put_bits_ptr ( & s -> pb ) ;
 put_bits ( & s -> pb , 22 , 0x20 ) ;
 temp_ref = s -> picture_number * ( int64_t ) coded_frame_rate * s -> avctx -> time_base . num / ( coded_frame_rate_base * ( int64_t ) s -> avctx -> time_base . den ) ;
 put_sbits ( & s -> pb , 8 , temp_ref ) ;
 put_bits ( & s -> pb , 1 , 1 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 format = ff_match_2uint16 ( ff_h263_format , FF_ARRAY_ELEMS ( ff_h263_format ) , s -> width , s -> height ) ;
 if ( ! s -> h263_plus ) {
 put_bits ( & s -> pb , 3 , format ) ;
 put_bits ( & s -> pb , 1 , ( s -> pict_type == AV_PICTURE_TYPE_P ) ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , s -> obmc ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 5 , s -> qscale ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 }
 else {
 int ufep = 1 ;
 put_bits ( & s -> pb , 3 , 7 ) ;
 put_bits ( & s -> pb , 3 , ufep ) ;
 if ( format == 8 ) put_bits ( & s -> pb , 3 , 6 ) ;
 else put_bits ( & s -> pb , 3 , format ) ;
 put_bits ( & s -> pb , 1 , s -> custom_pcf ) ;
 put_bits ( & s -> pb , 1 , s -> umvplus ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , s -> obmc ) ;
 put_bits ( & s -> pb , 1 , s -> h263_aic ) ;
 put_bits ( & s -> pb , 1 , s -> loop_filter ) ;
 put_bits ( & s -> pb , 1 , s -> h263_slice_structured ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , s -> alt_inter_vlc ) ;
 put_bits ( & s -> pb , 1 , s -> modified_quant ) ;
 put_bits ( & s -> pb , 1 , 1 ) ;
 put_bits ( & s -> pb , 3 , 0 ) ;
 put_bits ( & s -> pb , 3 , s -> pict_type == AV_PICTURE_TYPE_P ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 put_bits ( & s -> pb , 1 , s -> no_rounding ) ;
 put_bits ( & s -> pb , 2 , 0 ) ;
 put_bits ( & s -> pb , 1 , 1 ) ;
 put_bits ( & s -> pb , 1 , 0 ) ;
 if ( format == 8 ) {
 s -> aspect_ratio_info = ff_h263_aspect_to_info ( s -> avctx -> sample_aspect_ratio ) ;
 put_bits ( & s -> pb , 4 , s -> aspect_ratio_info ) ;
 put_bits ( & s -> pb , 9 , ( s -> width >> 2 ) - 1 ) ;
 put_bits ( & s -> pb , 1 , 1 ) ;
 put_bits ( & s -> pb , 9 , ( s -> height >> 2 ) ) ;
 if ( s -> aspect_ratio_info == FF_ASPECT_EXTENDED ) {
 put_bits ( & s -> pb , 8 , s -> avctx -> sample_aspect_ratio . num ) ;
 put_bits ( & s -> pb , 8 , s -> avctx -> sample_aspect_ratio . den ) ;
 }
 }
 if ( s -> custom_pcf ) {
 if ( ufep ) {
 put_bits ( & s -> pb , 1 , best_clock_code ) ;
 put_bits ( & s -> pb , 7 , best_divisor ) ;
 }
 put_sbits ( & s -> pb , 2 , temp_ref >> 8 ) ;
 }
 if ( s -> umvplus ) put_bits ( & s -> pb , 2 , 1 ) ;
 if ( s -> h263_slice_structured ) put_bits ( & s -> pb , 2 , 0 ) ;
 put_bits ( & s -> pb , 5 , s -> qscale ) ;
 }
 put_bits ( & s -> pb , 1 , 0 ) ;
 if ( s -> h263_slice_structured ) {
 put_bits ( & s -> pb , 1 , 1 ) ;
 assert ( s -> mb_x == 0 && s -> mb_y == 0 ) ;
 ff_h263_encode_mba ( s ) ;
 put_bits ( & s -> pb , 1 , 1 ) ;
 }
 if ( s -> h263_aic ) {
 s -> y_dc_scale_table = s -> c_dc_scale_table = ff_aic_dc_scale_table ;
 }
 else {
 s -> y_dc_scale_table = s -> c_dc_scale_table = ff_mpeg1_dc_scale_table ;
 }
 }