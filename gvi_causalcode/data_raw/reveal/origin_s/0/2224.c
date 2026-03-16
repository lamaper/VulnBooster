TEST_F ( TemplateURLParserTest , FailOnBogusURL ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "bogus.xml" , nullptr ) ) ;
 EXPECT_FALSE ( template_url_ ) ;
 }