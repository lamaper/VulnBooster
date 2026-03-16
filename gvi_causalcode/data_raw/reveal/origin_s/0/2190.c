int main ( void ) {
 static void ( * test_functions [ ] ) ( void ) = {
 test_rfc822_parse_quoted_string , test_rfc822_parse_content_param , NULL }
 ;
 return test_run ( test_functions ) ;
 }