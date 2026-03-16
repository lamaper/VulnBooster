static void TestValidOriginIdentifier ( bool expected_result , const std : : string & id ) {
 EXPECT_EQ ( expected_result , DatabaseUtil : : IsValidOriginIdentifier ( id ) ) ;
 }