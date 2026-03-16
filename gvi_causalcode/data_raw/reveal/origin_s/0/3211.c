TEST ( DownloadPrefsTest , AutoOpenPrefSkipsDangerousFileTypesInPrefs ) {
 const base : : FilePath kDangerousFilePath ( FILE_PATH_LITERAL ( "/b/very-bad.swf" ) ) ;
 const base : : FilePath kSafeFilePath ( FILE_PATH_LITERAL ( "/goodothing-wrong.txt" ) ) ;
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 profile . GetPrefs ( ) -> SetString ( prefs : : kDownloadExtensionsToOpen , "swf:txt" ) ;
 DownloadPrefs prefs ( & profile ) ;
 EXPECT_FALSE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kDangerousFilePath ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kSafeFilePath ) ) ;
 }