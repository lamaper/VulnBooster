void dynstr_append_sorted ( DYNAMIC_STRING * ds , DYNAMIC_STRING * ds_input , bool keep_header ) {
 unsigned i ;
 char * start = ds_input -> str ;
 DYNAMIC_ARRAY lines ;
 DBUG_ENTER ( "dynstr_append_sorted" ) ;
 if ( ! * start ) DBUG_VOID_RETURN ;
 my_init_dynamic_array ( & lines , sizeof ( const char * ) , 32 , 32 ) ;
 if ( keep_header ) {
 while ( * start && * start != '\n' ) start ++ ;
 start ++ ;
 dynstr_append_mem ( ds , ds_input -> str , start - ds_input -> str ) ;
 }
 while ( * start ) {
 char * line_end = ( char * ) start ;
 while ( * line_end && * line_end != '\n' ) line_end ++ ;
 * line_end = 0 ;
 if ( insert_dynamic ( & lines , ( uchar * ) & start ) ) die ( "Out of memory inserting lines to sort" ) ;
 start = line_end + 1 ;
 }
 qsort ( lines . buffer , lines . elements , sizeof ( char * * ) , ( qsort_cmp ) comp_lines ) ;
 for ( i = 0 ;
 i < lines . elements ;
 i ++ ) {
 const char * * line = dynamic_element ( & lines , i , const char * * ) ;
 dynstr_append ( ds , * line ) ;
 dynstr_append ( ds , "\n" ) ;
 }
 delete_dynamic ( & lines ) ;
 DBUG_VOID_RETURN ;
 }