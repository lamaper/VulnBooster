IN_PROC_BROWSER_TEST_F ( PrintPreviewDialogControllerBrowserTest , ReloadInitiatorTab ) {
 PrintPreview ( ) ;
 WebContents * preview_dialog = GetPrintPreviewDialog ( ) ;
 ASSERT_TRUE ( preview_dialog ) ;
 ASSERT_NE ( initiator ( ) , preview_dialog ) ;
 PrintPreviewDialogDestroyedObserver dialog_destroyed_observer ( preview_dialog ) ;
 chrome : : Reload ( browser ( ) , WindowOpenDisposition : : CURRENT_TAB ) ;
 content : : WaitForLoadStop ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 ASSERT_TRUE ( dialog_destroyed_observer . dialog_destroyed ( ) ) ;
 PrintPreview ( ) ;
 WebContents * new_preview_dialog = GetPrintPreviewDialog ( ) ;
 EXPECT_TRUE ( new_preview_dialog ) ;
 }