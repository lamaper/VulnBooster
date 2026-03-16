static inline void RENAME(yuv2rgb2)(uint16_t *buf0, uint16_t *buf1, uint16_t *uvbuf0, uint16_t *uvbuf1,

			    uint8_t *dest, int dstW, int yalpha, int uvalpha, int dstbpp)

{

	int yalpha1=yalpha^4095;

	int uvalpha1=uvalpha^4095;



	if(fullUVIpol)

	{


		if(dstbpp == 32)

		{

			asm volatile(





FULL_YSCALEYUV2RGB

			"punpcklbw %%mm1, %%mm3		\n\t"  

			"punpcklbw %%mm7, %%mm0		\n\t"  



			"movq %%mm3, %%mm1		\n\t"

			"punpcklwd %%mm0, %%mm3		\n\t"  

			"punpckhwd %%mm0, %%mm1		\n\t"  



			MOVNTQ(%%mm3, (%4, %%eax, 4))

			MOVNTQ(%%mm1, 8(%4, %%eax, 4))



			"addl $4, %%eax			\n\t"

			"cmpl %5, %%eax			\n\t"

			" jb 1b				\n\t"





			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}

		else if(dstbpp==24)

		{

			asm volatile(



FULL_YSCALEYUV2RGB



								 

			"punpcklbw %%mm1, %%mm3		\n\t"  

			"punpcklbw %%mm7, %%mm0		\n\t"  



			"movq %%mm3, %%mm1		\n\t"

			"punpcklwd %%mm0, %%mm3		\n\t"  

			"punpckhwd %%mm0, %%mm1		\n\t"  



			"movq %%mm3, %%mm2		\n\t"  

			"psrlq $8, %%mm3		\n\t"  

			"pand "MANGLE(bm00000111)", %%mm2\n\t"  

			"pand "MANGLE(bm11111000)", %%mm3\n\t"  

			"por %%mm2, %%mm3		\n\t"  

			"movq %%mm1, %%mm2		\n\t"

			"psllq $48, %%mm1		\n\t"  

			"por %%mm1, %%mm3		\n\t"  



			"movq %%mm2, %%mm1		\n\t"  

			"psrld $16, %%mm2		\n\t"  

			"psrlq $24, %%mm1		\n\t"  

			"por %%mm2, %%mm1		\n\t"  



			"movl %4, %%ebx			\n\t"

			"addl %%eax, %%ebx		\n\t"


			 

			"movntq %%mm3, (%%ebx, %%eax, 2)\n\t"

			"movntq %%mm1, 8(%%ebx, %%eax, 2)\n\t"


			"movd %%mm3, (%%ebx, %%eax, 2)	\n\t"

			"psrlq $32, %%mm3		\n\t"

			"movd %%mm3, 4(%%ebx, %%eax, 2)	\n\t"

			"movd %%mm1, 8(%%ebx, %%eax, 2)	\n\t"


			"addl $4, %%eax			\n\t"

			"cmpl %5, %%eax			\n\t"

			" jb 1b				\n\t"



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "m" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax", "%ebx"

			);

		}

		else if(dstbpp==15)

		{

			asm volatile(



FULL_YSCALEYUV2RGB


			"paddusb "MANGLE(g5Dither)", %%mm1\n\t"

			"paddusb "MANGLE(r5Dither)", %%mm0\n\t"

			"paddusb "MANGLE(b5Dither)", %%mm3\n\t"


			"punpcklbw %%mm7, %%mm1		\n\t"  

			"punpcklbw %%mm7, %%mm3		\n\t"  

			"punpcklbw %%mm7, %%mm0		\n\t"  



			"psrlw $3, %%mm3		\n\t"

			"psllw $2, %%mm1		\n\t"

			"psllw $7, %%mm0		\n\t"

			"pand "MANGLE(g15Mask)", %%mm1	\n\t"

			"pand "MANGLE(r15Mask)", %%mm0	\n\t"



			"por %%mm3, %%mm1		\n\t"

			"por %%mm1, %%mm0		\n\t"



			MOVNTQ(%%mm0, (%4, %%eax, 2))



			"addl $4, %%eax			\n\t"

			"cmpl %5, %%eax			\n\t"

			" jb 1b				\n\t"



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}

		else if(dstbpp==16)

		{

			asm volatile(



FULL_YSCALEYUV2RGB


			"paddusb "MANGLE(g6Dither)", %%mm1\n\t"

			"paddusb "MANGLE(r5Dither)", %%mm0\n\t"

			"paddusb "MANGLE(b5Dither)", %%mm3\n\t"


			"punpcklbw %%mm7, %%mm1		\n\t"  

			"punpcklbw %%mm7, %%mm3		\n\t"  

			"punpcklbw %%mm7, %%mm0		\n\t"  



			"psrlw $3, %%mm3		\n\t"

			"psllw $3, %%mm1		\n\t"

			"psllw $8, %%mm0		\n\t"

			"pand "MANGLE(g16Mask)", %%mm1	\n\t"

			"pand "MANGLE(r16Mask)", %%mm0	\n\t"



			"por %%mm3, %%mm1		\n\t"

			"por %%mm1, %%mm0		\n\t"



			MOVNTQ(%%mm0, (%4, %%eax, 2))



			"addl $4, %%eax			\n\t"

			"cmpl %5, %%eax			\n\t"

			" jb 1b				\n\t"



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}


		if(dstbpp==32 || dstbpp==24)

		{

			int i;

			for(i=0;i<dstW;i++){

				 

				int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

				int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);

				dest[0]=clip_table[((Y + yuvtab_40cf[U]) >>13)];

				dest[1]=clip_table[((Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13)];

				dest[2]=clip_table[((Y + yuvtab_3343[V]) >>13)];

				dest+=dstbpp>>3;

			}

		}

		else if(dstbpp==16)

		{

			int i;

			for(i=0;i<dstW;i++){

				 

				int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

				int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);



				((uint16_t*)dest)[i] =

					clip_table16b[(Y + yuvtab_40cf[U]) >>13] |

					clip_table16g[(Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13] |

					clip_table16r[(Y + yuvtab_3343[V]) >>13];

			}

		}

		else if(dstbpp==15)

		{

			int i;

			for(i=0;i<dstW;i++){

				 

				int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

				int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);



				((uint16_t*)dest)[i] =

					clip_table15b[(Y + yuvtab_40cf[U]) >>13] |

					clip_table15g[(Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13] |

					clip_table15r[(Y + yuvtab_3343[V]) >>13];

			}

		}


	} 

	else

	{


		if(dstbpp == 32)

		{

			asm volatile(

				YSCALEYUV2RGB

				WRITEBGR32



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}

		else if(dstbpp==24)

		{

			asm volatile(

				"movl %4, %%ebx			\n\t"

				YSCALEYUV2RGB

				WRITEBGR24



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "m" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax", "%ebx"

			);

		}

		else if(dstbpp==15)

		{

			asm volatile(

				YSCALEYUV2RGB


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g5Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"




				WRITEBGR15



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}

		else if(dstbpp==16)

		{

			asm volatile(

				YSCALEYUV2RGB


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g6Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"




				WRITEBGR16



			:: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

			"m" (yalpha1), "m" (uvalpha1)

			: "%eax"

			);

		}


		if(dstbpp==32)

		{

			int i;

			for(i=0; i<dstW-1; i+=2){

				 

				int Y1=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int Y2=yuvtab_2568[((buf0[i+1]*yalpha1+buf1[i+1]*yalpha)>>19)];

				int U=((uvbuf0[i>>1]*uvalpha1+uvbuf1[i>>1]*uvalpha)>>19);

				int V=((uvbuf0[(i>>1)+2048]*uvalpha1+uvbuf1[(i>>1)+2048]*uvalpha)>>19);



				int Cb= yuvtab_40cf[U];

				int Cg= yuvtab_1a1e[V] + yuvtab_0c92[U];

				int Cr= yuvtab_3343[V];



				dest[4*i+0]=clip_table[((Y1 + Cb) >>13)];

				dest[4*i+1]=clip_table[((Y1 + Cg) >>13)];

				dest[4*i+2]=clip_table[((Y1 + Cr) >>13)];



				dest[4*i+4]=clip_table[((Y2 + Cb) >>13)];

				dest[4*i+5]=clip_table[((Y2 + Cg) >>13)];

				dest[4*i+6]=clip_table[((Y2 + Cr) >>13)];

			}

		}

		else if(dstbpp==24)

		{

			int i;

			for(i=0; i<dstW-1; i+=2){

				 

				int Y1=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int Y2=yuvtab_2568[((buf0[i+1]*yalpha1+buf1[i+1]*yalpha)>>19)];

				int U=((uvbuf0[i>>1]*uvalpha1+uvbuf1[i>>1]*uvalpha)>>19);

				int V=((uvbuf0[(i>>1)+2048]*uvalpha1+uvbuf1[(i>>1)+2048]*uvalpha)>>19);



				int Cb= yuvtab_40cf[U];

				int Cg= yuvtab_1a1e[V] + yuvtab_0c92[U];

				int Cr= yuvtab_3343[V];



				dest[0]=clip_table[((Y1 + Cb) >>13)];

				dest[1]=clip_table[((Y1 + Cg) >>13)];

				dest[2]=clip_table[((Y1 + Cr) >>13)];



				dest[3]=clip_table[((Y2 + Cb) >>13)];

				dest[4]=clip_table[((Y2 + Cg) >>13)];

				dest[5]=clip_table[((Y2 + Cr) >>13)];

				dest+=6;

			}

		}

		else if(dstbpp==16)

		{

			int i;

			for(i=0; i<dstW-1; i+=2){

				 

				int Y1=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int Y2=yuvtab_2568[((buf0[i+1]*yalpha1+buf1[i+1]*yalpha)>>19)];

				int U=((uvbuf0[i>>1]*uvalpha1+uvbuf1[i>>1]*uvalpha)>>19);

				int V=((uvbuf0[(i>>1)+2048]*uvalpha1+uvbuf1[(i>>1)+2048]*uvalpha)>>19);



				int Cb= yuvtab_40cf[U];

				int Cg= yuvtab_1a1e[V] + yuvtab_0c92[U];

				int Cr= yuvtab_3343[V];



				((uint16_t*)dest)[i] =

					clip_table16b[(Y1 + Cb) >>13] |

					clip_table16g[(Y1 + Cg) >>13] |

					clip_table16r[(Y1 + Cr) >>13];



				((uint16_t*)dest)[i+1] =

					clip_table16b[(Y2 + Cb) >>13] |

					clip_table16g[(Y2 + Cg) >>13] |

					clip_table16r[(Y2 + Cr) >>13];

			}

		}

		else if(dstbpp==15)

		{

			int i;

			for(i=0; i<dstW-1; i+=2){

				 

				int Y1=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

				int Y2=yuvtab_2568[((buf0[i+1]*yalpha1+buf1[i+1]*yalpha)>>19)];

				int U=((uvbuf0[i>>1]*uvalpha1+uvbuf1[i>>1]*uvalpha)>>19);

				int V=((uvbuf0[(i>>1)+2048]*uvalpha1+uvbuf1[(i>>1)+2048]*uvalpha)>>19);



				int Cb= yuvtab_40cf[U];

				int Cg= yuvtab_1a1e[V] + yuvtab_0c92[U];

				int Cr= yuvtab_3343[V];



				((uint16_t*)dest)[i] =

					clip_table15b[(Y1 + Cb) >>13] |

					clip_table15g[(Y1 + Cg) >>13] |

					clip_table15r[(Y1 + Cr) >>13];



				((uint16_t*)dest)[i+1] =

					clip_table15b[(Y2 + Cb) >>13] |

					clip_table15g[(Y2 + Cg) >>13] |

					clip_table15r[(Y2 + Cr) >>13];

			}

		}


	}  

}
