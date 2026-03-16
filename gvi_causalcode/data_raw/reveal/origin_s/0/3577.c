TEST_F ( TemplateURLTest , ReplaceSearchTermsInURLPath ) {
 TemplateURLData data ;
 data . SetURL ( "http://term-in-path.com/begin/{
searchTerms}
/end" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms ( ASCIIToUTF16 ( "Bob Morane" ) ) ;
 GURL result ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://term-in-path.com/begin/something/end" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://term-in-path.com/begin/Bob%20Morane/end" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://term-in-path.com/begin/1%202%203/end" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://term-in-path.com/begin/Bob%20Morane/end" ) , result ) ;
 result = GURL ( "http://should.not.change.com" ) ;
 EXPECT_FALSE ( url . ReplaceSearchTermsInURL ( GURL ( "http://term-in-path.com/about" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://should.not.change.com" ) , result ) ;
 }