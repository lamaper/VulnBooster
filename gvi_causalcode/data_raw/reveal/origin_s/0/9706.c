static int dca_decode_block ( DCAContext * s , int base_channel , int block_index ) {
 int ret ;
 if ( s -> current_subframe >= s -> subframes ) {
 av_log ( s -> avctx , AV_LOG_DEBUG , "check failed: %i>%i" , s -> current_subframe , s -> subframes ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( ! s -> current_subsubframe ) {


 }


 s -> current_subsubframe ++ ;
 if ( s -> current_subsubframe >= s -> subsubframes [ s -> current_subframe ] ) {
 s -> current_subsubframe = 0 ;
 s -> current_subframe ++ ;
 }
 if ( s -> current_subframe >= s -> subframes ) {


 }
 return 0 ;
 }