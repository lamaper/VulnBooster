TEST_F ( TemplateURLTest , URLRefTestSearchTermsUsingTermsData ) {
 struct SearchTermsCase {
 const char * url ;
 const base : : string16 terms ;
 const char * output ;
 }
 search_term_cases [ ] = {
 {
 "{
google:baseURL}
{
language}
{
searchTerms}
" , base : : string16 ( ) , "http://example.com/e/en" }
 , {
 "{
google:baseSuggestURL}
{
searchTerms}
" , base : : string16 ( ) , "http://example.com/complete/" }
 }
 ;
 TestingSearchTermsData search_terms_data ( "http://example.com/e/" ) ;
 TemplateURLData data ;
 for ( size_t i = 0 ;
 i < arraysize ( search_term_cases ) ;
 ++ i ) {
 const SearchTermsCase & value = search_term_cases [ i ] ;
 data . SetURL ( value . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( value . terms ) , search_terms_data , NULL ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( value . output , result . spec ( ) ) ;
 }
 }