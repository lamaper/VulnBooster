TEST_F ( TemplateURLTest , ReplaceInputType ) {
 struct TestData {
 const base : : string16 search_term ;
 metrics : : OmniboxInputType : : Type input_type ;
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 ASCIIToUTF16 ( "foo" ) , metrics : : OmniboxInputType : : UNKNOWN , "{
google:baseURL}
?{
searchTerms}
&{
google:inputType}
" , "http://www.google.com/?foo&oit=1&" }
 , {
 ASCIIToUTF16 ( "foo" ) , metrics : : OmniboxInputType : : URL , "{
google:baseURL}
?{
searchTerms}
&{
google:inputType}
" , "http://www.google.com/?foo&oit=3&" }
 , {
 ASCIIToUTF16 ( "foo" ) , metrics : : OmniboxInputType : : FORCED_QUERY , "{
google:baseURL}
?{
searchTerms}
&{
google:inputType}
" , "http://www.google.com/?foo&oit=5&" }
 , }
 ;
 TemplateURLData data ;
 data . input_encodings . push_back ( "UTF-8" ) ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 data . SetURL ( test_data [ i ] . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( test_data [ i ] . search_term ) ;
 search_terms_args . input_type = test_data [ i ] . input_type ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }