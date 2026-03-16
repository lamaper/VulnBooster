TEST_F ( TemplateURLTest , ReplaceSearchTermsInURL ) {
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

 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms ( ASCIIToUTF16 ( "Bob Morane" ) ) ;
 GURL result ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http: 
 EXPECT_EQ ( GURL ( "http://google.com/?q=Bob+Morane" ) , result ) ;
 result = GURL ( "http://should.not.change.com" ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.ca/?q=something" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://should.not.change.com" ) , result ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/foo/?q=foo" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "https://google.com/?q=foo" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "https://google.com/?q=Bob+Morane" ) , result ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com:8080/?q=foo" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/?q=1+2+3&b=456" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://google.com/?q=Bob+Morane&b=456" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?q=123#q=456" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://google.com/alt/?q=123#q=Bob+Morane" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?a=012&q=123&b=456#f=789" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://google.com/alt/?a=012&q=Bob+Morane&b=456#f=789" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?a=012&q=123&b=456#j=abc&q=789&h=def9" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://google.com/alt/?a=012&q=123&b=456" "#j=abc&q=Bob+Morane&h=def9" ) , result ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?q=" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?#q=" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?q=#q=" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?q=123#q=" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://google.com/alt/?q=#q=123" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://google.com/alt/?q=#q=Bob+Morane" ) , result ) ;
 }