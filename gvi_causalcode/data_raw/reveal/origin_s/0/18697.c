TEST ( DownloadPrefsTest , PrefsInitializationSkipsInvalidFileTypes ) {
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 profile . GetPrefs ( ) -> SetString ( prefs : : kDownloadExtensionsToOpen , "swf:txt::.foo:baz" ) ;
 DownloadPrefs prefs ( & profile ) ;
 prefs . DisableAutoOpenBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.baz" ) ) ) ;
 EXPECT_FALSE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.swf" ) ) ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.txt" ) ) ) ) ;
 EXPECT_FALSE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.foo" ) ) ) ) ;
 EXPECT_STREQ ( "txt" , profile . GetPrefs ( ) -> GetString ( prefs : : kDownloadExtensionsToOpen ) . c_str ( ) ) ;
 }