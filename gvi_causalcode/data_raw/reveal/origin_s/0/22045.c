IN_PROC_BROWSER_TEST_F ( ChooserDialogViewTest , Accept ) {
 EXPECT_CALL ( * mock_chooser_controller_ , Select ( testing : : _ ) ) . Times ( 1 ) ;
 chooser_dialog_view_ -> Accept ( ) ;
 }