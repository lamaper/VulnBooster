static void test_read_format_mtree2 ( void ) {
 static char archive [ ] = "#mtree\n" "d type=dir content=.\n" ;
 struct archive_entry * ae ;
 struct archive * a ;
 assert ( ( a = archive_read_new ( ) ) != NULL ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_filter_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_format_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_set_options ( a , "mtree:checkfs" ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_open_memory ( a , archive , sizeof ( archive ) ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualInt ( archive_format ( a ) , ARCHIVE_FORMAT_MTREE ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "d" ) ;
 assertEqualInt ( archive_entry_filetype ( ae ) , AE_IFDIR ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_EOF , archive_read_next_header ( a , & ae ) ) ;
 assertEqualInt ( 1 , archive_file_count ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_close ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_free ( a ) ) ;
 }