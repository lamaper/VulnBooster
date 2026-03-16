TEST ( URLFixerTest , FixupRelativeFile ) {
 base : : FilePath full_path ;
 base : : FilePath file_part ( FILE_PATH_LITERAL ( "url_fixer_upper_existing_file.txt" ) ) ;
 base : : ScopedTempDir temp_dir_ ;
 ASSERT_TRUE ( temp_dir_ . CreateUniqueTempDir ( ) ) ;
 ASSERT_TRUE ( MakeTempFile ( temp_dir_ . GetPath ( ) , file_part , & full_path ) ) ;
 full_path = base : : MakeAbsoluteFilePath ( full_path ) ;
 ASSERT_FALSE ( full_path . empty ( ) ) ;
 for ( size_t i = 0 ;
 i < arraysize ( fixup_cases ) ;
 ++ i ) {
 FixupCase value = fixup_cases [ i ] ;
 base : : FilePath input = base : : FilePath : : FromUTF8Unsafe ( value . input ) ;
 EXPECT_EQ ( value . output , url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , input ) . possibly_invalid_spec ( ) ) ;
 }
 EXPECT_TRUE ( IsMatchingFileURL ( url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , file_part ) . possibly_invalid_spec ( ) , full_path ) ) ;
 EXPECT_TRUE ( base : : DeleteFile ( full_path , false ) ) ;
 base : : FilePath nonexistent_file ( FILE_PATH_LITERAL ( "url_fixer_upper_nonexistent_file.txt" ) ) ;
 std : : string fixedup ( url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , nonexistent_file ) . possibly_invalid_spec ( ) ) ;
 EXPECT_NE ( std : : string ( "file:///" ) , fixedup . substr ( 0 , 8 ) ) ;
 EXPECT_FALSE ( IsMatchingFileURL ( fixedup , nonexistent_file ) ) ;
 base : : FilePath sub_dir ( FILE_PATH_LITERAL ( "url fixer-upper dir" ) ) ;
 base : : FilePath sub_file ( FILE_PATH_LITERAL ( "url fixer-upper existing file.txt" ) ) ;
 base : : FilePath new_dir = temp_dir_ . GetPath ( ) . Append ( sub_dir ) ;
 base : : CreateDirectory ( new_dir ) ;
 ASSERT_TRUE ( MakeTempFile ( new_dir , sub_file , & full_path ) ) ;
 full_path = base : : MakeAbsoluteFilePath ( full_path ) ;
 ASSERT_FALSE ( full_path . empty ( ) ) ;
 base : : FilePath relative_file = sub_dir . Append ( sub_file ) ;
 EXPECT_TRUE ( IsMatchingFileURL ( url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , relative_file ) . possibly_invalid_spec ( ) , full_path ) ) ;
 base : : FilePath : : StringType relative_file_str = sub_dir . value ( ) + FILE_PATH_LITERAL ( "/" ) + sub_file . value ( ) ;
 base : : ReplaceSubstringsAfterOffset ( & relative_file_str , 0 , FILE_PATH_LITERAL ( " " ) , FILE_PATH_LITERAL ( "%20" ) ) ;
 EXPECT_TRUE ( IsMatchingFileURL ( url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , base : : FilePath ( relative_file_str ) ) . possibly_invalid_spec ( ) , full_path ) ) ;
 relative_file_str = sub_dir . value ( ) + FILE_PATH_LITERAL ( "/../" ) + sub_dir . value ( ) + FILE_PATH_LITERAL ( "///./" ) + sub_file . value ( ) ;
 EXPECT_TRUE ( IsMatchingFileURL ( url_formatter : : FixupRelativeFile ( temp_dir_ . GetPath ( ) , base : : FilePath ( relative_file_str ) ) . possibly_invalid_spec ( ) , full_path ) ) ;
 EXPECT_TRUE ( base : : DeleteFile ( full_path , false ) ) ;
 EXPECT_TRUE ( base : : DeleteFile ( new_dir , true ) ) ;
 base : : FilePath empty_path ;
 base : : FilePath http_url_path ( FILE_PATH_LITERAL ( "http://../" ) ) ;
 EXPECT_TRUE ( url_formatter : : FixupRelativeFile ( empty_path , http_url_path ) . SchemeIs ( "http" ) ) ;
 }