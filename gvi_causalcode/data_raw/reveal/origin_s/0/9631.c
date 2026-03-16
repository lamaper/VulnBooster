static void write_profile ( BITSTREAM_PROFILE profile , struct vp9_write_bit_buffer * wb ) {
 switch ( profile ) {
 case PROFILE_0 : vp9_wb_write_literal ( wb , 0 , 2 ) ;
 break ;
 case PROFILE_1 : vp9_wb_write_literal ( wb , 2 , 2 ) ;
 break ;
 case PROFILE_2 : vp9_wb_write_literal ( wb , 1 , 2 ) ;
 break ;
 case PROFILE_3 : vp9_wb_write_literal ( wb , 6 , 3 ) ;
 break ;
 default : assert ( 0 ) ;
 }
 }