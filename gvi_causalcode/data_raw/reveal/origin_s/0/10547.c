TEST_F ( AutocompleteResultTest , SortAndCullWithMatchDups ) {
 TemplateURLData url_data ;
 url_data . SetShortName ( base : : ASCIIToUTF16 ( "unittest" ) ) ;
 url_data . SetKeyword ( base : : ASCIIToUTF16 ( "foo" ) ) ;
 url_data . SetURL ( "http://www.foo.com/s?q={
searchTerms}
" ) ;
 template_url_service_ . get ( ) -> Add ( new TemplateURL ( url_data ) ) ;
 AutocompleteMatch dup_match ;
 dup_match . destination_url = GURL ( "http://www.foo.com/s?q=foo&oq=dup" ) ;
 std : : vector < AutocompleteMatch > dups ;
 dups . push_back ( dup_match ) ;
 TestData data [ ] = {
 {
 0 , 1 , 1300 , true , dups }
 , {
 1 , 1 , 1200 , true }
 , {
 2 , 1 , 1100 , true }
 , {
 3 , 1 , 1000 , true , dups }
 , {
 4 , 2 , 900 , true }
 , {
 5 , 1 , 800 , true }
 , }
 ;
 ACMatches matches ;
 PopulateAutocompleteMatches ( data , arraysize ( data ) , & matches ) ;
 matches [ 0 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo" ) ;
 matches [ 1 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo2" ) ;
 matches [ 2 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo&oq=f" ) ;
 matches [ 3 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo&aqs=0" ) ;
 matches [ 4 ] . destination_url = GURL ( "http://www.foo.com/" ) ;
 matches [ 5 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo2&oq=f" ) ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : INVALID_SPEC , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 3U , result . size ( ) ) ;
 ASSERT_EQ ( 4U , result . match_at ( 0 ) -> duplicate_matches . size ( ) ) ;
 const AutocompleteMatch * first_match = result . match_at ( 0 ) ;
 EXPECT_EQ ( matches [ 2 ] . destination_url , first_match -> duplicate_matches . at ( 1 ) . destination_url ) ;
 EXPECT_EQ ( dup_match . destination_url , first_match -> duplicate_matches . at ( 2 ) . destination_url ) ;
 EXPECT_EQ ( matches [ 3 ] . destination_url , first_match -> duplicate_matches . at ( 3 ) . destination_url ) ;
 ASSERT_EQ ( 1U , result . match_at ( 1 ) -> duplicate_matches . size ( ) ) ;
 EXPECT_EQ ( matches [ 5 ] . destination_url , result . match_at ( 1 ) -> duplicate_matches . at ( 0 ) . destination_url ) ;
 }