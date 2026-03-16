TEST_F ( TemplateURLParserTest , TestEmptyKeyword ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "empty_keyword.xml" , nullptr ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Example" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_EQ ( "https://www.example.com/search?q={
searchTerms}
" , template_url_ -> url ( ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "example.com" ) , template_url_ -> keyword ( ) ) ;
 }