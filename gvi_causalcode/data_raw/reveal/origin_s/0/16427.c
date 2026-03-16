TEST_F ( TemplateURLTest , URLRefTermToWide ) {
 struct ToWideCase {
 const char * encoded_search_term ;
 const base : : string16 expected_decoded_term ;
 }
 to_wide_cases [ ] = {
 {
 "hello+world" , ASCIIToUTF16 ( "hello world" ) }
 , {
 "%a7A%A6%6e+to+you" , base : : WideToUTF16 ( L"\x4f60\x597d to you" ) }
 , {
 "%e4%bd%a05%e5%a5%bd+to+you" , base : : WideToUTF16 ( L"\x4f60\x35\x597d to you" ) }
 , {
 "%91%01+abcd" , base : : WideToUTF16 ( L"%91%01 abcd" ) }
 , {
 "C%2B%2B" , ASCIIToUTF16 ( "C++" ) }
 , {
 "C%252B" , ASCIIToUTF16 ( "C%2B" ) }
 , }
 ;
 TemplateURLData data ;
 data . SetURL ( "http://foo?q={
searchTerms}
" ) ;
 data . input_encodings . push_back ( "big-5" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 for ( size_t i = 0 ;
 i < arraysize ( to_wide_cases ) ;
 i ++ ) {
 EXPECT_EQ ( to_wide_cases [ i ] . expected_decoded_term , url . url_ref ( ) . SearchTermToString16 ( to_wide_cases [ i ] . encoded_search_term ) ) ;
 }
 }