TEST_F ( TemplateURLTest , ReplaceCursorPosition ) {
 struct TestData {
 const base : : string16 search_term ;
 size_t cursor_position ;
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 ASCIIToUTF16 ( "foo" ) , base : : string16 : : npos , "{
google:baseURL}
?{
searchTerms}
&{
google:cursorPosition}
" , "http://www.google.com/?foo&" }
 , {
 ASCIIToUTF16 ( "foo" ) , 2 , "{
google:baseURL}
?{
searchTerms}
&{
google:cursorPosition}
" , "http://www.google.com/?foo&cp=2&" }
 , {
 ASCIIToUTF16 ( "foo" ) , 15 , "{
google:baseURL}
?{
searchTerms}
&{
google:cursorPosition}
" , "http://www.google.com/?foo&cp=15&" }
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
 search_terms_args . cursor_position = test_data [ i ] . cursor_position ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }