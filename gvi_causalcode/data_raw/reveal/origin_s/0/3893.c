TEST_F ( TemplateURLTest , ReplaceSearchTermsInUTF8URL ) {
 TemplateURLData data ;
 data . SetURL ( "http://utf-8.ru/?q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://utf-8.ru/#q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://utf-8.ru/path/{
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms ( base : : WideToUTF16 ( L"\x0442\x0435\x043A\x0441\x0442" ) ) ;
 GURL result ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://utf-8.ru/?q=a+b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://utf-8.ru/?q=%D1%82%D0%B5%D0%BA%D1%81%D1%82" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://utf-8.ru/#q=a+b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://utf-8.ru/#q=%D1%82%D0%B5%D0%BA%D1%81%D1%82" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://utf-8.ru/path/a%20b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://utf-8.ru/path/%D1%82%D0%B5%D0%BA%D1%81%D1%82" ) , result ) ;
 }