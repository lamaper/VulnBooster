PHP_MINFO_FUNCTION ( uwsgi_php_minfo ) {
 php_info_print_table_start ( ) ;
 php_info_print_table_row ( 2 , "uwsgi api" , "enabled" ) ;
 if ( uwsgi . caches ) {
 php_info_print_table_row ( 2 , "uwsgi cache" , "enabled" ) ;
 }
 else {
 php_info_print_table_row ( 2 , "uwsgi cache" , "disabled" ) ;
 }
 php_info_print_table_end ( ) ;
 }