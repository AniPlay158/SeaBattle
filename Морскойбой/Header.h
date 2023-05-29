
enum Color { Black, Green, Blue, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
// ����� �������� ����� ����������: ���� ������; ���� ������� ������

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //���������� ��������� ����


void setColor(Color text, Color background) //������� � ������� ������� ���������� ��������� ����� ������
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); //��������� ���������� ������
}
enum Napravlenie { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, escepushka = 27, BackSpace = 8, Q = 113 };
//�������, ���������� � ������� � ���� ����� ����� �� ���

void SetCursor(int x, int y) //������� ��� ���� ����� ������������� ������� ������� � ������� �� ��� � � Y
{
	COORD myCoords = { x,y }; //������������� ���������
	SetConsoleCursorPosition(hStdOut, myCoords); //������ ����������� ������� �� ������ ����������
}
struct Ships //��������� ������������� ���������
{
	int deck = { 0 }; //���������� �����
	bool horizontal = true; //��������� (���������� - ��������������)
	bool alive = true; //�������� �� ��, ��������� �� �������� ��� ���
	int x, y; //������� ��������� �� "x" � "y" (������ ������), ���������� ��� ����������� ����������� ���������
};
void explosion(Ships* characteristic, int ship_pos[12][24], int plus, int& end) //����������� ����������� � ����������� ���������� � ����
{
	int A = 0; //���������� ��� ���������� ��������� ������� ������ ����������� ���������
	int B = 13; //����������, ������� ����� �������� ��������� �� ������ ��������
	int C = 0; //����������, ������� ������ ���������� ������������ ���������� (���� = 10, �� ���� �����������)
	bool alive = false; //���������� � ������� ������� �� ����� ��������� ����������� ����������
	for (size_t n = 13; n > 3; n--) //��������� ��� ������� ���������� �� ������� �� � �������
	{
		for (size_t i = 1; i < 11; i++) //��������� ������ �� ��������
		{
			for (size_t r = 2; r < 22; r++) //��������� ������ �� ��������
			{
				if (ship_pos[i][r] == n) //���������, ���� �� � ������� ���� ���� ������� � ����������
				{
					alive = true; //� ������ ������ - �������� ���/�����
					i = 11; //������ �������� ����� ������� � ���������� �������
					break; //������� �� �����
				}
			}
		}
		if (alive == false) //���� ������� ������ �� ���, �� �������, ��� �������� �������� ��� �������� ���� ����� ���������
		{
			characteristic[B - n + plus].alive = false; //������� ��� ������ �������� ���������
		}
		else //�����
		{
			alive = false; //������ ������ ���������� �� "false", ����� ��������� ��������� ��������
		}
	}
	for (size_t i = plus; i < 10 + plus; i++) //��������� ����, � ������� ����� ��������� ��� ��������� ����� ������� �� �����������
	{
		if (i == 0 || i == 10) //��� 4-� ��������
		{
			A = 0; //������ �������� ���������� ��� ���������� ���������
		}
		else if (i == 1 || i == 2 || i == 11 || i == 12)  //��� 3-� ��������
		{
			A = 1; //������ �������� ���������� ��� ���������� ���������
		}
		else if (i > 2 && i < 6 || i > 12 && i < 16)  //��� 2-� ��������
		{
			A = 2; //������ �������� ���������� ��� ���������� ���������
		}
		else  //��� 1-� ��������
		{
			A = 3; //������ �������� ���������� ��� ���������� ���������
		}
		if (characteristic[i].alive == false) //���� ������ �������� ���������
		{
			if (characteristic[i].horizontal == true) //���� �� ����� �������������� ���������
			{
				for (size_t q = 0; q < 3; q++) //��������� ������������� ��� 3 ���� ��� ��� ��� ���������� ����������� �������� ����� ��� �� ������ �������� � ���� �����
				{
					for (size_t w = 0; w < characteristic[i].deck * 3 + A; w++) //��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� "�����������" ������������ ��������
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x - 4 + w] = 2; //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "2" (������)
					}
				}
				for (size_t g = 0; g < 2 * characteristic[i].deck; g++) //��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� �������� ������������ ��������
				{
					ship_pos[characteristic[i].y - 1][characteristic[i].x - 2 + g] = 3; //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "3" (���������)
				}
			}
			else if (characteristic[i].horizontal == false)  //���� �� ����� ������������ ���������
			{
				for (size_t q = 0; q < characteristic[i].deck + 2; q++) //��������� ������������� ��� 3 ���� ��� ��� ��� ���������� ����������� �������� ����� ��� �� ������ �������� � ���� �����
				{
					for (int w = -4; w < 2; w++)  //��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� "�����������" ������������ ��������
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x + w] = 2; //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "2" (������)
					}
				}
				for (int g = 0; g < characteristic[i].deck; g++) //��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� �������� ������������ ��������
				{
					for (int n = -2; n < 0; n++) //��������� ������������� ��� 2 ���� ��� ��� ��� ����� �������� �������� � ������� ��� 2-�� �������� (����� ������)
					{
						ship_pos[characteristic[i].y - 1 + g][characteristic[i].x + n] = 3; //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "3" (���������)
					}
				}
			}
			C++; // ����������� �������� �������� ������������ ���������� �� 1
		}
	}
	if (C == 10 && plus == 0) //���� ��� ���� ��������� ����������
	{
		end = 1; //��������� ���� (���������)
	}
	else if (C == 10 && plus == 10) //���� ��� ��������� ����� ����������
	{
		end = 2; //��������� ���� (������)
	}
	else //�����
	{
		C = 0; //���������� ������� ������������ ����������
	}
}
void LoadCharactShips(Ships* characteristic) //���������� ����� � ������������ � ������� ���������
{
	for (size_t i = 0; i < 20; i++) //��������� ������������� ��� 20 ��� ��� ��� ����� ���������� ���������� ����� 20
	{
		if (i == 0 || i == 10) //��� 4-� ��������
		{
			characteristic[i].deck = 4; //������ �������� � 4-�� ��������
		}
		else if (i > 0 && i <= 2 || i > 10 && i <= 12) //��� 3-� ��������
		{
			characteristic[i].deck = 3; //������ �������� � 3-�� ��������
		}
		else if (i > 2 && i <= 5 || i > 12 && i <= 15) //��� 2-� ��������
		{
			characteristic[i].deck = 2; //������ �������� � 2-�� ��������
		}
		else if (i > 5 && i <= 9 || i > 15 && i <= 19) ///��� 1-� ��������
		{
			characteristic[i].deck = 1; //������ �������� � 1-�� �������
		}
	}
}
void auto_arrangement(Ships* characteristic, int ship_pos[12][24], int plus) //a������������� ����������� ����������
{
	int y, x, ship = plus; //���������� ��� ��������� � ������ ��������� 
	while (ship < plus + 10) //��������� ������������� ��� �� ��� ��� ����, �� ����� ����������� ��� 10 ����������
	{
		characteristic[ship].horizontal = 0 + rand() % 2; //����������� ��������� ����������
		y = 2 + rand() % 9, x = (1 + rand() % 9) * 2; //����������� ��������� ���������� (� ������ ������� ����)
		if (characteristic[ship].horizontal == false && y + characteristic[ship].deck >= 13)
			//��������� ������� �� �������� ������� �� ��������� ��� ����������, ���� ��� �� ����������
		{
			y -= y + characteristic[ship].deck - 12; //���� ��, �� ������� ������� ��� ��������� ����� �� �� ������ ������ ������� ���� �� ���������
		}
		else if (characteristic[ship].horizontal == true && x + characteristic[ship].deck * 2 >= 24)
			//��������� ������� �� �������� ������� �� ��������� ��� ����������, ���� ��� �� ����������
		{
			x -= (x + characteristic[ship].deck * 2) - 22; //���� ��, �� ������� ������� ��� ��������� ����� �� �� ������ ������ ������� ���� �� ���������
		}
		if (characteristic[ship].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[ship].deck * 2 - 2] == 0)
			// ��������� ����� �� �������� �������������� ��������� � ��� �� ������ �� �������� ���� �� ����� ���������������
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y; //���������� ���������� ������ ������ � ������� ���������, ����� � ���������� ��������� �� ��������
			for (size_t q = 0; q < 3; q++) //��������� ������������� ��� 3 ���� ��� ��� ��� ���������� "�����������" �������� ����� ��� �� ������ �������� � ���� �����
			{
				for (size_t w = 1; w < characteristic[ship].deck * 3 + 1; w++)//��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� "�����������" ������������ ��������
				{
					ship_pos[y - 2 + q][x - 3 + w] = 1;  //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "1" (����������� ������� ������ ���������)
				}
			}
			for (int g = 0; g < 2 * characteristic[ship].deck; g++) //��������� ������������� ��� ������ ���������� ��� (��� ������� �������� �������), ����� �������� ������������ ��������
			{
				ship_pos[y - 1][x + g] = 13 - ship + plus;  //������ �������� ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "4-13" (������ ���������� (� ������� ����))
			}
			ship++; //��������� � ���������� ���������
		}
		if (characteristic[ship].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[ship].deck - 2][x] == 0)
			// ��������� ����� �� �������� �������������� ��������� � ��� �� ������ �� �������� ���� �� ����� ���������������
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y;//���������� ���������� ������ ������ � ������� ���������, ����� � ���������� ��������� �� ��������
			for (size_t q = 0; q < characteristic[ship].deck + 2; q++)
			{
				for (size_t w = 0; w < 6; w++)
				{
					ship_pos[y - 2 + q][x - 2 + w] = 1; //������ �������� "�����������" ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "1" (����������� ������� ������ ���������)
				}
			}
			for (int g = 0; g < characteristic[ship].deck; g++)
			{
				for (int n = 0; n < 2; n++) //��������� ������������� ��� 2 ���� ��� ��� ��� ����� �������� �������� � ������� ��� 2-�� �������� (����� ������)
				{
					ship_pos[y - 1 + g][x + n] = 13 - ship + plus; //������ �������� ������� � ��������� ������� ������� ����� �������� �� ��������� �������, �� "4-13" (������ ���������� (� ������� ����))
				}
			}
			ship++; //��������� � ���������� ���������
		}
	}
}
void PaintPos(int mas[12][24], int x, int num_color) //���������� ������� ����� � ����������� � ���������� ������������ ����������
{
	for (size_t i = 1; i < 11; i++) //��������� ������������� ��� 10 ��� ��� ��� ����� ���������� ����� ����� 10
	{
		int y = 1 + i; //�������������� ���������� �� ��������� 2 �� � � 2 �� Y ��� ��� ��������� ���� ������ ���������� ���
		SetCursor(x, y); //���������� ������ �� ������������� �������

		for (size_t g = 2; g < 22; g++)  //��������� ������������� ��� 20 ��� ��� ��� ����� ���������� �������� ����� 20
		{
			if (mas[i][g] == 2) //���� � ������� �� ���� ����� ��������� "2"
			{
				setColor(LightGray, LightGray); //������ ����� ��������
			}
			else if (mas[i][g] == 3) //���� � ������� �� ���� ����� ��������� "3"
			{
				setColor(LightMagenta, LightMagenta); //������ �������� ����������� �����
			}
			else if (mas[i][g] >= 4) //���� � ������� �� ���� ����� ��������� "4+"
			{
				setColor(Color(num_color), Color(num_color)); //������������� ���� ���������� (���� - ������ / ����� - �����)
			}
			else //� ���� ������� ������ ����� ��������
			{
				setColor(White, White); //������������� ����� ���� ��� ��� ����� ������ ����� ������� ������� �� ������� ����� ����������� �������� ��������
			}
			cout << "+"; //������ ����� ����, ��-�� ������� �� ����� �����������
		}
		cout << "\n"; //������� �� ����� ������ ��� ��������� ����� ������ ���������
	}
}
void Avake() //������� ������� ����� �������� ������ ����� ������
{
	setColor(White, Black); //������������� ���� ������ (����� �� ������)
	SetCursor(28, 7); //������������� ������� ������� (�� ��� �����������)
	cout << "������� ���"; //������� ������� �� �����
}
void CreatField(int speed, int X, int num_color) //������� ��������� ������� ����� �������������� ������� ����
{
	SetCursor(X, 1); //������������� ������ �� ������ �������
	char mas[10] = { '�','�','�','�','�','�','�','�','�','�' }; //������� ������� ����� ��������� ������ �������� ���� � ������������� ������ ���� �� ����
	setColor(White, Color(num_color)); //����� ����� (����� - �����; ������� - �������/�������)
	int A = 0, B = 0; //���������� ����������� ��� ���������� ��������� �������� ����
	cout << "  " << mas[0]; //� ������� ����� �������� ����� "�" � ������ � ������ ������ ����� ���� ��������� � �������
	for (size_t i = 0; i < 12; i++) //��������� ������������� ��� 12 ��� ��� ��� ����� ���������� ����� ����� 12
	{
		if (B == 0) //���������� ��������, ������� ��������� ���� ���
		{
			SetCursor(X + 3, 1 + i); //������������� ������ �� ������ �������
			B++; //����������� �������� ����������
		}
		else //�����
		{
			SetCursor(X, 1 + i);  //������������� ������ �� ������ �������
		}
		for (size_t g = 0; g < 23; g++) //��������� ������������� ��� 23 ��� ��� ��� ����� ���������� �������� ����� 23
		{
			if (i == 0 && g == 22) //��������� ������������� ���, ���� �� �� ������ ������, � 22 ��������
			{
				setColor(Color(num_color), Color(num_color)); //������ ���� ������ � ������� �� �������/������� (������� ���� �� ������� ���� ���� �� ����)
			
				cout << '+'; //������ ����� ����, ��-�� ������� �� ����� �����������
			}
			if (i == 0 && g > 0 && g < 10) //��������� ������������� ���, ���� �� �� ������ ������, � � ��������� � 0-�� �� 10-�� �������
			{
				setColor(White, Color(num_color)); //����� ����� (����� - �����; ������� - �������/�������)
				cout << " " << mas[g]; //����� ������, � ����� ������� ����� �� ����� �������� ����� �������� ����� �������� "g"
			}
			else if (i > 0 && i < 11 && g == 0) //����� ���� �� ��������� � 0-�� �� 11-�� ������ �� 0-� ��������
			{
				setColor(White, Color(num_color)); //����� ����� (����� - �����; ������� - �������/�������)
				if (i < 10) //���� �� ��������� �� ������� �� ����������� �������� "10"
				{
					cout << i << ' '; //����� ����� ����������� �� ����� ������ ������� ����� �������� ������ ��������������� ���� �� �������� () ��� ���� ����� ���� ����� �� ����������� � ����������� �������
				}
				else //�����
				{
					cout << i; //����� ����� ��� �������� ��� ��� ��� ��� �� ����� ����� ���� ����� ������� ����� ���������� "10"
				}
			}
			else if (i == 11 || g > 20 && g < 23) //����� ���� �� ��������� �� 11-�� ������, �� 21-22-�� ���������
			{
				if (A == 0 && i == 11) //�������� �� ��������� ������ ������� ����� ����� ��������� ����� ������� �� ��������� ��������������
				{
					cout << "+";//������ ����� ����, ��-�� ������� �� ����� �����������
					A++; //������ �������� ���������� ��������� ������� ���� ����� ����������� ��������� ������� ������
				}
				setColor(Color(num_color), Color(num_color)); //������ ���� ������ � ������� �� �������/������� (������� ���� �� ������� ���� ���� �� ����)
				cout << '+'; //������ ����� ����, ��-�� ������� �� ����� �����������
			}
			else if (i > 0) //���� �� ��������� �� ������ ����� ������� �� ����� "0" (��������������� ������� ����)
			{
				setColor(White, White); //������ ���� ������ � ������� �� ����� (��������������� ������� ����)
				cout << '+'; //������ ����� ����, ��-�� ������� �� ����� �����������
			}
		}
	}
	setColor(Black, Black); //������������� ��������� ������ ����
}
void Paint(char variant[2][30], int T) //���� ������ ����������� 
{
	system("cls"); //������� �������
	for (size_t i = 0; i < 2; i++) //������ ���� ��� 2-�� ���������
	{
		SetCursor(30, 6 + i); //������������� ������ �� ������ �������
		for (size_t p = 0; p < 30; p++) //������ ���� ��� ���� 30-�� ������� 
		{
			if (i == T) //�������� �� ��������� �����
			{
				setColor(Black, White); //�������� ��������� �����
			}
			else //�����
			{
				setColor(White, Black); //������� ��������� ���������� ������
			}
			cout << variant[i][p]; //������� ������ � ���� ������
		}
	}
	setColor(Black, Black); //������������� ��������� ������ ����
}
void Meny(int num)
{
	char variant[11][40] = { "���� ������ ���� �������...","���� ��������!", "���� �����!", "���� �������... �� ������...", "���� ���." , "�� ��������...", "�� �����!", "�� �������, ����������!", "+++++++++++++++++++++++++++++++++++++++", "�� �����, ���� �����!", "���, �� ��������� ��������� ��������!" };
	//������ ��������� ������ ������� ����� ��������� �� ����� ����
	SetCursor(22, 15); //������������� ������ �� ������ �������
	setColor(Black, Black); //������������� ��������� ������ ����
	for (size_t i = 0; i < 25; i++) //���� ��� �������� ����������� ������
	{
		cout << variant[10][i]; //������� "+"
		cout << variant[10][i]; //������� "+"
	}
	SetCursor(22, 15); //������������� ������ �� ������ �������
	if (num > 0 && num < 4) //���������, ���� ������� ������ ��������� � �����
	{
		setColor(Red, Black); //������������� ������� ���� ������ �� ������ ���� 
	}
	else //����� ������� ������ ��������� �� ���
	{
		setColor(Blue, Black); //������������� ������� ���� ������ �� ������ ���� 
	}
	for (size_t i = 0; i < 30; i++) //������ ���� ��� ���� 30-�� ������� 
	{
		cout << variant[num][i];  //������� ������� � ���� ������
	}
}