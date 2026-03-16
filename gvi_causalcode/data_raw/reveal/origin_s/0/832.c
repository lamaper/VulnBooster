static int svq3_decode_slice_header ( AVCodecContext * avctx ) {
 SVQ3Context * s = avctx -> priv_data ;
 H264Context * h = & s -> h ;
 const int mb_xy = h -> mb_xy ;
 int i , header ;
 unsigned slice_id ;
 header = get_bits ( & h -> gb , 8 ) ;
 if ( ( ( header & 0x9F ) != 1 && ( header & 0x9F ) != 2 ) || ( header & 0x60 ) == 0 ) {
 av_log ( avctx , AV_LOG_ERROR , "unsupported slice header (%02X)\n" , header ) ;
 return - 1 ;
 }
 else {
 int length = header >> 5 & 3 ;
 s -> next_slice_index = get_bits_count ( & h -> gb ) + 8 * show_bits ( & h -> gb , 8 * length ) + 8 * length ;
 if ( s -> next_slice_index > h -> gb . size_in_bits ) {
 av_log ( avctx , AV_LOG_ERROR , "slice after bitstream end\n" ) ;
 return - 1 ;
 }
 h -> gb . size_in_bits = s -> next_slice_index - 8 * ( length - 1 ) ;
 skip_bits ( & h -> gb , 8 ) ;
 if ( s -> watermark_key ) {
 uint32_t header = AV_RL32 ( & h -> gb . buffer [ ( get_bits_count ( & h -> gb ) >> 3 ) + 1 ] ) ;
 AV_WL32 ( & h -> gb . buffer [ ( get_bits_count ( & h -> gb ) >> 3 ) + 1 ] , header ^ s -> watermark_key ) ;
 }
 if ( length > 0 ) {
 memcpy ( ( uint8_t * ) & h -> gb . buffer [ get_bits_count ( & h -> gb ) >> 3 ] , & h -> gb . buffer [ h -> gb . size_in_bits >> 3 ] , length - 1 ) ;
 }
 skip_bits_long ( & h -> gb , 0 ) ;
 }
 if ( ( slice_id = svq3_get_ue_golomb ( & h -> gb ) ) >= 3 ) {
 av_log ( h -> avctx , AV_LOG_ERROR , "illegal slice type %d \n" , slice_id ) ;
 return - 1 ;
 }
 h -> slice_type = golomb_to_pict_type [ slice_id ] ;
 if ( ( header & 0x9F ) == 2 ) {
 i = ( h -> mb_num < 64 ) ? 6 : ( 1 + av_log2 ( h -> mb_num - 1 ) ) ;
 h -> mb_skip_run = get_bits ( & h -> gb , i ) - ( h -> mb_y * h -> mb_width + h -> mb_x ) ;
 }
 else {
 skip_bits1 ( & h -> gb ) ;
 h -> mb_skip_run = 0 ;
 }
 h -> slice_num = get_bits ( & h -> gb , 8 ) ;
 h -> qscale = get_bits ( & h -> gb , 5 ) ;
 s -> adaptive_quant = get_bits1 ( & h -> gb ) ;
 skip_bits1 ( & h -> gb ) ;
 if ( s -> unknown_flag ) skip_bits1 ( & h -> gb ) ;
 skip_bits1 ( & h -> gb ) ;
 skip_bits ( & h -> gb , 2 ) ;
 while ( get_bits1 ( & h -> gb ) ) skip_bits ( & h -> gb , 8 ) ;
 if ( h -> mb_x > 0 ) {
 memset ( h -> intra4x4_pred_mode + h -> mb2br_xy [ mb_xy - 1 ] + 3 , - 1 , 4 * sizeof ( int8_t ) ) ;
 memset ( h -> intra4x4_pred_mode + h -> mb2br_xy [ mb_xy - h -> mb_x ] , - 1 , 8 * sizeof ( int8_t ) * h -> mb_x ) ;
 }
 if ( h -> mb_y > 0 ) {
 memset ( h -> intra4x4_pred_mode + h -> mb2br_xy [ mb_xy - h -> mb_stride ] , - 1 , 8 * sizeof ( int8_t ) * ( h -> mb_width - h -> mb_x ) ) ;
 if ( h -> mb_x > 0 ) h -> intra4x4_pred_mode [ h -> mb2br_xy [ mb_xy - h -> mb_stride - 1 ] + 3 ] = - 1 ;
 }
 return 0 ;
 }