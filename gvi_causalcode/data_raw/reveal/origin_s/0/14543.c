IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestDownloadDirPref ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 base : : FilePath new_download_dir = DownloadPrefs ( browser ( ) -> profile ( ) ) . DownloadPath ( ) . AppendASCII ( "subdir" ) ;
 base : : FilePath downloaded_pkg = new_download_dir . AppendASCII ( "a_zip_file.zip" ) ;
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetFilePath ( prefs : : kDownloadDefaultDirectory , new_download_dir ) ;
 std : : unique_ptr < content : : DownloadTestObserver > downloads_observer ( CreateWaiter ( browser ( ) , 1 ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/downloads/a_zip_file.zip" ) ) ;
 downloads_observer -> WaitForFinished ( ) ;
 base : : ScopedAllowBlockingForTesting allow_blocking ;
 EXPECT_TRUE ( base : : PathExists ( downloaded_pkg ) ) ;
 }