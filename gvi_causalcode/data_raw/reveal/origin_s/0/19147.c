IN_PROC_BROWSER_TEST_F ( ChooserDialogViewTest , Close ) {
 EXPECT_CALL ( * mock_chooser_controller_ , Close ( ) ) . Times ( 1 ) ;
 chooser_dialog_view_ -> Close ( ) ;
 }