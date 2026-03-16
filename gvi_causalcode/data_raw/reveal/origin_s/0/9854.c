TEST_F ( TemplateURLParserTest , TestFirefoxWebster ) {
 ParamFilterImpl filter ( std : : string ( ) , "Mozilla" ) ;
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "firefox_webster.xml" , & filter ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Webster" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://www.webster.com/cgi-bin/dictionary?va={
searchTerms}
" , template_url_ -> url ( ) ) ;
 ASSERT_EQ ( 1U , template_url_ -> input_encodings ( ) . size ( ) ) ;
 EXPECT_EQ ( "ISO-8859-1" , template_url_ -> input_encodings ( ) [ 0 ] ) ;
 EXPECT_EQ ( GURL ( "http://www.webster.com/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 }