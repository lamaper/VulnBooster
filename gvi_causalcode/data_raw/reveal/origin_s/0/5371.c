TEST_F ( OmniboxViewViewsTest , Emphasis ) {
 constexpr struct {
 const char * input ;
 bool expected_base_text_emphasized ;
 Range expected_emphasis_range ;
 Range expected_scheme_range ;
 }
 test_cases [ ] = {
 {
 "data:text/html,Hello%20World" , false , Range ( 0 , 4 ) , Range ( 0 , 4 ) }
 , {
 "http://www.example.com/path/file.htm" , false , Range ( 7 , 22 ) , Range ( 0 , 4 ) }
 , {
 "https://www.example.com/path/file.htm" , false , Range ( 8 , 23 ) , Range ( 0 , 5 ) }
 , {
 "chrome-extension://ldfbacdbackkjhclmhnjabngnppnkagl" , false , Range : : InvalidRange ( ) , Range ( 0 , 16 ) }
 , {
 "nosuchscheme://opaque/string" , true , Range : : InvalidRange ( ) , Range ( 0 , 12 ) }
 , {
 "nosuchscheme:opaquestring" , true , Range : : InvalidRange ( ) , Range ( 0 , 12 ) }
 , {
 "host.com/path/file" , false , Range ( 0 , 8 ) , Range : : InvalidRange ( ) }
 , {
 "This is plain text" , true , Range : : InvalidRange ( ) , Range : : InvalidRange ( ) }
 , }
 ;
 for ( const auto & test_case : test_cases ) {
 SCOPED_TRACE ( test_case . input ) ;
 SetAndEmphasizeText ( test_case . input , false ) ;
 EXPECT_EQ ( TestingOmniboxView : : to_base_text_emphasis ( test_case . expected_base_text_emphasized ) , omnibox_view ( ) -> base_text_emphasis ( ) ) ;
 EXPECT_EQ ( test_case . expected_emphasis_range , omnibox_view ( ) -> emphasis_range ( ) ) ;
 EXPECT_FALSE ( omnibox_view ( ) -> scheme_range ( ) . IsValid ( ) ) ;
 if ( test_case . expected_scheme_range . IsValid ( ) ) {
 SetAndEmphasizeText ( test_case . input , true ) ;
 EXPECT_EQ ( TestingOmniboxView : : to_base_text_emphasis ( test_case . expected_base_text_emphasized ) , omnibox_view ( ) -> base_text_emphasis ( ) ) ;
 EXPECT_EQ ( test_case . expected_emphasis_range , omnibox_view ( ) -> emphasis_range ( ) ) ;
 EXPECT_EQ ( test_case . expected_scheme_range , omnibox_view ( ) -> scheme_range ( ) ) ;
 }
 }
 }