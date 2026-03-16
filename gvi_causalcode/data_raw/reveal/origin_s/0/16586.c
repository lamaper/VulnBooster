TEST_F ( TemplateURLTest , ReplaceArbitrarySearchTerms ) {
 struct TestData {
 const std : : string encoding ;
 const base : : string16 search_term ;
 const std : : string url ;
 const std : : string expected_result ;
 }
 test_data [ ] = {
 {
 "BIG5" , base : : WideToUTF16 ( L"\x60BD" ) , "http://foo/?{
searchTerms}
{
inputEncoding}
" , "http://foo/?%B1~BIG5" }
 , {
 "UTF-8" , ASCIIToUTF16 ( "blah" ) , "http://foo/?{
searchTerms}
{
inputEncoding}
" , "http://foo/?blahUTF-8" }
 , {
 "Shift_JIS" , base : : UTF8ToUTF16 ( "\xe3\x81\x82" ) , "http://foo/{
searchTerms}
/bar" , "http://foo/%82%A0/bar" }
 , {
 "Shift_JIS" , base : : UTF8ToUTF16 ( "\xe3\x81\x82 \xe3\x81\x84" ) , "http://foo/{
searchTerms}
/bar" , "http://foo/%82%A0%20%82%A2/bar" }
 , }
 ;
 TemplateURLData data ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 data . SetURL ( test_data [ i ] . url ) ;
 data . input_encodings . clear ( ) ;
 data . input_encodings . push_back ( test_data [ i ] . encoding ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( test_data [ i ] . search_term ) , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( test_data [ i ] . expected_result , result . spec ( ) ) ;
 }
 }