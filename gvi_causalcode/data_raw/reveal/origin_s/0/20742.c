TEST_F ( TemplateURLTest , ParseURLEmpty ) {
 TemplateURL url ( ( TemplateURLData ( ) ) ) ;
 TemplateURLRef : : Replacements replacements ;
 bool valid = false ;
 EXPECT_EQ ( std : : string ( ) , url . url_ref ( ) . ParseURL ( std : : string ( ) , & replacements , NULL , & valid ) ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 EXPECT_TRUE ( valid ) ;
 }