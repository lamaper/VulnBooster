TEST_F ( TemplateURLTest , HasSearchTermsReplacementKey ) {
 TemplateURLData data ;
 data . SetURL ( "http://google.com/?q={
searchTerms}
" ) ;
 data . instant_url = "http://google.com/instant#q={
searchTerms}
" ;
 data . alternate_urls . push_back ( "http://google.com/alt/#q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://google.com/alt/?ext=foo&q={
searchTerms}

 data . search_terms_replacement_key = "espv" ;
 TemplateURL url ( data ) ;
 EXPECT_FALSE ( url . HasSearchTermsReplacementKey ( GURL ( "http: 
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/#espv" ) ) ) ;
 EXPECT_FALSE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something&espv" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something&espv=1" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something&espv=0" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv&q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv=1&q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv=0&q=something" ) ) ) ;
 EXPECT_FALSE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#q=something&espv" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#q=something&espv=1" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#q=something&espv=0" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#espv&q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#espv=1&q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/alt/#espv=0&q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv#q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?espv=1#q=something" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something#espv" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://google.com/?q=something#espv=1" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://bing.com/?espv" ) ) ) ;
 EXPECT_TRUE ( url . HasSearchTermsReplacementKey ( GURL ( "http://bing.com/#espv" ) ) ) ;
 }