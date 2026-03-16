void xmlHashScan ( xmlHashTablePtr table , xmlHashScanner f , void * data ) {
 stubData stubdata ;
 stubdata . data = data ;
 stubdata . hashscanner = f ;
 xmlHashScanFull ( table , stubHashScannerFull , & stubdata ) ;
 }