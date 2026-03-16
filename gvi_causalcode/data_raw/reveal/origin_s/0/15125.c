TEST_F ( TemplateURLTest , RLZFromAppList ) {
 base : : string16 rlz_string = search_terms_data_ . GetRlzParameterValue ( true ) ;
 TemplateURLData data ;
 data . SetURL ( "http://bar/?{
google:RLZ}
{
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 TemplateURLRef : : SearchTermsArgs args ( ASCIIToUTF16 ( "x" ) ) ;
 args . from_app_list = true ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( "http://bar/?rlz=" + base : : UTF16ToUTF8 ( rlz_string ) + "&x" , result . spec ( ) ) ;
 }