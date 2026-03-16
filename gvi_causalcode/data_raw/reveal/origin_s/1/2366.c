void xmlHashScan3 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 , xmlHashScanner f , void * data ) {
 xmlHashScanFull3 ( table , name , name2 , name3 , ( xmlHashScannerFull ) f , data ) ;
 }