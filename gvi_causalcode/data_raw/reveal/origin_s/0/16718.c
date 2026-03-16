TEST_F ( OmniboxViewViewsTest , EditTextfield ) {
 omnibox_textfield ( ) -> SetCursorEnabled ( false ) ;
 ui : : KeyEvent char_event ( ui : : ET_KEY_PRESSED , ui : : VKEY_A , ui : : DomCode : : US_A , 0 , ui : : DomKey : : FromCharacter ( 'a' ) , ui : : EventTimeForNow ( ) ) ;
 omnibox_textfield ( ) -> InsertChar ( char_event ) ;
 EXPECT_TRUE ( IsCursorEnabled ( ) ) ;
 }