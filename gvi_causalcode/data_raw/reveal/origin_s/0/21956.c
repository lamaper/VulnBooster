TEST_F ( MdDownloadsDOMHandlerTest , ChecksForRemovedFiles ) {
 EXPECT_CALL ( * manager ( ) , CheckForHistoryFilesRemoval ( ) ) ;
 TestMdDownloadsDOMHandler handler ( manager ( ) , web_ui ( ) ) ;
 testing : : Mock : : VerifyAndClear ( manager ( ) ) ;
 EXPECT_CALL ( * manager ( ) , CheckForHistoryFilesRemoval ( ) ) ;
 handler . OnJavascriptDisallowed ( ) ;
 }