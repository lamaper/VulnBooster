static void print_xml_comment ( FILE * xml_file , size_t len , const char * comment_string ) {
 const char * end ;
 fputs ( "<!-- " , xml_file ) ;
 for ( end = comment_string + len ;
 comment_string != end ;
 comment_string ++ ) {
 switch ( * comment_string ) {
 case '-' : if ( * ( comment_string + 1 ) == '-' ) break ;
 default : fputc ( * comment_string , xml_file ) ;
 break ;
 }
 }
 fputs ( " -->\n" , xml_file ) ;
 check_io ( xml_file ) ;
 }