void sun4m_pic_info ( Monitor * mon , const QDict * qdict ) {
 if ( slavio_intctl ) slavio_pic_info ( mon , slavio_intctl ) ;
 }