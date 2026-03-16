void show_diff ( DYNAMIC_STRING * ds , const char * filename1 , const char * filename2 ) {
 DYNAMIC_STRING ds_tmp ;
 const char * diff_name = 0 ;
 if ( init_dynamic_string ( & ds_tmp , "" , 256 , 256 ) ) die ( "Out of memory" ) ;

 else if ( diff_check ( "mtrdiff" ) ) diff_name = "mtrdiff" ;
 else diff_name = 0 ;


 if ( run_tool ( diff_name , & ds_tmp , "-u" , filename1 , filename2 , "2>&1" , NULL ) > 1 ) {
 dynstr_set ( & ds_tmp , "" ) ;
 if ( run_tool ( diff_name , & ds_tmp , "-c" , filename1 , filename2 , "2>&1" , NULL ) > 1 ) {
 dynstr_set ( & ds_tmp , "" ) ;
 if ( run_tool ( diff_name , & ds_tmp , filename1 , filename2 , "2>&1" , NULL ) > 1 ) {
 diff_name = 0 ;
 }
 }
 }
 }
 if ( ! diff_name ) {
 dynstr_append ( & ds_tmp , "\n" ) ;
 dynstr_append ( & ds_tmp , "\n" "The two files differ but it was not possible to execute 'diff' in\n" "order to show only the difference. Instead the whole content of the\n" "two files was shown for you to diff manually.\n\n" "To get a better report you should install 'diff' on your system, which you\n" "for example can get from http://www.gnu.org/software/diffutils/diffutils.html\n" # ifdef __WIN__ "or http://gnuwin32.sourceforge.net/packages/diffutils.htm\n" # endif "\n" ) ;
 dynstr_append ( & ds_tmp , " --- " ) ;
 dynstr_append ( & ds_tmp , filename1 ) ;
 dynstr_append ( & ds_tmp , " >>>\n" ) ;
 cat_file ( & ds_tmp , filename1 ) ;
 dynstr_append ( & ds_tmp , "<<<\n --- " ) ;
 dynstr_append ( & ds_tmp , filename1 ) ;
 dynstr_append ( & ds_tmp , " >>>\n" ) ;
 cat_file ( & ds_tmp , filename2 ) ;
 dynstr_append ( & ds_tmp , "<<<<\n" ) ;
 }
 if ( ds ) {
 dynstr_append_mem ( ds , ds_tmp . str , ds_tmp . length ) ;
 }
 else {
 fprintf ( stderr , "%s\n" , ds_tmp . str ) ;
 }
 dynstr_free ( & ds_tmp ) ;
 }