
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	雑魚のカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	アリス(仮)	洗濯機カード
	-------------------------------------------------------
	テキトー
---------------------------------------------------------*/
local OBJ_CALL_FUNC(spell_create_09_zako_sentakki)
{
	if (0==((REG_10_BOSS_SPELL_TIMER)&0x03))
	{
		src->tmp_angleCCW1024 -= (int)(1024/24);
		mask1024(src->tmp_angleCCW1024);
	//
		#if 0
			HATSUDAN_06_n_way					= (8);										/* [8way] */
			HATSUDAN_07_div_angle65536			= (int)(65536/24);							/* 分割角度 */
	//
			HATSUDAN_01_speed256				= (t256(2.0)+((REG_10_BOSS_SPELL_TIMER)<<2)); /* 弾速 */
		{
			HATSUDAN_03_angle65536				= ((src->tmp_angleCCW1024)<<6); 				/* 角度 */
			HATSUDAN_05_bullet_obj_type 		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [青鱗弾] */
			bullet_regist_multi_vector_direct();
		//
			HATSUDAN_03_angle65536				= ((-((src->tmp_angleCCW1024)<<6))&(65536-1));		/* 角度 */
			HATSUDAN_05_bullet_obj_type 		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [水鱗弾] */
			bullet_regist_multi_vector_direct();
		}
		#endif
		#if 1
			HATSUDAN_02_speed_offset			= t256(1);		/* 調整減速弾 */	/* この方式になるか検討中 */
			HATSUDAN_04_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_06_n_way					= (8);										/* [8way] */
			HATSUDAN_07_div_angle65536			= (int)(65536/24);							/* 分割角度 */
	//
			HATSUDAN_01_speed256				= (t256(1.0)+((REG_10_BOSS_SPELL_TIMER)<<2)); /* 弾速 */
		{
			int first_angle65536 = ((src->tmp_angleCCW1024)<<6);
			HATSUDAN_03_angle65536				= (first_angle65536);						/* 角度 */
			HATSUDAN_05_bullet_obj_type 		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [青鱗弾] */
			hatudan_system_regist_katayori_n_way();/* (r33-) */
		//
			HATSUDAN_03_angle65536				= ((-first_angle65536)&(65536-1));			/* 角度 */
			HATSUDAN_05_bullet_obj_type 		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [水鱗弾] */
			hatudan_system_regist_katayori_n_way();/* (r33-) */
		}
		#endif
		#if (1)
		cpu_bullet_play_15_auto();
		#endif
	}
}
