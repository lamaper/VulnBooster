TEST_F ( TemplateURLTest , ParseURLTwoParameters ) {
 TemplateURLData data ;
 data . SetURL ( "{
}
{
{
%s}
}
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : Replacements replacements ;
 bool valid = false ;
 EXPECT_EQ ( "{
}
{
}
" , url . url_ref ( ) . ParseURL ( "{
}
{
{
searchTerms}
}
" , & replacements , NULL , & valid ) ) ;
 ASSERT_EQ ( 1U , replacements . size ( ) ) ;
 EXPECT_EQ ( 3U , replacements [ 0 ] . index ) ;
 EXPECT_EQ ( TemplateURLRef : : SEARCH_TERMS , replacements [ 0 ] . type ) ;
 EXPECT_TRUE ( valid ) ;
 }