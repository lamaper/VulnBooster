TEST_F ( TemplateURLParserTest , PassOnHTTPS ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "https.xml" , nullptr ) ) ;
 EXPECT_TRUE ( template_url_ ) ;
 }