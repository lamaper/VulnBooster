TEST_F ( TemplateURLTest , SessionToken ) {
 TemplateURLData data ;
 search_terms_data_ . set_google_base_url ( "http://bar/" ) ;
 data . SetURL ( "http://bar/search?q={
searchTerms}
&{
google:sessionToken}
xssi=t" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foo" ) ) ;
 search_terms_args . session_token = "SESSIONTOKENGOESHERE" ;
 std : : string result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/search?q=foo&psi=SESSIONTOKENGOESHERE&xssi=t" , result ) ;
 TemplateURL url2 ( data ) ;
 search_terms_args . session_token = "" ;
 result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/search?q=foo&xssi=t" , result ) ;
 }