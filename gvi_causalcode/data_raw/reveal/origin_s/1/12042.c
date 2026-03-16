TEST_F ( AutocompleteResultTest , SortAndCullDuplicateSearchURLs ) {
 TemplateURLData url_data ;
 url_data . SetShortName ( base : : ASCIIToUTF16 ( "unittest" ) ) ;
 url_data . SetKeyword ( base : : ASCIIToUTF16 ( "foo" ) ) ;
 url_data . SetURL ( "http://www.foo.com/s?q={
searchTerms}
" ) ;
 template_url_service_ . get ( ) -> Add ( new TemplateURL ( url_data ) ) ;
 TestData data [ ] = {
 {
 0 , 1 , 1300 , true }
 , {
 1 , 1 , 1200 , true }
 , {
 2 , 1 , 1100 , true }
 , {
 3 , 1 , 1000 , true }
 , {
 4 , 2 , 900 , true }
 , }
 ;
 ACMatches matches ;
 PopulateAutocompleteMatches ( data , arraysize ( data ) , & matches ) ;
 matches [ 0 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo" ) ;
 matches [ 1 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo2" ) ;
 matches [ 2 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo&oq=f" ) ;
 matches [ 3 ] . destination_url = GURL ( "http://www.foo.com/s?q=foo&aqs=0" ) ;
 matches [ 4 ] . destination_url = GURL ( "http://www.foo.com/" ) ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : INVALID_SPEC , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , std : : string ( ) , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 3U , result . size ( ) ) ;
 EXPECT_EQ ( "http://www.foo.com/s?q=foo" , result . match_at ( 0 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( 1300 , result . match_at ( 0 ) -> relevance ) ;
 EXPECT_EQ ( "http://www.foo.com/s?q=foo2" , result . match_at ( 1 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( 1200 , result . match_at ( 1 ) -> relevance ) ;
 EXPECT_EQ ( "http://www.foo.com/" , result . match_at ( 2 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( 900 , result . match_at ( 2 ) -> relevance ) ;
 }