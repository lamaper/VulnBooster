DEFINE_TEST ( test_read_format_mtree_nochange ) {
 static char archive [ ] = "#mtree\n" "./a type=file mode=0644 time=123\n" "./b type=file mode=0644 time=234\n" "./c type=file mode=0644 time=345\n" ;
 static char archive2 [ ] = "#mtree\n" "./a type=file mode=0644 time=123 nochange\n" "./b type=file mode=0644 time=234\n" "./c type=file mode=0644 time=345 nochange\n" ;
 struct archive_entry * ae ;
 struct archive * a ;
 assertMakeFile ( "a" , 0640 , "12345" ) ;
 assertMakeFile ( "b" , 0664 , "123456" ) ;
 assertMakeFile ( "c" , 0755 , "1234567" ) ;
 assert ( ( a = archive_read_new ( ) ) != NULL ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_filter_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_format_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_set_options ( a , "mtree:checkfs" ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_open_memory ( a , archive , sizeof ( archive ) ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./a" ) ;
 assertEqualInt ( archive_entry_mode ( ae ) , AE_IFREG | 0644 ) ;
 assertEqualInt ( archive_entry_mtime ( ae ) , 123 ) ;
 assertEqualInt ( archive_entry_size ( ae ) , 5 ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./b" ) ;
 assertEqualInt ( archive_entry_mode ( ae ) , AE_IFREG | 0644 ) ;
 assertEqualInt ( archive_entry_mtime ( ae ) , 234 ) ;
 assertEqualInt ( archive_entry_size ( ae ) , 6 ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./c" ) ;
 assertEqualInt ( archive_entry_mode ( ae ) , AE_IFREG | 0644 ) ;
 assertEqualInt ( archive_entry_mtime ( ae ) , 345 ) ;
 assertEqualInt ( archive_entry_size ( ae ) , 7 ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_EOF , archive_read_next_header ( a , & ae ) ) ;
 assertEqualInt ( 3 , archive_file_count ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_close ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_free ( a ) ) ;
 assert ( ( a = archive_read_new ( ) ) != NULL ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_filter_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_support_format_all ( a ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_set_options ( a , "mtree:checkfs" ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_open_memory ( a , archive2 , sizeof ( archive2 ) ) ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./a" ) ;


 assertEqualInt ( archive_entry_size ( ae ) , 5 ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./b" ) ;
 assertEqualInt ( archive_entry_mode ( ae ) , AE_IFREG | 0644 ) ;
 assertEqualInt ( archive_entry_mtime ( ae ) , 234 ) ;
 assertEqualInt ( archive_entry_size ( ae ) , 6 ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_OK , archive_read_next_header ( a , & ae ) ) ;
 assertEqualString ( archive_entry_pathname ( ae ) , "./c" ) ;


 assertEqualInt ( archive_entry_size ( ae ) , 7 ) ;
 assertEqualInt ( archive_entry_is_encrypted ( ae ) , 0 ) ;
 assertEqualIntA ( a , archive_read_has_encrypted_entries ( a ) , ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ) ;
 assertEqualIntA ( a , ARCHIVE_EOF , archive_read_next_header ( a , & ae ) ) ;
 assertEqualInt ( 3 , archive_file_count ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_close ( a ) ) ;
 assertEqualInt ( ARCHIVE_OK , archive_read_free ( a ) ) ;
 }