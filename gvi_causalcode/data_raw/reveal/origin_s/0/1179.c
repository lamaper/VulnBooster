TEST_F ( TemplateURLTest , ParseParameterUnknown ) {
 std : : string parsed_url ( "{
fhqwhgads}
abc" ) ;
 TemplateURLData data ;
 data . SetURL ( parsed_url ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 EXPECT_FALSE ( url . url_ref ( ) . ParseParameter ( 0 , 10 , & parsed_url , & replacements ) ) ;
 EXPECT_EQ ( "{
fhqwhgads}
abc" , parsed_url ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 parsed_url = "{
fhqwhgads}
abc" ;
 data . prepopulate_id = 1 ;
 TemplateURL url2 ( data ) ;
 EXPECT_TRUE ( url2 . url_ref ( ) . ParseParameter ( 0 , 10 , & parsed_url , & replacements ) ) ;
 EXPECT_EQ ( "abc" , parsed_url ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 }