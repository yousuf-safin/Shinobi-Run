#include "iGraphics.h"
#include "bitmap_loader.h"
#include <iostream> 
#include <fstream>
#include <string>
#pragma warning(disable:4996) //Disable Deprecation Errors

using namespace std;
#define SCREENWIDTH 1530
#define SCREENHEIGHT 785
#define PERWIDTH 85
#define JUMPLIMIT 200
#define BANDORNUM 25
#define SHAPNUM 20
#define FIRENUM 1
#define GHOSTNUM 25
#define DRAGONNUM 20
#define BIRDNUM 20
#define HEALNUM 10
#define HUDAI 500
#define BOSSPOWER1 100
#define BOSS2NUM 30


bool congratulations = false;
bool level_2 = false;
bool level_1 = true;
int enemyMorse = 0;
int enemyDead2 = 0;
char nameInput[100];
char score_Arr[100] = {"SCORE "};
int nameIndex = 0;


int scoreCount1 = 0;
void showHighScore(){

	FILE* ptr;
	char str[50];
	ptr = fopen("scores.txt", "a+"); // reading the file in append mode
	string scores;
	int all_scores[100];
	int i = 0;

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}


	while (fgets(str, 50, ptr) != NULL) {
		//printf("%s", str);
		//scores += str;
		if (str != "\n"){
			all_scores[i++] = stoi(str); //converting the string into integer and storing it in an array

		}
	}
	fclose(ptr);
	int len = i, a;

	//sorting in descending order to determine high scores...

	for (i = 0; i < len; ++i){
		for (int j = i + 1; j < len; ++j)
		{
			if (all_scores[i] < all_scores[j])
			{
				a = all_scores[i];
				all_scores[i] = all_scores[j];
				all_scores[j] = a;
			}
		}

	}




	int space = 130, max_scores = 10;
	char score_text[1000], c;

	for (int i = 0; i < len; i++){
		strcpy_s(score_text, to_string(all_scores[i]).c_str()); // converting the ints to string first and then char array
		iText(150, SCREENHEIGHT - (space), score_text, GLUT_BITMAP_TIMES_ROMAN_24); // rendering it on display
		space += 35; // space for the next score
		max_scores--; // if it reaches 0, it means total 10 scores have been painted
		if (max_scores <= 0){
			break;
		}

	}


}



/*function to save score in a file in the same directory*/
void saveScore(){
	FILE *fp; //file pointer

	fp = fopen("scores.txt", "a"); //open the existing file in append mode
	char final_score[33];

	itoa(scoreCount1, final_score, 10); //converting numbers to string

	fprintf(fp, "%s", final_score); // printing final score to text file
	fprintf(fp, "%s", "\n");

	fclose(fp); //close file
}


char* stringConverter(int scoreCount1){
	char str[20];
	itoa(scoreCount1, str, 10);
	return str;
}



struct buttoncord
{
	int x;
	int y;

}bcord[5];

int mposx, mposy;
int gamestate = -1;
char homemenu[15] = "menu\\menu1.bmp";
char button[5][20] = { "button\\12.bmp", "button\\13.bmp", "button\\10.bmp", "button\\14.bmp", "button\\15.bmp" };
char pausemenu[25] = "pmenu\\pausemenu.bmp";
char pausebutton[5][20] = { "pmenu\\1.bmp", "pmenu\\2.bmp", "pmenu\\3.bmp", "pmenu\\3.bmp" };
char highscore[25] = "pmenu\\highscore.bmp";
char credits[25] = "pmenu\\credits2.bmp";
char instruction[25] = "pmenu\\ins.bmp";
char out[25] = "pmenu\\exit2.bmp";

//backbutton
struct backbuttoncord
{
	int bx;
	int by;
}bbcord[1];
struct yesbuttoncord
{
	int yx;
	int yy;
}ycord[1];
struct nobuttoncord
{
	int nx;
	int ny;
}ncord[1];
struct hbuttoncord
{
	int hx;
	int hy;
}hcord[1];
struct pausebuttoncord
{
	int px = 320;
	int py = 200;
}pbcord[2];
char pausebtn[5][20] = { "pbtn\\2.bmp", "pbtn\\4.bmp" };
char no[5][20] = { "button\\no.bmp" };
char yes[5][20] = { "button\\yes.bmp" };
char back[5][20] = { "button\\16.bmp" };
char home[5][20] = { "pbtn\\4.bmp" };


void health_coll();
void collision();
void health();
void position_of_Kakashi();
void enemyMove();
void pause_pic();
void showBG();
void showBG2();
void enemyMove2();
void boss1_collision();
void boss2_collision();



void score()
{
	int score_x = 680;
	int score_y = 720;
	char score_Arr[100] = { "SCORE :  " };
	strcat(score_Arr, stringConverter(scoreCount1));
	iSetColor(0, 0, 255);
	iText(score_x, score_y, score_Arr, GLUT_BITMAP_TIMES_ROMAN_24);
}


//MENU BAR
void menu()
{
	if (gamestate == -1)
	{
		iShowBMP(0, 0, homemenu);
		for (int i = 0; i<5; i++)
		{
			iShowBMP2(bcord[i].x, bcord[i].y, button[i], 0);
		}
	}
	

	else if (gamestate == 1)
	{
		iShowBMP(0, 0, highscore);

		iShowBMP2(bbcord[1].bx, bbcord[1].by, back[0], 0);
		showHighScore();

	}
	else if (gamestate == 2)
	{
		iShowBMP(0, 0, instruction);
		iShowBMP2(bbcord[1].bx, bbcord[1].by, back[0], 0);


	}
	else if (gamestate == 3)
	{
		iShowBMP(0, 0, credits);
		iShowBMP2(bbcord[1].bx, bbcord[1].by, back[0], 0);


	}
	else if (gamestate == 4)
	{
		iShowBMP(0, 0, out);
		iShowBMP2(bbcord[1].bx, bbcord[1].by, back[0], 0);
		iShowBMP2(ycord[1].yx, ycord[1].yy, yes[0], 0);
		iShowBMP2(ncord[1].nx, ncord[1].ny, no[0], 0);

	}

}

bool pause = false;
void pause_menu();
void pause_pic()
{
	if (!pause){
		iShowBMP(0, 0, "pmenu\\pausemenu.bmp");
		for (int i = 0; i<2; i++)
		{
			iShowBMP2(pbcord[i].px, pbcord[i].py, pausebtn[i], 0);
		}
	}
	else if (gamestate == 0)
	{
		if (level_1){
			showBG();
			position_of_Kakashi();
			enemyMove();
		}
		else if (level_2){
			showBG2();
			position_of_Kakashi();
			enemyMove2();
		}
		score();
		health();
		//pause_pic();

	}
	else if (gamestate == 0)
	{
		menu();
	}

	else
	{
	}
}

void level_2_all()
{
	showBG2();
	position_of_Kakashi();
	//enemyMove();
	//pause_pic();
	//health();
	score();
}


int mousepos_x = -1, mousepos_y = -1;
int mouseDragPos_x = -1, mouseDragPos_y = -1;
int mouseClickPos_x = -1, mouseClickPos_y = -1;
char mouse_button[20] = "", mouse_state[20] = "";
char keyButton = '\0', spcial_key = '\0';
int circle_x = 0, circle_y = 0;
int circleStatus = false;
int r = 255, g = 255, b = 255;
int x = 10, y = 10;
int dx = 10, dy = 10;
bool userName = true;
bool jump = false;
bool jup = false;
int jCor = 0;

int pic_x = 900, pic_y = 100;


//RUN RUN
char Running[8][20] = { "char\\1.bmp", "char\\2.bmp", "char\\3.bmp", "char\\4.bmp", "char\\5.bmp", "char\\6.bmp", "char\\7.bmp", "char\\8.bmp" };
char Kakajump[3][20] = { "char\\j1.bmp", "char\\j2.bmp", "char\\j3.bmp" };
int rIn = 0;
int k_x = 110;
int k_y = 135;

//FIGHT
int k_f_x = 200;
int k_f_y = 80;
char fighting[6][20] = { "char\\f1.bmp", "char\\f2.bmp", "char\\f3.bmp" };
int fIn = 0;
bool fight = false;

//POWER
int k_p_x = 200;
int k_p_y = 80;
char pow_arr[3][20] = {  "char\\p2.bmp",  "char\\p4.bmp", "char\\p6.bmp", };
int pIn = 0;
bool power = false;
char pow_ball[2][20] = { "char\\pb1.bmp", "char\\pb2.bmp" };
int p_bIn = 0;
bool p_bS = false;
int p_b_x;
int p_b_y;


//NINJA STAR
char nStar[3][20] = { "char\\n1.bmp", "char\\n2.bmp", "char\\n3.bmp" };
int nIn = 0;
bool nS = false;
int n_x;
int n_y;



//KAKASHI MOVE
void position_of_Kakashi()
{
		if (jump)
		{
			if (jup)
			{

				iShowBMP2(k_x, k_y + jCor, Kakajump[0], 255);
				iShowBMP2(k_x, k_y + jCor, Kakajump[1], 255);
				if(fight){
					iShowBMP2(k_x, k_y + jCor, fighting[fIn], 255);
					iShowBMP2(n_x, n_y, nStar[nIn], 0);
				}
				else if (nS){
					iShowBMP2(k_x, k_y + jCor, Kakajump[0], 255);
					iShowBMP2(k_x, k_y + jCor, Kakajump[1], 255);
					iShowBMP2(n_x, n_y, nStar[nIn], 0);
				}
				if (power){
					iShowBMP2(k_x, k_y + jCor, pow_arr[pIn], 255);
					iShowBMP2(p_b_x, p_b_y, pow_ball[p_bIn], 255);
				}
				else if (p_bS){
					iShowBMP2(k_x, k_y + jCor, Kakajump[0], 255);
					iShowBMP2(k_x, k_y + jCor, Kakajump[1], 255);
					iShowBMP2(p_b_x, p_b_y, pow_ball[p_bIn], 255);
				}
			}

			else
			{
				iShowBMP2(k_x, k_y + jCor, Kakajump[2], 255);
				if (fight){
					iShowBMP2(k_x, k_y + jCor, fighting[fIn], 255);
					iShowBMP2(n_x, n_y, nStar[nIn], 0);
				}
				else if (nS){
					iShowBMP2(k_x, k_y + jCor, Kakajump[2], 255);
					iShowBMP2(n_x, n_y, nStar[nIn], 0);
				}
			}
		}
		else
		{
			if (fight)
			{
				k_f_x = 200;
				k_f_y = 80;
				iShowBMP2(k_x, k_y, fighting[fIn], 255);
				iShowBMP2(n_x, n_y, nStar[nIn], 0);
			}
			else if (nS){
				iShowBMP2(k_x, k_y, Running[rIn], 255);
				iShowBMP2(n_x, n_y, nStar[nIn], 0);
			}
			else if (power)
			{
				k_p_x = 200;
				k_p_y = 80;
				//nS = true;
				iShowBMP2(k_x, k_y, pow_arr[pIn], 255);
			}
			else
			{
				iShowBMP2(k_x, k_y, Running[rIn], 255);
			}

		}
		/*if (nS)
		{
			iShowBMP2(n_x, n_y, nStar[nIn], 0);
		}*/
		if (p_bS)
		{
			iShowBMP2(p_b_x, p_b_y, pow_ball[p_bIn], 255);
		}
}



//HEALTH PICTURE
char health_pic[4][20] = {"health\\1.bmp", "health\\2.bmp", "health\\3.bmp", "health\\4.bmp"};
int healthIndex = 0;
int health_x = 90;
int health_y = 700;

bool gameOver = false;

void health()
{
	if (pause){
		if (!congratulations){
			if (healthIndex == 0){
				iShowBMP2(10, 700, "health\\icon.bmp", 0);
				iShowBMP2(70, 700, health_pic[0], 0);
			}
			else if (healthIndex == 1){
				iShowBMP2(10, 700, "health\\icon.bmp", 0);
				iShowBMP2(70, 700, health_pic[1], 0);
			}
			else if (healthIndex == 2){
				iShowBMP2(10, 700, "health\\icon.bmp", 0);
				iShowBMP2(70, 700, health_pic[2], 0);
			}
			else if (healthIndex == 3){
				iShowBMP2(10, 700, "health\\icon.bmp", 0);
				iShowBMP2(70, 700, health_pic[3], 0);
			}
			else if (gameOver)
			{
				pause = true;
				iShowBMP2(0, 0, "menu\\gameover.bmp", 0);
				saveScore();
				score();
				iShowBMP2(hcord[1].hx, hcord[1].hy, home[0], 0);
			}
		}
	};
			
}

//LEVEL-1 BOSS
bool boss1 = false;
int boss1_x = 1215;
int boss1_y = 300;
char boss_health_pic[4][20] = { "bosshealth\\1.bmp", "bosshealth\\2.bmp", "bosshealth\\3.bmp", "bosshealth\\4.bmp" };
int boss_healthIndex = 0;
int boss_health_x = 90;
int boss_health_y = 700;
char boss_power_pic [1][30] = { "BossChar\\bosspow.bmp" };
int boss_pow_x = 1100;
int boss_pow_y = 300;
bool bossPowerShow = false;

void boss_health()
{
	if (boss_healthIndex == 0 || boss_healthIndex == 1){
		iShowBMP2(770, 700, boss_health_pic[0], 0);
	}
	else if (boss_healthIndex == 2 || boss_healthIndex == 3){
		iShowBMP2(770, 700, boss_health_pic[1], 0);
	}
	else if (boss_healthIndex == 4 || boss_healthIndex == 5){
		iShowBMP2(770, 700, boss_health_pic[2], 0);
	}
	else if (boss_healthIndex == 6 || boss_healthIndex == 7){
		iShowBMP2(770, 700, boss_health_pic[3], 0);
	}
	else if (boss_healthIndex > 7)
		boss1 = false;

}

void boss_power_fun()
{
	if (pause)
	{
		if (boss1)
		{
			if (bossPowerShow)
				iShowBMP2(boss_pow_x, boss_pow_y, boss_power_pic[0], 0);
		}
	}
}

//LEVEL-2 BOSS
bool boss2 = false;
int boss2_x = 1215;
int boss2_y = 300;
char boss2_pic[4][20] = { "BossChar\\1.bmp", "BossChar\\2.bmp", "BossChar\\3.bmp", "BossChar\\4.bmp" };
int boss2In = 0;
char boss2_health_pic[4][20] = { "bosshealth\\1.bmp", "bosshealth\\2.bmp", "bosshealth\\3.bmp", "bosshealth\\4.bmp" };
int boss2_healthIndex = 0;
int boss2_health_x = 90;
int boss2_health_y = 700;
char boss2_power_pic[3][30] = { "BossChar\\boss2_3.bmp", "BossChar\\boss2_2.bmp", "BossChar\\boss2_1.bmp" };
int boss2PowerIn = 0;
int boss2_pow_x = 1100;
int boss2_pow_y = 300;
bool boss2PowerShow = false;


void boss2_health()
{
	if (boss2_healthIndex == 0 || boss2_healthIndex == 1){
		iShowBMP2(770, 700, boss2_health_pic[0], 0);
	}
	else if (boss2_healthIndex == 2 || boss2_healthIndex == 3){
		iShowBMP2(770, 700, boss2_health_pic[1], 0);
	}
	else if (boss2_healthIndex == 4 || boss2_healthIndex == 5){
		iShowBMP2(770, 700, boss2_health_pic[2], 0);
	}
	else if (boss2_healthIndex == 6 || boss2_healthIndex == 7){
		iShowBMP2(770, 700, boss2_health_pic[3], 0);
	}
	else if (boss2_healthIndex > 7)
		boss2 = false;

}

void boss2_power_fun()
{
	if (pause)
	{
		//if (boss1)
		//{
			if (boss2PowerShow)
				iShowBMP2(boss2_pow_x, boss2_pow_y, boss2_power_pic[boss2PowerIn], 0);
		//}
	}
}


//score
void score();




//level 1 BG
char BackGround_1[18][20] = { "stage1\\1.bmp", "stage1\\2.bmp", "stage1\\3.bmp", "stage1\\4.bmp", "stage1\\5.bmp", "stage1\\6.bmp", "stage1\\7.bmp", "stage1\\8.bmp", "stage1\\9.bmp", "stage1\\10.bmp", "stage1\\111.bmp", "stage1\\122.bmp", "stage1\\133.bmp", "stage1\\144.bmp", "stage1\\155.bmp", "stage1\\166.bmp", "stage1\\177.bmp", "stage1\\188.bmp"};
struct background
{
	int x = 0;
	int y = 0;
};
background BackGround1[18];

void showBG()
{
	for (int i = 0; i < 18; i++)
	{
		iShowBMP(BackGround1[i].x, BackGround1[i].y, BackGround_1[i]);
	}
}

//level 2 BG
char BackGround_2[18][20] = { "stage2\\1.bmp", "stage2\\2.bmp", "stage2\\3.bmp", "stage2\\4.bmp", "stage2\\5.bmp", "stage2\\6.bmp", "stage2\\7.bmp", "stage2\\8.bmp", "stage2\\9.bmp", "stage2\\10.bmp", "stage2\\11.bmp", "stage2\\12.bmp", "stage2\\13.bmp", "stage2\\14.bmp", "stage2\\15.bmp", "stage2\\16.bmp", "stage2\\17.bmp", "stage2\\18.bmp" };
struct background_level2
{
	int x1 = 0;
	int y1 = 0;
};
background_level2 BackGround2[18];

void showBG2()
{
	for (int i = 0; i < 18; i++)
	{
		iShowBMP(BackGround2[i].x1, BackGround2[i].y1, BackGround_2[i]);
	}
}




//BANDOR SET ALL
int b_x = 1350;
int b_y = 130;
int bIn = 0;
char bbandor[8][20] = { "char\\b1.bmp", "char\\b2.bmp", "char\\b3.bmp", "char\\b4.bmp", "char\\b5.bmp", "char\\b6.bmp", "char\\b7.bmp", "char\\b8.bmp" };
//char bandor_t[1][20] = {"char\\b9.bmp"};
int b_tIn = 0;
int bt_x = 1250;
int bt_y = 110;

struct bandor{
	int b_x;
	int b_y;
	int bIn;
	bool bShow;
};

bandor enemy[BANDORNUM];



//SHAAP SET ALL
char shaap[3][20] = { "char\\en1.bmp", "char\\en2.bmp", "char\\en3.bmp" };
int sIn = 0;
int s_x = 1350;
int s_y = 110;


struct Shap{
int s_x;
int s_y;
int sIn;
bool sShow;
};

Shap enemy1[SHAPNUM];


//AGUNN SET ALL
char fire_arr[6][20] = { "snake\\f1.bmp", "snake\\f2.bmp", "snake\\f3.bmp", "snake\\f4.bmp", "snake\\f5.bmp", "snake\\f6.bmp" };
int fireIn = 0;
int f_x = 1350;
int f_y = 120;


struct fire{
	int f_x;
	int f_y;
	int fireIn;
	bool fShow;
};

fire enemy2[FIRENUM];



//HEAL SET ALL
char heart_pic[1][20] = { "life\\heart.bmp" };
int heart_x = 1350;
int heart_y = 180;

struct heart{
	int heart_x;
	int heart_y;
	int healIn = 0;
	bool heartShow = true;
};
heart heal_kakashi[HEALNUM];


//level 2 enemy//

//ghost
int g_x = 1350;
int g_y = 180;
int gIn = 0;
char ghost[7][20] = { "enemy2\\1.bmp", "enemy2\\2.bmp", "enemy2\\3.bmp", "enemy2\\4.bmp", "enemy2\\5.bmp", "enemy2\\6.bmp", "enemy2\\7.bmp"};
int g_tIn = 0;

struct ghost_1{
	int g_x = 1350;
	int g_y = 140;
	int gIn;
	bool gShow;
};

ghost_1 enemy3[GHOSTNUM];


//dragon
int d_x = 1350;
int d_y = 180;
int dIn = 0;
char dragon_pic[10][20] = { "enemy2\\dra1.bmp", "enemy2\\dra2.bmp", "enemy2\\dra3.bmp", "enemy2\\dra4.bmp", "enemy2\\dra5.bmp", "enemy2\\dra6.bmp", "enemy2\\dra7.bmp", "enemy2\\dra8.bmp", "enemy2\\dra9.bmp", "enemy2\\dra10.bmp" };

struct dragon{
	int d_x = 1350;
	int d_y = 140;
	int dIn;
	bool dShow;
};

dragon enemy4[DRAGONNUM];

//bird
int bird_x = 1350;
int bird_y = 180;
int birdIn = 0;
char bird_pic[10][20] = { "enemy2\\bird1.bmp", "enemy2\\bird2.bmp", "enemy2\\bird3.bmp", "enemy2\\bird4.bmp", "enemy2\\bird5.bmp", "enemy2\\bird6.bmp", "enemy2\\bird7.bmp", "enemy2\\bird8.bmp", "enemy2\\bird9.bmp", "enemy2\\bird10.bmp" };

struct bird{
	int bird_x = 1350;
	int bird_y = 140;
	int birdIn;
	bool birdShow;
};

bird enemy5[BIRDNUM];



//ENEMY SHOW
void enemyMove()
{
	if (!congratulations){
		if (level_1){
			if (enemyMorse <= 1){
				//bandor
				for (int i = 0; i < BANDORNUM; i++)
				{
					if (enemy[i].bShow == true)
					{
						iShowBMP2(enemy[i].b_x, enemy[i].b_y, bbandor[enemy[i].bIn], 0);
					}
				}

				//shaap
				for (int i = 0; i < SHAPNUM; i++)
				{
					if (enemy1[i].sShow == true)
					{
						iShowBMP2(enemy1[i].s_x, enemy1[i].s_y, shaap[enemy1[i].sIn], 0);
					}
				}

				//fire
				for (int i = 0; i < FIRENUM; i++)
				{
					if (enemy2[i].fShow == true)
					{
						iShowBMP2(enemy2[i].f_x, enemy2[i].f_y, fire_arr[enemy2[i].fireIn], 255);
					}
				}
			}
			else{
				boss1 = true;
				bossPowerShow = true;
				iShowBMP2(boss1_x, boss1_y, "BossChar\\DRAGONBOSS.bmp", 0);
				boss_health();
				boss_power_fun();
			}
		}

		//heal
		for (int i = 0; i < HEALNUM; i++)
		{
			if (heal_kakashi[i].heartShow == true)
			{
				iShowBMP2(heal_kakashi[i].heart_x, heal_kakashi[i].heart_y, heart_pic[heal_kakashi[i].healIn], 0);
			}
		}
	}
}

void enemyMove2(){
	if (!congratulations){
		if (level_2){
			if (enemyDead2 <= 1){
				//ghost
				for (int i = 0; i < GHOSTNUM; i++)
				{
					if (enemy3[i].gShow == true)
					{
						iShowBMP2(enemy3[i].g_x, enemy3[i].g_y, ghost[enemy3[i].gIn], 0);
					}
				}

				//dragon
				for (int i = 0; i < DRAGONNUM; i++)
				{
					if (enemy4[i].dShow == true)
					{
						iShowBMP2(enemy4[i].d_x, enemy4[i].d_y, dragon_pic[enemy4[i].dIn], 0);
					}
				}

				//bird
				for (int i = 0; i < BIRDNUM; i++)
				{
					if (enemy5[i].birdShow == true)
					{
						iShowBMP2(enemy5[i].bird_x, enemy5[i].bird_y, bird_pic[enemy5[i].birdIn], 0);
					}
				}

				//heal
				for (int i = 0; i < HEALNUM; i++)
				{
					if (heal_kakashi[i].heartShow == true)
					{
						iShowBMP2(heal_kakashi[i].heart_x, heal_kakashi[i].heart_y, heart_pic[heal_kakashi[i].healIn], 0);
					}
				}


			}
			else{
				boss2 = true;
				boss2PowerShow = true;
				iShowBMP2(boss2_x, boss2_y, boss2_pic[boss2In], 0);
				boss2_health();
				boss2_power_fun();
			}
		}
	}
}

void con(){
	if (congratulations){
		iShowBMP(0, 0, "menu\\congratulations.bmp");
		iShowBMP2(hcord[1].hx, hcord[1].hy, home[0], 0);
	}
}



//SONG
bool soundOn = true;
char sound[50] = {"music\\Naruto Soundtrack - Naruto Main Theme.wav"};
void sou();
void music();

void power_sound();
char powerSound[40] = { "music\\Chidori Sound Effect.wav" };




//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();
	
	//showBG();
	menu();
	if (gamestate == 0){
		if (level_1){
			showBG();
			position_of_Kakashi();
			enemyMove();
			score();
			health();
		}
		else if (level_2){
			showBG2();
			position_of_Kakashi();
			enemyMove2();
			score();
			health();
		}
		else if(congratulations){
			con();
			score();
		}
		//health();
		pause_pic();

	}

}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	mouseDragPos_x = mx;
	mouseDragPos_y = my;
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	mousepos_x = mx;
	mousepos_y = my;
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gamestate == -1){
			for (int i = 0; i < 5; i++)
			{
				if (mx >= bcord[i].x && mx <= bcord[i].x + 300 && my >= bcord[i].y && my <= bcord[i].y + 50)
				{
					gamestate = i;
					if (gamestate == 0)
						pause = true;
				}
			}
		}

		if (gamestate == 0){
			for (int i = 0; i < 2; i++)
			{
				if (mx >= pbcord[i].px && mx <= pbcord[i].px + 110 && my >= pbcord[i].py + 130 && my <= pbcord[i].py + 250)

				{
					if (pause == true)
						pause = false;
					else{ 
						pause = true; 
					}


				}

			}
		}
		if (gamestate == 0){
			for (int i = 0; i < 2; i++)
			{
				if (mx >= pbcord[i].px && mx <= pbcord[i].px + 110 && my >= pbcord[i].py && my <= pbcord[i].py + 120)
				{
					//pause_menu();
					gamestate = -1;

				}

			}
		}

		//backbutton
		if (gamestate == 3){
			if (mx >= bbcord[1].bx && mx <= bbcord[1].bx + 300 && my >= bbcord[1].by && my <= bbcord[1].by + 50)
			{
				gamestate = -1;
			}
		}
		//yes
		if (gamestate == 4){
			if (mx >= ycord[1].yx && mx <= ycord[1].yx + 300 && my >= ycord[1].yy && my <= ycord[1].yy + 50)
			{
				exit(0);
			}

			//no
			if (mx >= ncord[1].nx && mx <= ncord[1].nx + 300 && my >= ncord[1].ny && my <= ncord[1].ny + 50)
			{
				gamestate = -1;
			}
		}

		if (gameOver){
			if (mx >= hcord[1].hx && mx <= hcord[1].hx + 120 && my >= hcord[1].hy && my <= hcord[1].hy + 100)
			{
				gamestate = -1;
			}
		}
		if (congratulations){
			if (mx >= hcord[1].hx && mx <= hcord[1].hx + 120 && my >= hcord[1].hy && my <= hcord[1].hy + 100)
			{
				gamestate = -1;
			}
		}

		//fight & ninja star
		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		
	}

	mouseClickPos_x = mx;
	mouseClickPos_y = my;
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{	
	if (key == '1'){
			if (!nS){
				nS = true;
				if(!fight) 
				fight = true;
				n_x = k_x;
				if (jump)
				{
					n_y = jCor + k_y + 50;
				}
				else
				{
					n_y = k_y + 50;
				}
			}
	}

	if (key == '2'){
			if (!power){
				power = true;
				p_bS = true;
				p_b_x = k_x;
				p_b_y = k_y + 50;
			}


			if (jump)
			{
				p_b_y = jCor + k_y + 50;
			}
			else
			{
				p_b_y = k_y + 50;
			}
		}

	if (key == 'a')
	{
		k_x -= 20;
	}

	if (key == 'd')
	{
		k_x += 20;
	}
	
	if (key == ' ')
	{
		if (!jump){
			jump = true;
			jup = true;
		}
	}

	if (key == 'k')
	{
		music();
	}

	if (key == 'p')
	{
		pause_menu();
	}

	keyButton = key;
	
	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
				
	}
	if (key == GLUT_KEY_LEFT)
	{
		
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}

	spcial_key = key;
	
}

void run()
{
	rIn++;
	if (rIn >= 7)
	{
		rIn = 0;
	}
}

void ninjaStar()
{
	if (pause){
		if (nS)
		{
			nIn++;
			if (nIn >= 2)
			{
				nIn = 0;
			}
			n_x = n_x + 90;
			if (n_x >= SCREENWIDTH)
			{
				nS = false;
				n_x = k_x + 10000000000000000000;
				n_y = k_y;
			}
		}
	}
}

void fig()
{
	if (fight){
		fIn++;
		if (fIn >= 2)
		{
			fIn = 0;
			fight = false;
		}
	}
}

void pow_fun()
{
	if (power){
		pIn++;
		if (pIn >= 2)
		{
			pIn = 0;
			power = false;
		}
	}
}

void p_b_function()
{

	p_bIn++;
	if (p_bS)
	{
		p_b_x = p_b_x + 90;
		if (p_b_x >= SCREENWIDTH){
			p_b_x = k_x;
			p_bS = false;
		}
	}

	if (p_bIn >= 1)
	{
		p_bIn = 0;
	}
}

int diff = 20;
void boss_move(){
	if (boss1){
		boss1_y += diff;
		if (boss1_y >= 500){
			diff = diff* -1;
		}
		else if (boss1_y <= 120){
			diff = diff * -1;
		}
	}
}

void boss_power()
{
	if (boss1)
	{
		if (bossPowerShow){
			boss_pow_x -= 40;
			if (boss_pow_x <= 0)
			{
				boss_pow_x = boss1_x;
				boss_pow_y = boss1_y;
				bossPowerShow = true;
			}
		}
	}
}

//boss 2 move//
void boss2Pic()
{
	boss2In++;
	if (boss2In >= 3)
	{
		boss2In = 0;
	}
}

int diff2 = 20;
void boss2_move(){
	//if (boss2){
		boss2_y += diff2;
		if (boss2_y >= 500){
			diff2 = diff2* -1;
		}
		else if (boss2_y <= 120){
			diff2 = diff2 * -1;
		}
	//}
}

void boss2_power()
{
	//if (boss2)
	//{
		//if (boss2PowerShow){
			boss2_pow_x -= 40;
			if (boss2_pow_x <= 0)
			{
				boss2_pow_x = boss2_x;
				boss2_pow_y = boss2_y;
				boss2PowerShow = true;
			}
			if (boss2PowerIn >= 2)
			{
				boss2PowerIn = 0;
			}
		//}
	//}
}

void setEnemy()
{
	if (!congratulations){
		if (level_1){
			//bandor
			if (enemyMorse <= 1){
				for (int i = 0; i < BANDORNUM; i++)
				{
					enemy[i].b_x = SCREENWIDTH + rand() % 100000000;
					enemy[i].b_y = b_y;
					enemy[i].bIn = rand() % 8;
					enemy[i].bShow = true;
				}


				//shap
				for (int i = 0; i < SHAPNUM; i++)
				{
					enemy1[i].s_x = SCREENWIDTH + rand() % 10000000000;
					enemy1[i].s_y = s_y;
					enemy1[i].sIn = rand() % 3;
					enemy1[i].sShow = true;
				}


				//fire
				for (int i = 0; i < FIRENUM; i++)
				{
					enemy2[i].f_x = SCREENWIDTH + rand() % 100;
					enemy2[i].f_y = f_y;
					enemy2[i].fireIn = rand() % 6;
					enemy2[i].fShow = true;
				}
			}
		}
		else if (level_2){
			if (enemyDead2 <= 1){
				//ghost
				for (int i = 0; i < GHOSTNUM; i++)
				{
					enemy3[i].g_x = SCREENWIDTH + rand() % 100000000;
					enemy3[i].g_y = g_y;
					enemy3[i].gIn = rand() % 7;
					enemy3[i].gShow = true;
				}

				//dragon
				for (int i = 0; i < DRAGONNUM; i++)
				{
					enemy4[i].d_x = SCREENWIDTH + rand() % 100000000;
					enemy4[i].d_y = d_y;
					enemy4[i].dIn = rand() % 10;
					enemy4[i].dShow = true;
				}

				//bird
				for (int i = 0; i < BIRDNUM; i++)
				{
					enemy5[i].bird_x = SCREENWIDTH + rand() % 100000000;
					enemy5[i].bird_y = SCREENHEIGHT + rand() % 100000000;
					enemy5[i].birdIn = rand() % 10;
					enemy5[i].birdShow = true;
				}
			}


			//life
			for (int i = 0; i < HEALNUM; i++)
			{
				heal_kakashi[i].heart_x = SCREENWIDTH + rand() % 1000000000000;
				heal_kakashi[i].heart_y = heart_y;
				heal_kakashi[i].healIn = 0;
				heal_kakashi[i].heartShow = true;
			}
		}
	}
}

void b_change()
{
	if (!congratulations){
		if (level_1){
			if (enemyMorse <= 1){
				//bandor
				for (int i = 0; i < BANDORNUM; i++)
				{
					if (enemy[i].bShow){
						enemy[i].b_x -= 20;
						if (enemy[i].b_x <= 0)
						{
							enemy[i].b_x = SCREENWIDTH + rand() % 1000000;
							//enemy[i].bShow = true;
						}
						enemy[i].bIn++;
						if (enemy[i].bIn >= 8)
						{
							enemy[i].bIn = 0;
						}
					}
					else if (enemy[i].bShow == false){
						enemy[i].b_x = SCREENWIDTH + rand() % 1000000;
						enemy[i].bIn = rand() % 8;
						enemy[i].bShow = true;
					}
				}


				//shaap
				for (int i = 0; i < SHAPNUM; i++)
				{
					if (enemy1[i].sShow){
						enemy1[i].s_x -= 35;
						if (enemy1[i].s_x <= 0)
						{
							enemy1[i].s_x = SCREENWIDTH + rand() % 1000000;
							//enemy[i+1].b_x = 1366 + 30;
						}
						enemy1[i].sIn++;
						if (enemy1[i].sIn >= 3)
						{
							enemy1[i].sIn = 0;
						}
					}
					else if (enemy1[i].sShow == false){
						enemy1[i].s_x = SCREENWIDTH + rand() % 1000000;
						enemy1[i].sIn = rand() % 3;
						enemy1[i].sShow = true;
					}
				}



				//fire
				for (int i = 0; i < FIRENUM; i++)
				{
					if (enemy2[i].fShow){
						enemy2[i].f_x -= 50;
						if (enemy2[i].f_x <= 0)
						{
							enemy2[i].f_x = SCREENWIDTH + rand() % 1000000;
							//enemy[i+1].b_x = 1366 + 30;
						}
						enemy2[i].fireIn++;
						if (enemy2[i].fireIn >= 6)
						{
							enemy2[i].fireIn = 0;
						}
					}
					else if (enemy2[i].fShow == false){
						enemy2[i].f_x = SCREENWIDTH + rand() % 1000000;
						enemy2[i].fireIn = rand() % 6;
						enemy2[i].fShow = true;

					}
				}
			}
		}

		if (level_2){
			if (enemyDead2 <= 1){
				//ghost
				for (int i = 0; i < GHOSTNUM; i++)
				{
					if (enemy3[i].gShow){
						enemy3[i].g_x -= 20;
						if (enemy3[i].g_x <= 0)
						{
							enemy3[i].g_x = SCREENWIDTH + rand() % 1000000;
						}
						enemy3[i].gIn++;
						if (enemy3[i].gIn >= 7)
						{
							enemy3[i].gIn = 0;
						}
					}
					else if (enemy3[i].gShow == false){
						enemy3[i].g_x = SCREENWIDTH + rand() % 1000000;
						enemy3[i].gIn = rand() % 7;
						enemy3[i].gShow = true;
					}
				}

				//dragon
				for (int i = 0; i < DRAGONNUM; i++)
				{
					if (enemy4[i].dShow){
						enemy4[i].d_x -= 20;
						if (enemy4[i].d_x <= 0)
						{
							enemy4[i].d_x = SCREENWIDTH + rand() % 1000000;
						}
						enemy4[i].dIn++;
						if (enemy4[i].dIn >= 10)
						{
							enemy4[i].dIn = 0;
						}
					}
					else if (enemy4[i].dShow == false){
						enemy4[i].d_x = SCREENWIDTH + rand() % 1000000;
						enemy4[i].dIn = rand() % 10;
						enemy4[i].dShow = true;
					}
				}

				//bird
				for (int i = 0; i < BIRDNUM; i++)
				{
					if (enemy5[i].birdShow){
						enemy5[i].bird_x -= 20;
						if (enemy5[i].bird_x <= 0)
						{
							enemy5[i].bird_x = SCREENWIDTH + rand() % 1000000;
						}
						enemy5[i].birdIn++;
						if (enemy5[i].birdIn >= 10)
						{
							enemy5[i].birdIn = 0;
						}
					}
					else if (enemy5[i].birdShow == false){
						enemy5[i].bird_x = SCREENWIDTH + rand() % 1000000;
						enemy5[i].birdIn = rand() % 10;
						enemy5[i].birdShow = true;
					}
				}
			}
		}

		//life
		for (int i = 0; i < HEALNUM; i++)
		{
			if (heal_kakashi[i].heartShow){
				heal_kakashi[i].heart_x -= 50;
				if (heal_kakashi[i].heart_x <= 0)
				{
					heal_kakashi[i].heart_x = SCREENWIDTH + rand() % 1000000;
				}
				heal_kakashi[i].healIn++;
				if (heal_kakashi[i].healIn >= 1)
				{
					heal_kakashi[i].healIn = 0;
				}
			}
			else if (heal_kakashi[i].heartShow == false){
				heal_kakashi[i].heart_x = SCREENWIDTH + rand() % 1000000;
				heal_kakashi[i].healIn = rand() % 6;
				heal_kakashi[i].heartShow = true;

			}
		}
	}
}


void change(){
	
	if (!congratulations){
		if (pause){
			b_change();
			boss2Pic();
			boss2_power();
			boss2_move();
			boss_move();
			boss_power();
			run();
			p_b_function();
			if (fight || nS)
			{
				fig();
				ninjaStar();
			}

			if (power)
			{
				pow_fun();
				PlaySound(powerSound, NULL, SND_ASYNC);
			}


			if (jump)
			{
				if (jup)
				{
					jCor += 90;
					if (jCor >= JUMPLIMIT)
					{
						jup = false;
					}
				}
				else
				{
					jCor -= 90;
					if (jCor < 0)
					{
						jump = false;
						jCor = 100;
					}
				}
			}
		}
	}
}


//bg coordinate set
void setAll(){

	if (level_1){
		int sum = 0;
		for (int i = 0; i < 18; i++)
		{

			BackGround1[i].y = 0;

			BackGround1[i].x = sum;



			sum += PERWIDTH;
		}
	}
}


//bg render
void render()
{
	if (pause){
		for (int i = 0; i < 18; i++)
		{
			BackGround1[i].x -= PERWIDTH;

			if (BackGround1[i].x < 0)
			{
				BackGround1[i].x = SCREENWIDTH - PERWIDTH;

			}

		}
	}
}

//level 2 bg
void setAll2(){

	//if (level_2){
		int sum = 0;
		for (int i = 0; i < 18; i++)
		{

			BackGround2[i].y1 = 0;

			BackGround2[i].x1 = sum;



			sum += PERWIDTH;
		}
	}


//bg render
void render2()
{
	if (pause){
		for (int i = 0; i < 18; i++)
		{
			BackGround2[i].x1 -= PERWIDTH;

			if (BackGround2[i].x1 < 0)
			{
				BackGround2[i].x1 = SCREENWIDTH - PERWIDTH;

			}

		}
	}
}



//collision
void collision()
{
	if (level_1){
		if (pause){
			//ninja star

			for (int i = 0; i < BANDORNUM; i++)
			{
				if (n_x + 37 >= enemy[i].b_x &&n_x <= enemy[i].b_x + 100 && n_y + 33 >= enemy[i].b_y && n_y <= enemy[i].b_y + 100)
				{
					enemy[i].bShow = false;
					nS = false;
					fight = false;
					n_x = k_x + 10000000000000000000;
					enemyMorse++;
					scoreCount1 += 10;
				}


			}

			for (int i = 0; i < SHAPNUM; i++)
			{
				if (n_x + 37 >= enemy1[i].s_x &&n_x <= enemy1[i].s_x + 100 && n_y + 33 >= enemy1[i].s_y && n_y <= enemy1[i].s_y + 100)
				{
					enemy1[i].sShow = false;
					nS = false;
					fight = false;
					n_x = k_x + 10000000000000000000;
					enemyMorse++;
					scoreCount1 += 10;
				}


			}


			//power

			for (int i = 0; i < BANDORNUM; i++)
			{
				if (p_b_x + 37 >= enemy[i].b_x && p_b_x + 37 <= enemy[i].b_x + 100 && p_b_y >= enemy[i].b_y && p_b_y <= enemy[i].b_y + 100)
				{

					enemy[i].bShow = false;
					p_bS = false;
					p_b_x = k_x + 10000000000000000000;
					enemyMorse++;
					scoreCount1 += 10;
				}


			}

			for (int i = 0; i < SHAPNUM; i++)
			{
				if (p_b_x + 37 >= enemy1[i].s_x && p_b_x + 37 <= enemy1[i].s_x + 100 && p_b_y >= enemy1[i].s_y && p_b_y <= enemy1[i].s_y + 100)
				{

					enemy1[i].sShow = false;
					p_bS = false;
					p_b_x = k_x + 10000000000000000000;
					enemyMorse++;
					scoreCount1 += 10;
				}


			}

			for (int i = 0; i < FIRENUM; i++)
			{
				if (p_b_x + 37 >= enemy2[i].f_x && p_b_x + 37 <= enemy2[i].f_x + 100 && p_b_y >= enemy2[i].f_y && p_b_y <= enemy2[i].f_y + 100)
				{
					enemy2[i].fShow = false;
					p_bS = false;
					p_b_x = k_x + 10000000000000000000;
					enemyMorse++;
					scoreCount1 += 10;
				}
			}

		}
	}
	else if (level_2){
		if (pause){
			//ninjastar
			for (int i = 0; i < GHOSTNUM; i++)
			{
				if (n_x + 37 >= enemy3[i].g_x &&n_x <= enemy3[i].g_x + 100 && n_y + 33 >= enemy3[i].g_y && n_y <= enemy3[i].g_y + 100)
				{
					enemy3[i].gShow = false;
					nS = false;
					fight = false;
					n_x = k_x + 10000000000000000000;
					enemyDead2++;
					scoreCount1 += 10;
				}
			}

			for (int i = 0; i < BIRDNUM; i++)
			{
				if (n_x + 37 >= enemy5[i].bird_x &&n_x <= enemy5[i].bird_x + 100 && n_y + 33 >= enemy5[i].bird_y && n_y <= enemy5[i].bird_y + 100)
				{
					enemy5[i].birdShow = false;
					nS = false;
					fight = false;
					n_x = k_x + 10000000000000000000;
					enemyDead2++;
					scoreCount1 += 10;
				}
			}

			//power
			for (int i = 0; i < GHOSTNUM; i++)
			{
				if (p_b_x + 37 >= enemy3[i].g_x && p_b_x <= enemy3[i].g_x + 100 && p_b_y + 33 >= enemy3[i].g_y && p_b_y <= enemy3[i].g_y + 100)
				{
					enemy3[i].gShow = false;
					p_bS = false;
					power = false;
					p_b_x = k_x + 10000000000000000000;
					enemyDead2++;
					scoreCount1 += 10;
				}
			}

			for (int i = 0; i < DRAGONNUM; i++)
			{
				if (p_b_x + 37 >= enemy4[i].d_x && p_b_x + 37 <= enemy4[i].d_x + 100 && p_b_y >= enemy4[i].d_y && p_b_y <= enemy4[i].d_y + 100)
				{

					enemy4[i].dShow = false;
					p_bS = false;
					p_b_x = k_x + 10000000000000000000;
					enemyDead2++;
					scoreCount1 += 10;
				}


			}

			for (int i = 0; i < BIRDNUM; i++)
			{
				if (p_b_x + 37 >= enemy5[i].bird_x && p_b_x <= enemy5[i].bird_x + 100 && p_b_y + 33 >= enemy5[i].bird_y && p_b_y <= enemy5[i].bird_y + 100)
				{
					enemy5[i].birdShow = false;
					p_bS = false;
					power = false;
					p_b_x = k_x + 10000000000000000000;
					enemyDead2++;
					scoreCount1 += 10;
				}
			}
		}
	}
	boss1_collision();
	boss2_collision();
			
}

void boss1_collision()
{
	if (pause){
		//ninjastar
		if (n_x + 100 >= boss1_x && n_x <= boss1_x + 160 && n_y + jCor >= boss1_y && n_y + jCor <= boss1_y + 150)
		{
			nS = false;
			fight = false;
			n_x = k_x + 10000000000000000000;
			scoreCount1 += 20;
			//enemyMorse += 1;
		}

		//power
		if (p_b_x + 37 >= boss1_x && p_b_x + 37 <= boss1_x + 100 && p_b_y >= boss1_y && p_b_y <= boss1_y + 100)
		{
			p_bS = false;
			power = false;
			//p_b_x = k_x + 10000000000000000000;
			scoreCount1 += 20;
			//enemyMorse += 1;
		}
	}
}

void boss2_collision()
{
	if (pause){
		//ninjastar
		if (n_x + 100 >= boss2_x && n_x <= boss2_x + 160 && n_y + jCor >= boss2_y && n_y + jCor <= boss2_y + 150)
		{
			nS = false;
			fight = false;
			n_x = k_x + 10000000000000000000;
			scoreCount1 += 20;
			//enemyMorse += 1;
		}

		//power
		if (p_b_x + 37 >= boss2_x && p_b_x + 37 <= boss2_x + 100 && p_b_y >= boss2_y && p_b_y <= boss2_y + 100)
		{
			p_bS = false;
			power = false;
			//p_b_x = k_x + 10000000000000000000;
			scoreCount1 += 20;
			//enemyMorse += 1;
		}
	}
}


//life of kakashi :")
void health_coll()
{
	if (level_1){
		if (pause){
			for (int i = 0; i < BANDORNUM; i++)
			{
				if (k_x + 100 >= enemy[i].b_x && k_x <= enemy[i].b_x + 160 && k_y + jCor >= enemy[i].b_y && k_y + jCor <= enemy[i].b_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy[i].bShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy[i].bShow = false;
						scoreCount1 += 10;

					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < SHAPNUM; i++)
			{
				if (k_x + 100 >= enemy1[i].s_x && k_x <= enemy1[i].s_x + 160 && k_y + jCor >= enemy1[i].s_y && k_y + jCor <= enemy1[i].s_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy1[i].sShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy1[i].sShow = false;
						scoreCount1 += 10;
					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < FIRENUM; i++)
			{
				if (k_x + 100 >= enemy2[i].f_x && k_x <= enemy2[i].f_x + 160 && k_y + jCor >= enemy2[i].f_y && k_y + jCor <= enemy2[i].f_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy2[i].fShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy2[i].fShow = false;
						scoreCount1 += 10;
					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < BOSSPOWER1; i++)
			{
				if (k_x + 100 >= boss_pow_x && k_x <= boss_pow_x + 160 && k_y + jCor >= boss_pow_y && k_y + jCor <= boss_pow_y + 150)
				{
					if (healthIndex <= 3){
						if (boss_power){
							int a = 20;
							healthIndex++;
							bossPowerShow = false;
							boss_pow_x = a * -1;
						}
						cout << healthIndex << endl;
						
						//scoreCount1 += 10;
					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < HEALNUM; i++)
			{
				if (k_x + 100 >= heal_kakashi[i].heart_x && k_x <= heal_kakashi[i].heart_x + 50 && k_y + jCor >= heal_kakashi[i].heart_y && k_y + jCor <= heal_kakashi[i].heart_y + 45)
				{
					if (heal_kakashi[i].heartShow)
						healthIndex--;
					cout << healthIndex << endl;
					heal_kakashi[i].heartShow = false;
					if (healthIndex <= 0)
					{
						healthIndex = 0;
					}


				}
			}
		}
	}
	else if (level_2){
		if (pause){
			for (int i = 0; i < GHOSTNUM; i++)
			{
				if (k_x + 100 >= enemy3[i].g_x && k_x <= enemy3[i].g_x + 160 && k_y + jCor >= enemy3[i].g_y && k_y + jCor <= enemy3[i].g_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy3[i].gShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy3[i].gShow = false;
						scoreCount1 += 10;

					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < DRAGONNUM; i++)
			{
				if (k_x + 100 >= enemy4[i].d_x && k_x <= enemy4[i].d_x + 160 && k_y + jCor >= enemy4[i].d_y && k_y + jCor <= enemy4[i].d_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy4[i].dShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy4[i].dShow = false;
						scoreCount1 += 10;

					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}

			for (int i = 0; i < BIRDNUM; i++)
			{
				if (k_x + 100 >= enemy5[i].bird_x && k_x <= enemy5[i].bird_x + 160 && k_y + jCor >= enemy5[i].bird_y && k_y + jCor <= enemy5[i].bird_y + 150)
				{
					if (healthIndex <= 3){
						if (enemy5[i].birdShow)
							healthIndex++;
						cout << healthIndex << endl;
						enemy5[i].birdShow = false;
						scoreCount1 += 10;

					}
					else if (healthIndex > 3)
					{
						//healthIndex = 3;
						gameOver = true;
					}
				}
			}
		}
	}
}

void boss1_health()
{
	if (pause){
		//ninjastar
		if (n_x + 100 >= boss1_x && n_x <= boss1_x + 160 && n_y + jCor >= boss1_y && n_y + jCor <= boss1_y + 150)
		{
			if (boss_healthIndex <= 7){
				if (boss1)
					boss_healthIndex++;
				cout << boss_healthIndex << endl;

			}
			else if (boss_healthIndex > 7)
			{
				boss1 = false;
				level_1 = false;
				level_2 = true;
			}

		}

		//power
		if (p_b_x + 100 >= boss1_x && p_b_x <= boss1_x + 160 && p_b_y + jCor >= boss1_y && p_b_y + jCor <= boss1_y + 150)
		{
			if (boss_healthIndex <= 7){
				if (boss1){
					boss_healthIndex++;
					k_p_x = SCREENWIDTH + 10;
				}
				cout << boss_healthIndex << endl;
			}
				else if (boss_healthIndex > 7)
				{
					boss1 = false;
					level_1 = false;
					level_2 = true;
				}
			}
		}
}

void boss2_health2()
{
	if (pause){
		//ninjastar
		if (n_x + 100 >= boss2_x && n_x <= boss2_x + 160 && n_y + jCor >= boss2_y && n_y + jCor <= boss2_y + 150)
		{
			if (boss2_healthIndex <= 7){
				if (boss2)
					boss2_healthIndex++;
				cout << boss2_healthIndex << endl;

			}
			else if (boss2_healthIndex > 7)
			{
				boss2 = false;
				level_2 = false;
				congratulations = true;
			}

		}

		//power
		if (p_b_x + 100 >= boss2_x && p_b_x <= boss2_x + 160 && p_b_y + jCor >= boss2_y && p_b_y + jCor <= boss2_y + 150)
		{
			if (boss2_healthIndex <= 7){
				if (boss2){
					boss2_healthIndex++;
					k_p_x = SCREENWIDTH + 10;
				}
				cout << boss2_healthIndex << endl;
			}
			else if (boss2_healthIndex > 7)
			{
				boss2 = false;
				level_2 = false;
				congratulations = true;
			}
		}
	}
}


//sound function

void music()
{
	if (soundOn)
	{
		soundOn = false;
		//PlaySound(sound, NULL, SND_LOOP | SND_ASYNC);
		PlaySound(0, 0, 0);
	}
	else
	{
		soundOn = true;
		PlaySound(sound, NULL, SND_ASYNC | SND_LOOP);
	}
}

void sou()
{
	if (soundOn)
	{
		PlaySound(sound, NULL, SND_LOOP | SND_ASYNC);
	}
}




void pause_menu()
{
	if (!pause)
	{
		pause = true;
		
	}
	else
	{
		pause = false;
		
	}
}

//menu system

void set()
{
	int sum = 200;
	for (int i = 5; i >= 0; i--)
	{
		bcord[i].x = 70;
		bcord[i].y = sum;
		sum += 80;
	}

}
void bset()
{
	bbcord[1].bx = 600;
	bbcord[1].by = 20;
}
void yset()
{
	ycord[1].yx = 420;
	ycord[1].yy = 400;
}
void nset()
{
	ncord[1].nx = 820;
	ncord[1].ny = 400;
}

void hset()
{
	hcord[1].hx = 720;
	hcord[1].hy = 20;
}

void pset()
{
	int sum = 100;
	for (int i = 2; i >= 0; i--)
	{
		pbcord[i].px = 690;
		pbcord[i].py = sum;
		sum += 120;
	}

}


int main()
{
	///srand((unsigned)time(NULL));
	//menu_set();
	nset();
	hset();
	pset();
	yset();
	bset();
	set();
	setAll();
	setAll2();
	iSetTimer(10, boss2_health2);
	iSetTimer(10, health_coll);
	iSetTimer(10, boss1_health);
	iSetTimer(10, collision);
	iSetTimer(25, ninjaStar);
	iSetTimer(150, render);
	iSetTimer(150, render2);
	setEnemy();
	//sou();
	//power_sound();
	iSetTimer(200, change);
	iInitialize(SCREENWIDTH, SCREENHEIGHT, "ShinobiRun");
	///updated see the documentations
	iStart();
	return 0;
}