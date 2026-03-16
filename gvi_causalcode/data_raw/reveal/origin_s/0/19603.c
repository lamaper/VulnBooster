TEST_F ( TemplateURLTest , RLZ ) {
 base : : string16 rlz_string = search_terms_data_ . GetRlzParameterValue ( false ) ;
 TemplateURLData data ;
 data . SetURL ( "http://bar/?{
google:RLZ}
{
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( ASCIIToUTF16 ( "x" ) ) , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( "http://bar/?rlz=" + base : : UTF16ToUTF8 ( rlz_string ) + "&x" , result . spec ( ) ) ;
 }