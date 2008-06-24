#include "../include/background.h"

int createBackground(background *bg)
{
	int error;
	error=gorgonLoadAnimationPack(&bg->bg.animationPack,"./resource/background/yamatto.apk");
	error=gorgonLoadSpritePack(&bg->bg.spritePack,"./resource/background/yamatto.spk");

	error=gorgonCreateBackground(&bg->bg,768,240,0,768,0,240,0,0,1,2);
	error=gorgonCreateLayer(&bg->bg.layer[0],1,0,1);
		error=gorgonCreateTile(&bg->bg.layer[0].tile[0],101,1);
		error=gorgonSetTilePositionByLayer(&bg->bg.layer[0].tile[0],0,0,0);
	error=gorgonCreateLayer(&bg->bg.layer[1],1,1,13);
		error=gorgonCreateTile(&bg->bg.layer[1].tile[0],0,13);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],0	,0,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],1	,160,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],2	,192,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],3	,240,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],4	,352,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],5	,384,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],6	,416,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],7	,448,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],8	,480,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],9	,512,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],10	,544,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],11	,704,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[0],12	,736,	0);
		gorgonCreateTile(&bg->bg.layer[1].tile[1],1,2);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[1],0	,208,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[1],1	,256,	128);

		gorgonCreateTile(&bg->bg.layer[1].tile[2],2,13);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],0	,16,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],1	,176,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],2	,224,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],3	,272,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],4	,368,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],5	,400,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],6	,432,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],7	,464,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],8	,496,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],9	,528,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],10	,560,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],11	,720,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[2],12	,752,	0);

		gorgonCreateTile(&bg->bg.layer[1].tile[3],3,22);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],0	,32,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],1	,48,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],2	,64,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],3	,80,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],4	,96,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],5	,112,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],6	,128,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],7	,144,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],8	,288,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],9	,304,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],10	,320,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],11	,336,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],12	,304,	80);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],13	,320,	80);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],14	,336,	80);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],15	,352,	80);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],16	,416,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],17	,432,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],18	,448,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],19	,464,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],20	,624,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[3],21	,640,	112);

		gorgonCreateTile(&bg->bg.layer[1].tile[4],4,31);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],0	,272,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],1	,288,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],2	,304,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],3	,320,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],4	,336,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],5	,352,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],6	,368,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],7	,384,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],8	,400,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],9	,416,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],10	,432,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],11	,448,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],12	,464,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],13	,480,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],14	,496,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],15	,512,	80);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],16	,528,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],17	,560,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],18	,576,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],19	,592,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],20	,624,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],21	,656,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],22	,688,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],23	,704,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],24	,304,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],25	,320,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],26	,336,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],27	,368,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],28	,624,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],29	,640,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[4],30	,656,	32);

		gorgonCreateTile(&bg->bg.layer[1].tile[5],5,6);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],0	,288,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],1	,352,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],2	,544,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],3	,608,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],4	,672,	32);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[5],5	,608,	128);
//22
		gorgonCreateTile(&bg->bg.layer[1].tile[6],22,21);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],0	,0,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],1	,160,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],2	,192,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],3	,240,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],4	,192,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],5	,240,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],6	,352,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],7	,352,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],8	,384,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],9	,448,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],10	,480,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],11	,512,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],12	,480,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],13	,512,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],14	,544,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],15	,480,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],16	,412,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],17	,544,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],18	,704,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],19	,736,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[6],20	,736,	80);
		
		gorgonCreateTile(&bg->bg.layer[1].tile[7],23,4);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[7],0	,208,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[7],1	,256,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[7],2	,208,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[7],3	,256,	208);
		
		gorgonCreateTile(&bg->bg.layer[1].tile[8],24,21);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],0	,16,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],1	,176,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],2	,224,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],3	,272,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],4	,224,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],5	,272,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],6	,368,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],7	,368,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],8	,400,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],9	,464,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],10	,496,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],11	,528,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],12	,496,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],13	,528,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],14	,560,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],15	,496,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],16	,528,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],17	,560,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],18	,720,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],19	,752,	16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[8],20	,752,	80);

		gorgonCreateTile(&bg->bg.layer[1].tile[9],25,16);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],0	,32,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],1	,48,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],2	,64,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],3	,80,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],4	,96,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],5	,112,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],6	,128,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],7	,144,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],8	,288,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],9	,304,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],10	,320,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],11	,336,	144);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],12	,416,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],13	,432,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],14	,448,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[9],15	,464,	176);

		gorgonCreateTile(&bg->bg.layer[1].tile[10],26,18);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],0	,288,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],1	,352,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],2	,416,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],3	,416,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],4	,480,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],5	,480,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],6	,544,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],7	,544,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],8	,544,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],9	,608,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],10	,608,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],11	,672,	64);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],12	,672,	96);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],13	,672,	128);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],14	,672,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],15	,608,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],16	,608,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[10],17	,672,	192);

		gorgonCreateTile(&bg->bg.layer[1].tile[11],27,8);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],0	,576,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],1	,592,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],2	,608,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],3	,624,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],4	,640,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],5	,656,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],6	,672,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[11],7	,688,	208);
		
		gorgonCreateTile(&bg->bg.layer[1].tile[12],44,11);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],0	,0,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],1	,160,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],2	,192,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],3	,240,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],4	,352,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],5	,384,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],6	,480,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],7	,512,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],8	,544,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],9	,736,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[12],10	,736,	48);

		gorgonCreateTile(&bg->bg.layer[1].tile[13],45,11);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[13],0	,208,	176
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[13],1	,256,	176);
			
		gorgonCreateTile(&bg->bg.layer[1].tile[14],46,11);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],0	,16,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],1	,176,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],2	,224,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],3	,272,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],4	,368,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],5	,400,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],6	,496,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],7	,528,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],8	,560,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],9	,752,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[14],10	,752,	48);
		gorgonCreateTile(&bg->bg.layer[1].tile[15],47,11);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],0	,32,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],1	,48,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],2	,64,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],3	,80,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],4	,96,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,112,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,128,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,144,	192);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,32,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],9	,48,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],10	,64,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],0	,80,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],1	,96,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],2	,112,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],3	,128,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],4	,144,	208);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,32,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],9	,48,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],10	,64,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],0	,80,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],1	,96,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],2	,112,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],3	,128,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],4	,144,	224);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,288,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,304,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,320,	160);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,336,	160);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,288,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,304,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,320,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,336,	176);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,288,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,304,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,320,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,336,	192);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,288,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,304,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,320,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,336,	208);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,288,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,304,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,320,	224);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,336,	224);

			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],10	,,	48);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],0	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],1	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],2	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],3	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],4	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],9	,,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],10	,,	48);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],0	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],1	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],2	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],3	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],4	,,	176);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],5	,,	208);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],6	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],7	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],8	,,	192);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],9	,,	112);
			error=gorgonSetTilePositionByLayer(&bg->bg.layer[1].tile[15],10	,,	48);

return 1;	
}
int backgroundCollision(int x, int y, int width, int height, background *bg)
{
return 1;
}
/*
int colisaoCenario(cenario *til,int x,int y, int l, int a,float *atrito)
{
	int i,j;
	for(i=0; i<til->numero; i++)
	{
		for(j=0; j<til->tiles[i].numero; j++)
		{
			if
			(til->tiles[i].obstaculo && !(
				(til->tiles[i].posX[j] +til->posX > x + l) ||
				(til->tiles[i].posY[j] +til->posY> y + a) ||
				(til->tiles[i].posX[j] +til->posX + til->tiles[i].sprite->w < x) ||
				(til->tiles[i].posY[j] +til->posY + til->tiles[i].sprite->h < y)
			))
			{
				if(DEBUG) printf("%d, %d!\n",til->tiles[i].posX[j],til->tiles[i].posY[j]);
				if(atrito!=NULL) *atrito=til->tiles[i].atrito;
				return 1;
			 }
		}
	}
	return 0;
}
*/
