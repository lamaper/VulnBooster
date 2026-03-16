static int get_buffer ( AVCodecContext * avctx , Picture * pic ) {
 SVQ3Context * s = avctx -> priv_data ;
 H264Context * h = & s -> h ;
 const int big_mb_num = h -> mb_stride * ( h -> mb_height + 1 ) + 1 ;
 const int mb_array_size = h -> mb_stride * h -> mb_height ;
 const int b4_stride = h -> mb_width * 4 + 1 ;
 const int b4_array_size = b4_stride * h -> mb_height * 4 ;
 int ret ;
 if ( ! pic -> motion_val_buf [ 0 ] ) {
 int i ;
 pic -> mb_type_buf = av_buffer_allocz ( ( big_mb_num + h -> mb_stride ) * sizeof ( uint32_t ) ) ;
 if ( ! pic -> mb_type_buf ) return AVERROR ( ENOMEM ) ;
 pic -> mb_type = ( uint32_t * ) pic -> mb_type_buf -> data + 2 * h -> mb_stride + 1 ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 pic -> motion_val_buf [ i ] = av_buffer_allocz ( 2 * ( b4_array_size + 4 ) * sizeof ( int16_t ) ) ;
 pic -> ref_index_buf [ i ] = av_buffer_allocz ( 4 * mb_array_size ) ;
 if ( ! pic -> motion_val_buf [ i ] || ! pic -> ref_index_buf [ i ] ) {
 ret = AVERROR ( ENOMEM ) ;
 goto fail ;
 }
 pic -> motion_val [ i ] = ( int16_t ( * ) [ 2 ] ) pic -> motion_val_buf [ i ] -> data + 4 ;
 pic -> ref_index [ i ] = pic -> ref_index_buf [ i ] -> data ;
 }
 }
 pic -> f . motion_subsample_log2 = 2 ;
 pic -> reference = ! ( h -> pict_type == AV_PICTURE_TYPE_B ) ;
 ret = ff_get_buffer ( avctx , & pic -> f , pic -> reference ? AV_GET_BUFFER_FLAG_REF : 0 ) ;
 if ( ret < 0 ) goto fail ;
 if ( ! h -> edge_emu_buffer ) {
 h -> edge_emu_buffer = av_mallocz ( pic -> f . linesize [ 0 ] * 17 ) ;
 if ( ! h -> edge_emu_buffer ) return AVERROR ( ENOMEM ) ;
 }
 h -> linesize = pic -> f . linesize [ 0 ] ;
 h -> uvlinesize = pic -> f . linesize [ 1 ] ;
 return 0 ;
 fail : free_picture ( avctx , pic ) ;
 return ret ;
 }