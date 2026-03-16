TEST_F ( PrintPreviewUIUnitTest , PrintPreviewData ) {
 WebContents * initiator = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 ASSERT_TRUE ( initiator ) ;
 EXPECT_FALSE ( IsShowingWebContentsModalDialog ( initiator ) ) ;
 printing : : PrintPreviewDialogController * controller = printing : : PrintPreviewDialogController : : GetInstance ( ) ;
 ASSERT_TRUE ( controller ) ;
 printing : : PrintViewManager * print_view_manager = printing : : PrintViewManager : : FromWebContents ( initiator ) ;
 print_view_manager -> PrintPreviewNow ( initiator -> GetMainFrame ( ) , false ) ;
 WebContents * preview_dialog = controller -> GetOrCreatePreviewDialog ( initiator ) ;
 EXPECT_NE ( initiator , preview_dialog ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_TRUE ( IsShowingWebContentsModalDialog ( initiator ) ) ;
 PrintPreviewUI * preview_ui = static_cast < PrintPreviewUI * > ( preview_dialog -> GetWebUI ( ) -> GetController ( ) ) ;
 ASSERT_TRUE ( preview_ui != NULL ) ;
 scoped_refptr < base : : RefCountedBytes > data ;
 preview_ui -> GetPrintPreviewDataForIndex ( printing : : COMPLETE_PREVIEW_DOCUMENT_INDEX , & data ) ;
 EXPECT_EQ ( NULL , data . get ( ) ) ;
 scoped_refptr < base : : RefCountedBytes > dummy_data = CreateTestData ( ) ;
 preview_ui -> SetPrintPreviewDataForIndex ( printing : : COMPLETE_PREVIEW_DOCUMENT_INDEX , dummy_data . get ( ) ) ;
 preview_ui -> GetPrintPreviewDataForIndex ( printing : : COMPLETE_PREVIEW_DOCUMENT_INDEX , & data ) ;
 EXPECT_EQ ( dummy_data -> size ( ) , data -> size ( ) ) ;
 EXPECT_EQ ( dummy_data . get ( ) , data . get ( ) ) ;
 dummy_data = new base : : RefCountedBytes ( ) ;
 preview_ui -> SetPrintPreviewDataForIndex ( printing : : FIRST_PAGE_INDEX , dummy_data . get ( ) ) ;
 preview_ui -> ClearAllPreviewData ( ) ;
 preview_ui -> GetPrintPreviewDataForIndex ( printing : : COMPLETE_PREVIEW_DOCUMENT_INDEX , & data ) ;
 EXPECT_EQ ( NULL , data . get ( ) ) ;
 }