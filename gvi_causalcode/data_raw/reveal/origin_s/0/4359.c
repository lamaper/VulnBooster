static int dca_subframe_footer ( DCAContext * s , int base_channel ) {
 int aux_data_count = 0 , i ;
 if ( ! base_channel ) {
 if ( s -> timestamp ) skip_bits_long ( & s -> gb , 32 ) ;
 if ( s -> aux_data ) aux_data_count = get_bits ( & s -> gb , 6 ) ;
 for ( i = 0 ;
 i < aux_data_count ;
 i ++ ) get_bits ( & s -> gb , 8 ) ;
 if ( s -> crc_present && ( s -> downmix || s -> dynrange ) ) get_bits ( & s -> gb , 16 ) ;
 }
 return 0 ;
 }