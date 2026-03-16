TEST_F ( TemplateURLTest , DisplayURLToURLRef ) {
 struct TestData {
 const std : : string url ;
 const base : : string16 expected_result ;
 }
 test_data [ ] = {
 {
 "http://foo{
searchTerms}
x{
inputEncoding}
y{
outputEncoding}
a" , ASCIIToUTF16 ( "http://foo%sx{
inputEncoding}
y{
outputEncoding}
a" ) }
 , {
 "http://X" , ASCIIToUTF16 ( "http://X" ) }
 , {
 "http://foo{
searchTerms" , ASCIIToUTF16 ( "http://foo{
searchTerms" ) }
 , {
 "http://foo{
searchTerms}
{
language}
" , ASCIIToUTF16 ( "http://foo%s{
language}
" ) }
 , }
 ;
 TemplateURLData data ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 data . SetURL ( test_data [ i ] . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , url . url_ref ( ) . DisplayURL ( search_terms_data_ ) ) ;
 EXPECT_EQ ( test_data [ i ] . url , TemplateURLRef : : DisplayURLToURLRef ( url . url_ref ( ) . DisplayURL ( search_terms_data_ ) ) ) ;
 }
 }