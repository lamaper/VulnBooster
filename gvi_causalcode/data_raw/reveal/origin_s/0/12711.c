TEST_F ( TemplateURLTest , URLRefTestSearchTerms ) {
 struct SearchTermsCase {
 const char * url ;
 const base : : string16 terms ;
 const std : : string output ;
 }
 search_term_cases [ ] = {
 {
 "http://foo{
searchTerms}
" , ASCIIToUTF16 ( "sea rch/bar" ) , "http://foosea%20rch/bar" }
 , {
 "http://foo{
searchTerms}
?boo=abc" , ASCIIToUTF16 ( "sea rch/bar" ) , "http://foosea%20rch/bar?boo=abc" }
 , {
 "http://foo/?boo={
searchTerms}
" , ASCIIToUTF16 ( "sea rch/bar" ) , "http://foo/?boo=sea+rch%2Fbar" }
 , {
 "http://en.wikipedia.org/{
searchTerms}
" , ASCIIToUTF16 ( "wiki/?" ) , "http://en.wikipedia.org/wiki/%3F" }
 }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( search_term_cases ) ;
 ++ i ) {
 const SearchTermsCase & value = search_term_cases [ i ] ;
 TemplateURLData data ;
 data . SetURL ( value . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( value . terms ) , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( value . output , result . spec ( ) ) ;
 }
 }