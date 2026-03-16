static void mp_get_code ( MotionPixelsContext * mp , GetBitContext * gb , int size , int code ) {
 while ( get_bits1 ( gb ) ) {
 ++ size ;
 if ( size > mp -> max_codes_bits ) {
 av_log ( mp -> avctx , AV_LOG_ERROR , "invalid code size %d/%d\n" , size , mp -> max_codes_bits ) ;
 return ;
 }
 code <<= 1 ;
 mp_get_code ( mp , gb , size , code + 1 ) ;
 }
 if ( mp -> current_codes_count >= MAX_HUFF_CODES ) {
 av_log ( mp -> avctx , AV_LOG_ERROR , "too many codes\n" ) ;
 return ;
 }
 mp -> codes [ mp -> current_codes_count ] . code = code ;
 mp -> codes [ mp -> current_codes_count ++ ] . size = size ;
 }