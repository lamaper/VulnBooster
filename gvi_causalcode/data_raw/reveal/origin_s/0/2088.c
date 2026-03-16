TEST_F ( TemplateURLParserTest , TestFirefoxEbay ) {
 ParamFilterImpl filter ( "ebay" , "ebay" ) ;
 ASSERT_NO_FATAL_FAILURE ( ParseFile ( "firefox_ebay.xml" , & filter ) ) ;
 ASSERT_TRUE ( template_url_ ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "eBay" ) , template_url_ -> short_name ( ) ) ;
 EXPECT_TRUE ( template_url_ -> url_ref ( ) . SupportsReplacement ( SearchTermsData ( ) ) ) ;
 EXPECT_EQ ( "http://search.ebay.com/search/search.dll?query={
searchTerms}
&" "MfcISAPICommand=GetResult&ht=1&srchdesc=n&maxRecordsReturned=300&" "maxRecordsPerPage=50&SortProperty=MetaEndSort" , template_url_ -> url ( ) ) ;
 ASSERT_EQ ( 1U , template_url_ -> input_encodings ( ) . size ( ) ) ;
 EXPECT_EQ ( "ISO-8859-1" , template_url_ -> input_encodings ( ) [ 0 ] ) ;
 EXPECT_EQ ( GURL ( "http://search.ebay.com/favicon.ico" ) , template_url_ -> favicon_url ( ) ) ;
 }