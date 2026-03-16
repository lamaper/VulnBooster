int SDK_RPRINT ( RegressionTest * t , const char * api_name , const char * testcase_name , int status , const char * err_details_format , ... ) {
 int l ;
 char buffer [ 8192 ] ;
 char format2 [ 8192 ] ;
 snprintf ( format2 , sizeof ( format2 ) , "[%s] %s : [%s] <<%s>> {
 %s }
\n" , t -> name , api_name , testcase_name , status == TC_PASS ? "PASS" : "FAIL" , err_details_format ) ;
 va_list ap ;
 va_start ( ap , err_details_format ) ;
 l = ink_bvsprintf ( buffer , format2 , ap ) ;
 va_end ( ap ) ;
 fputs ( buffer , stderr ) ;
 return ( l ) ;
 }