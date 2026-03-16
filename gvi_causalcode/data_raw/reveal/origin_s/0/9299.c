TEST_F ( TemplateURLTest , ReplaceSearchTermsInNonUTF8URL ) {
 TemplateURLData data ;
 data . SetURL ( "http://windows-1251.ru/?q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://windows-1251.ru/#q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://windows-1251.ru/path/{
searchTerms}
" ) ;
 data . input_encodings . push_back ( "windows-1251" ) ;
 TemplateURL url ( data ) ;
 TemplateURLRef : : SearchTermsArgs search_terms ( base : : WideToUTF16 ( L"\x0442\x0435\x043A\x0441\x0442" ) ) ;
 GURL result ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://windows-1251.ru/?q=a+b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://windows-1251.ru/?q=%F2%E5%EA%F1%F2" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://windows-1251.ru/#q=a+b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://windows-1251.ru/#q=%F2%E5%EA%F1%F2" ) , result ) ;
 EXPECT_TRUE ( url . ReplaceSearchTermsInURL ( GURL ( "http://windows-1251.ru/path/a%20b" ) , search_terms , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( GURL ( "http://windows-1251.ru/path/%F2%E5%EA%F1%F2" ) , result ) ;
 }