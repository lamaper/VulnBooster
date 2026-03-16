void WriteData ( Archive * AHX , const void * data , size_t dLen ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 if ( ! AH -> currToc ) exit_horribly ( modulename , "internal error -- WriteData cannot be called outside the context of a DataDumper routine\n" ) ;
 ( * AH -> WriteDataPtr ) ( AH , data , dLen ) ;
 return ;
 }