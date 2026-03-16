TEST_F ( UsbBlocklistTest , BasicExclusions ) {
 SetDynamicBlocklist ( "18D1:58F0:0100" ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0090 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0200 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F1 , 0x0100 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58EF , 0x0100 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x18D0 , 0x58F0 , 0x0100 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x18D2 , 0x58F0 , 0x0100 }
 ) ) ;
 }