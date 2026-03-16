TEST_F ( ExternalProtocolHandlerTest , TestGetBlockStateUnknown ) {
 ExternalProtocolHandler : : BlockState block_state = ExternalProtocolHandler : : GetBlockState ( "tel" , profile_ . get ( ) ) ;
 EXPECT_EQ ( ExternalProtocolHandler : : UNKNOWN , block_state ) ;
 EXPECT_TRUE ( local_state_ -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 EXPECT_FALSE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 }