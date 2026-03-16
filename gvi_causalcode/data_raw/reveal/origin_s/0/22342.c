TEST_F ( TemplateURLTest , ReplaceAssistedQueryStats ) {
 struct TestData {
 const base : : string16 search_term ;
 const std : : string aqs ;
 const std : : string base_url ;
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 ASCIIToUTF16 ( "foo" ) , "chrome.0.0l6" , "http://foo/" , "{
google:baseURL}
?{
searchTerms}
{
google:assistedQueryStats}
" , "http://foo/?foo" }
 , {
 ASCIIToUTF16 ( "foo" ) , "chrome.0.0l6" , "https://foo/" , "{
google:baseURL}
?{
searchTerms}
{
google:assistedQueryStats}
" , "https://foo/?fooaqs=chrome.0.0l6&" }
 , {
 ASCIIToUTF16 ( "foo" ) , "" , "https://foo/" , "{
google:baseURL}
?{
searchTerms}
{
google:assistedQueryStats}
" , "https://foo/?foo" }
 , {
 ASCIIToUTF16 ( "foo" ) , "chrome.0.0l6" , "http://www.google.com" , "http://foo?{
searchTerms}
{
google:assistedQueryStats}
" , "http://foo/?foo" }
 , {
 ASCIIToUTF16 ( "foo" ) , "chrome.0.0l6" , "https://www.google.com" , "https://foo?{
searchTerms}
{
google:assistedQueryStats}
" , "https://foo/?fooaqs=chrome.0.0l6&" }
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
 search_terms_args . assisted_query_stats = test_data [ i ] . aqs ;
 search_terms_data_ . set_google_base_url ( test_data [ i ] . base_url ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }