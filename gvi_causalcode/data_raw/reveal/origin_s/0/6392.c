IN_PROC_BROWSER_TEST_F ( ChooserDialogViewTest , Cancel ) {
 EXPECT_CALL ( * mock_chooser_controller_ , Cancel ( ) ) . Times ( 1 ) ;
 chooser_dialog_view_ -> Cancel ( ) ;
 }