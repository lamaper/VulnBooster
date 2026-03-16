TEST_F ( TemplateURLTest , InvalidateCachedValues ) {
 TemplateURLData data ;
 data . SetURL ( "{
google:baseURL}
search?q={
searchTerms}
" ) ;
 data . suggestions_url = "{
google:baseSuggestURL}
search?q={
searchTerms}
" ;
 data . instant_url = "{
google:baseURL}
webhp" ;
 data . image_url = "{
google:baseURL}
searchbyimage/upload" ;
 data . new_tab_url = "{
google:baseURL}
_/chromeewtab" ;
 data . contextual_search_url = "{
google:baseURL}
_/contextualsearch" ;
 data . alternate_urls . push_back ( "{
google:baseURL}
s#q={
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "X" ) ) ;
 base : : string16 search_terms ;
 EXPECT_TRUE ( url . HasGoogleBaseURLs ( search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/search?q=X" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/s#q=X" , url . url_refs ( ) [ 0 ] . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/search?q=X" , url . url_refs ( ) [ 1 ] . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/complete/search?q=X" , url . suggestions_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/webhp" , url . instant_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/searchbyimage/upload" , url . image_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/_/chromeewtab" , url . new_tab_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "http://www.google.com/_/contextualsearch" , url . contextual_search_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://www.google.com/search?q=Y+Z" ) , search_terms_data_ , & search_terms ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "Y Z" ) , search_terms ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://www.google.com/s#q=123" ) , search_terms_data_ , & search_terms ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "123" ) , search_terms ) ;
 search_terms_data_ . set_google_base_url ( "https://www.foo.org/" ) ;
 url . InvalidateCachedValues ( ) ;
 EXPECT_TRUE ( url . HasGoogleBaseURLs ( search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/search?q=X" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/s#q=X" , url . url_refs ( ) [ 0 ] . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/search?q=X" , url . url_refs ( ) [ 1 ] . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/complete/search?q=X" , url . suggestions_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/webhp" , url . instant_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/searchbyimage/upload" , url . image_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/_/chromeewtab" , url . new_tab_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_EQ ( "https://www.foo.org/_/contextualsearch" , url . contextual_search_url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "https://www.foo.org/search?q=Y+Z" ) , search_terms_data_ , & search_terms ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "Y Z" ) , search_terms ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "https://www.foo.org/s#q=123" ) , search_terms_data_ , & search_terms ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "123" ) , search_terms ) ;
 search_terms_data_ . set_google_base_url ( "http://www.google.com/" ) ;
 }