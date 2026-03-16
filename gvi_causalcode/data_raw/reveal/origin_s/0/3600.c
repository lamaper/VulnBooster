TEST ( DownloadPrefsTest , Prerequisites ) {
 ASSERT_FALSE ( FileTypePolicies : : GetInstance ( ) -> IsAllowedToOpenAutomatically ( base : : FilePath ( FILE_PATH_LITERAL ( "a.swf" ) ) ) ) ;
 ASSERT_TRUE ( FileTypePolicies : : GetInstance ( ) -> IsAllowedToOpenAutomatically ( base : : FilePath ( FILE_PATH_LITERAL ( "a.txt" ) ) ) ) ;
 }