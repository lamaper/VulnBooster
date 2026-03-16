TEST_F ( TemplateURLTest , SearchClient ) {
 const std : : string base_url_str ( "http://google.com/?" ) ;
 const std : : string terms_str ( "{
searchTerms}
&{
google:searchClient}
" ) ;
 const std : : string full_url_str = base_url_str + terms_str ;
 const base : : string16 terms ( ASCIIToUTF16 ( terms_str ) ) ;
 search_terms_data_ . set_google_base_url ( base_url_str ) ;
 TemplateURLData data ;
 data . SetURL ( full_url_str ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foobar" ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( "http://google.com/?foobar&" , result . spec ( ) ) ;
 search_terms_data_ . set_search_client ( "search_client" ) ;
 GURL result_2 ( url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result_2 . is_valid ( ) ) ;
 EXPECT_EQ ( "http://google.com/?foobar&client=search_client&" , result_2 . spec ( ) ) ;
 }