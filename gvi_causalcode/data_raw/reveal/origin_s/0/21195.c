TEST_F ( OmniboxViewViewsTest , ScheduledTextEditCommand ) {
 omnibox_textfield ( ) -> SetTextEditCommandForNextKeyEvent ( ui : : TextEditCommand : : MOVE_UP ) ;
 EXPECT_EQ ( ui : : TextEditCommand : : MOVE_UP , scheduled_text_edit_command ( ) ) ;
 ui : : KeyEvent up_pressed ( ui : : ET_KEY_PRESSED , ui : : VKEY_UP , 0 ) ;
 omnibox_textfield ( ) -> OnKeyEvent ( & up_pressed ) ;
 EXPECT_EQ ( ui : : TextEditCommand : : INVALID_COMMAND , scheduled_text_edit_command ( ) ) ;
 }