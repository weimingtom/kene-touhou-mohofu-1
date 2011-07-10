
#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	�v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�~���[�W�b�N���[�� ���z���َ�
---------------------------------------------------------*/

#include "kanji_system.h"

enum
{
	MOJI_00 = 0,MOJI_01,	MOJI_02,	MOJI_03,
	MOJI_04,	MOJI_05,	MOJI_06,	MOJI_07,
	MOJI_08,	MOJI_09,	MOJI_10,	MOJI_11,
	MOJI_12,	MOJI_13,	MOJI_14,	MOJI_15,
	MOJI_16,	MOJI_17,	MOJI_18,	MOJI_19,
	MOJI_20,	MOJI_21,	MOJI_22,	MOJI_23,
	MOJI_24,	MOJI_25,	MOJI_26,	MOJI_27,
	MOJI_28,	MOJI_29_MAX 	/* �ő吔 */
};

enum
{
	SOUND_TYPE_00_BGM = 0,
	SOUND_TYPE_01_SOUND,
	SOUND_TYPE_02_QUIT,
	SOUND_TYPE_03_MAX,
};

#define MAX_KEY_NAMES_21		(MOJI_29_MAX+SOUND_TYPE_03_MAX)
/*
���ߕ���(�V�t�gJIS��2�o�C�g�ڂ�0x5c�A���Ȃ킿'\'('�_')�ł��镶���̂��ƁB)
	�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
*/



static void music_room_draw_message(int cursor1, int cursor2)
{
//	kanji_window_all_clear();				/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
	static const char *const_kaisetu_str[(MOJI_29_MAX)+(1)/*(�N���p���b�Z�[�W)*/][(3)] =
	{
		//								"-------------------------------------"
		//	"SOUND ���",				"BGM ���", 								"-------------------------------------"
		{	"�V���b�g", 				"�Ȃ��~�߂܂�", 							"�e�ɂ͖������ǂ��ł���ˁB",					},/* */
		{	"���j���[����", 			"No.1 �t�̖���",							"1�ʂ̃e�[�}�ł��B",							},/* */
	//	{	"���j���[�I��", 			"No.2 �o�b�h�E�A�b�v�� �` Bad Apple!!", 	"2�ʂ̃e�[�}�ł��B",							},/* */
		{	"���j���[�I��", 			"No.2 ���}���e�B�b�N�E�`���h����",			"2�ʂ̃e�[�}�ł��B",							},/* */
		{	"�{�X�ޏ�", 				"No.3 ���H���[�W��1969",					"3�ʂ̃e�[�}�ł��B",							},/* */
		{	"�s�`���[��",				"No.4 �t�H�[���I�u�t�H�[�� �` �H�߂���",	"4�ʂ̃e�[�}�ł��B",							},/* */
		{	"�A�C�e���擾", 			"No.5 ���A�����@�}����",					"5�ʂ̃e�[�}�ł��B",							},/* */
		{	"������",					"No.6 ���C�h�ƌ��̉������v",				"6�ʂ̃e�[�}�ł��B",							},/* */
		{	"�����J�[�h",				"No.7 ���� �` Innocent Treasures",			"�X�^�b�t���[���̃e�[�}�ł��B", 				},/* */ 	// ����Ȋw���I�u���� Innocent Treasures�v
		{	"�U�R�|����",				"No.8 ���[�l�C�g�G���t",					"�G�L�X�g���X�e�[�W�̃e�[�}�ł��B", 			},/* */
		{	"�O���C�Y", 				"No.9 ���쌶�z����",						"�t�@���^�Y���X�e�[�W�̃e�[�}�ł��B",			},/* */
		{	"���Ԑ���", 				"No.10 ��C�g����  �` Chinese Tea", 		"�G���f�B���O2�̃e�[�}�ł��B",					},/* */
		{	"�L��������",				"No.11 �l�`�ٔ� �` �l�̌`�M�т�����",		"�A���X�̃e�[�}�ł��B", 						},/* */
		{	"�{�X�V���b�g1",			"No.12 �R���v���[�g�E�_�[�N�l�X",			"�����̃e�[�}�ł��B",							},/* */ 	// Complete Darkness
		{	"�{�X�V���b�g2",			"No.13 �|����� �` Lunatic Princess",		"�H���R �P��̃e�[�}�ł��B",					},/* */
		{	"�{�X�V���b�g3",			"No.14 ���_����",							"�˖��� ���̃e�[�}�ł��B",						},/* */
		{	"�{�X�V���b�g4",			"No.15 ���N�g�K�[�� �` ��������",			"�p�`�����[�E�m�[���b�W�̃e�[�}�ł��B", 		},/* */
		{	"�{�X�V���b�g5",			"No.16 �����v �` ���i�E�_�C�A��",			"�\\�Z�� ���̃e�[�}�ł��B",					},/* */
		{	"�{�X����1",				"No.17 ���Ă�Η���",						"�`���m�̃e�[�}�ł��B", 						},/* */
		{	""/*"���g�p18��"*/, 		"No.18 �O�����A �I�u �A���X",				"�A���X�̃e�[�}�ł��B", 						},/* */ 	// Grimoire of Alice
		{	""/*"���g�p19��"*/, 		"No.19 ���F�}�X�^�[�X�p�[�N",				"���J �������̃e�[�}�ł��B",					},/* */
		{	""/*"���g�p20��"*/, 		"No.20 �L�L�ˉ����� �` Till When?", 		"�d���̃e�[�}�ł��B",							},/* */
		{	""/*"���g�p21��"*/, 		"No.21 �S�������ׂ̈̃Z�v�e�b�g",			"���~���A�E�X�J�[���b�g�̃e�[�}�ł��B", 		},/* */
		{	""/*"���g�p22��"*/, 		"No.22 U.N.�I�[�G���͔ޏ��Ȃ̂��H", 		"�t�����h�[���E�X�J�[���b�g�̃e�[�}�ł��B", 	},/* */
		{	""/*"���g�p23��"*/, 		"No.23 �����Y�z�� �` capriccio",			"���� �얲�̃e�[�}�ł��B",						},/* */ 	// Capriccio == ��z��(���y�p��,�C�^���A��), Un sogno capriccioso == �C�܂���Ȗ�(�C�^���A��)
		{	""/*"���g�p24��"*/, 		"No.24 �d����s",							"���[�~�A�̃e�[�}�ł��B",						},/* */
		{	""/*"���g�p25��"*/, 		"No.25 �v���C���[�Y�X�R�A", 				"�G���f�B���O�̃e�[�}�ł��B",					},/* */
		{	""/*"���g�p26��"*/, 		"No.26 �����L�̋� �` Deep Mountain",		"�L�[�R���t�B�O�̃e�[�}�ł��B", 				},/* */
		{	""/*"���g�p27��"*/, 		"No.27 �g���R���i��", 					"�^�C�g����ʂ̃e�[�}�ł��B",					},/* */
		{	"����H�������A��ł����H", "No.28 Bad Apple!!",						"���g�p�Ȃł��B",								},/* */ /*("�I��"�Ŏg��)*/
		{	"", 						"�悤�������z���َ���", 					"BGM�͑S�ȏ���ɃA�����W�łł��B",				},/* */
	};
	//
	/*(�F�͂Ƃ肠������)*/
	{
		unsigned int ii;
		unsigned int yyy18;
		yyy18 = (0);/* Y�ʒu */
		for (ii=0; ii<(7); ii++) /* 7 �s�`��(8�s�ڂ͎g��Ȃ�) */
		{
			kanji_window_clear_line(ii);	/* �����E�B���h�E��4�s��(==3)�̓��e�������B */
			set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18));	/* �J�[�\����4�s��(==3)�ֈړ� */
			if (0==cursor1)/* BGM���[�h */
			{
				if (0==ii)	/* 1�s�ڂ̂�(0) */
				{
					kanji_color((9)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char *)const_kaisetu_str[cursor2][(/*ii+*/1)]);
				}
				else
				if (ii<5)	/* 2345�s�ڂ̂�(1,2,3,4) */
				{
					kanji_color((8)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char *)const_kaisetu_str[cursor2][(/*ii+*/1)]);
				}
				else/* 6�s�ڂ̂� */
				{
					kanji_color((7)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char *)const_kaisetu_str[cursor2][(2/*ii+1-4*/)]);
				}
			}
			else/* ���ʉ����[�h & �I�� */
			{
				kanji_color((9)|STR_CODE_NO_ENTER);
				if (0==ii)	/* 1�s�ڂ̂� */
				{
					strcpy(my_font_text, (char *)const_kaisetu_str[cursor2][0]);
				}
				else	/* �c��(2-7�s��)�������B */
				{
					strcpy(my_font_text, (char *)"");
				}
			}
			kanji_draw();
			yyy18 += (18);
		}
	}
}
#if 0
global void music_game_draw_message(int cursor1)
{
	static const char *const_music_title_str[(MOJI_29_MAX)] =
	{	/*	�ő唼�p��31�����B */
	/*	"feeddccbbaa99887766554433221100",'\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
		" �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@", // No. 0 "�Ȃ��~�߂܂�"
		" �@�@�@�@�@�@�@�@�@�@��t�̖���", // No. 1 "1�ʂ̃e�[�}�ł��B"
		"��i��̕� Imperishable Night", // No. 2 "2�ʂ̃e�[�}�ł��B" 				// ���}�`���͎~�߂ē���ւ���Ǝv���B
		" �@�@�@�@�@�@�􃔃H���[�W��1969", // No. 3 "3�ʂ̃e�[�}�ł��B"
		" �@ ��Fall of fall�@�` �H�߂���", // No. 4 "4�ʂ̃e�[�}�ł��B"
		" �@�@�@�@�@�@�􃔃A�����@�}����", // No. 5 "5�ʂ̃e�[�}�ł��B"
		" �@�@���S�������ׂ̈̃Z�v�e�b�g", // No. 6 "6�ʂ̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�@�@�@�@������", // No. 7 "�X�^�b�t���[���̃e�[�}�ł��B"
		" �@�@�@�@�@�@�􃋁[�l�C�g�G���t", // No. 8 "�G�L�X�g���X�e�[�W�̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�􉓖쌶�z����", // No. 9 "�t�@���^�Y���X�e�[�W�̃e�[�}�ł��B"
		" �@���C�g����  �` Chinese Tea", // No.10 "�G���f�B���O2�̃e�[�}�ł��B"
		"���l�`�ٔ��@�` �l�̌`�M�т�����", // No.11 "�A���X�̃e�[�}�ł��B"
		" �@�@�@�@�@ ��Complete Darkness", // No.12 "�����̃e�[�}�ł��B"
		"���|����ā@�` Lunatic Princess", // No.13 "�H���R �P��̃e�[�}�ł��B"
		" �@ �����_�����@�` Full Version", // No.14 "�˖��� ���̃e�[�}�ł��B"
		" �@ �􃉃N�g�K�[���@�` ��������", // No.15 "�p�`�����[�E�m�[���b�W�̃e�[�}�ł��B"
		" �@ �􌎎��v�@�` ���i�E�_�C�A��", // No.16 "�\\�Z�� ���̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�􂨂Ă�Η���", // No.17 "�`���m�̃e�[�}�ł��B"
		" �@�@�@�@�@ ��Grimoire of Alice", // No.18 "�A���X�̃e�[�}�ł��B"
		" �@�@�@�@�����F�}�X�^�[�X�p�[�N", // No.19 "�������̃e�[�}�ł��B"
		" �@��L�L�ˉ����� �` Till When?", // No.20 "�d���̃e�[�}�ł��B"				// �d���ǂ�����B
		" �@�@�@�@�@��v���C���[�Y�X�R�A", // No.20 "�G���f�B���O�̃e�[�}�ł��B"		// ���������ւ���Ǝv���B
		" �������L�̋��@�` Deep Mountain", // No.21 "�L�[�R���t�B�O�̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@��g���R���i��", // No.22 "�^�C�g����ʂ̃e�[�}�ł��B"
	};
	strcpy(my_font_text, (char *)const_music_title_str[cursor1]);
	kanji_color(7);
	kanji_draw();
}
#endif

static int music_room_setting[(2)+(2)];/*SOUND_TYPE_03_MAX*/

static int sound_type;
static int bg_alpha_aaa;

/*---------------------------------------------------------
	���z���َ� �t�F�[�h�A�E�g���Ă����܂���
---------------------------------------------------------*/

static void music_room_state_03_fade_out(void)
{
	bg_alpha_aaa += (2);	/*(1) (8)*/ 	/*fps_factor*/
	if ((224) < bg_alpha_aaa)/*(250-8)*/
	{
		bg_alpha_aaa = (255);
		#if 1/* �����̕\���p�摜���J������ */

		#endif
		cb.main_call_func = title_menu_start;	/* �^�C�g�����j���[�ֈړ� */
	}
	SDL_SetAlpha(cb.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_pop_screen();
}


/*---------------------------------------------------------
	���z���َ� ���j���[�I�����āA�Đ�������A�`�悵���蒆
---------------------------------------------------------*/

static void music_room_state_02_select_menu(void)
{
	psp_pop_screen();
	cg.msg_time = /*(�i���ɕ`��)*/byou60(5);	/* �� 5 �b */
	if (0==psp_pad.pad_data_alter)/* ����������������ĂȂ������ꍇ�ɃL�[�`�F�b�N(���쏀��) */
	{
		if (psp_pad.pad_data & PSP_KEY_LEFT)			/* ���{�^������ */
		{
			if (SOUND_TYPE_00_BGM == sound_type)		{	sound_type = (SOUND_TYPE_03_MAX-1); }
			else										{	sound_type--;	}
		}
		else
		if (psp_pad.pad_data & PSP_KEY_RIGHT)			/* �E�{�^������ */
		{
			if ((SOUND_TYPE_03_MAX-1) == sound_type)	{	sound_type = SOUND_TYPE_00_BGM; }
			else										{	sound_type++;	}
		}
		else	/* ���E�ȊO�̒ʏ폈��(�΂ߓ��͂�r������ׁA���E�̓��͂��������ꍇ�͂���ȊO�̏��������Ȃ�) */
		{
			if (SOUND_TYPE_02_QUIT == sound_type) /* ����[ QUIT ] ��I��ł���ꍇ */
			{
				if (psp_pad.pad_data & (PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL))	/* �V���b�g || �L�����Z���{�^������ */
				{
					#if (1)
					voice_play(VOICE04_SHIP_HAKAI, TRACK03_SHORT_MUSIC/*TRACK01_EXPLODE*/);/* ���@���ɉ��́A�Ȃ�ׂ��d�˂Ȃ� */
				//	voice_play(VOICE02_MENU_SELECT, TRACK01_EXPLODE);/*�e�L�g�[*/
					#endif
					play_music_num(BGM_26_menu01);
					load_SDL_bg(BG_TYPE_00_title_bg);
					cg.msg_time = (0);	/* �� 0 �b */
//					bg_alpha_aaa		= 255;
					bg_alpha_aaa		= 0;
					cb.main_call_func = music_room_state_03_fade_out;
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN))		/* �㉺�{�^������ */
			{
				if (psp_pad.pad_data & PSP_KEY_UP)			/* ��{�^������ */
				{
					music_room_setting[sound_type]--;
					if ((0/*MOJI_00*/) > music_room_setting[sound_type])
					{	music_room_setting[sound_type] = music_room_setting[sound_type+(2)]; }
				}
				else
				if (psp_pad.pad_data & PSP_KEY_DOWN)		/* ���{�^������ */
				{
					music_room_setting[sound_type]++;
					if (music_room_setting[sound_type+(2)] < music_room_setting[sound_type])
					{	music_room_setting[sound_type] = 0/*MOJI_00*/; }
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK) /* �V���b�g�{�^������ */
			{
				if (SOUND_TYPE_00_BGM == sound_type)	/* ����[ BGM ] ��I��ł���ꍇ */
				{
					play_music_num(music_room_setting[sound_type]/*BGM_05_stage5*/);
				}
				else
//				if (SOUND_TYPE_01_SOUND == sound_type)	/* ����[ SOUND ] ��I��ł���ꍇ */
				{
					#if (1)
					voice_play(music_room_setting[sound_type]/*VOICE07_BOMB*/, TRACK01_EXPLODE);/*�e�L�g�[*/
					#endif
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL) /* �L�����Z���{�^������ */
			{
				play_music_num(BGM_00_stop);
			}
		}
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_LEFT|PSP_KEY_RIGHT))	/* �㉺���E�{�^������ */
		{
			/* �ĕ`�� */
			music_room_draw_message(sound_type, music_room_setting[sound_type]);
			/* �`�� */
			{
				/* �@�\�ԍ��̕`�� */
				#define MAX_MENU_02 			(SOUND_TYPE_02_QUIT)
				{
				static const char *const_aaa_str[(3)] =
				{
					/* [[ ���j���[ ]] */
				//	"0123456789"
					"�ȍĐ� #00",
					"���ʉ� #00",
					"�I��      "
				};
				strcpy(my_font_text, (char *)const_aaa_str[sound_type]);
				/* ���[�h�`�� */
					/* �ԍ��{�^���ݒ�`�� */
					if (2 > sound_type)/*0 or 1*/
					{
						int kinou_number;
						kinou_number = music_room_setting[sound_type];
						dec_print_format( ((kinou_number)), 2, (char *)&my_font_text[8]);
					}
					kanji_window_clear_line(ML_LINE_08);	/* �����E�B���h�E��4�s��(==3)�̓��e�������B */
					set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_08*18));	/* �J�[�\����4�s��(==3)�ֈړ� */
					kanji_color(7);
					kanji_draw();
				}
			}
		}
	}
}


/*---------------------------------------------------------
	���z���َ� �t�F�[�h�C����
---------------------------------------------------------*/

static void music_room_state_01_fade_in(void)
{
	bg_alpha_aaa += (2);	/*fps_factor*/
	if ((200) < bg_alpha_aaa)/*(250-6) (224)*/
	{
		bg_alpha_aaa = (255);
		psp_push_screen();
		cb.main_call_func = music_room_state_02_select_menu;
	}
	SDL_SetAlpha(cb.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_pop_screen();
}


/*---------------------------------------------------------
	���z���َ� �J�n����
---------------------------------------------------------*/

global void music_room_start(void)
{
//	play_music_num(BGM_06_stage6);// ��� ����
	play_music_num(BGM_23_boss12);// �얲 �{�X
	load_SDL_bg(BG_TYPE_03_music_room);
	music_room_setting[0] = (0);
	music_room_setting[1] = (0);
	music_room_setting[2] = (USE_28_MUSIC_FILES-1);/*MOJI_29_MAX*/	/*(BGM�̍ő吔)*/
	music_room_setting[3] = (VOICE18_MAX_FILES-1);/*MOJI_29_MAX*/	/*(���ʉ��̍ő吔)*/
//
	sound_type			= SOUND_TYPE_02_QUIT;
	bg_alpha_aaa		= (0);
	#if 0
	{
		unsigned int yyy18;
		yyy18 = (100);/* Y�ʒu */
		//
		unsigned int i;
		for (i=0; i<(ML_LINE_99_MAX); i++)
		{
			ml_font[i].x		= (24);/* X�ʒu */
			ml_font[i].y		= (yyy18);
			ml_font[i].timer	= ML_ON;
//			ml_font[i].render	= NULL;
//			ml_font[i].str		= my_font_text;/*(�f�o�b�O)*/
			yyy18 += (19/*18*/);/*(���Ԃ������L����)*/
		}
	}
	#else
	set_kanji_origin_xy(24, 100);/*(�\�����_�̐ݒ�)*/
	set_kanji_origin_kankaku(19);/*(���Ԃ������L����)*/
	//
	set_kanji_hide_line(ML_LINE_99_MAX);/*(�S�s�\������B)*/
	#endif
		{
			/* 1�s�ڂ̂ݓ���Ȉʒu�ֈړ��B */
			ml_font[ML_LINE_01].x		= (0);/* X�ʒu */
			ml_font[ML_LINE_01].y		= (64);/* Y�ʒu */
		}
		{
			/* 8�s�ڂ̂ݓ���Ȉʒu�ֈړ��B */
			ml_font[ML_LINE_08].x		= (160);/* X�ʒu */
			ml_font[ML_LINE_08].y		= (240);/* Y�ʒu */
		}
	kanji_window_all_clear();				/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
	cg.msg_time = (65536);	/* �� 18 �� */
//	cg.msg_time = byou60(5);	/* �� 5 �b */
	music_room_draw_message(0, (MOJI_29_MAX)/*(�N���p���b�Z�[�W)*/ );
	cb.main_call_func = music_room_state_01_fade_in;
}