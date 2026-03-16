TEST_F ( ExternalProtocolHandlerTest , TestClearProfileState ) {
 base : : DictionaryValue prefs ;
 prefs . SetBoolean ( "tel" , true ) ;
 profile_ -> GetPrefs ( ) -> Set ( prefs : : kExcludedSchemes , prefs ) ;
 EXPECT_FALSE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 ExternalProtocolHandler : : ClearData ( profile_ . get ( ) ) ;
 EXPECT_TRUE ( profile_ -> GetPrefs ( ) -> GetDictionary ( prefs : : kExcludedSchemes ) -> empty ( ) ) ;
 }