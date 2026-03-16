static inline int wmv2_decode_motion ( Wmv2Context * w , int * mx_ptr , int * my_ptr ) {
 MpegEncContext * const s = & w -> s ;
 int ret ;
 ret = ff_msmpeg4_decode_motion ( s , mx_ptr , my_ptr ) ;
 if ( ret < 0 ) return - 1 ;
 if ( ( ( ( * mx_ptr ) | ( * my_ptr ) ) & 1 ) && s -> mspel ) w -> hshift = get_bits1 ( & s -> gb ) ;
 else w -> hshift = 0 ;
 return 0 ;
 }