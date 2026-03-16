ATF_TC_BODY ( pretty_print_option , tc ) {
 struct option * option ;
 unsigned code ;
 unsigned char bad_data [ 32 * 1024 ] ;
 unsigned char good_data [ ] = {
 1 , 2 , 3 , 4 , 5 , 6 }
 ;
 int emit_commas = 1 ;
 int emit_quotes = 1 ;
 const char * output_buf ;
 memset ( bad_data , 0x1f , sizeof ( bad_data ) ) ;
 initialize_common_option_spaces ( ) ;
 code = 61 ;
 option = NULL ;
 if ( ! option_code_hash_lookup ( & option , dhcp_universe . code_hash , & code , 0 , MDL ) ) {
 atf_tc_fail ( "can't find option %d" , code ) ;
 }
 if ( option == NULL ) {
 atf_tc_fail ( "option is NULL" ) ;
 }
 output_buf = pretty_print_option ( option , good_data , sizeof ( good_data ) , emit_commas , emit_quotes ) ;
 if ( ! output_buf || strcmp ( output_buf , "1:2:3:4:5:6" ) ) {
 atf_tc_fail ( "pretty_print_option did not return \"<error>\"" ) ;
 }
 output_buf = pretty_print_option ( option , bad_data , sizeof ( bad_data ) , emit_commas , emit_quotes ) ;
 if ( ! output_buf || strcmp ( output_buf , "<error>" ) ) {
 atf_tc_fail ( "pretty_print_option did not return \"<error>\"" ) ;
 }
 }