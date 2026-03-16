TEST_F ( TemplateURLTest , Suggestions ) {
 struct TestData {
 const int accepted_suggestion ;
 const base : : string16 original_query_for_suggestion ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 TemplateURLRef : : NO_SUGGESTIONS_AVAILABLE , base : : string16 ( ) , "http://bar/foo?q=foobar" }
 , {
 TemplateURLRef : : NO_SUGGESTIONS_AVAILABLE , ASCIIToUTF16 ( "foo" ) , "http://bar/foo?q=foobar" }
 , {
 TemplateURLRef : : NO_SUGGESTION_CHOSEN , base : : string16 ( ) , "http://bar/foo?q=foobar" }
 , {
 TemplateURLRef : : NO_SUGGESTION_CHOSEN , ASCIIToUTF16 ( "foo" ) , "http://bar/foo?q=foobar" }
 , {
 0 , base : : string16 ( ) , "http://bar/foo?oq=&q=foobar" }
 , {
 1 , ASCIIToUTF16 ( "foo" ) , "http://bar/foo?oq=foo&q=foobar" }
 , }
 ;
 TemplateURLData data ;
 data . SetURL ( "http://bar/foo?{
google:originalQueryForSuggestion}
" "q={
searchTerms}
" ) ;
 data . input_encodings . push_back ( "UTF-8" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foobar" ) ) ;
 search_terms_args . accepted_suggestion = test_data [ i ] . accepted_suggestion ;
 search_terms_args . original_query = test_data [ i ] . original_query_for_suggestion ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }