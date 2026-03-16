TEST_F ( TemplateURLTest , ContextualSearchParameters ) {
 TemplateURLData data ;
 search_terms_data_ . set_google_base_url ( "http://bar/" ) ;
 data . SetURL ( "http://bar/_/contextualsearch?" "{
google:contextualSearchVersion}
" "{
google:contextualSearchContextData}
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foo" ) ) ;
 std : : string result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/_/contextualsearch?ctxsl_resolve=1" , result ) ;
 TemplateURLRef : : SearchTermsArgs : : ContextualSearchParams params ( 1 , 6 , 11 , "allen" , "woody+allen+movies" , "www.wikipedia.org" , "utf-8" , true ) ;
 search_terms_args . contextual_search_params = params ;
 result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://bar/_/contextualsearch?" "ctxs=1&" "ctxs_start=6&" "ctxs_end=11&" "q=allen&" "ctxs_content=woody+allen+movies&" "ctxsl_url=www.wikipedia.org&" "ctxs_encoding=utf-8&" "ctxsl_resolve=1" , result ) ;
 }