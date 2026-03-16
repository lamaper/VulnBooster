TEST_F ( TemplateURLTest , URLRefTestIndices ) {
 TemplateURLData data ;
 data . SetURL ( "http://foo{
searchTerms}
x{
startIndex?}
y{
startPage?}
" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_TRUE ( url . url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 GURL result ( url . url_ref ( ) . ReplaceSearchTerms ( TemplateURLRef : : SearchTermsArgs ( ASCIIToUTF16 ( "X" ) ) , search_terms_data_ ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( "http://fooxxy/" , result . spec ( ) ) ;
 }