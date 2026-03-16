static inline void RENAME(yuv2packed1)(SwsContext *c, uint16_t *buf0, uint16_t *uvbuf0, uint16_t *uvbuf1,

			    uint8_t *dest, int dstW, int uvalpha, int dstFormat, int flags, int y)

{

	const int yalpha1=0;

	int i;



	uint16_t *buf1= buf0;  

	const int yalpha= 4096;  



	if(flags&SWS_FULL_CHR_H_INT)

	{

		RENAME(yuv2packed2)(c, buf0, buf0, uvbuf0, uvbuf1, dest, dstW, 0, uvalpha, y);

		return;

	}


	if( uvalpha < 2048 )  

	{

		switch(dstFormat)

		{

		case PIX_FMT_RGB32:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1(%%REGBP, %5)

				WRITEBGR32(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR24:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1(%%REGBP, %5)

				WRITEBGR24(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR555:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1(%%REGBP, %5)


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g5Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"


				WRITEBGR15(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR565:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1(%%REGBP, %5)


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g6Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"




				WRITEBGR16(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_YUYV422:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2PACKED1(%%REGBP, %5)

				WRITEYUY2(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		}

	}

	else

	{

		switch(dstFormat)

		{

		case PIX_FMT_RGB32:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1b(%%REGBP, %5)

				WRITEBGR32(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR24:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1b(%%REGBP, %5)

				WRITEBGR24(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR555:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1b(%%REGBP, %5)


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g5Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"


				WRITEBGR15(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_BGR565:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2RGB1b(%%REGBP, %5)


				"paddusb "MANGLE(b5Dither)", %%mm2\n\t"

				"paddusb "MANGLE(g6Dither)", %%mm4\n\t"

				"paddusb "MANGLE(r5Dither)", %%mm5\n\t"




				WRITEBGR16(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		case PIX_FMT_YUYV422:

			asm volatile(

				"mov %%"REG_b", "ESP_OFFSET"(%5)	\n\t"

				"mov %4, %%"REG_b"			\n\t"

                                "push %%"REG_BP"                        \n\t"

				YSCALEYUV2PACKED1b(%%REGBP, %5)

				WRITEYUY2(%%REGb, 8280(%5), %%REGBP)

                                "pop %%"REG_BP"                         \n\t"

				"mov "ESP_OFFSET"(%5), %%"REG_b"	\n\t"



			:: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

			"a" (&c->redDither)

			);

			return;

		}

	}


	if( uvalpha < 2048 )

	{

		YSCALE_YUV_2_ANYRGB_C(YSCALE_YUV_2_RGB1_C, YSCALE_YUV_2_PACKED1_C)

	}else{

		YSCALE_YUV_2_ANYRGB_C(YSCALE_YUV_2_RGB1B_C, YSCALE_YUV_2_PACKED1B_C)

	}

}
