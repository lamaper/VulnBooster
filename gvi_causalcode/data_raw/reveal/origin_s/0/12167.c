static void print_quoted_xml ( FILE * xml_file , const char * str , size_t len , my_bool is_attribute_name ) {
 const char * end ;
 for ( end = str + len ;
 str != end ;
 str ++ ) {
 switch ( * str ) {
 case '<' : fputs ( "&lt;
" , xml_file ) ;
 break ;
 case '>' : fputs ( "&gt;
" , xml_file ) ;
 break ;
 case '&' : fputs ( "&amp;
" , xml_file ) ;
 break ;
 case '\"' : fputs ( "&quot;
" , xml_file ) ;
 break ;
 case ' ' : if ( is_attribute_name ) {
 fputs ( "_" , xml_file ) ;
 break ;
 }
 default : fputc ( * str , xml_file ) ;
 break ;
 }
 }
 check_io ( xml_file ) ;
 }