/*      ����, ᮤ�ঠ騩 �㭪樨 ����� � 䠩� � �⥭�� �� 䠩��.
void Write(char M[K_Strok][K_Stolb], int  st, int  el); //   ������ � 䠩�.
*/
void Write(cell CB[S][S])      // ������ � 䠩�.
{
  int sh=0;
  char name[40];
  abc im=i, jm=j;
  core *Way;
  core BC[65];
		 textattr(0x1A); clrscr();
  gotoxy(20, 2); cout << "����� �뢮�� �ࠥ��� � 䠩�";
  gotoxy(25,12); cout << "���樠������ ���ᨢ�...";
  for(int i=64; i>0; i--)
   {
     sh++;
     Way=CB[im][jm].adrs();  		      // ���⨥ ���� ⥪. �������;
     BC[i].i=im; im=(abc)Way->i;
     BC[i].j=jm; jm=(abc)Way->j;
     Progress(15,24,64,sh); 					delay(10);
   }
  gotoxy(20,20); clreol();
  gotoxy(20,12); clreol(); cout << "��� 䠩��:   ";  cin >> name;

 FILE *fff;

 if((fff=fopen(name, "w+t"))==NULL)
 {
    gotoxy(25,15);   cout << "�� ���� ᮧ���� 䠩� "<< name;
    getch();     return;
 }

		       fputs("/* ���न���� �ன������ ��� :   \n\n", fff);
  for(int k=1;k<65;k++)
   {
    fprintf(fff, "  %c\-%d",IvC((abc)BC[k].j), (unsigned int)BC[k].i+1);
    if(k&&!(k%8))
    fputs("\n\n", fff);
   }
		 fputs("\n\n * * * * * * * * * * * * * * * * * * /", fff);
  fclose(fff);

  textattr(0x31); clrscr();
  gotoxy(25,15); cout << "� � � � � �   ��������� !!!"; Stohas(5,333);
}

