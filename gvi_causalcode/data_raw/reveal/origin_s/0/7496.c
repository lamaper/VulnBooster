TEST_F ( TemplateURLTest , SetPrepopulatedAndParse ) {
 TemplateURLData data ;
 data . SetURL ( "http://foo{
fhqwhgads}
bar" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 bool valid = false ;
 EXPECT_EQ ( "http://foo{
fhqwhgads}
bar" , url . url_ref ( ) . ParseURL ( "http://foo{
fhqwhgads}
bar" , & replacements , NULL , & valid ) ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 EXPECT_TRUE ( valid ) ;
 data . prepopulate_id = 123 ;
 TemplateURL url2 ( data ) ;
 EXPECT_EQ ( "http://foobar" , url2 . url_ref ( ) . ParseURL ( "http://foo{
fhqwhgads}
bar" , & replacements , NULL , & valid ) ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 EXPECT_TRUE ( valid ) ;
 }