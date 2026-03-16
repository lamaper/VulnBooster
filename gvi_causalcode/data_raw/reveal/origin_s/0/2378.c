static int mxpeg_check_dimensions ( MXpegDecodeContext * s , MJpegDecodeContext * jpg , AVFrame * reference_ptr ) {
 if ( ( jpg -> width + 0x0F ) >> 4 != s -> mb_width || ( jpg -> height + 0x0F ) >> 4 != s -> mb_height ) {
 av_log ( jpg -> avctx , AV_LOG_ERROR , "Picture dimensions stored in SOF and MXM mismatch\n" ) ;
 return AVERROR ( EINVAL ) ;
 }
 if ( reference_ptr -> data [ 0 ] ) {
 int i ;
 for ( i = 0 ;
 i < MAX_COMPONENTS ;
 ++ i ) {
 if ( ( ! reference_ptr -> data [ i ] ^ ! jpg -> picture_ptr -> data [ i ] ) || reference_ptr -> linesize [ i ] != jpg -> picture_ptr -> linesize [ i ] ) {
 av_log ( jpg -> avctx , AV_LOG_ERROR , "Dimensions of current and reference picture mismatch\n" ) ;
 return AVERROR ( EINVAL ) ;
 }
 }
 }
 return 0 ;
 }