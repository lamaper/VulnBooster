afs_int32 SPR_ChangeEntry ( struct rx_call * call , afs_int32 aid , char * name , afs_int32 oid , afs_int32 newid ) {
 afs_int32 code ;
 afs_int32 cid = ANONYMOUSID ;
 code = changeEntry ( call , aid , name , oid , newid , & cid ) ;
 osi_auditU ( call , PTS_ChgEntEvent , code , AUD_ID , aid , AUD_STR , name , AUD_LONG , oid , AUD_LONG , newid , AUD_END ) ;
 ViceLog ( 5 , ( "PTS_ChangeEntry: code %d cid %d aid %d name %s oid %d newid %d\n" , code , cid , aid , name , oid , newid ) ) ;
 return code ;
 }