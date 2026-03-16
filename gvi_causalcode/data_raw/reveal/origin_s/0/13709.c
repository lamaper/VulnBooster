ATF_TP_ADD_TCS ( tp ) {
 ATF_TP_ADD_TC ( tp , option_refcnt ) ;
 ATF_TP_ADD_TC ( tp , pretty_print_option ) ;
 return ( atf_no_error ( ) ) ;
 }