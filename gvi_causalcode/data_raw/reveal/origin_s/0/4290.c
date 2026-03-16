TEST_F ( ExternalProtocolHandlerTest , TestGetBlockStateDefaultBlock ) {
 ExternalProtocolHandler : : BlockState block_state = ExternalProtocolHandler : : GetBlockState ( "afp" , profile_ . get ( ) ) ;
 EXPECT_EQ ( ExternalProtocolHandler : : BLOCK , block_state ) ;
 EXPECT_TRUE ( local_state_ -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 EXPECT_TRUE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 }