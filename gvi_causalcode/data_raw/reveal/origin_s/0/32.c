TEST ( DownloadPrefsTest , NoAutoOpenForDisallowedFileTypes ) {
 const base : : FilePath kDangerousFilePath ( FILE_PATH_LITERAL ( "/b/very-bad.swf" ) ) ;
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 DownloadPrefs prefs ( & profile ) ;
 EXPECT_FALSE ( prefs . EnableAutoOpenBasedOnExtension ( kDangerousFilePath ) ) ;
 EXPECT_FALSE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kDangerousFilePath ) ) ;
 }