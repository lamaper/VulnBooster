TEST_F ( OmniboxEditTest , InlineAutocompleteText ) {
 EXPECT_EQ ( base : : string16 ( ) , view ( ) . inline_autocomplete_text ( ) ) ;
 model ( ) -> SetUserText ( base : : ASCIIToUTF16 ( "he" ) ) ;
 model ( ) -> OnPopupDataChanged ( base : : ASCIIToUTF16 ( "llo" ) , nullptr , base : : string16 ( ) , false ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "hello" ) , view ( ) . GetText ( ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "llo" ) , view ( ) . inline_autocomplete_text ( ) ) ;
 base : : string16 text_before = base : : ASCIIToUTF16 ( "he" ) ;
 base : : string16 text_after = base : : ASCIIToUTF16 ( "hel" ) ;
 OmniboxView : : StateChanges state_changes {
 & text_before , & text_after , 3 , 3 , false , true , false , false }
 ;
 model ( ) -> OnAfterPossibleChange ( state_changes , true ) ;
 EXPECT_EQ ( base : : string16 ( ) , view ( ) . inline_autocomplete_text ( ) ) ;
 model ( ) -> OnPopupDataChanged ( base : : ASCIIToUTF16 ( "lo" ) , nullptr , base : : string16 ( ) , false ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "hello" ) , view ( ) . GetText ( ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "lo" ) , view ( ) . inline_autocomplete_text ( ) ) ;
 model ( ) -> Revert ( ) ;
 EXPECT_EQ ( base : : string16 ( ) , view ( ) . GetText ( ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , view ( ) . inline_autocomplete_text ( ) ) ;
 model ( ) -> SetUserText ( base : : ASCIIToUTF16 ( "he" ) ) ;
 model ( ) -> OnPopupDataChanged ( base : : ASCIIToUTF16 ( "llo" ) , nullptr , base : : string16 ( ) , false ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "hello" ) , view ( ) . GetText ( ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "llo" ) , view ( ) . inline_autocomplete_text ( ) ) ;
 model ( ) -> AcceptTemporaryTextAsUserText ( ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "hello" ) , view ( ) . GetText ( ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , view ( ) . inline_autocomplete_text ( ) ) ;
 }