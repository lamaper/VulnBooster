TEST_F ( TransportSecurityPersisterTest , SerializeDataOld ) {
 std : : string output = "{
 " "\"NiyD+3J1r6z1wjl2n1ALBu94Zj9OsEAMo0kCN8js0Uk=\": {
" "\"expiry\": 1266815027.983453, " "\"include_subdomains\": false, " "\"mode\": \"strict\" " "}
" "}
" ;
 bool dirty ;
 EXPECT_TRUE ( persister_ -> LoadEntries ( output , & dirty ) ) ;
 EXPECT_TRUE ( dirty ) ;
 }