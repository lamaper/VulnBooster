TEST_F ( TemplateURLParserTest , TestWikipedia ) {
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "wikipedia.xml" , nullptr ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Wikipedia (English)" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_EQ ( GURL ( "http://en.wikipedia.org/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://en.wikipedia.org/w/index.php?" "title=Special:Search&search={
searchTerms}
" , template_url_ -> url ( ) ) ;
 EXPECT_TRUE ( template_url_ -> suggestions_url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://en.wikipedia.org/w/api.php?" "action=opensearch&search={
searchTerms}
" , template_url_ -> suggestions_url ( ) ) ;
 ASSERT_EQ ( 2U , template_url_ -> input_encodings ( ) . size ( ) ) ;
 EXPECT_EQ ( "UTF-8" , template_url_ -> input_encodings ( ) [ 0 ] ) ;
 EXPECT_EQ ( "Shift_JIS" , template_url_ -> input_encodings ( ) [ 1 ] ) ;
 }