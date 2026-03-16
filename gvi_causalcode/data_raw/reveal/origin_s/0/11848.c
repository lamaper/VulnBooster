void print_help_box ( char * content ) {
 printf ( "<img src='%s%s' onMouseOver=\"return tooltip('<table border=0 width=100%% height=100%%>" , url_images_path , CONTEXT_HELP_ICON ) ;
 printf ( "<tr><td>%s</td></tr>" , content ) ;
 printf ( "</table>', '&nbsp;
&nbsp;
&nbsp;
Help', 'border:1, width:500, xoffset:-250, yoffset:25, bordercolor:#333399, title_padding:2px, titletextcolor:#FFFFFF, backcolor:#CCCCFF');
\" onMouseOut=\"return hideTip()\"" ) ;
 printf ( " BORDER=0>" ) ;
 return ;
 }