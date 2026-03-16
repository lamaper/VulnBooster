TEST_F ( ExternalProtocolHandlerTest , TestGetBlockStateDefaultDontBlock ) {
 ExternalProtocolHandler : : BlockState block_state = ExternalProtocolHandler : : GetBlockState ( "mailto" , profile_ . get ( ) ) ;
 EXPECT_EQ ( ExternalProtocolHandler : : DONT_BLOCK , block_state ) ;
 EXPECT_TRUE ( local_state_ -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 EXPECT_FALSE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 }