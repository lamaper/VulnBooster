static void handle_transform ( TSCont contp ) {
 TSVConn output_conn ;
 TSVIO write_vio ;
 int64_t towrite ;
 int64_t avail ;
 output_conn = TSTransformOutputVConnGet ( contp ) ;
 write_vio = TSVConnWriteVIOGet ( contp ) ;
 auto * data = static_cast < AppendTransformTestData * > ( TSContDataGet ( contp ) ) ;
 if ( ! data -> output_buffer ) {
 towrite = TSVIONBytesGet ( write_vio ) ;
 if ( towrite != INT64_MAX ) {
 towrite += append_buffer_length ;
 }
 data -> output_buffer = TSIOBufferCreate ( ) ;
 data -> output_reader = TSIOBufferReaderAlloc ( data -> output_buffer ) ;
 data -> output_vio = TSVConnWrite ( output_conn , contp , data -> output_reader , towrite ) ;
 }
 ink_assert ( data -> output_vio ) ;
 if ( ! TSVIOBufferGet ( write_vio ) ) {
 if ( data -> append_needed ) {
 data -> append_needed = 0 ;
 TSIOBufferCopy ( TSVIOBufferGet ( data -> output_vio ) , append_buffer_reader , append_buffer_length , 0 ) ;
 }
 TSVIONBytesSet ( data -> output_vio , TSVIONDoneGet ( write_vio ) + append_buffer_length ) ;
 TSVIOReenable ( data -> output_vio ) ;
 return ;
 }
 towrite = TSVIONTodoGet ( write_vio ) ;
 if ( towrite > 0 ) {
 avail = TSIOBufferReaderAvail ( TSVIOReaderGet ( write_vio ) ) ;
 if ( towrite > avail ) {
 towrite = avail ;
 }
 if ( towrite > 0 ) {
 TSIOBufferCopy ( TSVIOBufferGet ( data -> output_vio ) , TSVIOReaderGet ( write_vio ) , towrite , 0 ) ;
 TSIOBufferReaderConsume ( TSVIOReaderGet ( write_vio ) , towrite ) ;
 TSVIONDoneSet ( write_vio , TSVIONDoneGet ( write_vio ) + towrite ) ;
 }
 }
 if ( TSVIONTodoGet ( write_vio ) > 0 ) {
 if ( towrite > 0 ) {
 TSVIOReenable ( data -> output_vio ) ;
 TSContCall ( TSVIOContGet ( write_vio ) , TS_EVENT_VCONN_WRITE_READY , write_vio ) ;
 }
 }
 else {
 if ( data -> append_needed ) {
 data -> append_needed = 0 ;
 TSIOBufferCopy ( TSVIOBufferGet ( data -> output_vio ) , append_buffer_reader , append_buffer_length , 0 ) ;
 }
 TSVIONBytesSet ( data -> output_vio , TSVIONDoneGet ( write_vio ) + append_buffer_length ) ;
 TSVIOReenable ( data -> output_vio ) ;
 TSContCall ( TSVIOContGet ( write_vio ) , TS_EVENT_VCONN_WRITE_COMPLETE , write_vio ) ;
 }
 }