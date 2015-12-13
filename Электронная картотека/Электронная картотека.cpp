#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <windows.h>

typedef struct stWood
  {
  char* Neck;                                               //������ �����
  char* Deck;                                               //������ �������
  } WOOD;

typedef struct stGuitars
  {
  char* Name;                                               //�������� ������
  int Strings;                                              //���-�� �����
  int Year;                                                 //��� ������������
  WOOD Wood;                                                //������
  } GUITARS;

typedef struct stList
  {
  GUITARS Guitars;                                          //��������� � ��������������� ������
  struct stList *next;                                      //��������� �������
  struct stList *prev;                                      //���������� �������
  } sLIST;

typedef sLIST* LIST;                                        //��������� �� ������� ������

//------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------��������� �������----------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------//
int onLoad();                                                 //��������
int help();                                                   //�������
int menus(int Key);                                           //����� ����
int chooseList();                                             //����� ������
int messages(int Key);                                        //����� ���������
int enterMenu(LIST* list);                                    //������� ����� ���������
LIST addNth(LIST list, LIST temp, int n);                     //���������� n-�� ��������
int editMenu(LIST* list);                                     //������� �������������� ���������
LIST enterField();                                            //���� �������������� �����
char* enterWord();                                            //���� ����� �� 10 ��������
int enterNum(int first, int last);                            //���� ������������� �������� � ���������
int deleteMenu(LIST* list);                                   //������� �������� ���������
int del(LIST *list, int Key, int n);                          //�������� n-�� ��������
int sortMenu(LIST *list);                                     //������� ����������
LIST sort(LIST list, int Key);                                //����������
LIST searchMenu(LIST list);                                   //������� ������
LIST search(LIST list, int Key, int num, char* str);          //�����
char* fileName(int Key);                                      //���� ����� �����
int recordFile(LIST list, const char* name);                  //������ � ����
int readFile(LIST *list, const char* name);                   //������ �����
int outputMenu(LIST list);                                    //������� ������
int outputList(LIST list, int Key);                           //����� ������
LIST getElem(LIST list, int Key, int n);                      //���������� ���������
int count(LIST list);                                         //������� ���������� ���������
//------------------------------------------------------------------------------------------------------------------------//

int main()
  {
  system("mode con cols=80 lines=20");
  system("color 2");
  LIST list = NULL, newList = NULL, *tempList=NULL;
  int Q;
  system("chcp 1251");
  onLoad();
  do
    {
    switch (Q = menus(0))
      {
        case 0:
          help();
          break;
        case 1:
          enterMenu(&list);
          break;
        case 2:
          if (editMenu(&list))
            messages(9);
          break;
        case 3:
          if(deleteMenu(&list))
            messages(9);
          break;
        case 4:
          if (!list)
            {
            messages(9);
            break;
            }
          switch (chooseList())
            {
              case 1:
                outputMenu(list);
                break;
              case 2:
                outputMenu(newList);
                break;
              case 3:
                break;
            }
          break;
        case 5:
          del(&newList, 1, 0);
          newList = searchMenu(list);
          break;
        case 6:
          if (!list)
            {
            messages(9);
            break;
            }
          switch (chooseList())
            {
              case 1:
                tempList = &list;
                break;
              case 2:
                tempList = &newList;
                break;
            }
          if (tempList != NULL)
            {
            switch (sortMenu(tempList))
              {
                case 0:
                  messages(4);
                  break;
                case 1:
                  messages(9);
                  break;
                case 2:
                  break;
              }
            tempList = NULL;
            }
          break;
        case 7:
          messages(8);
          break;
      }
    }
    while (Q != 7);
    del(&list, 3, 0);
    del(&newList, 3, 0);
    return 0;
  }
//*****************************************************************************************
//������� �������
int onLoad()
  {
  system("cls");
  puts("\t\t\t>>����������� ��������� �����<<");
  puts("\t\t\t\t     _");
  puts("\t\t\t\t    / 7");
  puts("\t\t\t\t   /_(");
  puts("\t\t\t\t   |_|");
  puts("\t\t\t\t   |_|");
  puts("\t\t\t\t   |_|");
  puts("\t\t\t\t   |_| /\\");
  puts("\t\t\t\t /\\|=|/ /");
  puts("\t\t\t\t \\ |_| /");
  puts("\t\t\t\t  ) _  \\");
  puts("\t\t\t\t / |_|  \\");
  puts("\t\t\t\t/  -=-o /");
  puts("\t\t\t\t\\  /~\\_/");
  puts("\t\t\t\t \\/\n\n");
  Beep(657, 250);
  Beep(327, 150);
  Beep(327, 150);
  Beep(657, 250);
  Beep(619, 250);
  Beep(657, 250);
  Beep(520, 250);
  Beep(327, 150);
  Beep(327, 150);
  Beep(657, 250);
  Beep(619, 250);
  Beep(657, 250);
  Beep(491, 250);
  Beep(327, 150);
  Beep(327, 150);
  Beep(657, 250);
  Beep(619, 250);
  Beep(657, 250);
  Beep(739, 250);
  Beep(327, 150);
  Beep(327, 150);
  Beep(739, 250);
  Beep(657, 250);
  Beep(739, 250);
  Beep(784, 250);
  Beep(327, 150);
  Beep(327, 150);
  system("cls");
  puts("\n\n\t\t\t\t����������� ���������");
  puts("\n\n ������ ��������� ������������� ��� �������� ��������� � ������ � ���.");
  puts(" �����������:");
  puts("   *�������� ��������� � ����������� � �������");
  puts("   *���������� �������� � ���������");
  puts("   *�������������� ��������");
  puts("   *���������� ��������� � ����");
  puts("   *������ ��������� �� �����");
  puts("   *�������� �������� ���/� ������");
  puts("   *����� �� ��������� �� ���������� ��������� (������������ �������)");
  puts("   *���������� ��������� �� ���������� ���������");
  puts("   *����� ��������� �� �����\n\n");
  system("pause");
  return 0;
  }
//*****************************************************************************************
//������� �������
int help()
  {
  int Q;
  do
    {
  system("cls");
  puts("\n\n\t\t\t\t����������� ���������");
  puts("================================================================================");
  puts("0 - �����������");
  puts("1 - ��� ��������� ��������?");
  puts("2 - ��� ������������� ��������?");
  puts("3 - ��� ������� ��������?");
  puts("4 - ��� ���������� ��������?");
  puts("5 - ��� ����� ��������?");
  puts("6 - ��� ������������� ��������?");
  puts("7 - ��������� � ������� ����");
  printf("������� ����� ���� - ");
    switch (Q = enterNum(0, 7))
      {
        case 0:
          system("cls");
          puts(" �����������:");
          puts("   *�������� ��������� � ����������� � �������");
          puts("   *���������� �������� � ���������");
          puts("   *�������������� ��������");
          puts("   *���������� ��������� � ����");
          puts("   *������ ��������� �� �����");
          puts("   *�������� �������� ���/� ������");
          puts("   *����� �� ��������� �� ���������� ��������� (������������ �������)");
          puts("   *���������� ��������� �� ���������� ���������");
          puts("   *����� ��������� �� �����\n\n");
          break;
        case 1:
          system("cls");
          puts("� ��� ����� � ������� ���������� �������� ���������� ������� 1-�� ����� ����.");
          puts("- ��� ���������� �������� �� ��������������� �������, �������� ��������� ����� ������� � �������� ���������� �����.");
          puts("- ��� ���������� ��������� �� ����� ����������� �� ������ �����, �������� 4 - �� ����� �������.");
          puts("- ��� �������� � ������� ���� ���������� ������� 5 - �� ����� �������.");
          break;
        case 2:
          system("cls");
          puts("� ��� ����� � ������� �������� �������� ���������� ������� 2-�� ����� ����.");
          puts("- ��� ���� ����� ���������� ��� ����� ������� ��������� �������� �������� 1 - �� ����� �������.");
          puts("- ��� ��������� ���������������� ��������������� ���� n - �� �������� �������� ��������� ����� ���� � �������� ���������� �����.");
          puts("- ��� �������� � ������� ���� �������� 7 - �� ����� ����.");
          break;
        case 3:
          system("cls");
          puts("� ��� ����� � ������� �������� �������� ���������� ������� 3-�� ����� ����.");
          puts("- ��� �������� �������� �� ��������������� �������, �������� ��������� ����� �������.");
          puts("- ��� �������� ���� ���������, �������� 4 - �� �������.");
          puts("- ��� �������� � ������� ���� �������� 5 - �� ����� �������.");
          break;
        case 4:
          system("cls");
          puts("� ��� ����� � ������� ������ �������� ������ ���������� ������� 4-�� ����� ����.");
          puts("- ��������� ��������� �������, ��� ����� ��������� ��������� �����, ������� �1� ��� ������ �������� ��� �2� ��� ������ ��������������.");
          puts("- ��� ������ ��������� ��������� �� ����� �������� 1 - �� ����� �������.");
          puts("- ��� ���������� ��������� � ���� �������� 2 - �� ����� ������� � �������� ����������.");
          puts("- ��� �������� � ������� ���� �������� 3 - �� ����� �������.");
          break;
        case 5:
          system("cls");
          puts("� ��� ����� � ������� ������ �������� ���������� ������� 5-�� ����� ����.");
          puts("- ��� ������ �������� �� ���������, �������� ��������� ����� ������� � �������� ����������.");
          puts("- ��� �������� � ������� ���� �������� 6 - �� ����� �������.");
          break;
        case 6:
          system("cls");
          puts("� ��� ����� � ������� ���������� ��������� ���������� ������� 6-�� ����� ����.");
          puts("- ��������� ��������� �������, ��� ����� ��������� ��������� �����, ������� �1� ��� ������ �������� ��� �2� ��� ������ ��������������.");
          puts("- ��� ���������� ��������� �� ���������, �������� ��������� ����� �������.");
          puts("- ��� �������� � ������� ���� �������� 6 - �� ����� �������.");
          break;
        case 7:
          return 0;
          break;
      }
     puts("\n\n���� �������� �������� �����������, ����������, �� ����������� �����:");
     puts(" komdosh@gelezo2.ru\n");
     system("pause");
    }
  while (Q != 7);
  return 0;
  }
//*****************************************************************************************
//������� ����
int menus(int Key)
  {
  system("cls");
  int first=0, last=0;
  switch (Key)
    {
      case 0:
        puts("������� ����");
        puts("0 - �������");
        puts("1 - ���������� �������� � �������");
        puts("2 - �������������� ��������");
        puts("3 - �������� ��������");
        puts("4 - ����� ���������");
        puts("5 - ����� �������� �� ���������");
        puts("6 - ���������� �������� �� ���������");
        puts("7 - �����");
        first = 0;
        last = 7;
        break;
      case 1:
        puts("���� ���������� ��������");
        puts("1 - �������� �������� � ������ ������");
        puts("2 - �������� �������� � ����� ������");
        puts("3 - �������� �������� �� ��������� �������");
        puts("4 - ��������� ��������� � �����");
        puts("5 - ��������� � ������� ����");
        first = 1;
        last = 5;
        break;
      case 2:
        puts("���� �������� ��������");
        puts("1 - ������� ������ �������� � ���������");
        puts("2 - ������� ��������� �������� � ���������");
        puts("3 - ������� �������� �� � �������");
        puts("4 - ������� ��� ���������");
        puts("5 - �������� � ������� ����");
        first = 1;
        last = 5;
        break;
      case 3:
        puts("���� ����������");
        puts("�� ������ ������ ��������� ����������?");
        puts("1 - ��������");
        puts("2 - ���������� �����");
        puts("3 - ��� ������������");
        puts("4 - ������ �����");
        puts("5 - ������ �������");
        puts("6 - ��������� � ������� ����");
        first = 1;
        last = 6;
        break;
      case 4:
        puts("���� ������");
        puts("�� ������ ������ ������� �������?");
        puts("1 - ��������");
        puts("2 - ���������� �����");
        puts("3 - ��� ������������");
        puts("4 - ������ �����");
        puts("5 - ������ �������");
        puts("6 - ��������� � ������� ����");
        first = 1;
        last = 6;
        break;
      case 5:
        puts("���� ������ ���������");
        puts("1 - ������� ��������� �� �����");
        puts("2 - ��������� ��������� � ����");
        puts("3 - ��������� � ������� ����");
        first = 1;
        last = 3;
        break;
      case 6:
        puts("���� �������������� ��������");
        puts("1 - ������� ��������� �� �����");
        puts("2 - �������� ����� n-�� ��������");
        puts("3 - �������� ���������� ����� n-�� ��������");
        puts("4 - �������� ��� ������������ n-�� ��������");
        puts("5 - �������� ������ ����� n-�� ��������");
        puts("6 - �������� ������ ������� n-�� ��������");
        puts("7 - ��������� � ������� ����");
        first = 1;
        last = 7;
        break;
    }
  printf("������� ����� ������ - ");
  return enterNum(first, last);
  }
//*****************************************************************************************
//������� ������ ������
int chooseList()
  {
  system("cls");
  puts("��� ����� ��������� ��������� ��� ��������?");
  puts("1 - ��������");
  puts("2 - ��������������");
  puts("3 - ��������� � ������ ����");
  printf("������� ����� ������ (�� %d �� %d): ", 1, 3);
  return enterNum(1, 3);
  }
//*****************************************************************************************
//������� ������ ��������� ������������
int messages(int Key)
  {
  system("cls");
  switch (Key)
    {
      case 3:
        puts("��������� �������");
        break;
      case 4:
        puts("���������� ������� ���������");
        puts("��� ��������� �������� ����� '����� ������'");
        break;
      case 5:
        puts("������� �� ������ ������� ������������");
        puts("��� ��������� �������� ����� '�����' -> '��������������'");
        break;
      case 6:
        puts("������� �� ������ �� ���� ������������");
        puts("� �������� ������ �� ������� ����� �����������");
        break;
      case 8:
        puts("�� ����� ������!");
        break;
      case 9:
        puts("��������� �����");
        puts("��� ���������� ����� ��������, �������� ���������, ������ 1 ����� ����");
        break;
      case 10:
        puts("������� ������� �����");
        break;
      case 11:
        puts("������� ������� ��������");
        puts("��� ��������� �������� ����� '�����' -> '��������'");
        break;
      case 12:
        puts("��� ���� ����� �������� ������� �� �������, ���������� ������� ��� �������\n2-� ���������");
        break;
      case 13:
        puts("��� ���� ����� ������� ������� �� �������, ���������� ������� ��� �������\n2-� ���������");
        break;
      case 14:
        puts("��������� ������� �������� � ����");
        break;
      case 15:
        puts("��������� ������� ������� � ����� � ��������� � ��������");
        break;
      case 17:
        puts("����� � ����� ������ �� ����������");
        puts("�������� ��� �����!");
        break;
      case 18:
        puts("��������� �� ��������. �������� �������� � ������, ���������� � ������������.");
        puts("Komdosh@gelezo2.ru");
        puts("� ���� ������� '�������� �������� � ����������� ����������'.");
        puts("� ���� ������ �������, ��� ��������� ������ ������, � ����������� �������");
        puts("�������� ����� ��������.");
        break;
      case 19:
        puts("���� ������");
        break;
      case 20:
        puts("���� ������� ��������");
        break;
      case 777:
        puts("�������� �������� ������. ����������, �������� ������������ �� ����������� �����:");
        puts("Komdosh@gelezo2.ru");
        puts("� ���� ������� '�������� �������� � ����������� ����������'.");
        puts("� ���� ������ �������, ��� ��������� ������ ������, � ����������� �������");
        puts("�������� ����� ��������.");
        break;
    }
  system("pause");
  return 0;
  }
//*****************************************************************************************
//������� ������� ���������� ���������
int enterMenu(LIST* list)
  {
  LIST temp;
  int Q;
  do
    {
    switch (Q = menus(1))
      {
        case 1:
          temp = enterField();
          *list = addNth(*list, temp, 0);
          messages(11);
          break;
        case 2:
          if (*list)
            {
            temp = enterField();
            *list = addNth(*list, temp, count(*list));
            messages(11);
            }
          else
            messages(9);
          break;
        case 3:
          if (*list)
            if (count(*list)>1)
              {
              temp = enterField();
              printf("������� ����� �������, ���� �������� �������� (�� %d �� %d): ", 2, (count(*list)>2) ? count(*list) - 1 : count(*list));
              *list = addNth(*list, temp, enterNum(2, count(*list)) - 1);
              messages(11);
              }
            else
              messages(12);
          else
            messages(9);
          break;
        case 4:
          switch (readFile(list, fileName(2)))
            {
              case 0:
                messages(15);
                break;
              case 1:
                messages(17);
                break;
              case 2:
                messages(19);
                break;
            }
          break;
      }
    }
   while (Q != 5);
   return 0;
  }
//*****************************************************************************************
//������� ���������� n-��
LIST addNth(LIST list, LIST temp, int n)
  {
  if (!n)
    {
    if (list)
      list->prev = temp;
    temp->next = list;
    temp->prev = NULL;
    return temp;
    }
  else
    {
    list = getElem(list, 2, n);
    if (list->next)
      {
      temp->next = list->next;
      temp->prev = list;
      list->next->prev = temp;
      }
    else
      {
      temp->next = NULL;
      temp->prev = list;
      }
    list->next = temp;
    return getElem(list, 0, 0);
    }
  }
//*****************************************************************************************
//������� ������� �������������� ���������
int editMenu(LIST *list)
  {
  if (!*list)
    return 1;
  int Q;
    do
      {
      Q = menus(6);
      if (Q == 1)
        outputList(*list, 0);
      else
        {
        if (Q != 7)
          {
          printf("������� ����� �������� n - ");
          *list = getElem(*list, 2, enterNum(1, count(*list)));
          }
        }
      switch (Q)
        {
          case 2:
            printf("������� ����� ������ (���-�� �������� �� 1 �� 10): ");
            (*list)->Guitars.Name = enterWord();
            break;
          case 3:
            printf("������� ���������� ����� (�� %d �� %d): ", 1, 20);
            (*list)->Guitars.Strings = enterNum(1, 20);
            break;
          case 4:
            printf("������� ��� ������������ (�� %d �� %d): ", 1899, 2015);
            (*list)->Guitars.Year = enterNum(1899, 2015);
            break;
          case 5:
            printf("������� �������� ������ ����� (���-�� �������� �� 1 �� 10): ");
            (*list)->Guitars.Wood.Neck = enterWord();
            break;
          case 6:
            printf("������� �������� ������ ������� (���-�� �������� �� 1 �� 10): ");
            (*list)->Guitars.Wood.Deck = enterWord();
            break;
        }
      if (Q != 7)
        messages(20);
      *list = getElem(*list, 0, 0);
      }
      while (Q != 7);
  return 0;
  }
//*****************************************************************************************
//������� ����� ������ � ����
LIST enterField()
  {
  system("cls");
  LIST list = (LIST) malloc(sizeof(sLIST));
  printf("================================================================================");
  printf("������� ����� ������\nK��������� �������� �� 1 �� 10, � ������ �� ����� ���� ��������\n�����:");
  list->Guitars.Name = enterWord(); 
  printf("================================================================================");
  printf("������� ���������� ����� (�� %d �� %d): ", 1, 20);
  list->Guitars.Strings = enterNum(1, 20);
  printf("================================================================================");
  printf("������� ��� ������������ (�� %d �� %d): ", 1899, 2015);
  list->Guitars.Year = enterNum(1899, 2015);
  printf("================================================================================");
  printf("������� �������� ������ �����\nK��������� �������� �� 1 �� 10, � ������ �� ����� ���� ��������\n������ �����:");
  list->Guitars.Wood.Neck = enterWord();
  printf("================================================================================");
  printf("������� �������� ������ �������\nK��������� �������� �� 1 �� 10, � ������ �� ����� ���� ��������\n������ �������:");
  list->Guitars.Wood.Deck = enterWord();
  return list;
  }
//*****************************************************************************************
//������� ����� �����
char* enterWord()
  {
    char str[11], *temp;
    unsigned int i;
    do
    {
    gets(str);
    fflush(stdin);
    for (i = 0; i < strlen(str) && str[i] != ' '; i++);
    i = (i == strlen(str))?0:1;
    if (strlen(str)<1 || strlen(str)>10 || i)
      printf("�������� �� �������� ��� �����?\n���������� �������� �� 1 �� 10, � ������ �� ����� ���� ��������\n��������� ����: ");
    }
    while (strlen(str)<1 || strlen(str)>10 || i);
    temp = (char*) malloc(strlen(str)*sizeof(char));
    strcpy(temp, str);
    return temp;
  }
//*****************************************************************************************
//������� ����� ������������� ���������� � ���������
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
    for (int i = 0; str[i] != '\0' && check_all; i++)
      {
      for (int j = 0; numbers[j] != '\0' && !check_num; j++)
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
      printf("�������� �� �������� ��� �����?\n������� ����� �� %d �� %d\n��������� ����: ", first, last);
    }
    while (num < first || num > last || !check_all);
    return num;
  }
//*****************************************************************************************
//������� ������� �������� ���������
int deleteMenu(LIST* list)
  {
   int Q;
   if (!*list)
       return 1;
   do
      {
      switch (Q = menus(2))
        {
          case 1:
            if (!del(list, 0, 0))
              messages(10);
            else
              messages(9);
            break;
          case 2:
            if (!del(list, 1, 0))
              messages(10);
            else
              messages(9);
            break;
          case 3:
            if (count(*list) > 1)
              {
              printf("������� ����� ������� ��������, ������� ������� ������� (�� %d �� %d): ", 2, (count(*list) > 2) ? count(*list) - 1 : count(*list));
              if (!del(list, 2, enterNum(2, count(*list))))
                messages(10);
              else
                messages(9);
              }
            else
              messages(13);
            break;
          case 4:
            if (!del(list, 3, 0))
              messages(3);
            else
              messages(9);
            break;
        }
      }
   while (Q != 5);
   return 0;
  }
//*****************************************************************************************
//������� �������� n-�� �������� � ������
int del(LIST *list, int Key, int n) //Key: 0 - ������, 1 - �����, 2 - �-��, 3 - ���� ������
  {
  if (!*list)
    return 1;
  LIST temp;
  switch (Key)
    {
      case 0:
        if ((*list)->next)
          {
          free((*list)->Guitars.Name);
          free((*list)->Guitars.Wood.Deck);
          free((*list)->Guitars.Wood.Neck);
          *list = (*list)->next;
          free((*list)->prev);
          (*list)->prev = NULL;
          }
        else
          {
          free((*list)->Guitars.Name);
          free((*list)->Guitars.Wood.Deck);
          free((*list)->Guitars.Wood.Neck);
          free(*list);
          *list = NULL;
          }
        return 0;
        break;
      case 1:
        temp = getElem(*list, 1, 0);
        if (!temp->prev)
          *list = NULL;
        else
          temp->prev->next = NULL;
        free(temp->Guitars.Name);
        free(temp->Guitars.Wood.Deck);
        free(temp->Guitars.Wood.Neck);
        free(temp);
        return 0;
        break;
      case 2:
        temp = getElem(*list, 2, n);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp->Guitars.Name);
        free(temp->Guitars.Wood.Deck);
        free(temp->Guitars.Wood.Neck);
        free(temp);
        return 0;
        break;
      case 3:
        for (; (*list)->next; (*list) = (*list)->next, free((*list)->prev->Guitars.Name),
             free((*list)->prev->Guitars.Wood.Deck), free((*list)->prev->Guitars.Wood.Neck),
             free((*list)->prev));
        free((*list)->Guitars.Name);
        free((*list)->Guitars.Wood.Deck);
        free((*list)->Guitars.Wood.Neck);
        free(*list);
        (*list) = NULL;
        return 0;
        break;
    }
  return 0;
  }
//*****************************************************************************************
//������� ������� ����������
int sortMenu(LIST *list)
  {
  if (!*list)
    return 1;
  int Q = menus(3);
  if (Q == 6)
    return 2;
  else
    *list = sort(*list, Q);
  return 0;
  }
//*****************************************************************************************
//������� ���������� ������
LIST sort(LIST list, int Key)
  {
  LIST temp, sort = NULL, pFwd, pBwd;
  bool check = true;
  while (list)
    {
    temp = list;
    list = list->next;
    for (pFwd = sort, pBwd = NULL; pFwd && (Key == 1 && strcmp(pFwd->Guitars.Name, temp->Guitars.Name)>0 || Key == 2 && temp->Guitars.Strings > pFwd->Guitars.Strings ||
      Key == 3 && temp->Guitars.Year > pFwd->Guitars.Year || Key == 4 && strcmp(pFwd->Guitars.Wood.Neck, temp->Guitars.Wood.Neck)>0 ||
      Key == 5 && strcmp(pFwd->Guitars.Wood.Deck, temp->Guitars.Wood.Deck)>0); pBwd = pFwd, pFwd = pFwd->next);
    if (!pBwd)
      {
      temp->next = sort;
      sort = temp;
      sort->prev = NULL;
      check = false;
      }
    else
      {
      temp->next = pFwd;
      pBwd->next = temp;
      }
    }
  if (check)
    return getElem(list, 0, 0);
  for (list = sort, sort = sort->next; sort->next; sort->prev = list, list = list->next, sort = sort->next);
  return getElem(sort, 0, 0);
  }
//*****************************************************************************************
//������� ������� ���������
LIST searchMenu(LIST list)
  {
  if (!list)
    {
    messages(9);
    return NULL;
    }
  LIST New_list = NULL;
  const char* str = NULL;
  char* tempstr = NULL;
  int Q, temp=0, first=0, last=0;
  system("cls");
  switch (Q = menus(4))
    {
      case 1:
        str = "��������";
        break;
      case 2: 
        first = 1;
        last = 20;
        str = "�� ������ ���������� �����";
        break;
      case 3:
        first = 1899;
        last = 2015;
        str = "�� ������ ���� ������������";
        break;
      case 4:
        str = "������ �����";
        break;
      case 5:
        str = "������ �������";
        break;
    }
  if (Q == 2 || Q == 3)
    {
    printf("������� %s �������� ���������� (�� %d �� %d): ", str, first, last);
    temp = enterNum(first, last);
    }
  else
    {
    if (Q != 6)
      {
      printf("������� �� ������ %s �������� ���������� - ", str);
      tempstr = enterWord();
      }
    }
  if (Q!=6)
    {
    New_list = search(list, Q, temp, tempstr);
    if (New_list)
      messages(5);
    else
      messages(6);
    }
  return New_list;
  }
//*****************************************************************************************
//������� ������ ������
LIST search(LIST list, int Key, int num, char* str)
  {
  LIST search = NULL, temp = NULL;
  for (; list; list = list->next)
  if (Key == 1 && !strcmp(list->Guitars.Name, str) || Key == 2 && list->Guitars.Strings <= num || 
      Key == 3 && list->Guitars.Year <= num || Key == 4 && !strcmp(list->Guitars.Wood.Neck, str)
      || Key == 5 && !strcmp(list->Guitars.Wood.Deck, str))
    {
    temp = (LIST) malloc(sizeof(sLIST));
    temp->Guitars = list->Guitars;
    search = addNth(search, temp, 0);
    }
   return search;
  }
//*****************************************************************************************
//������� ����� �������� �����
char* fileName(int Key)
  {
  system("cls");
  char *name;
  switch (Key)
    {
      case 1:
        puts("������� ��� �����");
        puts("���� ����� ���� �� ����������, �� ����� ������, ����� - �����������");
        break;
      case 2:
        puts("!���� ������� �������� ���������, �� �������� ����� ��������� � ���");
        puts("1 - ������ �������� ����� � ����������");
        puts("2 - ������� ���������������� �������");
        printf("������� ����� ������ - ");
        if (!(enterNum(1, 2) - 1))
          puts("������� ��� �����");
        else
          {
          name = (char*) malloc(6*sizeof(char));
          strcpy(name, "Guitars");
          return name;
          }
        break;
    }
  printf("��� ����� - ");
  name = enterWord();
  return name;
  }
//*****************************************************************************************
//������� ������ � ����
int recordFile(LIST list, const char* name)
  {
  FILE* file;
  system("cls");
  if (file = fopen(name, "w"))
    {
    fprintf(file, "%d\n", count(list));
    while (list)
      {
      fprintf(file, "%s %d %d %s %s\n", list->Guitars.Name, list->Guitars.Strings, list->Guitars.Year, list->Guitars.Wood.Neck, list->Guitars.Wood.Deck);
      list = list->next;
      }
    fclose(file);
    return 0;
    }
  else
    return 1;
  }
//*****************************************************************************************
//������� ������ �����
int readFile(LIST *list, const char* name)
  {
  LIST temp;
  FILE* file;
  char tempChar;
  int a=1;
  system("cls");
  if (!(file = fopen(name, "r")))
    return 1;         //����� �� ����������
  fseek(file, 0, SEEK_END);
  if (!ftell(file))
    return 2;         //���� ������
  rewind(file);
  int Count, i;
  fscanf(file, "%d", &Count);
  fgetc(file);
  temp = (LIST) malloc(sizeof(sLIST));
  while (Count)
    {
    temp = (LIST) malloc(sizeof(sLIST));
    temp->Guitars.Name = NULL;
    for (i = 0, tempChar = fgetc(file); tempChar != ' '; tempChar = fgetc(file), i++)
      {
      temp->Guitars.Name = (char*) realloc(temp->Guitars.Name, (i + 1)*sizeof(char));
      temp->Guitars.Name[i] = tempChar;
      }
    temp->Guitars.Name[i] = '\0';
    fscanf(file, "%d", &(temp->Guitars.Strings));
    fgetc(file);
    fscanf(file, "%d", &(temp->Guitars.Year));
    fgetc(file);
    temp->Guitars.Wood.Neck = NULL;
    for (i = 0, tempChar = fgetc(file); tempChar != ' '; tempChar = fgetc(file), i++)
      {
      temp->Guitars.Wood.Neck = (char*) realloc (temp->Guitars.Wood.Neck, (i + 1)*sizeof(char));
      temp->Guitars.Wood.Neck[i] = tempChar;
      }
    temp->Guitars.Wood.Neck[i] = '\0';
    temp->Guitars.Wood.Deck = NULL;
    for (i = 0, tempChar = fgetc(file); tempChar != '\n'; tempChar = fgetc(file), i++)
      {
      temp->Guitars.Wood.Deck = (char*) realloc(temp->Guitars.Wood.Deck, (i + 1)*sizeof(char));
      temp->Guitars.Wood.Deck[i] = tempChar;
      }
    temp->Guitars.Wood.Deck[i] = '\0';
    if (!*list)
      *list = addNth(*list, temp, 0);
    else
      *list = addNth(*list, temp, count(*list));
    Count--;
    }
  fclose(file);
  return 0;
  }
//*****************************************************************************************
//������� ������� ������
int outputMenu(LIST list)
  {
  if (list)
    {
    switch (menus(5))
      {
        case 1:
          system("cls");
          puts("������ � ������ ��� � �����?");
          puts("1 - � ������");
          puts("2 - � �����");
          printf("������� ����� ������ (�� %d �� %d): ", 1, 2);
          if(outputList(list, enterNum(1, 2) - 1))
            messages(9);
          break;
        case 2:
          if (!recordFile(list, fileName(1)))
            messages(14);
          else
            messages(18);
          break;
      }
    }
  else
    messages(9);
  return 0;
  }
//*****************************************************************************************
//������� ������ ������
int outputList(LIST list, int Key) //Key: 0 - � ������, 1 - � �����
  {
  if(!list)
    return 1;
  system("mode con cols=85 lines=47");
  if (Key)
    list = getElem(list, 1, 0);
  system("cls");
  int i = 1;
  printf("=====================================================================================");
  printf("%2s | %12s | %18s | %14s | %17s\n", " ", " ", " ", "���������� ", "������:");
  printf("%2s | %12s | %18s | %14s | %s\n","�", "��������  ", "��� ������������ ", "�����    ", "__________________________");
  printf("%2s | %12s | %18s | %14s | %11s | %6s\n", " ", " ", " ", " ", "������  ", "����");
  printf("=====================================================================================");
  while (list)
    {
    printf("%2d | %12s | %18d | %14d | %11s | %6s ", i, list->Guitars.Name, list->Guitars.Year,
           list->Guitars.Strings, list->Guitars.Wood.Deck, list->Guitars.Wood.Neck);
    printf("\n=====================================================================================");
    if (list->prev && Key || list->next && !Key)
      printf("��� ������ ���������� �������� ������� ����� �������, ��� ������ ������� Esc\r");
    else
      puts("��� ���������� ��������� ������� Esc");
    if (_getch() == 27)
      return 0;
    list = (Key) ? list->prev : list->next;
    i++;
    }
  do
    {
    
    }
  while (_getch() != 27);
  system("mode con cols=80 lines=20");
  return 0;
  }
//*****************************************************************************************
//������� ���������� ���������� ��������
LIST getElem(LIST list, int Key, int n) //Key: 0 - ������, 1 - �����, 2 - n-��
  {
  for (; list->prev && Key == 0; list = list->prev);
  for (; list->next && Key == 1; list = list->next);
  for (int i = 1; i < n && list->next && Key == 2; i++, list = list->next);
  return list;
  }
//*****************************************************************************************
//������� �������� ���������� ���������
int count(LIST list)
  {
  int Count;
  for (Count = 0; list; list = list->next, Count++);
  return Count;
  }
