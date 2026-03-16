void PrintTOCSummary ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 RestoreOptions * ropt = AH -> public . ropt ;
 TocEntry * te ;
 teSection curSection ;
 OutputContext sav ;
 const char * fmtName ;
 char stamp_str [ 64 ] ;
 sav = SaveOutput ( AH ) ;
 if ( ropt -> filename ) SetOutput ( AH , ropt -> filename , 0 ) ;
 if ( strftime ( stamp_str , sizeof ( stamp_str ) , PGDUMP_STRFTIME_FMT , localtime ( & AH -> createDate ) ) == 0 ) strcpy ( stamp_str , "[unknown]" ) ;
 ahprintf ( AH , ";
\n;
 Archive created at %s\n" , stamp_str ) ;
 ahprintf ( AH , ";
 dbname: %s\n;
 TOC Entries: %d\n;
 Compression: %d\n" , AH -> archdbname , AH -> tocCount , AH -> compression ) ;
 switch ( AH -> format ) {
 case archCustom : fmtName = "CUSTOM" ;
 break ;
 case archDirectory : fmtName = "DIRECTORY" ;
 break ;
 case archTar : fmtName = "TAR" ;
 break ;
 default : fmtName = "UNKNOWN" ;
 }
 ahprintf ( AH , ";
 Dump Version: %d.%d-%d\n" , AH -> vmaj , AH -> vmin , AH -> vrev ) ;
 ahprintf ( AH , ";
 Format: %s\n" , fmtName ) ;
 ahprintf ( AH , ";
 Integer: %d bytes\n" , ( int ) AH -> intSize ) ;
 ahprintf ( AH , ";
 Offset: %d bytes\n" , ( int ) AH -> offSize ) ;
 if ( AH -> archiveRemoteVersion ) ahprintf ( AH , ";
 Dumped from database version: %s\n" , AH -> archiveRemoteVersion ) ;
 if ( AH -> archiveDumpVersion ) ahprintf ( AH , ";
 Dumped by pg_dump version: %s\n" , AH -> archiveDumpVersion ) ;
 ahprintf ( AH , ";
\n;
\n;
 Selected TOC Entries:\n;
\n" ) ;
 curSection = SECTION_PRE_DATA ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( te -> section != SECTION_NONE ) curSection = te -> section ;
 if ( ropt -> verbose || ( _tocEntryRequired ( te , curSection , ropt ) & ( REQ_SCHEMA | REQ_DATA ) ) != 0 ) ahprintf ( AH , "%d;
 %u %u %s %s %s %s\n" , te -> dumpId , te -> catalogId . tableoid , te -> catalogId . oid , te -> desc , te -> namespace ? te -> namespace : "-" , te -> tag , te -> owner ) ;
 if ( ropt -> verbose && te -> nDeps > 0 ) {
 int i ;
 ahprintf ( AH , ";
\tdepends on:" ) ;
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) ahprintf ( AH , " %d" , te -> dependencies [ i ] ) ;
 ahprintf ( AH , "\n" ) ;
 }
 }
 if ( ropt -> strict_names ) StrictNamesCheck ( ropt ) ;
 if ( ropt -> filename ) RestoreOutput ( AH , sav ) ;
 }