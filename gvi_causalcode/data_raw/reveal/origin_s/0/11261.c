IN_PROC_BROWSER_TEST_F ( PrintPreviewDialogControllerBrowserTest , NavigateFromInitiatorTab ) {
 PrintPreview ( ) ;
 WebContents * preview_dialog = GetPrintPreviewDialog ( ) ;
 ASSERT_TRUE ( preview_dialog ) ;
 ASSERT_NE ( initiator ( ) , preview_dialog ) ;
 PrintPreviewDialogDestroyedObserver dialog_destroyed_observer ( preview_dialog ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( chrome : : kChromeUINewTabURL ) ) ;
 ASSERT_TRUE ( dialog_destroyed_observer . dialog_destroyed ( ) ) ;
 PrintPreview ( ) ;
 WebContents * new_preview_dialog = GetPrintPreviewDialog ( ) ;
 EXPECT_TRUE ( new_preview_dialog ) ;
 }