TEST_F ( TransportSecurityPersisterTest , SerializeData1 ) {
 std : : string output ;
 bool dirty ;
 EXPECT_TRUE ( persister_ -> SerializeData ( & output ) ) ;
 EXPECT_TRUE ( persister_ -> LoadEntries ( output , & dirty ) ) ;
 EXPECT_FALSE ( dirty ) ;
 }