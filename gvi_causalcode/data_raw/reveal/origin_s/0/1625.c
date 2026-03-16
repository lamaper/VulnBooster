ATF_TC_BODY ( option_refcnt , tc ) {
 struct option_state * options ;
 struct option * option ;
 unsigned code ;
 int refcnt ;
 unsigned char buffer [ 3 ] = {
 15 , 255 , 0 }
 ;
 initialize_common_option_spaces ( ) ;
 options = NULL ;
 if ( ! option_state_allocate ( & options , MDL ) ) {
 atf_tc_fail ( "can't allocate option state" ) ;
 }
 option = NULL ;
 code = 15 ;
 if ( ! option_code_hash_lookup ( & option , dhcp_universe . code_hash , & code , 0 , MDL ) ) {
 atf_tc_fail ( "can't find option 15" ) ;
 }
 if ( option == NULL ) {
 atf_tc_fail ( "option is NULL" ) ;
 }
 refcnt = option -> refcnt ;
 buffer [ 0 ] = 15 ;
 buffer [ 1 ] = 255 ;
 buffer [ 2 ] = 0 ;
 if ( parse_option_buffer ( options , buffer , 3 , & dhcp_universe ) ) {
 atf_tc_fail ( "parse_option_buffer is expected to fail" ) ;
 }
 if ( refcnt != option -> refcnt ) {
 atf_tc_fail ( "refcnt changed from %d to %d" , refcnt , option -> refcnt ) ;
 }
 }