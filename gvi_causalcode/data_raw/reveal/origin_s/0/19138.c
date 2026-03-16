TEST ( DownloadPrefsTest , AutoOpenForSafeFiles ) {
 const base : : FilePath kSafeFilePath ( FILE_PATH_LITERAL ( "/goodothing-wrong.txt" ) ) ;
 const base : : FilePath kAnotherSafeFilePath ( FILE_PATH_LITERAL ( "/okot-bad.txt" ) ) ;
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 DownloadPrefs prefs ( & profile ) ;
 EXPECT_TRUE ( prefs . EnableAutoOpenBasedOnExtension ( kSafeFilePath ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kSafeFilePath ) ) ;
 EXPECT_TRUE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kAnotherSafeFilePath ) ) ;
 }