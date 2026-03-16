TEST_F ( TemplateURLTest , ExtractSearchTermsFromUTF8URL ) {
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
 base : : string16 result ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://utf-8.ru/?q=%D0%97%D0%B4%D1%80%D0%B0%D0%B2%D1%81%D1%82" "%D0%B2%D1%83%D0%B9,+%D0%BC%D0%B8%D1%80!" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0417\x0434\x0440\x0430\x0432\x0441\x0442\x0432\x0443\x0439, " L"\x043C\x0438\x0440!" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://utf-8.ru/#q=%D0%B4%D0%B2%D0%B0+%D1%81%D0%BB%D0%BE%D0%B2" "%D0%B0" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0434\x0432\x0430 \x0441\x043B\x043E\x0432\x0430" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://utf-8.ru/path/%D0%B1%D1%83%D0%BA%D0%B2%D1%8B%20%D0%90%20" "%D0%B8%20A" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0431\x0443\x043A\x0432\x044B \x0410 \x0438 A" ) , result ) ;
 }