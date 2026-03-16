TEST_F ( TemplateURLTest , ParseURLNoKnownParameters ) {
 TemplateURLData data ;
 data . SetURL ( "{
}
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 bool valid = false ;
 EXPECT_EQ ( "{
}
" , url . url_ref ( ) . ParseURL ( "{
}
" , & replacements , NULL , & valid ) ) ;
 EXPECT_TRUE ( replacements . empty ( ) ) ;
 EXPECT_TRUE ( valid ) ;
 }