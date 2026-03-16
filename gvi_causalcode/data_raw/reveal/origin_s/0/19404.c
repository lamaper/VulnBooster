TEST_F ( TemplateURLTest , ParseParameterKnown ) {
 std : : string parsed_url ( "{
searchTerms}
" ) ;
 TemplateURLData data ;
 data . SetURL ( parsed_url ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 EXPECT_TRUE ( url . url_ref ( ) . ParseParameter ( 0 , 12 , & parsed_url , & replacements ) ) ;
 EXPECT_EQ ( std : : string ( ) , parsed_url ) ;
 ASSERT_EQ ( 1U , replacements . size ( ) ) ;
 EXPECT_EQ ( 0U , replacements [ 0 ] . index ) ;
 EXPECT_EQ ( TemplateURLRef : : SEARCH_TERMS , replacements [ 0 ] . type ) ;
 }