TEST ( DownloadPrefsTest , NoAutoOpenForFilesWithNoExtension ) {
 const base : : FilePath kFileWithNoExtension ( FILE_PATH_LITERAL ( "abcd" ) ) ;
 content : : TestBrowserThreadBundle threads_are_required_for_testing_profile ;
 TestingProfile profile ;
 DownloadPrefs prefs ( & profile ) ;
 EXPECT_FALSE ( prefs . EnableAutoOpenBasedOnExtension ( kFileWithNoExtension ) ) ;
 EXPECT_FALSE ( prefs . IsAutoOpenEnabledBasedOnExtension ( kFileWithNoExtension ) ) ;
 }