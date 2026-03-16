TEST_F ( ShortcutsProviderTest , DoesNotProvideOnFocus ) {
 AutocompleteInput input ( ASCIIToUTF16 ( "about:o" ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , metrics : : OmniboxEventProto : : INVALID_SPEC , false , false , true , true , true , TestSchemeClassifier ( ) ) ;
 provider_ -> Start ( input , false ) ;
 EXPECT_TRUE ( provider_ -> matches ( ) . empty ( ) ) ;
 }