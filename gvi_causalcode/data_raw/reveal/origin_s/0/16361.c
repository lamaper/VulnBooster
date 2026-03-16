TEST_F ( TemplateURLTest , HostAndSearchTermKey ) {
 struct TestData {
 const std : : string url ;
 const std : : string host ;
 const std : : string path ;
 const std : : string search_term_key ;
 }
 test_data [ ] = {
 {
 "http://blah/?foo=bar&q={
searchTerms}
&b=x" , "blah" , "/" , "q" }
 , {
 "http://blah/{
searchTerms}
" , "blah" , "/" , "" }
 , {
 "http://blah/" , "" , "" , "" }
 , {
 "http://blah/?q={
searchTerms}
&x={
searchTerms}
" , "" , "" , "" }
 , {
 "http://{
searchTerms}
" , "" , "" , "" }
 , {
 "http://blah/?q={
searchTerms}
" , "blah" , "/" , "q" }
 , {
 "https://blah/?q={
searchTerms}
" , "blah" , "/" , "q" }
 , {
 "http://blah/?q=stock:{
searchTerms}
" , "blah" , "/" , "q" }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 TemplateURLData data ;
 data . SetURL ( test_data [ i ] . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_EQ ( test_data [ i ] . host , url . url_ref ( ) . GetHost ( search_terms_data_ ) ) ;
 EXPECT_EQ ( test_data [ i ] . path , url . url_ref ( ) . GetPath ( search_terms_data_ ) ) ;
 EXPECT_EQ ( test_data [ i ] . search_term_key , url . url_ref ( ) . GetSearchTermKey ( search_terms_data_ ) ) ;
 }
 }