TEST ( IdlCompiler , ObjectTypes ) {
 FooType f1 ;
 f1 . x = 3 ;
 std : : unique_ptr < base : : DictionaryValue > serialized_foo = f1 . ToValue ( ) ;
 FooType f2 ;
 EXPECT_TRUE ( FooType : : Populate ( * serialized_foo . get ( ) , & f2 ) ) ;
 EXPECT_EQ ( f1 . x , f2 . x ) ;
 BarType b1 ;
 b1 . x . reset ( new base : : Value ( 7 ) ) ;
 std : : unique_ptr < base : : DictionaryValue > serialized_bar = b1 . ToValue ( ) ;
 BarType b2 ;
 EXPECT_TRUE ( BarType : : Populate ( * serialized_bar . get ( ) , & b2 ) ) ;
 int tmp_int = 0 ;
 EXPECT_TRUE ( b2 . x -> GetAsInteger ( & tmp_int ) ) ;
 EXPECT_EQ ( 7 , tmp_int ) ;
 std : : unique_ptr < base : : DictionaryValue > icon_props ( new base : : DictionaryValue ( ) ) ;
 icon_props -> SetString ( "hello" , "world" ) ;
 ObjectFunction1 : : Params : : Icon icon ;
 EXPECT_TRUE ( ObjectFunction1 : : Params : : Icon : : Populate ( * ( icon_props . get ( ) ) , & icon ) ) ;
 base : : ListValue list ;
 list . Append ( std : : move ( icon_props ) ) ;
 std : : unique_ptr < ObjectFunction1 : : Params > params = ObjectFunction1 : : Params : : Create ( list ) ;
 ASSERT_TRUE ( params . get ( ) != NULL ) ;
 std : : string tmp ;
 EXPECT_TRUE ( params -> icon . additional_properties . GetString ( "hello" , & tmp ) ) ;
 EXPECT_EQ ( "world" , tmp ) ;
 }