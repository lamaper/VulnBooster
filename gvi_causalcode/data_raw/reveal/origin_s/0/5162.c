TEST_F ( AutocompleteResultTest , TopMatchIsStandaloneVerbatimMatch ) {
 ACMatches matches ;
 AutocompleteResult result ;
 result . AppendMatches ( AutocompleteInput ( ) , matches ) ;
 EXPECT_FALSE ( result . TopMatchIsStandaloneVerbatimMatch ( ) ) ;
 PopulateAutocompleteMatchesFromTestData ( kNonVerbatimMatches , 1 , & matches ) ;
 result . AppendMatches ( AutocompleteInput ( ) , matches ) ;
 EXPECT_FALSE ( result . TopMatchIsStandaloneVerbatimMatch ( ) ) ;
 result . Reset ( ) ;
 matches . clear ( ) ;
 PopulateAutocompleteMatchesFromTestData ( kVerbatimMatches , 1 , & matches ) ;
 result . AppendMatches ( AutocompleteInput ( ) , matches ) ;
 EXPECT_TRUE ( result . TopMatchIsStandaloneVerbatimMatch ( ) ) ;
 result . Reset ( ) ;
 matches . clear ( ) ;
 PopulateAutocompleteMatchesFromTestData ( kVerbatimMatches , 1 , & matches ) ;
 PopulateAutocompleteMatchesFromTestData ( kNonVerbatimMatches , 1 , & matches ) ;
 result . AppendMatches ( AutocompleteInput ( ) , matches ) ;
 EXPECT_TRUE ( result . TopMatchIsStandaloneVerbatimMatch ( ) ) ;
 result . Reset ( ) ;
 matches . clear ( ) ;
 }