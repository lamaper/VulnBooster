TEST_F ( TemplateURLParserTest , TestDictionary ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "dictionary.xml" , nullptr ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Dictionary.com" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_EQ ( GURL ( "http://cache.lexico.com/g/d/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://dictionary.reference.com/browse/{
searchTerms}
?r=75" , template_url_ -> url ( ) ) ;
 }