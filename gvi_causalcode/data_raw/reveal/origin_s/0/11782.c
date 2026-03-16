TEST ( URLFixerTest , FixupFile ) {
 base : : ScopedTempDir temp_dir_ ;
 ASSERT_TRUE ( temp_dir_ . CreateUniqueTempDir ( ) ) ;
 base : : FilePath original ;
 ASSERT_TRUE ( MakeTempFile ( temp_dir_ . GetPath ( ) , base : : FilePath ( FILE_PATH_LITERAL ( "url fixer upper existing file.txt" ) ) , & original ) ) ;
 GURL golden ( net : : FilePathToFileURL ( original ) ) ;
 GURL fixedup ( url_formatter : : FixupURL ( original . AsUTF8Unsafe ( ) , std : : string ( ) ) ) ;
 EXPECT_EQ ( golden , fixedup ) ;

 EXPECT_EQ ( ':' , cur [ 1 ] ) ;
 cur [ 1 ] = '|' ;
 EXPECT_EQ ( golden , url_formatter : : FixupURL ( cur , std : : string ( ) ) ) ;
 FixupCase cases [ ] = {
 {
 "c:\\Non-existent%20file.txt" , "file:///C:/Non-existent%2520file.txt" }
 , {
 "\\\\NonexistentHost\\foo\\bar.txt" , "file:/onexistenthost/foo/bar.txt" }
 , {
 "//NonexistentHost\\foo/bar.txt" , "http:/onexistenthost/foo/bar.txt" }
 , {
 "file:///C:/foo/bar" , "file:///C:/foo/bar" }
 , {
 "file://C:/foo/bar" , "file:///C:/foo/bar" }
 , {
 "file:c:" , "file:///C:/" }
 , {
 "file:c:WINDOWS" , "file:///C:/WINDOWS" }
 , {
 "file:c|Program Files" , "file:///C:/Program%20Files" }
 , {
 "file:/file" , "file://file/" }
 , {
 "file:////////c:\\foo" , "file:///C:/foo" }
 , {
 "file://server/folder/file" , "file://server/folder/file" }
 , }
 ;

 FixupCase cases [ ] = {
 {
 "/A%20non-existent file.txt" , "file:///A%2520non-existent%20file.txt" }
 , {
 "/" , "file:///" }
 , {
 "~" , "file:///foo" }
 , {
 "~/bar" , "file:///foo/bar" }
 , {
 "~foo" , "file://" HOME "foo" }
 , {
 "~x/blah" , "file://" HOME "x/blah" }
 , }
 ;

 i < arraysize ( cases ) ;
 i ++ ) {
 EXPECT_EQ ( cases [ i ] . output , url_formatter : : FixupURL ( cases [ i ] . input , std : : string ( ) ) . possibly_invalid_spec ( ) ) ;
 }
 EXPECT_TRUE ( base : : DeleteFile ( original , false ) ) ;
 }