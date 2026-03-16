static void set_result_format_version ( ulong new_version ) {
 switch ( new_version ) {
 case 1 : break ;
 case 2 : break ;
 default : die ( "Version format %lu has not yet been implemented" , new_version ) ;
 break ;
 }
 opt_result_format_version = new_version ;
 }