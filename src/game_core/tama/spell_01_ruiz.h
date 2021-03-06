
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ルイズっぽいカードを定義します。
	と思ったけど、全然それっぽくない。
	-------------------------------------------------------
	とりあえずカード語の実験。
	-------------------------------------------------------
	カウンタ専用レジスタは廃止して、汎用レジスタと統合した。
---------------------------------------------------------*/

/*---------------------------------------------------------
	最終形態っぽい奴
	-------------------------------------------------------
	自機狙い32方向減速弾。
	左右に交互に撃つ。32方向で1/4周。原作は白小弾。
	-------------------------------------------------------
	新システムでカード語が使える予定(?)なので、
	カード語を意識して書いて試る。
	-------------------------------------------------------
	使用レジスタ(てすと):
	REG_08_REG0 	カウンタ。基本的に4回に一回処理。
	REG_09_REG1 	32方向弾にしよ〜っと。
	REG_0a_REG2 	左右で色を変えよう。
	REG_0b_REG3 	角度を保持するね。
	REG_0c_REG4
	REG_0d_REG5
	REG_0e_REG6
	REG_0f_REG7 	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)


	カウンタや加減算時には変数以外に、「0以外の定数」も使える。
	カウンタや加減算時に「0」は使えない。(が実質不便は無い筈)
	(0ならば変数、0以外は定数という仕様。)

	定数	t256(1)
	定数	t256(1.2)
	定数	((65536/4)/32)
---------------------------------------------------------*/
local OBJ_CALL_FUNC(spell_create_44_ruiz3)
{
	count_up_limit_NUM(REG_NUM_08_REG0, 4);// 基本的に4回に一回処理。
	if (0==(REG_08_REG0))
	{
		count_up_limit_NUM(REG_NUM_09_REG1, 32);//	32方向弾にしよ〜っと。
		if (1==(REG_09_REG1))	/* 始めての場合 */
		{
			count_up_limit_NUM(REG_NUM_0a_REG2, 2);//	左右で色を変えよう。
			calculate_jikinerai();/* 自機狙い角作成 */
			REG_0b_REG3 = HATSUDAN_03_angle65536;/* 自機狙い角 */
		}
		if (0==REG_0a_REG2)
				{	(REG_0b_REG3) += ((65536/4)/32);	}
		else	/* else はカード語で書くのめんどくさいので使わない。 */
	//	if (1==REG_0a_REG2)
				{	(REG_0b_REG3) -= ((65536/4)/32);	}
		HATSUDAN_01_speed256				= (t256(1.2)+(REG_09_REG1<<3)); 	/* 弾速 */
		HATSUDAN_02_speed_offset			= t256(1);/*(テスト)*/
		HATSUDAN_03_angle65536				= (REG_0b_REG3);
		HATSUDAN_04_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_05_bullet_obj_type 		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + REG_0a_REG2;	/* [ 弾] */
		hatudan_system_regist_single(); /*(1弾撃つよ)*/
	}
}
#if 0
[ID:supeka3500] 			; //識別文字列
試作「カード語のてすと」	; //譜名

[init]	; //初期化セクション
r0		44		; //登録番号(r0は常に定数0なので初期化できない。そこで、初期化セクションに書いた場合、登録番号にする。)
r1		5
r8		125
;	使用レジスタ(てすと):
;	r1	取り敢えず4回に一回でいいや。
;	r2	32方向弾にしよ〜っと。
;	r3	左右で色を変えよう。
;	r4	角度を保持するね。

[spell] 	; //発弾セクション
{
	; // カード語は命令と最大で引数3個まで。
	count_up_limit r1, 4, 0 			; 取り敢えず4回に一回でいいや。
	if_equal 0, r1						; // ifは引数2個まで引数3はシステムが使う(引数3==不成立の場合のジャンプ先の位置)
	{
		count_up_limit r2, 32, 0		; 32方向弾にしよ〜っと。
		if_equal 1, r2					; 始めての場合
		{
			count_up_limit r3, 2, 0 	; 左右で色を変えよう。
			jiki_nerai r4				; 自機狙い角作成  tmp_angleCCW65536_jiki_nerai();/*  */
			set r4, HATSUDAN_03_angle65536		; // /* 自機狙い角 */
		}
		if_equal 0, r3
		{
			add r4, 512 				; 512 == ((65536/4)/32)
		}
	;	else はカード語では存在しない。
		if_equal 1, r3
		{
			add r4, -512				; 512 == ((65536/4)/32)
		}
		set HATSUDAN_01_speed256,			(t256(1.2)+(r2<<3)) 			; /* 弾速 */
		set HATSUDAN_02_speed_offset,		t256(1) 						; /*(テスト)*/
		set HATSUDAN_03_angle65536, 		(r4)							;
		set HATSUDAN_04_tama_spec,			(DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)			; /* (r33-)標準弾 */
		set HATSUDAN_05_bullet_obj_type,	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + r3		; /* [ 弾] */
		hatudan_system_regist_single												; /*(1弾撃つよ)*/
	}
	label 123	;
	jump 123	;
}
#endif
