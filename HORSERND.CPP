/*
void metodMAN(cell CB[S][S]);          // ���冷� �㭪権 �� ��筮� ��室�.
void method(cell CB[S][S], int step, int cho);// ���冷� �㭪権 �� ��室�.
void zeroing(cell CB[S][S], int &step, int &cho);    // ���㫥��� �� �室�;
void parsing(cell CB[S][S]);          	   // �஢�ઠ ������ ��筮�� �����;
int assay(cell CB[S][S]);		      // �஢�ઠ �믮������ �����.
int choice(cell CB[S][S]);   		         // �롮� ᫥���饩 ����樨.
void storage(cell CB[S][S],int &min, int &key, int &im, int &jm, int id, int jd);
					   // �࠭���� �ਮ��⭮� ����樨.
int scan(cell CB[S][S], int i, int j, int &min);      // ���� �������쭮��.
int back(cell CB[S][S], int &cho);         // ������ �� ������襩 ࠧ�����.
void Stop(int N);                                      // �����襭�� ��室�.
*/
//---------------------------- ������  ������� -----------------------------
cell::cell()                   			     // ������ ���������;
 {
  status.i=0;                                  	   // ����塞 �� ���祭��;
  status.j=0;
  status.z=0;
  status.f=0;
  status.n=0;
  PrintS(22,20,2,1);                     // �뢮� ᮮ�饭�� � ࠡ�� ��⮤�;
 }
cell::operator = (int z)            	// ��������� ��ᢠ������;
 {
  int x, y; x=wherex(); y=wherey();         // ���������� ��������� �����;
  status.z=z;                                // ��ᢠ����� ⥪�饥 ��祭��;
  PrintS(22,20,3,1,1);                   // �뢮� ᮮ�饭�� � ࠡ�� ��⮤�;
  gotoxy(x,y);                           // ������ ����� ���⭮ ��� ��;
  return 0;                           		// �⮡� �� �㣠���;
 }
int cell::cors()                               // ������ ⥪�饣� ���祭��;
 {
  int x, y; x=wherex(); y=wherey();         // ���������� ��������� �����;
  PrintS(22,20,4,1,1);                   // �뢮� ᮮ�饭�� � ࠡ�� ��⮤�;
  gotoxy(x,y);                           // ������ ����� ���⭮ ��� ��;
  return(status.z);
 }
core *cell::adrs()                      // ������ ���� ⥪�饣� �������;
 {
  int x, y; x=wherex(); y=wherey();         // ���������� ��������� �����;
  PrintS(22,20,5,1,1);                   // �뢮� ᮮ�饭�� � ࠡ�� ��⮤�;
  gotoxy(x,y);                           // ������ ����� ���⭮ ��� ��;
  return(&status);
 }
void cell::change(int i, int j, int z)//��������� �᭮���� ���祭�� �������;
 {
  int x, y; x=wherex(); y=wherey();         // ���������� ��������� �����;
  status.i=i;                               // ��������� ��ਧ��⠫� �।��;
  status.j=j;                                 // ��������� ���⨪��� �।��;
  status.z=z;                                // ��������� ⥪�饣� ���祭��;
  PrintS(22,20,3,1,1);                   // �뢮� ᮮ�饭�� � ࠡ�� ��⮤�;
  gotoxy(x,y);                           // ������ ����� ���⭮ ��� ��;
 }
ostream &operator<<(ostream &stream, cell obg)
 {
       //     setw(3) ----------------- ���������, �����騩 �ਭ� ����.
    stream << setw(3) << obg.status.j << "-" << setw(3) << obg.status.i;
  //    ****** stream, � �� cout, �.�. ⮣�� �������� ������祭�� � ���
  //         ! ! ! ! ! ! ! ! ! ! ! ! !       ��⮪�, � �� ⮫쪮 �� ��࠭.

  return stream;
 }

//========================== ����������� ������� ===========================
//--------------------- ���冷� �� ��筮� ��室� ------------------------
void metodMAN(cell CB[S][S])
 {
  int step = 0;        			         // ��� � �����⬥ ��室�;
  cho=0;           			      // ������⢮ ᤥ����� 室��;
  brk=1;            			   // ��⠭���� ����প� � �������;
  regSTR=reg=0;                                      // ����� ��筮�� �롮� 室�;
  VIZ=1;
   Viz(CB);
   zeroing(CB,step,cho);       			   // ��⠫쭮�� ���㫥���;
   Viz(CB);
   coordViz();
  for(;;) {
	 switch (step){
	     case  0:  CB[i][j]=1; 		     // ��⠭���� � �������;
		       sign=-sign;  		// ����� ���ࠢ����� ��室�;
		       cho++;                   // ���६��� ���稪� 室��;
		       core *Way;
		       Way=CB[i][j].adrs(); // ���⨥ ���� ⥪. �������;
		       Way->n=cho-1;
					step=1; continue;//���室 � case:1;
	     case  1:  Viz(CB);                            // �뢮� ������;
		       Progress(11,50,64,cho);  // �뢮� �ண��� ����樨;
					step=2; continue;
	     case  2:  step = assay(CB);  	continue;//�஢�ઠ �믮������;
	     case  3:  step = choice(CB); 	continue;//�롮� ᫥���饣�;
	     case  4:  step = back(CB,cho);     continue; //�⪠� �� �㯨��;
	     case 10:  Stop(0);			return;//����砭�� ����樨;

	      default:                 step=10; continue; // ����砭�� ��
		   }                                             // ��䮫��;
	}
  }
//---------------------- ���冷� �㭪権 �� ��室� ------------------------
void method(cell CB[S][S], int step, int cho)
{
 for(;;) {
	 switch (step){
	     case  0:  CB[i][j]=1; 		     // ��⠭���� � �������;
		       sign=-sign;  		// ����� ���ࠢ����� ��室�;
		       cho++;                   // ���६��� ���稪� 室��;
		       gotoxy(47,16); printf("%4d",cho); // �뢮� ⥪. 室�;
		       Progress(15,24,64,cho);  // �뢮� �ண��� ����樨;
					step=1; continue;//���室 � case:1;
	     case  1:  Look(CB);	step=2; continue;  // �뢮� ������;
	     case  2:  step = assay(CB);  	continue;//�஢�ઠ �믮������;
	     case  3:  step = choice(CB); 	continue;//�롮� ᫥���饣�;
	     case  4:  step = back(CB,cho);     continue; //�⪠� �� �㯨��;
	     case 10:  Stop(0);			return;//����砭�� ����樨;

	      default:                 step=10; continue; // ����砭�� ��
		   }                                             // ��䮫��;
	}
}
//-------------------------- ���㫥��� �� �室� ---------------------------
void zeroing(cell CB[S][S], int &step, int &cho)
 {
   step = 0; cho=0;        			     // ���㫥��� �� �室�!
   Horscreen();      		      // ����ன�� ����䥩� ��࠭� ��室�;
   Look(CB);                          		  // �뢮� ������ �� ��࠭;
   for(int l=0;l<8;l++)
     for(int m=0;m<8;m++)
       {
	core *Way; 	Way=CB[l][m].adrs(); // ���⨥ ���� ⥪. �������;
	Way->i=0;
	Way->j=0;           		  // ���㫥��� ��� ���祭�� �祩��;
	Way->z=0;
	Way->f=0;
	if(reg){
	gotoxy(59+2*m,l+6); cout<<"."; gotoxy(59+2*m,13-l);}  // ��࠭�����;
       }
 }

//-------------------------- �஢�ઠ ��筮�� ����� ------------------------
void parsing(cell CB[S][S])
 {
  int key=0;// ���� �ᯥ譮�� ��室� �� 横�� ��筮�� ����� ᫥���饣� 室�;
  int oldi, oldj;                        // �࠭���� �।��饣� ���������;
  oldi=(int)i; oldj=(int)j;              	  // ���樠������ �࠭����;
  do{
      coordViz();
     if(!CB[skyline][vertical].cors())
      {
       if((skyline==(oldi-2))&&((oldj+1)==vertical)) key=1;

       if((skyline==(oldi-1))&&((oldj+2)==vertical)) key=1;

       if((skyline==(oldi+1))&&((oldj+2)==vertical)) key=1;

       if((skyline==(oldi+2))&&((oldj+1)==vertical)) key=1;

       if((skyline==(oldi+2))&&((oldj-1)==vertical)) key=1;

       if((skyline==(oldi+1))&&((oldj-2)==vertical)) key=1;

       if((skyline==(oldi-1))&&((oldj-2)==vertical)) key=1;

       if((skyline==(oldi-2))&&((oldj-1)==vertical)) key=1;
      }
   }while(!key);
   CB[skyline][vertical].change(oldi,oldj,0); 	// ���࠭��� ���� �।��;
 }

//---------------------- �஢�ઠ �믮������ ������� ------------------------

int assay(cell CB[S][S])
 {
  PrintS(22,22,8,1,1);                            // ����饭�� � ࠡ�� �-��;

  int Z=1;                           // ��६���� ��� ������祭�� १����.
  for(int i=0; i<S; i++)                   	      // ���譨� 横� �뢮��.
    for(int j=0; j<S; j++)                 	   // ����७��� 横� �뢮��.
       if(!(CB[i][j].cors())) Z=0;	    	// ������ �㫥���� ���祭��.
  if(Z) { return 10;}
  else return 3;
 }

//------------------------ �롮� ᫥���饩 ����樨 --------------------------
int choice(cell CB[S][S])
 {
  PrintS(22,22,9,1,1);                            // ����饭�� � ࠡ�� �-��;

  int min=8;		      // �������쭮� ������⢮ �����⨬�� ���室��.
  int im=i, jm=j;            		       // ���� �����⨬��� ���室�.
  int key=0;                  	  // ���� ����� ���� �����⨬��� ���室�.
  int start, end;                  	 // ������祭�� ��砫� � ���� 横��;
  if(sign>0) { start=0; end=9;}      			 // ��室 �� �ᮢ��;
  else {start=9; end=0;}                             // ��室 ��⨢ �ᮢ��;
  for( ; start!=end; start+=sign)
   {
    switch(start){
	      case 0: PrintS(58,17,10,0,1); continue;// ����饭�� � ���ࠢ�����;
	      case 1:
    if(i>1)
     if(j<7)
      if(!CB[i-2][j+1].cors()) { storage(CB,min,key,im,jm,i-2,j+1); }
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 2:
    if(i>0)
     if(j<6)
      if(!CB[i-1][j+2].cors()) {storage(CB,min,key,im,jm,i-1,j+2);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 3:
    if(i<7)
     if(j<6)
      if(!CB[i+1][j+2].cors()) {storage(CB,min,key,im,jm,i+1,j+2);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 4:
    if(i<6)
     if(j<7)
      if(!CB[i+2][j+1].cors()) {storage(CB,min,key,im,jm,i+2,j+1);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 5:
    if(i<6)
     if(j>0)
      if(!CB[i+2][j-1].cors()) {storage(CB,min,key,im,jm,i+2,j-1);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 6:
    if(i<7)
     if(j>1)
      if(!CB[i+1][j-2].cors()) {storage(CB,min,key,im,jm,i+1,j-2);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 7:
    if(i>0)
     if(j>1)
      if(!CB[i-1][j-2].cors()) {storage(CB,min,key,im,jm,i-1,j-2);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 8:
    if(i>1)
     if(j>0)
      if(!CB[i-2][j-1].cors()) {storage(CB,min,key,im,jm,i-2,j-1);}
    continue;                              // �࠭���� �ਮ��⭮� ����樨;
	      case 9: PrintS(58,17,11,0,1); continue;// ����饭�� � ���ࠢ�����;
	      default: Start(b); gotoxy(25,15); cout<<"������ �� ����� ����";
    }
   }
  if(!key)              			      // �᫨ ����� � �㯨�!
   {

			clrscr();
    gotoxy(30,10); printf("%s", "������ ����㤨����...");	delay(1000);
    if(reg&&!VIZ)
    {
     Horscreen();  		       // ����ன�� ���䥩� ��࠭� ��室�;
     Look(CB);                           	  // �뢮� ����� �� ��࠭;
     outputONS(skyline, vertical);             	     // �뢮� �窨 �����;
    }
    else     Viz(CB);
    return 4;                                    // ��室 �� ᫥����騩 蠣;
   }
  if(reg)              // ��⮬���᪨� ०�� ���室� �� �ਮ���� 室;
  {
   CB[im][jm].change(i,j,0);                    // ���࠭���� ���� �।��;
   i=(abc)im;  				    // ��७����祭�� �窨 �����.
   j=(abc)jm;
   gotoxy(59+2*j,13-i);					delay(10);
  }
  else
  {
  gotoxy(jm*7+15,(7-im)*5+7); cout << "���";
  gotoxy(jm*7+14,(7-im)*5+9); cout << "����!";
  parsing(CB);
  }   			  // ��筮� ०�� �롮� ��६�����;
  return 0;                                      // ��室 �� ᫥����騩 蠣;
}
//--------------------- �࠭���� �ਮ��⭮� ����樨 -----------------------
void storage(cell CB[S][S],int &min, int &key, int &im, int &jm, int id, int jd)
 {
  PrintS(22,22,13,1,1);                           // ����饭�� � ࠡ�� �-��;

  if(scan(CB, id, jd, min))          	      // ������ ����㯭�� ���室��;
   {im=id; jm=jd; key=1;}   // �࠭���� ���� ����樨 � 䨪��� १����;
  else if(!key)      // � ��砥 ������⢨� �ਮ��� � 䨪�樨 १����;
	{im=id; jm=jd; key=1;}//�࠭���� ���� ��ࢮ�� �����⨬��� ���室�
						   //  � 䨪��� १����;
  PrintD(im,jm,id,jd);         	      // �뢮� ������ � ���न���� �� ��࠭;
  if(reg)gotoxy(59+2*j,13-i);				  //	delay(100);
 }
//----------------------- ���� �������쭮�� �ᥤ� -------------------------
int scan(cell CB[S][S], int id, int jd, int &min)
{
 PrintS(22,22,14,1,1);                            // ����饭�� � ࠡ�� �-��;
 core *Way;	Way=CB[i][j].adrs();   	  // ���� �祩�� ⥪�饣� ���������;
 int temp=8;     			     // ������ �����⨬�� ���室��;
  if((id>1)&&(jd<7)) temp-=CB[id-2][jd+1].cors();	else temp--;
  if((id>0)&&(jd<6)) temp-=CB[id-1][jd+2].cors();	else temp--;
  if((id<7)&&(jd<6)) temp-=CB[id+1][jd+2].cors();	else temp--;
  if((id<6)&&(jd<7)) temp-=CB[id+2][jd+1].cors();	else temp--;
  if((id<6)&&(jd>0)) temp-=CB[id+2][jd-1].cors();	else temp--;
  if((id<7)&&(jd>1)) temp-=CB[id+1][jd-2].cors();	else temp--;
  if((id>0)&&(jd>1)) temp-=CB[id-1][jd-2].cors();	else temp--;
  if((id>1)&&(jd>0)) temp-=CB[id-2][jd-1].cors();	else temp--;
 if(reg){
  gotoxy(16,12); cout<<temp; gotoxy(59+2*jd,13-id); cout<<"*";
  gotoxy(59+2*jd,13-id);					  //	delay(300);
  }
 else Pr_Zw(jd*7+12,(7-id)*5+5,7,5,0xf,0xC,0);
 if(temp&&(temp==min))           // �ࠢ����� ������⢠ ����㯭�� ���室��;
  if(!bk){Way->f=1;}  	    		    // �c⠭���� 䫠�� ��ਠ⨢����;
  else{Way->f=0; bk=0;}                        // ���⨥ 䫠�� ��ਠ⨢����;
 if(temp<min)            // �����㦥��� ����襣� ���-�� �����⨬�� ���室��;
  {
   min=temp;               // �१����� ����襣� ���-�� �����⨬�� ���室��;
   Way->f=0;                    	       // ���⨥ 䫠�� ��ਠ⨢����;
   if(reg){
   gotoxy(18,14); cout<<min;}          		  // �뢮� �����㬠 �� ��࠭;
   return 1;                                     // ���室 � ᫥��饬� 蠣�;
  }
 else return 0;
}
//------------------------- ������ � ࠧ����� ------------------------------
int back(cell CB[S][S], int &cho)
 {
  PrintS(22,22,15,1,1);                           // ����饭�� � ࠡ�� �-��;
  core *Way; Way=CB[i][j].adrs();       // ���⨥ ���� ⥪��饣� ���������;
  cho--;                                 // �⪠� ������⢠ �ன����� 蠣��;
  if(reg&&!VIZ)
   {
    gotoxy(47,16); printf("%4d",cho);    // �뢮� ������⢠ �ன����� 蠣��;
    Progress(15,24,64,cho);                	 // �뢮� �ண��� ����樨;
    char J = IvC(j);		gotoxy(47,10); cout<<J<<"  "<<i;
			    // �뢮� ���न���� ⥪�饣� ���������� �� ��࠭;
    gotoxy(59+2*j,13-i);
   }			 				    delay(1000);
  if(!(Way->f))    			   // ���� ������襩 ��⪨ ࠧ�����;
   {
     Way->z=0; 				            // ���㫥��� ⥪�饣� ���祭��;
     if(reg&&!VIZ)cout<<Way->z;
     else{Viz(CB); gotoxy(32,2); cout<< "�⪠� ���������...";
     Progress(11,50,64,cho);}
     i=(abc)Way->i;                          // ���室 � �।��饩 ����樨;
     j=(abc)Way->j;
     return 4;
   }
  else
   {
    sign=-sign;                            	 // ����� ���ࠢ����� ��室�;
    Way->f=0;                                   	  // ���㫥��� 䫠��;
    bk=1;                                       // �⬥⪠ � ���㫥��� 䫠��;
    return 0;
   }
 }

//--------------------------- �ࠬ���� ��室 ------------------------------
void Stop(int N)
 {
  PrintS(22,22,16,1,1);                           // ����饭�� � ࠡ�� �-��;
   switch (N){
	     case  0: 	   /*	clrscr();
		gotoxy(35,10); cout<<"�������������!!!";*/ delay(1000); return;
	     default: 		clrscr();
		gotoxy(40,10); cout<<"���...";           delay(1000); return;
	     }
 }
//***************************************************************************