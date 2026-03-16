DEFINE_TEST ( test_read_format_mtree_nonexistent_contents_file ) {
 static char archive [ ] = "#mtree\n" "a type=file contents=nonexistent_file\n" ;
 struct archive_entry * ae ;
 struct archive * a ;
 assert ( ( a = archive_read_new ( ) ) != NULL ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_filter_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_format_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_set_options ( a , "mtree:checkfs" ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_open_memory ( a , archive , sizeof ( archive ) ) ) ;
 assertEqualIntA ( a , ARCHIVE_WARN , archive_read_next_header ( a , & ae ) ) ;
 assert ( strlen ( archive_error_string ( a ) ) > 0 ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "a" ) ;
 assertEqualInt ( archive_entry_filetype ( ae ) , AE_IFREG ) ;
 assertEqualIntA ( a , ARCHIVE_EOF , archive_read_next_header ( a , & ae ) ) ;
 assertEqualInt ( 1 , archive_file_count ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_close ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_free ( a ) ) ;
 }