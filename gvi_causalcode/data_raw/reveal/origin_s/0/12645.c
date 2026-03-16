static int mpeg4_decode_profile_level ( MpegEncContext * s , GetBitContext * gb ) {
 int profile_and_level_indication ;
 profile_and_level_indication = get_bits ( gb , 8 ) ;
 s -> avctx -> profile = ( profile_and_level_indication & 0xf0 ) >> 4 ;
 s -> avctx -> level = ( profile_and_level_indication & 0x0f ) ;
 if ( s -> avctx -> profile == 0 && s -> avctx -> level == 8 ) {
 s -> avctx -> level = 0 ;
 }
 return 0 ;
 }