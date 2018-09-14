#include"my_player.h"

int main(int argc,char *argv[]){

	string path = "../music/";	
	Music::MyPlayer player(path);
	
	player.Init();
	player.Menu();

	return 0;
}

