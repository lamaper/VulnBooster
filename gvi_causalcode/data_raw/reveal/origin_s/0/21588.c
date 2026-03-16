TEST ( DownloadPrefsTest , AutoOpenCheckIsCaseInsensitive ) {
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 profile . GetPrefs ( ) -> SetString ( prefs : : kDownloadExtensionsToOpen , "txt:Foo:BAR" ) ;
 DownloadPrefs prefs ( & profile ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.txt" ) ) ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.TXT" ) ) ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.foo" ) ) ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( base : : FilePath ( FILE_PATH_LITERAL ( "x.Bar" ) ) ) ) ;
 }