
//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	道中の中ボス
	ToDo:
		(r39u1)背後の魔方陣は、現在の形態は廃止し、
		使い魔システムに移動する必要がある。
		-------------------------------------------------------
		中ボス->使い魔
		ボス->使い魔
	-------------------------------------------------------
		"ルーミア", 				"GFAIRY",
		"妖怪2"(赤),				"GFAIRY",
		"妖怪1"(青),(暫定的)		"GFAIRY",
		"妖怪3"(紫),(暫定的)		"GFAIRY",
	-------------------------------------------------------
	; (72==64[差分氏]+8[ルーミア弾])
	; (79==64[差分氏]+15[天狗弾])		(差分氏の妖怪互換)。
	-------------------------------------------------------
	使用レジスタ
//	REG_08_REG0 	向き。
---------------------------------------------------------*/

//#define YOKAI1_DATA_repeat			user_data05 	/* 繰り返し回数 */
#define YOKAI1_DATA_start_limit_y256	user_data06 	/* 登場y座標 */
//#define yokai_type					user_data07 	/* 妖怪の種類(0 ... 3) */
	/* 開始するカード番号 */

//
#define YOKAI1_DATA_s2					target_obj		/* OBJ *s2;*/

//enum /* _yokai_type_ */
//{
//	YOKAI_TYPE_00_RUMIA = 0,	/* 0:00 ルーミア */
//	YOKAI_TYPE_01_YOUKAI02, 	/* 1:32 "妖怪2"(赤) */
//	YOKAI_TYPE_02_YOUKAI01, 	/* 2:64 "妖怪1"(青) */
//	YOKAI_TYPE_03_YOUKAI03		/* 3:96 "妖怪3"(紫) */
//};

#define OSIMAI_JIKAN_256	(256)


/*---------------------------------------------------------
	OBJ *src;	中-ボス敵自体
	OBJ *tama;	自弾
---------------------------------------------------------*/

static void callback_hit_chuu_boss(OBJ/**/ *src, OBJ/**/ *tama)
{
	/* ボス & 中-ボスに自弾があたった場合の火花エフェクトを登録(現在Gu部分がないので描画してない) */
	set_REG_DEST_XY(tama);/* 発弾位置 座標xy */
	bakuhatsu_add_type_ccc(BAKUHATSU_MOVE12);/* 先に実行した方が速い */ /*BAKUHATSU_MINI00*/
//
	/* 上と分離した方がコード効率があがる。 */
	{
		src->base_hp -= tama->kougeki_ti;	/* 攻撃して体力減らす(強さ分引く) */
		if (0 >= src->base_hp)			/* ０か負値なら、倒した。 */
		{
			#if 1/*要るの？*/
			src->base_hp	= (9999);/* ２回は倒せない */
			#endif
			card.spell_used_number		= (SPELL_00);/*(カード実行停止にする)*/
			bullets_to_hosi();/* 弾全部、星アイテムにする */
		//
			/* (ザコの)カスタムやられ処理 */
/*[スペカコールバック共用なので不可能]*/	if (NULL != src->callback_loser)	/* カスタムやられ処理があれば実行。 */
/*[スペカコールバック共用なので不可能]*/	{
/*[スペカコールバック共用なので不可能]*/		src->callback_loser(src);	/* カスタムやられ処理を実行する。(標準は「ランダムテーブルからアイテム生成」) */
/*[スペカコールバック共用なので不可能]*/		src->callback_loser = NULL; 	/* 実行したので(念の為)消す。 */
/*[スペカコールバック共用なので不可能]*/		/* (やられ処理は1度しか実行しない) */
/*[スペカコールバック共用なので不可能]*/	}
			player_dummy_add_score(src->base_score);
			//
			bakuhatsu_add_circle(src, 0);
			/* 倒した場合背後の魔方陣が消えているが、逃がした場合背後の魔方陣がある。 */
			src->YOKAI1_DATA_s2->jyumyou		= JYUMYOU_NASI; /* 倒した場合、背後の魔方陣を消す。 */
			src->jyumyou						= (OSIMAI_JIKAN_256);/* [時間切れの位置]まで時間を進める。 */
			/* コールバック登録 */
			src->callback_hit_teki = NULL;	/* ダミーコールバック登録 */
		}
	}
}

/*---------------------------------------------------------

---------------------------------------------------------*/

#define LIMIT_TIME_512	(1536)
static OBJ_CALL_FUNC(move_chuu_boss)
{
	if ((OSIMAI_JIKAN_256) > src->jyumyou)	/* 「上へ退場」(256[count]==約4秒) */
	{
		#if 1/* 現在の実装方式は、あんま良くない気もする。 */
		/* 倒した場合背後の魔方陣が消えているが、逃がした場合背後の魔方陣がある。 */
		if (JYUMYOU_NASI <= src->YOKAI1_DATA_s2->jyumyou)/* 背後の魔方陣があれば移動。 */
		{
			src->YOKAI1_DATA_s2->center.y256	-= t256(1.5);	/*fps_factor*/
		}
		#endif
		src->center.y256						-= t256(1.5);	/*fps_factor*/
		if (0 > (src->center.y256+t256(55.0)))/* 55ドットとして(左上基点、縦のサイズ) */
	//	if (0 > src->center.y256)/* 簡略版 */
		{
			src->jyumyou						= JYUMYOU_NASI;
			if (JYUMYOU_NASI <= src->YOKAI1_DATA_s2->jyumyou)/* 背後の魔方陣があれば消去。 */
			{
				src->YOKAI1_DATA_s2->jyumyou	= JYUMYOU_NASI;
			}
			/* 退場処理 */
			cg.chuu_boss_mode = (0);
			//hold_game_mode_off();
		}
	}
	else
	if ((OSIMAI_JIKAN_256) == src->jyumyou) 	/* 「カード実行停止にする」 */
	{
			card.spell_used_number			= (SPELL_00);/*(カード実行停止にする)*/
	}
	/*([時間切れの位置]時間切れの場合、「カード実行停止にする」)*/
	/*(最大約8秒(512[count])でスペカ強制中断)*/
	else
	if ((256+LIMIT_TIME_512) > src->jyumyou)	/* 「カードが終わるまで待機」(512[count]==約8秒) */
	{
		/*(カード設定時間が512未満の場合は自然に終了する。その場合、[時間切れの位置]まで時間を進める。)*/
		if (SPELL_00 == card.spell_used_number)
		{
			src->jyumyou = (OSIMAI_JIKAN_256);
		}
	//	if (SPELL_00 != card.card_number)
	//	{
	//		src->jyumyou = (OSIMAI_JIKAN_256+1);/* 「カード実行停止にする」へ設定。 */
	//	}
	}
	else
//	if ((512) > src->jyumyou)	/* 「上から登場」(128[count]==約2秒) */
	{
		src->YOKAI1_DATA_s2->center.y256	+= t256(2.0);	/*fps_factor*/
		src->center.y256					+= t256(2.0);	/*fps_factor*/
		if ((src->YOKAI1_DATA_start_limit_y256) < src->center.y256)
		{
			src->jyumyou			= ((256+LIMIT_TIME_512)-1);/* 「カードが終わるまで待機」へ設定。 */
			card.spell_used_number	= card.address_temporaly;	/* カードをセット */		/* "妖怪2"&"ルーミア"専用 */
			card_maikai_init(src);/*(r35-, カードの初期化。カードが変わると毎回行う必要がある)*/
		}
	}

	if (JYUMYOU_NASI < src->jyumyou)/* あれば */
	/* アニメーション */
	{
		zako_anime_type05(src);
	}
	if (JYUMYOU_NASI < src->YOKAI1_DATA_s2->jyumyou)/* あれば */
	{
		src->YOKAI1_DATA_s2->rotationCCW1024 += (3);
		mask1024(src->YOKAI1_DATA_s2->rotationCCW1024);
	}
//
	if ((OSIMAI_JIKAN_256) > src->jyumyou)
	{
		;	/* 上へ退場 */
	}
	else
	{
		card_generate(src); 	/* スペルをCPU実行し、カードを１フレーム生成する。 */
	}
}


/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/
//extern void regist_settei_common(GAME_COMMAND *l, OBJ *src);
global void game_command_01_regist_chuu_boss(GAME_COMMAND *l)
{
	if (0==cg.chuu_boss_mode)
	{
		cg.chuu_boss_mode = (1);
		//hold_game_mode_on();
		/* プライオリティー(表示優先順位)があるから、背後に表示させる為に、初めに後ろの魔方陣を確保。 */
		OBJ *s2;		/* 後ろの魔方陣 */
		s2								= obj_regist_teki();
		if (NULL != s2)/* 登録できた場合のみ */
		{
			/* 後ろの魔方陣が確保出来たら本体を確保。 */
			OBJ *s1;	/* 本体 */
			s1									= obj_regist_teki();
			if (NULL != s1)/* 登録できた場合のみ */
			{
				/* 0ttd dddd
					'0': force only zero.
					't': yokai type. (0-3)
					'd': dan maku type. (0-31)
				*/
				unsigned int my_haikei_iro;
			//	my_haikei_iro = (((l->user_255_code)>>5)&(4-1));
				my_haikei_iro = (((l->user_255_code)   )&(4-1));
			//
				/* 魔方陣生成 */
				s2->m_Hit256R				= ZAKO_ATARI02_PNG;
				s2->obj_type_set			= ZAKO_28_MAHOJIN;
				s2->atari_hantei			= (1/*スコア兼用*/);
				{
					const u32 color_table[4] =
					{	/*	s2->alpha			= 0x00;*/
						MAKE32RGBA(0xff, 0xff, 0xff, 0x7f), 	/* 灰っぽく */
						MAKE32RGBA(0xff, 0x3f, 0x3f, 0x7f), 	/* 赤っぽく */
						MAKE32RGBA(0x3f, 0x00, 0xff, 0x7f), 	/* 青っぽく */
						MAKE32RGBA(0x5f, 0xff, 0xaf, 0x7f), 	/* 紫っぽく(水色になった) */
					};
					s2->color32 				= color_table[my_haikei_iro];
				}
			//
				s1->callback_mover			= move_chuu_boss;
			//
				regist_settei_common(l, s1);/* 中ボスと共用する必要がある。 */
				//	s1->type		 /* 設定ファイルから決める */
				/* easyでも存在感を印象づける為に 200 は必要 */ 	// 50+150*di fficulty;
			//	s1->atari_hantei				= (1/*スコア兼用*/);
			//	s1->m_Hit256R					= ZAKO_ATARI16_PNG;
			//	s1->base_hp 					= ((l->user_hp));		/* 設定ファイルから体力を決める。 */
			//	s1->base_score					= ((l->user_score));	/* 設定ファイルから獲得スコアを決める。 */
			//	s1->center.x256 				= ((l->user_locate_x)<<(8));
			//	s1->center.y256 				= ((l->user_locate_y)<<(8));
				s1->center.y256 				= t256(-30.0);		/* (中ボス用、特殊修正) */
			//	s1->center.x256 				= (s1->center.x256);
			//	s1->center.y256 				= (s1->center.y256);
				s2->center.x256 				= (s1->center.x256);
				s2->center.y256 				= (s1->center.y256);
				// 中ボスの場合、y座標は登場予定座標。
				s1->YOKAI1_DATA_start_limit_y256	= ((l->user_locate_y)<<(8));/* t256(50.0) */
				//
				s1->callback_hit_teki		= callback_hit_chuu_boss;	/* コールバック登録 */
			//
//				s1->YOKAI1_DATA_repeat		= (2+2+1);/*廃止*/
				s1->YOKAI1_DATA_s2			= s2;
				#if 1
				//------------ カード関連
				card.spell_used_number		= (SPELL_00);/*(カード実行停止にする)*/
				card.address_temporaly		= ((l->user_kougeki_type)&0x3f);
				s1->jyumyou = ((256+LIMIT_TIME_512+256)-1);/* 「上から登場」へ設定。 */
				#endif
			}
			else
			{
				/* 本体(s1)が登録できなかった場合、背後の魔方陣(s2)の登録もあきらめる。 */
				s2->jyumyou 				= JYUMYOU_NASI;/* 登録できなかった場合 */
			}
		}
	}
}
