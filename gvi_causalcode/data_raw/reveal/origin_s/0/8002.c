TEST_F ( TemplateURLTest , ReplaceSearchTerms ) {
 struct TestData {
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 "http://foo/{
language}
{
searchTerms}
{
inputEncoding}
" , "http://foo/{
language}
XUTF-8" }
 , {
 "http://foo/{
language}
{
inputEncoding}
{
searchTerms}
" , "http://foo/{
language}
UTF-8X" }
 , {
 "http://foo/{
searchTerms}
{
language}
{
inputEncoding}
" , "http://foo/X{
language}
UTF-8" }
 , {
 "http://foo/{
searchTerms}
{
inputEncoding}
{
language}
" , "http://foo/XUTF-8{
language}
" }
 , {
 "http://foo/{
inputEncoding}
{
searchTerms}
{
language}
" , "http://foo/UTF-8X{
language}
" }
 , {
 "http://foo/{
inputEncoding}
{
language}
{
searchTerms}
" , "http://foo/UTF-8{
language}
X" }
 , {
 "http://foo/{
language}
a{
searchTerms}
a{
inputEncoding}
a" , "http://foo/{
language}
aXaUTF-8a" }
 , {
 "http://foo/{
language}
a{
inputEncoding}
a{
searchTerms}
a" , "http://foo/{
language}
aUTF-8aXa" }
 , {
 "http://foo/{
searchTerms}
a{
language}
a{
inputEncoding}
a" , "http://foo/Xa{
language}
aUTF-8a" }
 , {
 "http://foo/{
searchTerms}
a{
inputEncoding}
a{
language}
a" , "http://foo/XaUTF-8a{
language}
a" }
 , {
 "http://foo/{
inputEncoding}
a{
searchTerms}
a{
language}
a" , "http://foo/UTF-8aXa{
language}
a" }
 , {
 "http://foo/{
inputEncoding}
a{
language}
a{
searchTerms}
a" , "http://foo/UTF-8a{
language}
aXa" }
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
 std : : string expected_result = test_data [ i ] . expected_result ;
 base : : ReplaceSubstringsAfterOffset ( & expected_result , 0 , "{
language}
" , search_terms_data_ . GetApplicationLocale ( ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( ASCIIToUTF16 ( "X" ) ) , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( expected_result , result . spec ( ) ) ;
 }
 }