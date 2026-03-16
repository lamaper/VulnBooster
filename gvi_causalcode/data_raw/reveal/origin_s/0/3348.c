TEST_F ( TemplateURLParserTest , NoCrashOnEmptyAttributes ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "url_with_no_attributes.xml" , nullptr ) ) ;
 }