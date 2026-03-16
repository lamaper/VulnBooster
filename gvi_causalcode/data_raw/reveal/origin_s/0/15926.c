TEST_F ( TemplateURLTest , ExtractSearchTermsFromURL ) {
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
 base : : string16 result ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http: 
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/?espv&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/?espv=1&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/?espv=0&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/#q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/#espv&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/#espv=1&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/#espv=0&q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "something" ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.ca/?q=something" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.ca/?q=something&q=anything" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/foo/?q=foo" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "https://google.com/?q=foo" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "foo" ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com:8080/?q=foo" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/?q=1+2+3&b=456" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "1 2 3" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?q=123#q=456" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "456" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?a=012&q=123&b=456#f=789" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "123" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?a=012&q=123&b=456#j=abc&q=789&h=def9" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "789" ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?q=" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?#q=" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?q=#q=" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_FALSE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?q=123#q=" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : string16 ( ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://google.com/alt/?q=#q=123" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "123" ) , result ) ;
 }