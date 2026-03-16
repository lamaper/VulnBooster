TEST_F ( TemplateURLParserTest , TestFirefoxYahoo ) {
 ParamFilterImpl filter ( std : : string ( ) , "Mozilla" ) ;
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "firefox_yahoo.xml" , & filter ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Yahoo" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://ff.search.yahoo.com/gossip?" "output=fxjson&command={
searchTerms}
" , template_url_ -> suggestions_url ( ) ) ;
 EXPECT_EQ ( "http://search.yahoo.com/search?p={
searchTerms}
&ei=UTF-8" , template_url_ -> url ( ) ) ;
 ASSERT_EQ ( 1U , template_url_ -> input_encodings ( ) . size ( ) ) ;
 EXPECT_EQ ( "UTF-8" , template_url_ -> input_encodings ( ) [ 0 ] ) ;
 EXPECT_EQ ( GURL ( "http://search.yahoo.com/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 }