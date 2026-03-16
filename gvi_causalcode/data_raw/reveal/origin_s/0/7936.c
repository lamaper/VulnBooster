static const char * qemuAgentStringifyErrorClass ( const char * klass ) {
 if ( STREQ_NULLABLE ( klass , "BufferOverrun" ) ) return "Buffer overrun" ;
 else if ( STREQ_NULLABLE ( klass , "CommandDisabled" ) ) return "The command has been disabled for this instance" ;
 else if ( STREQ_NULLABLE ( klass , "CommandNotFound" ) ) return "The command has not been found" ;
 else if ( STREQ_NULLABLE ( klass , "FdNotFound" ) ) return "File descriptor not found" ;
 else if ( STREQ_NULLABLE ( klass , "InvalidParameter" ) ) return "Invalid parameter" ;
 else if ( STREQ_NULLABLE ( klass , "InvalidParameterType" ) ) return "Invalid parameter type" ;
 else if ( STREQ_NULLABLE ( klass , "InvalidParameterValue" ) ) return "Invalid parameter value" ;
 else if ( STREQ_NULLABLE ( klass , "OpenFileFailed" ) ) return "Cannot open file" ;
 else if ( STREQ_NULLABLE ( klass , "QgaCommandFailed" ) ) return "Guest agent command failed" ;
 else if ( STREQ_NULLABLE ( klass , "QMPBadInputObjectMember" ) ) return "Bad QMP input object member" ;
 else if ( STREQ_NULLABLE ( klass , "QMPExtraInputObjectMember" ) ) return "Unexpected extra object member" ;
 else if ( STREQ_NULLABLE ( klass , "UndefinedError" ) ) return "An undefined error has occurred" ;
 else if ( STREQ_NULLABLE ( klass , "Unsupported" ) ) return "this feature or command is not currently supported" ;
 else if ( klass ) return klass ;
 else return "unknown QEMU command error" ;
 }