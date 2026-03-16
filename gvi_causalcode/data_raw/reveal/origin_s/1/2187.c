TEST_F ( ExternalProtocolHandlerTest , TestGetBlockStateLocalDontBlockCopiedAsIsToProfilePref ) {
 base : : DictionaryValue prefs_local ;
 prefs_local . SetBoolean ( "tel" , false ) ;
 local_state_ -> Set ( prefs : : kExcludedSchemes , prefs_local ) ;
 ExternalProtocolHandler : : BlockState block_state = ExternalProtocolHandler : : GetBlockState ( "tel" , profile_ . get ( ) ) ;
 EXPECT_EQ ( ExternalProtocolHandler : : DONT_BLOCK , block_state ) ;
 EXPECT_TRUE ( local_state_ -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 EXPECT_FALSE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 }