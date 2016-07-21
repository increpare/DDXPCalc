#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int monsterCount=41;

int defaultMonsters[] = {
	1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	6,6,6,
	7,7,7,
	8,8,8,
	9,9,
	10,10,10
};

int calcXP(int playerLevel,int enemyLevel){
	if (enemyLevel<=playerLevel){
		return enemyLevel;
	}
	int diff = enemyLevel-playerLevel;
	return enemyLevel+diff*(diff-1)+2;
}


void shuffle(int array[], size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int calcLevel(int xp){
	return (int)( (1 + sqrt(1+(8.0*xp)/5)) /2 );
}


int doBattle(int monsters[], int print){
	int xp=0;
	int curLevel=1;

	for (int i=0;i<monsterCount;i++){
		int monsterLevel=monsters[i];
		int playerLevel=calcLevel(xp);
		int battleXP = calcXP(playerLevel,monsterLevel);
		xp += battleXP;	

		if (print){
			printf("%d",monsterLevel);

			int newLevel=calcLevel(xp);	
			if (newLevel>playerLevel){
				printf(" ⬆(%d) ",newLevel);
			} else {
				printf(" ");
			}
		}
	}
	if (print){
		printf("\n");
	}
	return xp;
}

void runBattles(){
	int lastMax=0;
	//defaultMonsters.reverse();
	for (int i=0;i<10000000;i++){
		int xp = doBattle(defaultMonsters,0);
		if (xp>lastMax){

			printf("%d\n\t",xp);
			doBattle(defaultMonsters,1);


			lastMax=xp;
		}
		shuffle(defaultMonsters,monsterCount);
	}
}

int main() {
	runBattles();

	return 0;
}