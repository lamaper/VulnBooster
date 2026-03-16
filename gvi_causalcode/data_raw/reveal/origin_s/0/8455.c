TEST_F ( AutocompleteResultTest , SortAndCullReorderForDefaultMatch ) {
 TestData data [ ] = {
 {
 0 , 1 , 1300 , true }
 , {
 1 , 1 , 1200 , true }
 , {
 2 , 1 , 1100 , true }
 , {
 3 , 1 , 1000 , true }
 }
 ;
 {
 ACMatches matches ;
 PopulateAutocompleteMatches ( data , arraysize ( data ) , & matches ) ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : HOME_PAGE , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , template_url_service_ . get ( ) ) ;
 AssertResultMatches ( result , data , 4 ) ;
 }
 {
 ACMatches matches ;
 PopulateAutocompleteMatches ( data , arraysize ( data ) , & matches ) ;
 matches [ 0 ] . allowed_to_be_default_match = false ;
 matches [ 1 ] . allowed_to_be_default_match = false ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : HOME_PAGE , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 4U , result . size ( ) ) ;
 EXPECT_EQ ( "http://c/" , result . match_at ( 0 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://a/" , result . match_at ( 1 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://b/" , result . match_at ( 2 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://d/" , result . match_at ( 3 ) -> destination_url . spec ( ) ) ;
 }
 }