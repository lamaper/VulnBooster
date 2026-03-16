static void _doSetFixedOutputState ( ArchiveHandle * AH ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 ahprintf ( AH , "SET statement_timeout = 0;
\n" ) ;
 ahprintf ( AH , "SET lock_timeout = 0;
\n" ) ;
 ahprintf ( AH , "SET idle_in_transaction_session_timeout = 0;
\n" ) ;
 ahprintf ( AH , "SET client_encoding = '%s';
\n" , pg_encoding_to_char ( AH -> public . encoding ) ) ;
 ahprintf ( AH , "SET standard_conforming_strings = %s;
\n" , AH -> public . std_strings ? "on" : "off" ) ;
 if ( ropt && ropt -> use_role ) ahprintf ( AH , "SET ROLE %s;
\n" , fmtId ( ropt -> use_role ) ) ;
 ahprintf ( AH , "SET check_function_bodies = false;
\n" ) ;
 ahprintf ( AH , "SET client_min_messages = warning;
\n" ) ;
 if ( ! AH -> public . std_strings ) ahprintf ( AH , "SET escape_string_warning = off;
\n" ) ;
 if ( ropt && ropt -> enable_row_security ) ahprintf ( AH , "SET row_security = on;
\n" ) ;
 else ahprintf ( AH , "SET row_security = off;
\n" ) ;
 ahprintf ( AH , "\n" ) ;
 }