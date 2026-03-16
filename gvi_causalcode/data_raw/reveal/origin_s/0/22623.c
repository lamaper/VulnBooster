IN_PROC_BROWSER_TEST_F ( ChooserDialogViewTest , ClickStyledLabelLink ) {
 EXPECT_CALL ( * mock_chooser_controller_ , OpenHelpCenterUrl ( ) ) . Times ( 1 ) ;
 chooser_dialog_view_ -> StyledLabelLinkClicked ( nullptr , gfx : : Range ( ) , 0 ) ;
 }