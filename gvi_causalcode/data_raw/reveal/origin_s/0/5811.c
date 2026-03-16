static int rate_control ( AVCodecContext * avctx , void * arg ) {
 SliceArgs * slice_dat = arg ;
 VC2EncContext * s = slice_dat -> ctx ;
 const int top = slice_dat -> bits_ceil ;
 const int bottom = slice_dat -> bits_floor ;
 int quant_buf [ 2 ] = {
 - 1 , - 1 }
 ;
 int quant = slice_dat -> quant_idx , step = 1 ;
 int bits_last , bits = count_hq_slice ( slice_dat , quant ) ;
 while ( ( bits > top ) || ( bits < bottom ) ) {
 const int signed_step = bits > top ? + step : - step ;
 quant = av_clip ( quant + signed_step , 0 , s -> q_ceil - 1 ) ;
 bits = count_hq_slice ( slice_dat , quant ) ;
 if ( quant_buf [ 1 ] == quant ) {
 quant = FFMAX ( quant_buf [ 0 ] , quant ) ;
 bits = quant == quant_buf [ 0 ] ? bits_last : bits ;
 break ;
 }
 step = av_clip ( step / 2 , 1 , ( s -> q_ceil - 1 ) / 2 ) ;
 quant_buf [ 1 ] = quant_buf [ 0 ] ;
 quant_buf [ 0 ] = quant ;
 bits_last = bits ;
 }
 slice_dat -> quant_idx = av_clip ( quant , 0 , s -> q_ceil - 1 ) ;
 slice_dat -> bytes = SSIZE_ROUND ( bits >> 3 ) ;
 return 0 ;
 }