#include "stdio.h"
#include "stdlib.h"
#include <windows.h>

#define LEN 15

unsigned int map[15][15];

// ┏┳┓┣╋┫┗┻┛ ━┃

char* setp(int i, int j){
	if (i < 0 || j < 0){
		return NULL;
	}
	else{
		if (map[i][j] == 1){
			return "●";
		}
		else if (map[i][j] == 2){
			return "○";
		}
		else{
			if (i == 0){
				if (j==0){
					return "┏";
				}
				else if(j==14){
					return "┓";
				}
				else{
					return "┳";
				}
			}
			else if(i == 14){
				if (j == 0){
					return "┗";
				}
				else if (j == 14){
					return "┛";
				}
				else{
					return "┻";
				}
			}
			else{
				if (j == 0){
					return "┣";
				}
				else if (j == 14){
					return "┫";
				}
				else{
					return "╋";
				}
			}
		}
	}

}

void paint(int x, int y, unsigned int user){

	if (x<-1||x>14||y<-1||y>14){
		return;
	}
	else{
		map[x][y] = user;
	}

	system("cls");

	printf("  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O\n");

	for (int i = 0; i < 15; i++){
		printf("%c", 'A'+i);
		for (int j = 0; j < 15;j++){
			if (14 == j){
				printf("%s", setp(i, j));
			}
			else{
				printf("%s━", setp(i, j));
			}
		}
		printf("%c\n", 'A' + i);
		
		if (14!=i){
			printf(" ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃\n");
		}
	}

	printf("  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O\n");
}

unsigned int check_run(){
	for (int i = 0; i < LEN - 4; i++){
		for (int j = 0; j < LEN - 4; j++){

			if (map[i][j] == 0){
				continue;
			}

			if ((map[i][j] == map[i + 1][j]) && 
				(map[i + 1][j] == map[i + 2][j]) &&
				(map[i + 2][j] == map[i + 3][j]) &&
				(map[i + 3][j] == map[i + 4][j])){
				return map[i][j];
			}

			if ((map[i][j] == map[i][j + 1]) &&
				(map[i][j + 1] == map[i][j + 2]) &&
				(map[i][j + 2] == map[i][j + 3]) &&
				(map[i][j + 3] == map[i][j + 4])){
				return map[i][j];
			}

			if ((map[i][j] == map[i + 1][j + 1]) &&
				(map[i + 1][j + 1] == map[i + 2][j + 2]) &&
				(map[i + 2][j + 2] == map[i + 3][j + 3]) &&
				(map[i + 3][j + 3] == map[i + 4][j + 4])){
				return map[i][j];
			}

		}
	}

	for (int x = 0; x < LEN - 4; x++){
		for (int y = LEN - 1; y >= 4; y--){

			if (map[x][y] == 0){
				continue;
			}

			if ((map[x][y] == map[x + 1][y - 1]) &&
				(map[x + 1][y - 1] == map[x + 2][y - 2]) &&
				(map[x + 2][y - 2] == map[x + 3][y - 3]) &&
				(map[x + 3][y - 3] == map[x + 4][y - 4])
				){
				return map[x][y];
			}

		}
	}

	return 0;
}

int main(void){
	HWND win = GetForegroundWindow();
	SetWindowText(win, L"五子棋  作者 https://github.com/duguying");
	ShowWindow(win, SW_MAXIMIZE);
	unsigned int current_user = 1;

	memset(map, 0, sizeof(unsigned int) * 15 * 15);

	paint(-1,-1, 0);
	
	while (true){
		char buf[3];

		memset(buf, 0, 3 * sizeof(char));

		printf("请输入棋子坐标:");
		gets(buf);
		_strupr_s(buf);
		
		if (buf[0]<'A' || buf[0]>'O' || buf[1]<'A' || buf[1]>'O'){
			continue;
		}

		int x = buf[0] - 'A';
		int y = buf[1] - 'A';

		if (map[x][y]!=0){
			continue;
		}
		
		if (buf[0] == '0' || buf[1] == '0'){
			break;
		}

		++current_user;
		current_user = current_user % 2;
		paint(x, y, current_user + 1);
		
		unsigned int result = check_run();
		if (result == 1){
			printf("●胜\n");
			break;
		}
		else if (result == 2){
			printf("○胜\n");
			break;
		}
	}

	system("pause");
	return 0;
}