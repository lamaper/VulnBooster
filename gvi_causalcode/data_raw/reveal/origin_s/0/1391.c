TEST_F ( TemplateURLTest , TestValidWithComplete ) {
 TemplateURLData data ;
 data . SetURL ( "{
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 EXPECT_TRUE ( url . url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 }