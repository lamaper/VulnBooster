TEST_F ( TemplateURLTest , SearchboxVersionIncludedForAnswers ) {
 TemplateURLData data ;
 search_terms_data_ . set_google_base_url ( "http://bar/" ) ;
 data . SetURL ( "http://bar/search?q={
searchTerms}
&{
google:searchVersion}
xssi=t" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foo" ) ) ;
 std : : string result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/search?q=foo&gs_rn=42&xssi=t" , result ) ;
 }