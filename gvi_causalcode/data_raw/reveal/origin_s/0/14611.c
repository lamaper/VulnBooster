TEST_F ( WebFrameSimTest , NamedLookupIgnoresEmptyNames ) {
 SimRequest main_resource ( "https://example.com/main.html" , "text/html" ) ;
 LoadURL ( "https://example.com/main.html" ) ;
 main_resource . Complete ( R "HTML( < body > < iframe name = "" src = "data:text/html," > < / iframe > < / body > ) HTML ");
 EXPECT_EQ ( nullptr , MainFrame ( ) . GetFrame ( ) -> Tree ( ) . ScopedChild ( "" ) ) ;
 EXPECT_EQ ( nullptr , MainFrame ( ) . GetFrame ( ) -> Tree ( ) . ScopedChild ( AtomicString ( ) ) ) ;
 EXPECT_EQ ( nullptr , MainFrame ( ) . GetFrame ( ) -> Tree ( ) . ScopedChild ( g_empty_atom ) ) ;
 }