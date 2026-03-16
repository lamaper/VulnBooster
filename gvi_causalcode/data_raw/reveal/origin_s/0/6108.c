static double convert_timevalue_to_scalar ( Datum value , Oid typid ) {
 switch ( typid ) {
 case TIMESTAMPOID : return DatumGetTimestamp ( value ) ;
 case TIMESTAMPTZOID : return DatumGetTimestampTz ( value ) ;
 case ABSTIMEOID : return DatumGetTimestamp ( DirectFunctionCall1 ( abstime_timestamp , value ) ) ;
 case DATEOID : return date2timestamp_no_overflow ( DatumGetDateADT ( value ) ) ;
 case INTERVALOID : {
 Interval * interval = DatumGetIntervalP ( value ) ;



 case RELTIMEOID : # ifdef HAVE_INT64_TIMESTAMP return ( DatumGetRelativeTime ( value ) * 1000000.0 ) ;


 TimeInterval tinterval = DatumGetTimeInterval ( value ) ;



 }
 case TIMEOID : return DatumGetTimeADT ( value ) ;
 case TIMETZOID : {
 TimeTzADT * timetz = DatumGetTimeTzADTP ( value ) ;



 }
 elog ( ERROR , "unsupported type: %u" , typid ) ;
 return 0 ;
 }