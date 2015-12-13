#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <windows.h>


int Menu();												 			//Прототип функции меню
void Help();											 			//Прототип функции справки
void Messages(int);								 			//Прототип функции вывода сообщений пользователю
char** type_text(int*);						 			//Прототип функции ввода текста
void print_text(char**, int);			 			//Прототип функции вывода текста
char** process_text(char**, int, int*); //Прототип функции обработки текста
int String_check(char*);					 			//Прототип функции проверки одинаковых слов в строке
int Charisdevide(char);					   			//Прототип функции проверки разделителей
void fr(char**, int);							 			//Прототип функции освобождения памяти

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
						case 1:												//Справка
								 		Help();
										break;
						case 2:												//Ввод текста
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

						case 3:												//Вывод исходного текста
										if(rows) 
					 	    		  print_text(text, rows);
										else
										  Messages(1);
										break;
						case 4:												//Обработка текста
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
						case 5:												//Вывод сформированного текста
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
						case 6:												//Выход
										system("cls");
									  puts("До новых встреч!\n");
										system("pause");
										break;
						default:
										printf("Что-то пошло не так, введите пункт меню повторно\n");
										system("pause");
					}
			}
		while (Q!=6);
		fr(text, rows);
		fr(Newtext, Newrows);
		return 0;
	}
	
//*****************************************************************************************
//Функция меню
int Menu()
	{
		int Q;
		system("cls");
		puts("Главное меню");
		puts("1 - Справка");
		puts("2 - Ввод текста");
		puts("3 - Вывод исходного текста");
		puts("4 - Обработка текста");
		puts("5 - Вывод сформированного текста");
		puts("6 - Выход");
		printf("Введите номер пункта - ");
		scanf("%d", &Q);
		printf("\n");
		fflush(stdin);
		return Q;
	}
	
//*****************************************************************************************
//Функция справка
void Help()
	{
		system("cls");
		puts("\n\n  Данная программа предназначена для формирования нового текста, который");
		puts(" является результатом следующего преобразования исходного текста: удалить");
		puts(" строки, содержащие хотя бы два одинаковых слова.");
		puts("\n  Ввод текста пользователем заканчивается после нажатия двух раз клавиши Enter,");
		puts(" введенным через пробел от остального текста.\n");
		puts(" Если возникли проблемы обращайтесь, пожалуйста, на электронную почту:");
		puts(" komdosh@gelezo2.ru\n");
		system("pause");
	}
	
//*****************************************************************************************
//Функция вывода сообщений пользователю
void Messages(int Q)
	{
		system("cls");
		switch(Q)
		 	{
		 		case 1:
		 			puts("Сначала необходимо ввести текст");
		 			break;
	 			case 2:
	 				puts("Вы ввели текст, но не обработали его.");
	 				puts("Вам необходимо выбрать 4 пункт меню для обработки текста.");
	 				break;
 				case 3:
 					puts("Текст введён успешно");
 					break;
 				case 4:
 					puts("Ошибка, возможно, Вы не ввели текст?");
 					puts("Попробуйте ввести текст повторно.");
 					break;
 				case 5:
 					puts("Новый текст успешно сформирован.");
 					break;
 				case 6:
 					puts("Новый текст не был сформирован.");
 					puts("В исходном тексте все строки с одинаковыми словами.");
 					break;
		 	}
		system("pause");
	}
	
//*****************************************************************************************
//Функция ввода текста
char** type_text(int *rows)
	{
		system("cls");
		//setlocale(LC_ALL, "RUS");
		char** text=NULL;
		int i,j,w,v=0;
		char s[80];
		printf("Введите текст\n");
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
//Функция вывода текста
void print_text(char **text, int rows)
	{
		system("cls");
		for (int i = 0; i<rows; i++)
			puts(*(text+i));
		system("pause");
	}
	
//*****************************************************************************************
//Функция обработки текста
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
//Функция проверки одинаковых слов в строке
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
			 //Сравнение слов
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
//Функция проверки разделителей
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
//Функция освобождения памяти
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
