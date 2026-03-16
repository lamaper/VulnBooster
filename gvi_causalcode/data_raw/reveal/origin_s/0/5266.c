TEST_F ( TemplateURLTest , ParseURLNoTemplateEnd ) {
 TemplateURLData data ;
 data . SetURL ( "{
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 bool valid = false ;
 EXPECT_EQ ( std : : string ( ) , url . url_ref ( ) . ParseURL ( "{
" , & replacements , NULL , & valid ) ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 EXPECT_FALSE ( valid ) ;
 }