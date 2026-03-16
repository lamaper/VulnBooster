TEST_F ( TemplateURLTest , ExtractSearchTermsFromURLPath ) {
 TemplateURLData data ;
 data . SetURL ( "http://term-in-path.com/begin/{
searchTerms}
/end" ) ;
 TemplateURL url ( data ) ;
 base : : string16 result ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/begin/something/end" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/begin/a%20b%20c/end" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "a b c" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/begin/1+2+3/end" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "1+2+3" ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/about" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/begin" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://term-in-path.com/end" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 }