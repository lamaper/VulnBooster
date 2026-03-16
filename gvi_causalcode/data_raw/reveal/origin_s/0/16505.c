TEST ( IdlCompiler , PropertyValues ) {
 EXPECT_EQ ( 42 , test : : api : : idl_properties : : first ) ;
 EXPECT_EQ ( 42.1 , test : : api : : idl_properties : : second ) ;
 EXPECT_STREQ ( "hello world" , test : : api : : idl_properties : : third ) ;
 }