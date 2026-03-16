TEST_F ( OmniboxViewViewsTest , UpdatePopupCall ) {
 ui : : KeyEvent char_event ( ui : : ET_KEY_PRESSED , ui : : VKEY_A , ui : : DomCode : : US_A , 0 , ui : : DomKey : : FromCharacter ( 'a' ) , ui : : EventTimeForNow ( ) ) ;
 omnibox_textfield ( ) -> InsertChar ( char_event ) ;
 omnibox_view ( ) -> CheckUpdatePopupCallInfo ( 1 , base : : ASCIIToUTF16 ( "a" ) , Range ( 1 ) ) ;
 char_event = ui : : KeyEvent ( ui : : ET_KEY_PRESSED , ui : : VKEY_B , ui : : DomCode : : US_B , 0 , ui : : DomKey : : FromCharacter ( 'b' ) , ui : : EventTimeForNow ( ) ) ;
 omnibox_textfield ( ) -> InsertChar ( char_event ) ;
 omnibox_view ( ) -> CheckUpdatePopupCallInfo ( 2 , base : : ASCIIToUTF16 ( "ab" ) , Range ( 2 ) ) ;
 ui : : KeyEvent pressed ( ui : : ET_KEY_PRESSED , ui : : VKEY_BACK , 0 ) ;
 omnibox_textfield ( ) -> OnKeyEvent ( & pressed ) ;
 omnibox_view ( ) -> CheckUpdatePopupCallInfo ( 3 , base : : ASCIIToUTF16 ( "a" ) , Range ( 1 ) ) ;
 }