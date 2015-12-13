#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <windows.h>


int Menu();												 			//�������� ������� ����
void Help();											 			//�������� ������� �������
void Messages(int);								 			//�������� ������� ������ ��������� ������������
char** type_text(int*);						 			//�������� ������� ����� ������
void print_text(char**, int);			 			//�������� ������� ������ ������
char** process_text(char**, int, int*); //�������� ������� ��������� ������
int String_check(char*);					 			//�������� ������� �������� ���������� ���� � ������
int Charisdevide(char);					   			//�������� ������� �������� ������������
void fr(char**, int);							 			//�������� ������� ������������ ������

int main()
	{
		setlocale(LC_ALL, "RUS");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		char** text=NULL;
		char** Newtext=NULL;
		int rows=0, Newrows=0, Q, check_process=0;
		do
			{
				Q = Menu();
				switch (Q)
					{
						case 1:												//�������
								 		Help();
										break;
						case 2:												//���� ������
								 		  fr(text, rows);
							 		    do
							 		    {
												text=type_text(&rows);
												if(rows)
												  Messages(3);
						  				  else
						  				  	Messages(4);	
							 		    }
						 		    while(!rows);
						 		    check_process=0;
		    						break;

						case 3:												//����� ��������� ������
										if(rows) 
					 	    		  print_text(text, rows);
										else
										  Messages(1);
										break;
						case 4:												//��������� ������
								 		check_process=1;											
								 		if(rows)		
										 {
								 		 	Newtext=process_text(text, rows, &Newrows);
								 		 	if(Newrows)
		 		 						 		Messages(5);
 		 						 		  else
 		 						 		    Messages(6);
										 }									
						 				else
										  Messages(1);
										break;
						case 5:												//����� ��������������� ������
								 		if(rows)									
										 	if(check_process)		
											 	if(Newrows)													
													print_text(Newtext, Newrows);
												else
													Messages(6);	
											else
											  Messages(2);
										else
										  Messages(1);	
										break;
						case 6:												//�����
										system("cls");
									  puts("�� ����� ������!\n");
										system("pause");
										break;
						default:
										printf("���-�� ����� �� ���, ������� ����� ���� ��������\n");
										system("pause");
					}
			}
		while (Q!=6);
		fr(text, rows);
		fr(Newtext, Newrows);
		return 0;
	}
	
//*****************************************************************************************
//������� ����
int Menu()
	{
		int Q;
		system("cls");
		puts("������� ����");
		puts("1 - �������");
		puts("2 - ���� ������");
		puts("3 - ����� ��������� ������");
		puts("4 - ��������� ������");
		puts("5 - ����� ��������������� ������");
		puts("6 - �����");
		printf("������� ����� ������ - ");
		scanf("%d", &Q);
		printf("\n");
		fflush(stdin);
		return Q;
	}
	
//*****************************************************************************************
//������� �������
void Help()
	{
		system("cls");
		puts("\n\n  ������ ��������� ������������� ��� ������������ ������ ������, �������");
		puts(" �������� ����������� ���������� �������������� ��������� ������: �������");
		puts(" ������, ���������� ���� �� ��� ���������� �����.");
		puts("\n  ���� ������ ������������� ������������� ����� ������� ���� ��� ������� Enter,");
		puts(" ��������� ����� ������ �� ���������� ������.\n");
		puts(" ���� �������� �������� �����������, ����������, �� ����������� �����:");
		puts(" komdosh@gelezo2.ru\n");
		system("pause");
	}
	
//*****************************************************************************************
//������� ������ ��������� ������������
void Messages(int Q)
	{
		system("cls");
		switch(Q)
		 	{
		 		case 1:
		 			puts("������� ���������� ������ �����");
		 			break;
	 			case 2:
	 				puts("�� ����� �����, �� �� ���������� ���.");
	 				puts("��� ���������� ������� 4 ����� ���� ��� ��������� ������.");
	 				break;
 				case 3:
 					puts("����� ����� �������");
 					break;
 				case 4:
 					puts("������, ��������, �� �� ����� �����?");
 					puts("���������� ������ ����� ��������.");
 					break;
 				case 5:
 					puts("����� ����� ������� �����������.");
 					break;
 				case 6:
 					puts("����� ����� �� ��� �����������.");
 					puts("� �������� ������ ��� ������ � ����������� �������.");
 					break;
		 	}
		system("pause");
	}
	
//*****************************************************************************************
//������� ����� ������
char** type_text(int *rows)
	{
		system("cls");
		//setlocale(LC_ALL, "RUS");
		char** text=NULL;
		int i,j,w,v=0;
		char s[80];
		printf("������� �����\n");
		for (i=0; v!=1;i++)
			{	
				for(w=j=0;w!=1;j++)
					{
						*(s+j)=getchar();
						if(*(s+j)=='\n')
						{
							w=1;
							*(s+j)='\0';
						}
						if(*s=='\0')
						  v=1;
			 		  if(j==79)
			 		  {
			 		  	w=1;
			 		  	*(s+80)='\0';
			 		  }
					}
				text=(char**)realloc(text, (i+1)*sizeof(char*));
				*(text+i)=(char*)malloc((strlen(s)+1)*sizeof(char));
				strcpy(text[i],s);
				for(j=0;j<strlen(s);j++)
					*(s+j)=0;					
			}
		*rows=i-1;
		return text;
	}

//*****************************************************************************************
//������� ������ ������
void print_text(char **text, int rows)
	{
		system("cls");
		for (int i = 0; i<rows; i++)
			puts(*(text+i));
		system("pause");
	}
	
//*****************************************************************************************
//������� ��������� ������
char** process_text(char** text, int rows, int* Newrows)
	{
		int i,j,check,count=0;
		char** Newtext=NULL;
		system("cls");
		for(i=0;i<rows;i++)
			{
				check=String_check(*(text+i));
				if (!check)
				{
				 	 Newtext=(char**)realloc(Newtext, (count+1)*sizeof(char*));
				 	 *(Newtext+count)=*(text+i);
				 	 count++;
				}
			}	
		*Newrows=count;							 
		return Newtext;
	}

//*****************************************************************************************
//������� �������� ���������� ���� � ������
int String_check(char* text)
{
	int check=0,i=0,count=0,index=0, first, *mas=NULL;	 
	while(i<strlen(text))
		{
			while(Charisdevide(*(text+i)))
	            i++;
			while(!Charisdevide(*(text+i)))
				{
					if(count==0)
					  first=i;
					i++;
					count++;
				}
			count=0;	
			mas=(int*)realloc(mas, 2*(index+1)*sizeof(int));
			mas[2*index]=count;
			mas[2*index+1]=first;
			index++;
		}
	for(i=0; i<index-1 && !check; i++)
	  for(int j=i+1; j<index && !check; j++)
		 	if(mas[j*2]==mas[i*2])
		 	{
			 //��������� ����
			 for(int q=0; q<mas[j*2]; q++)
			   if(text[mas[j*2+1]+q]==text[mas[i*2+1]+q])	
			     check++;
			   else
				check=0;  
	     	 if(check == mas[j*2])
	       		check=1;
	    	}					 
	return check;
}		

//*****************************************************************************************
//������� �������� ������������
int Charisdevide(char ch)
	{
		char p[]={ '.', ',', ' ', '*', '"', '-', ';' , '!', '?', ':', ')', '(', ']', '@', '[', '+', '_', '\0', ' ', '=', '#', '^'};
		int check=0, i=0;
		while (*(p+i)!='^' && !check)
			{
				if (ch==*(p+i))
					check=1;
				i++;
			}
		return check;
	}	
	
//*****************************************************************************************
//������� ������������ ������
void fr(char** text, int rows)
	{
		if (text!=NULL)
			{
				for (int i = 0; i<rows; i++)
					free(*(text+i));
				free(text);
				text=NULL;
			}
	}	
