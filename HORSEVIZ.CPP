//----------------------------- ��ᬮ��  ���� -----------------------------
void Viz(cell CB[S][S])
{
		textmode(C4350); textattr(0x70); clrscr();

 int Rx=7, Ry=5;
 //          *(E + ��ப� * 160 + ������    ) = ������
//          *(E + ��ப� * 160 + ������ + 1) = ����,���
//   ���  ����� ����.㣮������� ��஭ �ೊ��� 梥⮢ � ���:� �����
// �㭪樨�  �� X �  �� Y �  �� X �  �� Y � ���������  ����   � ����

//void Pr_Zw(int Wlx,int Wly,int Dlx,int Dly,int ZwSim,int ZwFon,int nk)
 Pr_Zw(9,3,62,44,0xf,0);
 for( int i=0; i<8; i++)
  {
   gotoxy(11,i*Ry+10); cout<<8-i;
   gotoxy(i*Rx+19,5); printf("%c",'a'+i);
   for(int j=0; j<8; j++)
   {
    if(CB[i][j].cors())
    {
     core *Way;        Way=CB[i][j].adrs();
     Pr_Zw(j*Rx+12,(7-i)*Ry+5,Rx,Ry,0xf,(j+i)%2? 3 : 0xb ,0);
     gotoxy(j*7+16,(7-i)*5+7); cout << Way->n+1;
     gotoxy(j*7+15,(7-i)*5+9); cout << IvC((abc)Way->j)<<"-"<<(Way->i)+1;
    }
    else Pr_Zw(j*Rx+12,(7-i)*Ry+5,Rx,Ry,0xf,(i+j)%2? 1 : 0xE ,0);



   }
  gotoxy(74,4); cout<<"�����:";
  Pr_Zw(73,5,5,3,0xA,0xC);
  if(reg||regSTR){ gotoxy(75,7); cout<<"���";}
  else{ gotoxy(75,7); cout<<"���";}
  }
}
//----------------------------
void coordViz()
 {
  do{

     int XP, YP, ex;
     do{
	ex = get_press(0,XP,YP);
       }while(!ex);

	XP/=8;  YP/=8;

     if(!XP && !YP) break;
     if(XP>72&&XP<78&&YP>4&&YP<8)
      {
       reg=1;
       regSTR=1;
       gotoxy(75,7); cout<<"A��";
       break;
      }
     vertical=(XP-12)/7;
     skyline=7-((YP-5)/5);
     j=(abc)vertical;
     i=(abc)skyline;
  }while((skyline>S-1)||(vertical>S-1));
 }

//---------------------------- �뢮�  �����⮢ ----------------------------
//          *(E + ��ப� * 160 + ������    ) = ������
//          *(E + ��ப� * 160 + ������ + 1) = ����,���
//   ���  ����� ����.㣮������� ��஭ �ೊ��� 梥⮢ � ���:� �����
// �㭪樨�  �� X �  �� Y �  �� X �  �� Y � ���������  ����   � ����

void Pr_Zw(int Wlx,int Wly,int Dlx,int Dly,int ZwSim,int ZwFon,int nk)

// �������� !!! ���஦�� � ����஬ ���� !!! ����� 1 - ����� !!!.

{
char huge *E = (char *) 0xb8000000;                //      ���� ���������.
 int j,i;
				  E += nk * 8000;  // ������� �� nk-� ����.

   for(j=0;   j<  Dly;   j++ )
   for(i=0;   i<2*Dlx;   i+=2)

   *((E + 160*(Wly+j) + 2*Wlx) + i+1)= ZwSim + 16*ZwFon;
}
//---------------------------- ��ࠡ�⪪� ����� ----------------------------
int get_press(int butt, int& x_pos, int& y_pos) //  ��ࠡ�⪠ ᮡ��� �����,
					// ��।�� ��ࠬ��஢ �१ ������.
{
			    int x=100, y=100, pr;
	 asm {                                  //     ��ᥬ���ୠ� ��⠢��.
		mov ax,5;
		mov bx,butt;
		int 0x33;
		mov x,cx;
		mov y,dx;
		mov pr,bx;
	     }
			    x_pos = x;
			    y_pos = y;
return(pr ? 1:0);
}
//--------------------------------------------------------------------------
void outupText(char *name)			// �뢮� ⥪�� �� ��࠭;
{
 char buff[80];					// ���� ��� �࠭���� ��ப�;
 int len=0;					// ������ ��ப�;
 FILE *fff;
						clrscr();
 if((fff=fopen(name, "r+t"))==NULL)
 {
    gotoxy(20,16);   cout << "�� ���� ������ 䠩� "<< name;
    getch();     return;
 }

 cout << "\n\t      ";
 while(fgetc(fff) != EOF)		// ���� ���뢠��� �� 䠩��
  {					// � �뢮�� �� ��࠭;
	fscanf(fff, "%s", buff); 	//  ���뢠�� ᫮��

	 len += (strlen(buff)+1);	// ����⠥� ����� ��ப�;

	if(len<52 && buff[1]!=')')      // �᫨ ����� ��ப� �� ����蠥� �������� �ਭ�
	  cout << ' ' << buff;	// ���⠥�
	else                	// ����
	 {
	  cout << "\n\t       " << buff;     // ��७�ᥬ �� ����� ��ப�;
	  len=strlen(buff)+1;
	 }
  }
}
