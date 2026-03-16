TEST_F ( TemplateURLTest , ReplacePageClassification ) {
 TemplateURLData data ;
 data . input_encodings . push_back ( "UTF-8" ) ;
 data . SetURL ( "{
google:baseURL}
?{
google:pageClassification}
q={
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 TemplateURLRef : : SearchTermsArgs search_terms_args ( ASCIIToUTF16 ( "foo" ) ) ;
 std : : string result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://www.google.com/?q=foo" , result ) ;
 search_terms_args . page_classification = metrics : : OmniboxEventProto : : NTP ;
 result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://www.google.com/?pgcl=1&q=foo" , result ) ;
 search_terms_args . page_classification = metrics : : OmniboxEventProto : : HOME_PAGE ;
 result = url . url_ref ( ) . ReplaceSearchTerms ( search_terms_args , search_terms_data_ ) ;
 EXPECT_EQ ( "http://www.google.com/?pgcl=3&q=foo" , result ) ;
 }