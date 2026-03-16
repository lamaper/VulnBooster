TEST_F ( TemplateURLParserTest , TestMSDN ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "msdn.xml" , nullptr ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Search \" MSDN" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_EQ ( GURL ( "http://search.msdn.microsoft.com/search/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://search.msdn.microsoft.com/search/default.aspx?" "Query={
searchTerms}
&brand=msdn&locale=en-US" , template_url_ -> url ( ) ) ;
 }