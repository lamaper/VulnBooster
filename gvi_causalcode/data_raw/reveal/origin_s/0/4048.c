TEST_F ( TemplateURLTest , ExtraQueryParams ) {
 TemplateURLData data ;
 data . SetURL ( "{
google:baseURL}
search?q={
searchTerms}
" "#{
google:originalQueryForSuggestion}
x" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms ( ASCIIToUTF16 ( "abc" ) ) ;
 search_terms . original_query = ASCIIToUTF16 ( "def" ) ;
 search_terms . accepted_suggestion = 0 ;
 EXPECT_EQ ( "http://www.google.com/search?q=abc#oq=def&x" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms , search_terms_data_ ) ) ;
 search_terms . append_extra_query_params = true ;
 EXPECT_EQ ( "http://www.google.com/search?q=abc#oq=def&x" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms , search_terms_data_ ) ) ;
 base : : CommandLine : : ForCurrentProcess ( ) -> AppendSwitchASCII ( switches : : kExtraSearchQueryParams , "a=b" ) ;
 EXPECT_EQ ( "http://www.google.com/search?a=b&q=abc#oq=def&x" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms , search_terms_data_ ) ) ;
 search_terms . append_extra_query_params = false ;
 EXPECT_EQ ( "http://www.google.com/search?q=abc#oq=def&x" , url . url_ref ( ) . ReplaceSearchTerms ( search_terms , search_terms_data_ ) ) ;
 }