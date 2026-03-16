TEST_F ( TemplateURLParserTest , FailOnPost ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "post.xml" , nullptr ) ) ;
 EXPECT_FALSE ( template_url_ ) ;
 }