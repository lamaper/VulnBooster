IN_PROC_BROWSER_TEST_F ( FullscreenControllerTest , FullscreenOnFileURL ) {
 static const base : : FilePath : : CharType * kEmptyFile = FILE_PATH_LITERAL ( "empty.html" ) ;
 GURL file_url ( ui_test_utils : : GetTestUrl ( base : : FilePath ( base : : FilePath : : kCurrentDirectory ) , base : : FilePath ( kEmptyFile ) ) ) ;
 AddTabAtIndex ( 0 , file_url , PAGE_TRANSITION_TYPED ) ;
 RequestToLockMouse ( true , false ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayingButtons ( ) ) ;
 }