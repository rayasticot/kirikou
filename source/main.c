#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <nds.h>
#include <nf_lib.h>

void kirikou(int screen);
void title();
void level1();
void level2();
void level3();
void level4();
void end();
void sound(int marabout);
void loadsprite(char* url, int slot, int size_x, int size_y, int screen);
void showsprite(int screen, int id, int slot, int pos_x, int pos_y);
void createbg(char* url, int size_x, int size_y, int screen);
void deletesprite(int screen, int id);
void loadsounds();
void levelcol(int map, int snd);

touchPosition Stylus;
int level_index = 0;
int unk_index = 0; //marabout 0
int edgard_index = 0; //marabout 1
int dodji_index = 0; //marabout 2
int wadedji_index = 0; //marabout 3
int global_time = 0;
int kirikou_x;
int kirikou_y;

int main(int argc, char **argv) {
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);
	NF_SetRootFolder("NITROFS");
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	soundEnable();
	NF_InitRawSoundBuffers();
	NF_InitCmapBuffers();
	title();

	while(1) {
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamSub);
	}
	return 0;

}
void kirikou(int screen){
	loadsprite("sprite/nada", 0, 16, 32, 1);
	showsprite(1, 0, 0, 0, 0);
	NF_LoadColisionBg("maps/map1", 0, 256, 256);
	NF_LoadColisionBg("maps/maplevel1", 1, 256, 264);
	NF_LoadColisionBg("maps/map2level1", 2, 256, 264);
	NF_LoadColisionBg("maps/map3level1", 3, 256, 264);
	while(1) {
		scanKeys();
		if(global_time == 0){
		if(KEY_UP & keysHeld()){
			kirikou_y -= 1;}
		if(KEY_DOWN & keysHeld()){
			kirikou_y += 1;}
		if(KEY_RIGHT & keysHeld()){
			kirikou_x += 1;}
		if(KEY_LEFT & keysHeld()){
			kirikou_x -= 1;}
		}
		if(kirikou_x >= 256){
			kirikou_x = 256;}
		if(kirikou_x <= 0){
			kirikou_x = 0;}
		if(kirikou_y >= 192){
			kirikou_y = 192;}
		if(kirikou_y <= 0){
			kirikou_y = 0;}
		NF_MoveSprite(1, 0, kirikou_x, kirikou_y);
		if(NF_GetTile(0, kirikou_x, kirikou_y) == 1){
			level_index += 1;
			if(level_index == 1){
				NF_UnloadRawSound(1);
				NF_UnloadRawSound(2);
				NF_UnloadRawSound(3);
				NF_UnloadRawSound(4);
				NF_UnloadRawSound(5);
				NF_UnloadRawSound(6);
				NF_UnloadRawSound(7);
				NF_UnloadRawSound(8);
				NF_UnloadRawSound(9);
				NF_UnloadRawSound(10);
				NF_UnloadRawSound(11);
				NF_LoadRawSound("sound/dodji0", 12, 8000, 0);
				NF_LoadRawSound("sound/dodji1", 13, 11025, 0);
				NF_LoadRawSound("sound/dodji2", 14, 11025, 0);
				NF_LoadRawSound("sound/dodji3", 15, 11025, 0);
				NF_LoadRawSound("sound/dodji4", 16, 6000, 0);
				NF_LoadRawSound("sound/wadedji0", 17, 11025, 0);
				NF_LoadRawSound("sound/wadedji1", 18, 8000, 0);
				NF_LoadRawSound("sound/wadedji2", 19, 11025, 0);
				NF_LoadRawSound("sound/wadedji3", 20, 11025, 0);
				NF_LoadRawSound("sound/wadedji4", 21, 8000, 0);
				level2();}
			if(level_index == 2){
				level3();}
			if(level_index == 3){
				NF_LoadRawSound("sound/crie", 24, 11025, 0);
				NF_LoadRawSound("sound/co", 25, 11025, 0);
				level4();}
			if(level_index == 4){
				end();}
			kirikou_x = 0;
			kirikou_y = 0;
		}
		if(level_index == 0){
			levelcol(1, 0);
			levelcol(2, 4);
			levelcol(3, 1);
		}
		if(level_index == 1){
			levelcol(4, 2);
			levelcol(5, 3);
			levelcol(6, 5);
		}
		if(level_index == 2){
			levelcol(7, 4);
			levelcol(8, 5);
			levelcol(9, 4);
			levelcol(10, 5);
			levelcol(11, 4);
			levelcol(12, 5);
			levelcol(13, 5);
			levelcol(14, 4);
			levelcol(15, 5);
			levelcol(16, 4);
		}
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);
	}
}
void title(){
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
	createbg("bg/kirikoutitle", 256, 256, 0);
	loadsprite("sprite/kirikoustart", 1, 64, 32, 1);
	showsprite(1, 1, 1, 96, 80);
	loadsounds();
	NF_PlayRawSound(1, 127, 64, false, 0);
	while(1){
		scanKeys();
		touchRead(&Stylus);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamSub);
		if(KEY_TOUCH & keysDown()){
			if(Stylus.px >= 96){
				if(Stylus.px <= 160){
					if(Stylus.py >= 80){
						if(Stylus.py <= 112){
						deletesprite(1, 1);
						level1();
						break;
		}}}}}}}
void level1(){
	createbg("bg/level1", 256, 256, 1);
	loadsprite("sprite/maison", 2, 32, 32, 1); 
	loadsprite("sprite/stairs", 3, 32, 32, 1);
	loadsprite("sprite/npc0", 4, 16, 32, 1);
	loadsprite("sprite/npc3", 7, 16, 32, 1);
	loadsprite("sprite/cochon", 8, 32, 32, 1);
	showsprite(1, 2, 2, 23, 23);
	showsprite(1, 3, 2, 40, 95);
	showsprite(1, 4, 2, 30, 150);
	showsprite(1, 5, 2, 205, 24);
	showsprite(1, 6, 2, 206, 81);
	showsprite(1, 7, 2, 168, 151);
	showsprite(1, 8, 2, 120, 24);
	showsprite(1, 9, 3, 224, 160);
	showsprite(1, 10, 4, 70, 155);
	showsprite(1, 11, 7, 187, 32);
	showsprite(1, 12, 8, 142, 80);
	kirikou(1);
}
void level2(){
	soundKill(0);
	NF_LoadColisionBg("maps/map1level2", 4, 256, 264);
	NF_LoadColisionBg("maps/map2level2", 5, 256, 264);
	NF_LoadColisionBg("maps/map3level2", 6, 256, 264);
	createbg("bg/level2", 256, 256, 1);
	loadsprite("sprite/npc1", 5, 16, 32, 1);
	loadsprite("sprite/npc2", 6, 16, 32, 1);
	loadsprite("sprite/chevre", 9, 32, 32, 1);
	deletesprite(1, 2);
	deletesprite(1, 3);
	deletesprite(1, 4);
	deletesprite(1, 5);
	deletesprite(1, 6);
	deletesprite(1, 7);
	deletesprite(1, 8);
	deletesprite(1, 10);
	deletesprite(1, 11);
	deletesprite(1, 12);
	showsprite(1, 2, 2, 87, 40);
	showsprite(1, 3, 2, 30, 100);
	showsprite(1, 4, 2, 76, 129);
	showsprite(1, 5, 2, 180, 24);
	showsprite(1, 6, 2, 188, 150);
	showsprite(1, 7, 5, 218, 38);
	showsprite(1, 8, 6, 49, 150);
	showsprite(1, 10, 9, 123, 43);
}
void level3(){
	soundKill(0);
	NF_LoadColisionBg("maps/map1level3", 7, 256, 264);
	NF_LoadColisionBg("maps/map2level3", 8, 256, 264);
	NF_LoadColisionBg("maps/map3level3", 9, 256, 264);
	NF_LoadColisionBg("maps/map4level3", 10, 256, 264);
	NF_LoadColisionBg("maps/map5level3", 11, 256, 264);
	NF_LoadColisionBg("maps/map6level3", 12, 256, 264);
	NF_LoadColisionBg("maps/map7level3", 13, 256, 264);
	NF_LoadColisionBg("maps/map8level3", 14, 256, 264);
	NF_LoadColisionBg("maps/map9level3", 15, 256, 264);
	NF_LoadColisionBg("maps/map10level3", 16, 256, 264);
	createbg("bg/level3", 256, 256, 1);
	deletesprite(1, 2);
	deletesprite(1, 3);
	deletesprite(1, 4);
	deletesprite(1, 5);
	deletesprite(1, 6);
	deletesprite(1, 7);
	deletesprite(1, 10);
	deletesprite(1, 8);
	showsprite(1, 2, 9, 50, 145);
	showsprite(1, 3, 9, 37, 71);
	showsprite(1, 4, 9, 203, 14);
	showsprite(1, 5, 9, 132, 148);
	showsprite(1, 6, 9, 196, 103);
	showsprite(1, 7, 8, 115, 14);
	showsprite(1, 8, 8, 90, 96);
	showsprite(1, 13, 8, 154, 63);
	showsprite(1, 10, 8, 115, 14);
	showsprite(1, 11, 8, 53, 20);
	showsprite(1, 12, 8, 189, 147);
}
void level4(){
	createbg("bg/level4", 256, 256, 1);
	soundKill(0);
	NF_PlayRawSound(25, 127, 64, true, 0);
	deletesprite(1, 2);
	deletesprite(1, 3);
	deletesprite(1, 4);
	deletesprite(1, 5);
	deletesprite(1, 6);
	deletesprite(1, 7);
	deletesprite(1, 8);
	deletesprite(1, 10);
	deletesprite(1, 11);
	deletesprite(1, 12);
	deletesprite(1, 13);
}
void end(){
	createbg("bg/dead", 256, 256, 1);
	createbg("bg/dead", 256, 256, 0);
	soundKill(0);
	NF_PlayRawSound(24, 127, 64, false, 0);
	deletesprite(1, 0);
	deletesprite(1, 9);
}
void sound(int marabout){
	global_time = 0;
	int templol = 0;
	int son = 0;
	bool salade = false;
	soundKill(0);
	switch(marabout){
		case 0:
			templol = unk_index;
			if(unk_index < 4){
				unk_index += 1;}
			else{
				unk_index = 0;}
			break;
		case 1:
			templol = edgard_index;
			if(edgard_index < 4){
				edgard_index += 1;}
			else{
				edgard_index = 0;}
			break;
		case 2:
			templol = dodji_index;
			if(dodji_index < 4){
				dodji_index += 1;}
			else{
				dodji_index = 0;}
			break;
		case 3:
			templol = wadedji_index;
			if(wadedji_index < 4){
				wadedji_index += 1;}
			else{
				wadedji_index = 0;}
			break;
		case 4:
			salade = true;
			templol = 0;
			createbg("bg/cochonback", 256, 256, 0);
			break;
		case 5:
			salade = true;
			templol = -4;
			createbg("bg/chevreback", 256, 256, 0);
			break;
	}
	son = 2 + marabout*5 + templol;
	NF_PlayRawSound(son, 127, 64, false, 0);
	while(salade == true){
		swiWaitForVBlank();
		global_time += 1;
		if(global_time == 480){
			salade = false;
			global_time = 0;
			createbg("bg/kirikoutitle", 256, 256, 0);
			break;
}}}
void loadsprite(char* url, int slot, int size_x, int size_y, int screen){
	NF_LoadSpriteGfx(url, slot, size_x, size_y);
	NF_LoadSpritePal(url, slot);
	NF_VramSpriteGfx(screen, slot, slot, false);
	NF_VramSpritePal(screen, slot, slot);
}
void showsprite(int screen, int id, int slot, int pos_x, int pos_y){
	NF_CreateSprite(screen, id, slot, slot, pos_x, pos_y);
}
void createbg(char* url, int size_x, int size_y, int screen){
	NF_ResetTiledBgBuffers();
	NF_LoadTiledBg(url, url, size_x, size_y);
	NF_CreateTiledBg(screen, 3, url);
}
void deletesprite(int screen, int id){
	NF_DeleteSprite(screen, id);
}
void loadsounds(){
	NF_LoadRawSound("sound/kirikou", 1, 11025, 0);
	NF_LoadRawSound("sound/unk0", 2, 8000, 0);
	NF_LoadRawSound("sound/unk1", 3, 6000, 0);
	NF_LoadRawSound("sound/unk2", 4, 8000, 0);
	NF_LoadRawSound("sound/unk3", 5, 6000, 0);
	NF_LoadRawSound("sound/unk4", 6, 8000, 0);
	NF_LoadRawSound("sound/edgard0", 7, 11025, 0);
	NF_LoadRawSound("sound/edgard1", 8, 8000, 0);
	NF_LoadRawSound("sound/edgard2", 9, 11025, 0);
	NF_LoadRawSound("sound/edgard3", 10, 8000, 0);
	NF_LoadRawSound("sound/edgard4", 11, 11025, 0);
	NF_LoadRawSound("sound/cochon", 22, 11025, 0);
	NF_LoadRawSound("sound/millions", 23, 11025, 0);
}
void levelcol(int map, int snd){
	if(NF_GetTile(map, kirikou_x, kirikou_y) == 1){
		sound(snd);
		kirikou_x += 8;
	}
}