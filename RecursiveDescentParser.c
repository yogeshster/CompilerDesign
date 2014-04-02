#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *fp,*tfp,*tfp1,*tfp2;
int seek1,seek2;
char str[50],str1[10],str2[50];
int mflag=0,i,j,flag,sflag=0,eflag=0,cnum=0,cop=0,obr=0,cbr=0,fcount=0;
void pgm();
void stmt();
void forst();
void ifst();
void asst();
void list();
void expr();
void listprime();
void be();
void beprime();
void bf();
void bt();
void btprime();
void ae();
void aeprime();
void at();
void atprime();
void af();	
void ae()
{
	printf("\nEntered ae\t%s\n",str);
	at();
	aeprime();
}

void af()
{
        if(!strcmp(str,"("))
        {
                fscanf(fp,"%s",str);
                ae();
                if((strcmp(str,")"))!=0)
                        mflag++;
        }
        else if(isalpha(str[0]))
	{
		printf("\n%s\n",str);
		cnum++;
		fscanf(fp,"%s",str);
	}
        else if(str[0]>=48&&str[0]<=57)
	{
                fscanf(fp,"%s",str);
		cop++;
	}
        else if(!strcmp(str,";")&&cnum<=cop)
	{
                mflag++;
	}
}

void atprime()
{
        if(!strcmp(str,"*"))
        {
		cop++;
		eflag++;
                fscanf(fp,"%s",str);
                af();
                atprime();
        }
}
void at()
{
        af(); 
       	atprime();
}

void aeprime()
{
        if(!strcmp(str,"+"))
        {
		printf("\n%s\n",str);
		cop++;
		eflag++;
                fscanf(fp,"%s",str);
                at();
                aeprime();
        }
}

void listprime()
{
	//printf("\n\nList prime called\n\n");
	if(!strcmp(str,"for")||!strcmp(str,"if")||!strcmp(str,"{")||(isalpha(str[0])))
	{
		printf("\n%s\nEntered listprime\n",str);
		printf("\n%d\n",mflag);
		if(!strcmp(str,"{"))
		{
			fscanf(fp,"%s",str);
			obr++;
		}
		fcount++;
		stmt();
		listprime();
	}
}

void list()
{
	printf("\nentered list\n");
	stmt();
	listprime();
	printf("\nlist prime called\n");
}

void bf()
{
	if(!strcmp(str,"not"))
	{
		fscanf(fp,"%s",str);
		bf();
	}
	else if(!strcmp(str,"("))
	{
		fscanf(fp,"%s",str);
		be();
		if(strcmp(str,")")!=0)
			mflag++;
	}
	else if((isalpha(str[0]))&&(strcmp(str,"and")!=0)&&(strcmp(str,"or")!=0))
	{
		cnum++;
		fscanf(fp,"%s",str);
	}
	else if((str[0]>=48)&&(str[0]<=57))
	{
		cnum++;
		fscanf(fp,"%s",str);
	}
	else if(!strcmp(str,";")&&cnum<=cop)
	{ 
		mflag++;
	}	
}
 
void btprime()
{
	if(!strcmp(str,"and"))
	{
		cop++;
		eflag++;
		fscanf(fp,"%s",str);
		bf();
		btprime();
	}
}

void bt()
{
	bf();
	btprime();
}

void beprime()
{
	if(!strcmp(str,"or"))
	{
		cop++;
		eflag++;
		fscanf(fp,"%s",str);
		bt();
		beprime();
	}
}

void be()
{
	bt();
	beprime();
}

void expr()
{
	eflag=0;cnum=0;cop=0;
	be();
	if(eflag==0)
	{
		cnum=0;cop=0;
		printf("not in be\n");
		fseek(fp,seek2,SEEK_SET);
		fscanf(fp,"%s",str);
		ae();
		printf("\n%s\n",str);
	}
	if((eflag==0)&&(strcmp(str,";")!=0))
	{
		printf("\nenters\n");
		mflag++;
	}
}

void forst()
{
	//seek1=ftell(fp);
	//fscanf(fp,"%s",str);
	//if(!strcmp(str,"for"))
	//{
	//	fscanf(fp,"%s",str);
		if(isalpha(str[0]))
		{
			fscanf(fp,"%s",str);
			if(!strcmp(str,"="))
			{	
				seek2=ftell(fp);
				fscanf(fp,"%s",str);
				expr();
				{
					if(!strcmp(str,"until"))
					{
						fscanf(fp,"%s",str);
						expr();
						stmt();
					}
					else
						mflag++;
				}
			}
			else
				mflag++;
		}
		else
			mflag++;
	//}
	//else 
	//	sflag++;
}

void ifst()
{
	//fscanf(fp,"%s",str);
	//if(!strcmp(str,"if"))
	//{
		seek2=ftell(fp);
		//fscanf(fp,"%s",str);
		expr();
		stmt();
	//}
	//else 
	//	sflag++;
}

void asst()
{
	//fscanf(fp,"%s",str);
	//if(isalpha(str[0]))
	//{
	//	fscanf(fp,"%s",str);
		if(!strcmp(str,"="))
		{
			seek2=ftell(fp);
			fscanf(fp,"%s",str);
			expr();
			if(!strcmp(str,";"))
			{
				fscanf(fp,"%s",str);
			}
			else
				mflag++;
		}
		else
			mflag++;
	//}
	//else
	//	sflag++;
}

void stmt()		
{
	/*forst();
	if(sflag!=0)
	{
		sflag=0;
		fseek(fp,seek1,SEEK_SET);
		fscanf(fp,"%s",str);
		ifst();
		if(sflag!=0)
		{
			sflag=0;fseek(fp,seek1,SEEK_SET);fscanf(fp,"%s",str);
			asst();
			if(sflag!=0)
			{
				sflag=0;fseek(fp,seek1,SEEK_SET);
				fscanf(fp,"%s",str);
				if(!strcmp(str,"{"))
				{
					obr++;
					printf("%s\n",str);
					fscanf(fp,"%s",str);
					fcount++;
					list();
				}
				if(strcmp(str,"}")!=0)
					cbr++;
			}
		}
	}*/
	if(!strcmp(str,"for"))
	{
		fscanf(fp,"%s",str);
		forst();
	}
	else if(!strcmp(str,"if"))
	{
		fscanf(fp,"%s",str);
		ifst();
	}
	else if(isalpha(str[0]))
	{
		fscanf(fp,"%s",str);
		asst();
	}
	else if(!strcmp(str,"{"))
	{
		obr++;
		fscanf(fp,"%s",str);
		list();
		if(strcmp(str,"}")!=0)
			mflag++;
	}
	else
		mflag++;
		
}

void pgm()
{
	//seek1=ftell(fp);
	fscanf(fp,"%s",str);
	stmt();
	while(!feof(fp))
	{
		fscanf(fp,"%s",str);
		if(!strcmp(str,"{"))
			obr++;
		else if(!strcmp(str,"}"))
			cbr++;
	}
}

main()
{
	fp=fopen("input.txt","r");
	pgm();
	//printf("\n\n%d\t%d\n\n",obr,cbr);
	if(obr!=cbr)
		mflag++;
	if(mflag==0)
		printf("Accepted\n");
	else
		printf("Not Accepted\n");
}
