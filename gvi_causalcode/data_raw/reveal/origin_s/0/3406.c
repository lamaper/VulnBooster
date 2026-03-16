void open_file ( const char * name ) {
 char buff [ FN_REFLEN ] ;
 size_t length ;
 const char * curname = cur_file -> file_name ;
 DBUG_ENTER ( "open_file" ) ;
 DBUG_PRINT ( "enter" , ( "name: %s" , name ) ) ;
 if ( cur_file == file_stack_end ) die ( "Source directives are nesting too deep" ) ;
 if ( test_if_hard_path ( name ) ) {
 if ( open_and_set_current ( name ) ) DBUG_VOID_RETURN ;
 }
 else {


 bool in_suiteir = opt_overlay_dir && ! in_overlay && ! strncmp ( curname , opt_suite_dir , suite_dir_len ) ;
 if ( in_overlay || in_suiteir ) {
 size_t prefix_len = in_overlay ? overlay_dir_len : suite_dir_len ;
 char buf2 [ FN_REFLEN ] , * suffix = buf2 + prefix_len ;
 dirname_part ( buf2 , curname , & length ) ;
 strxnmov ( buff , sizeof ( buff ) , opt_overlay_dir , suffix , name , NullS ) ;
 if ( strcmp ( buff , curname ) && open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 strxnmov ( buff , sizeof ( buff ) , opt_suite_dir , suffix , name , NullS ) ;
 if ( open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 }
 else {
 dirname_part ( buff , curname , & length ) ;
 strxnmov ( buff , sizeof ( buff ) , buff , name , NullS ) ;
 if ( open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 }
 if ( opt_overlay_dir ) {
 strxmov ( buff , opt_overlay_dir , name , NullS ) ;
 if ( open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 }
 strxmov ( buff , opt_suite_dir , name , NullS ) ;
 if ( open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 strxnmov ( buff , sizeof ( buff ) , opt_basedir , name , NullS ) ;
 if ( open_and_set_current ( buff ) ) DBUG_VOID_RETURN ;
 }
 die ( "Could not open '%s' for reading, errno: %d" , name , errno ) ;
 DBUG_VOID_RETURN ;
 }