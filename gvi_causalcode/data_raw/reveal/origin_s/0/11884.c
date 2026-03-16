void TSRecordDump ( int rec_type , TSRecordDumpCb callback , void * edata ) {
 RecDumpRecords ( ( RecT ) rec_type , ( RecDumpEntryCb ) callback , edata ) ;
 }