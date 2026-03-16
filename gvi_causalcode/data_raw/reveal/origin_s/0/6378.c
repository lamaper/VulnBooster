TEST_F ( TemplateURLParserTest , TestKeyword ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "keyword.xml" , nullptr ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Example" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_EQ ( "https://www.example.com/search?q={
searchTerms}
" , template_url_ -> url ( ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "moose" ) , template_url_ -> keyword ( ) ) ;
 }