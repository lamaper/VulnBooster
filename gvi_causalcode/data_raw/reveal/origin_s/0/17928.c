TEST_F ( TemplateURLTest , PrefetchQueryParameters ) {
 TemplateURLData data ;
 search_terms_data_ . set_google_base_url ( "http://bar/" ) ;
 data . SetURL ( "http://bar/search?q={
searchTerms}
&{
google:prefetchQuery}
xssi=t" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foo" ) ) ;
 search_terms_args . prefetch_query = "full query text" ;
 search_terms_args . prefetch_query_type = "2338" ;
 std : : string result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/search?q=foo&pfq=full%20query%20text&qha=2338&xssi=t" , result ) ;
 TemplateURL url2 ( data ) ;
 search_terms_args . prefetch_query . clear ( ) ;
 search_terms_args . prefetch_query_type . clear ( ) ;
 result = url2 . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/search?q=foo&xssi=t" , result ) ;
 }