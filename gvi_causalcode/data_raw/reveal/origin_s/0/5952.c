static void stubHashScannerFull ( void * payload , void * data , const xmlChar * name , const xmlChar * name2 ATTRIBUTE_UNUSED , const xmlChar * name3 ATTRIBUTE_UNUSED ) {
 stubData * stubdata = ( stubData * ) data ;
 stubdata -> hashscanner ( payload , stubdata -> data , ( xmlChar * ) name ) ;
 }