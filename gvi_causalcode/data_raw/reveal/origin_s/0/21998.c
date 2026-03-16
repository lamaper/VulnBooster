TEST_F ( TemplateURLTest , ReplaceCurrentPageUrl ) {
 struct TestData {
 const base : : string16 search_term ;
 const std : : string current_page_url ;
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 ASCIIToUTF16 ( "foo" ) , "http://www.google.com/" , "{
google:baseURL}
?{
searchTerms}
&{
google:currentPageUrl}
" , "http://www.google.com/?foo&url=http%3A%2F%2Fwww.google.com%2F&" }
 , {
 ASCIIToUTF16 ( "foo" ) , "" , "{
google:baseURL}
?{
searchTerms}
&{
google:currentPageUrl}
" , "http://www.google.com/?foo&" }
 , {
 ASCIIToUTF16 ( "foo" ) , "http://g.com/+-/*&=" , "{
google:baseURL}
?{
searchTerms}
&{
google:currentPageUrl}
" , "http://www.google.com/?foo&url=http%3A%2F%2Fg.com%2F%2B-%2F*%26%3D&" }
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
 search_terms_args . current_page_url = test_data [ i ] . current_page_url ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }