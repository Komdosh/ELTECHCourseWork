#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <windows.h>
#include <fstream>
#include "Classes.h"
#include <deque>
#define pause system("pause")
#define cls system("cls")

using namespace std;

//***********************************************************************
//���������� �����
inline void doLine()
  {
  for (int k = 0; k < 79; ++k)
    cout << "=";
  cout << endl;
  }
//***********************************************************************
//������� ����������
template<class T>
void quickSort(T* nodes, int N)
  {
  int i = 0, j = N;
  T temp, p;
  p = nodes[N >> 1];
  do
    {
    while (nodes[i].getDist() < p.getDist()) i++;
    while (nodes[j].getDist() > p.getDist()) j--;
    if (i <= j)
      {
      temp = nodes[i]; nodes[i] = nodes[j]; nodes[j] = temp;
      i++; j--;
      }
    }
    while (i <= j);
    if (j > 0) quickSort(nodes, j);
    if (N > i) quickSort(nodes + i, N - i);
  }
//***********************************************************************
//��������� �������
int menu();
int enterNum(int first, int last);
int onLoad();
//***********************************************************************
//�������-�����
int Graph::setMem()
  {
  nodes = new Node[size*size/2];
  return 0;
  }
//***********************************************************************
int Graph::makeGraph()
  {
  int exist;
  float tempfl;
  if (inp == 0 || inp == 1)
    {
    cout << "������� ���������� ������ (�� 2 �� " << maxEdge << "): ";
    size = enterNum(2, maxEdge);
    setMem();
    }
  char sym = 'a', tSym;
  if (!inp || inp == 1)
    {
    for (int i = 0; i<size; ++i)
      {
      tSym = sym;
      for (int j = i + 1; j<size; ++j)
        {
        ++tSym;
        if (!inp)
          {
          cout << "����� " << sym << '-' << tSym << " ����������?\n������� 1 ���� ����������, ����� 0: ";
          exist = enterNum(0, 1);
          if (exist)
            {
            cin.clear();
            cin.sync();
            cout << "��� ����� " << sym << '-' << tSym << " (�� -" << maxEdge - 1 << " �� " << maxEdge - 1 << "): ";
            do
              {
              if (tempfl<(-maxEdge) || tempfl>maxEdge)
                cout << "��� ����� ������ ���� � �������� �� -" << maxEdge - 1 << " �� " << maxEdge - 1 << ": ";
              cin >> tempfl;
              }
              while (tempfl<(-maxEdge) - 1 || tempfl>maxEdge - 1);
            }
          }
        else
          {
          exist = rand() % 4;
          if (exist)
            {
            tempfl = (float)(rand() % maxEdge);
            tempfl /= (rand() % maxEdge + 1);
            if ((rand() % 2) && tempfl>0)
              tempfl*=(-1);
            }
          }
        if (exist)
          {
          nodes[count].first = sym - 'a';
          nodes[count].second = tSym - 'a';
          nodes[count++].dist = tempfl;
          }
        }
      sym++;
      }
    }
  else
    {
        FILE* file;
        if (!(file = fopen("matr", "r")))
          return 1;         //����� �� ����������
        fseek(file, 0, SEEK_END);
        if (!ftell(file))
          return 2;         //���� ������
        rewind(file);
        fscanf(file, "%d", &size);
		exist=1;
        setMem();
        fgetc(file);
        for (int i = 0; i<size; ++i)
          {
          tSym = sym;
          for (int j = i + 1; j<size; ++j)
            {
            ++tSym;
            fscanf(file, "%f", &tempfl);
            nodes[count].first = sym - 'a';
            nodes[count].second = tSym - 'a';
            nodes[count++].dist = tempfl;
            fgetc(file);
            }
          sym++;
          }
        fclose(file);
    }
  
  return exist;
  }
//***********************************************************************
int Graph::showGraph()
  {
  cls;
  doLine();
  cout << "\t\t\t\tи��� � �� ����\n";
  doLine();
  for (int i = 0; i < count; ++i)
    {
    cout << (char) (nodes[i].first + 'a') << '-' << (char) (nodes[i].second + 'a') << ": " << nodes[i].dist << endl;
    }
  return 0;
  }
//***********************************************************************
int Graph::handle()
  {

  //tempList.erase( ++Iter );

  quickSort(nodes, count-1);
  	deque <Node> tempList;
  for (int i = 0; i < count; ++i)
    tempList.push_back(nodes[i]);
  deque <Node>::iterator Iter;
  showGraph();
  doLine();
  cout << "\t\t\t\t��� ������� ����������\n";
  doLine();
  if (prima)
    delete [] prima;
  countPrima = 0;
  prima = new Node[size];
  int tSize=1;
  int *visited = new int[size];
  for (int i = 0; i < size; ++i)
    visited[i] = -1;
  visited[0] = (*tempList.begin()).first;
  bool Ready[4], fin, FS;
  while (tSize != size)      //���� �� ��� ������� ����������
    {
	fin = false;
	for ( Iter = tempList.begin( ); Iter != tempList.end( ) && !fin; Iter++)
	  {
      Ready[0] = false;
      Ready[1] = true;
      Ready[2] = false;
      Ready[3] = true;
        for (int k = 0; visited[k] != -1 && !Ready[0] && Ready[1]; ++k)
		  {
			  if ((*Iter).first == visited[k])
            {
			for (int j = 0; visited[j] != -1 && Ready[1]; ++j)
				if ((*Iter).second == visited[j])
              Ready[1] = false;
            if (Ready[1])
              Ready[0] = true;
            }
          }
        for (int k = 0; visited[k] != -1 && !Ready[2] && Ready[3]; ++k)
		  {
			  if ((*Iter).second == visited[k])
            {
            for (int j = 0; visited[j] != -1 && Ready[3]; ++j)
				if ((*Iter).first == visited[j])
              Ready[3] = false;
            if (Ready[3])
              Ready[2] = true;
            }
          }
        fin = (Ready[0] && Ready[1]) || (Ready[2] && Ready[3]);
        if (fin)
          {
          FS = (Ready[0] && Ready[1]);
		  if (FS)
				visited[tSize++] = (*Iter).second;
		  else
			visited[tSize++] = (*Iter).first;
		  prima[countPrima] = (*Iter);
		  countPrima++;
		  Iter=tempList.begin();
		  }
		}
    }
  for (int i = 0; i < countPrima; ++i)
    {
    cout << (char) (prima[i].first + 'a') << '-' << (char) (prima[i].second + 'a') << ": " << prima[i].dist << endl;
    }
  return 0;
  }
//***********************************************************************
//�������� �������
int main()
  {
  srand(time(nullptr));
  setlocale(0, ".1251");
  onLoad();
  int iMenu;
  do
    {
    Graph graph(26);
    cls;
    switch (iMenu = menu())
      {
        case 1:
          graph.setInp(0);
          break;
        case 2:
          graph.setInp(1);
          break;
        case 3:
          graph.setInp(2);
          break;
        case 0:
          cls;
          cout << "�� ����� ������!" << endl;
          break;
        default:
          cout << "������ ������ �� ����������, ��������� ����!" << endl;
          pause;
      }
    if (iMenu>0 && iMenu<4)
      {
	  if(graph.makeGraph())
		graph.handle();
	  else
		cout<<"\nи��� �����������!\n";
      pause;
      }
    }
    while (iMenu);
    pause;
    return 0;
  }
//***********************************************************************
//�������
int menu()
  {
  int point;
  do
    {
    cin.clear();
    cin.sync();
    cout << "�������� ����� ����" << endl;
    cout << "1 - ������ ����" << endl;
    cout << "2 - ������������� ����" << endl;
    cout << "3 - ��������� ���� �� ����� matr" << endl;
    cout << "0 - �����" << endl;
    cout << ">";
    cin >> point;
    if (cin.fail())
      cout << "���-�� ����� �� ���, �������� ����� ���� ��������" << endl;
    }
    while (cin.fail());
    return point;
  }
//***********************************************************************
int enterNum(int first, int last)
  {
  int num;
  bool check_num, check_all;
  char str[5];
  const char numbers[] = "0123456789";
  do
    {
    check_all = true;
    check_num = false;
    scanf("%s", &str);
    fflush(stdin);
    for (int i = 0; str[i] != '\0' && check_all; ++i)
      {
      for (int j = 0; numbers[j] != '\0' && !check_num; ++j)
      if (str[i] == numbers[j] || str[i] == '\0')
        check_num = true;
      if (check_num)
        check_num = false;
      else
        check_all = false;
      }
    if (check_all)
      num = atoi(str);
    else
      printf("� ������ ������ ���-�� ����� �����, ��������� ����:\n");
    if ((num < first || num > last) && check_all)
      printf("������ ����� �� �������� ��� �����\n������� ����� �� %d �� %d\n��������� ����: ", first, last);
    }
    while (num < first || num > last || !check_all);
    return num;
  }
//*****************************************************************************************
//��������
int onLoad()
  {
  system("cls");
  puts("\t\t\t>>�������� �����<<");
  puts("\n\n ������ ��������� ������������� ��� ������������ ��������� �����.");
  puts(" �����������:");
  puts("   *���� ���� � ����������");
  puts("   *��������� �����");
  puts("   *������ ����� �� �����");
  puts("   *����� ������� ��������� �� �������� �����");
  puts("   *�����, ������������� ���������� �����, �����");
  system("pause");
  return 0;
  }
