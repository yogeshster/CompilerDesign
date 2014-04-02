#include<stdio.h>
#include<string.h>
void assignment();
void handleif();
void handlefor();
void handlewhile();

char stack1[25][25],stack[25][25],postfix[25][25],str[50],icg[100][100],ts[50][50];
int tos,pfi=0,tos1=-1,icgcnt=0,tscnt=0,count=1,realflag=0;
FILE *fp;

int isnum(char a)
{
	if(a=='0'||a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9')
		return 1;
	else 
		return 0;
}
void push1(char *a)
{
	strcpy(stack1[++tos],a);
}

char *pop1()
{
	return(stack1[tos--]);
}

void push(char a,int flag)
{
	char tmpstr[10];
	if(flag==0)
	{
		tmpstr[0]=a;
		tmpstr[1]='\0';
	}
	else
	{
		if(a=='-')
			strcpy(tmpstr,"uminus");
		else
			strcpy(tmpstr,"uplus");
	}
	strcpy(stack[++tos],tmpstr);
	//printf("%s\t%s\n",tmpstr,stack[tos]);
}

char *pop()
{
	//printf("\nreturning %s\n",stack[tos]);
	return(stack[tos--]);
}

void postfixx()
{
	int flag=0,i=0,s,realflag1=0;
	char tmpstr[10],tmpstr1[10];
	pfi=0;
	tos=-1;
	for(i=0;i<strlen(str);i++)
	{
		if(str[i]=='.')
		{
			realflag++;
			break;
		}
	}
	i=0;
	while(str[i]!='=')
		i++;
	i++;
	while(1)
	{
		if((isalpha(str[i]))||(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/'&&str[i]!='('&&str[i]!=')'&&str[i]!='\0'))
		{
			s=0;realflag1=0;
			//printf("%c\n",str[i]);
			flag=0;
			while(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/'&&str[i]!='('&&str[i]!=')'&&str[i]!='\0')
			{
				//printf("\nloops\n");
				if(str[i]=='.')
					realflag1++;
				tmpstr[s++]=str[i++];
			}
			tmpstr[s]='\0';
			strcpy(postfix[pfi++],tmpstr);
			if(realflag!=0&&realflag1==0)
				strcpy(postfix[pfi++],"inttoreal");
		}
		else if(str[i]=='(')
		{
			push(str[i++],0);
		}
		else if(str[i]!=')')
		{
			//printf("%c\n",str[i]);
			push(str[i++],flag);
			//printf("%s\n",stack[tos]);
			if(flag==0)
				flag=1;
			else
				flag=0;
		}
		else if(str[i++]==')')
		{
			while(1)
			{
				//printf("%s\n",postfix[pfi-1]);
				strcpy(postfix[pfi++],pop());
				if(!strcmp(postfix[pfi-1],"("))
					break;
				
			}
			pfi--;
			printf("\nTOS is %d\n",tos);
			//tos--;
			//printf("\nThird else..%s\n",stack[tos]);	
			flag=0;
		}
		//i++;
		if(str[i]=='\0')
			break;
	}
	//strcpy(postfix[pfi++],stack[0]);
	printf("Top of stack is %s\t%d\n",stack[tos],tos);
	while(tos!=-1)
	{
		strcpy(postfix[pfi++],pop());
	}
	printf("\nPostfix equivalent\n");
	for(i=0;i<pfi;i++)
		printf("%s\n",postfix[i]);
	printf("\n");
}

void assignment()
{
	int i,j,k,l,cntbf,retbak;	//cntbf stores the goto address which is calculated later
	char a[5],b[5],cbe[5],tmpstr[20],cntstr[2],tmpstr1[20];	//cbe stores the character before =
	cbe[0]=str[0];cbe[1]='=';cbe[2]='\0';
	str[strlen(str)-1]='\0';
	postfixx();
	i=0;
	tos=-1;
	while(i<pfi)
	{
		if(((isalpha(postfix[i][0]))&&(strcmp(postfix[i],"inttoreal")!=0)&&(strcmp(postfix[i],"uminus")!=0)&&(strcmp(postfix[i],"uplus")!=0))||isnum(postfix[i][0]))
			push1(postfix[i]);
		else
		{
			if(!strcmp(postfix[i],"inttoreal"))
			{
				strcpy(a,pop1());
				sprintf(cntstr,"%d",count++);
				strcpy(ts[tscnt],"t");
				strcat(ts[tscnt],cntstr);
				strcpy(tmpstr,ts[tscnt]);
				strcat(ts[tscnt],"=");
				strcat(ts[tscnt],"(inttoreal)");
				strcat(ts[tscnt],a);
				sprintf(icg[icgcnt],"%d",(icgcnt+100));
				strcat(icg[icgcnt],":");
				strcat(icg[icgcnt++],ts[tscnt++]);
				push1(tmpstr);
			}
			else if(strcmp(postfix[i],"uminus")!=0&&strcmp(postfix[i],"uplus")!=0)
			{
				strcpy(b,pop1());
				strcpy(a,pop1());
				sprintf(cntstr,"%d",count++);
				strcpy(ts[tscnt],"t");
				strcat(ts[tscnt],cntstr);
				strcpy(tmpstr,ts[tscnt]);
				strcat(ts[tscnt],"=");
				strcat(ts[tscnt],a);
				if(realflag!=0)
					strcat(ts[tscnt]," real");
				strcat(ts[tscnt],postfix[i]);
				if(realflag!=0)
					strcat(ts[tscnt]," ");
				strcat(ts[tscnt],b);
				//strcat(ts[tscnt],";");
				sprintf(icg[icgcnt],"%d",(icgcnt+100));
				strcat(icg[icgcnt],":");
				strcat(icg[icgcnt++],ts[tscnt++]);
				push1(tmpstr);
			}
			else if(!strcmp(postfix[i],"uminus"))
			{
				strcpy(a,pop1());
				sprintf(cntstr,"%d",count++);
				strcpy(ts[tscnt],"t");
				strcat(ts[tscnt],cntstr);
				strcpy(tmpstr,ts[tscnt]);
				strcat(ts[tscnt],"=");
				strcat(ts[tscnt],"-");strcat(ts[tscnt],a);
				//strcat(ts[tscnt],";");
				sprintf(icg[icgcnt],"%d",(icgcnt+100));
				strcat(icg[icgcnt],":");
				strcat(icg[icgcnt++],ts[tscnt++]);
				push1(tmpstr);
			}
			else if(!strcmp(postfix[i],"uplus"))
			{
				strcpy(a,pop1());
				sprintf(cntstr,"%d",count++);
				strcpy(ts[tscnt],"t");
				strcat(ts[tscnt],cntstr);
				strcpy(tmpstr,ts[tscnt]);
				strcat(ts[tscnt],"=");
				strcat(ts[tscnt],"+");strcat(ts[tscnt],a);
				//strcat(ts[tscnt],";");
				sprintf(icg[icgcnt],"%d",(icgcnt+100));
				strcat(icg[icgcnt],":");
				strcat(icg[icgcnt++],ts[tscnt++]);
				push1(tmpstr);
			}
		}
		i++;
	}
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],cbe);
	strcat(icg[icgcnt++],pop1());
	realflag=0;
}

void handlefor()
{
	int inicnt=0,concnt=0,incrcnt=0,i,j,k,l,cntbf,retbak,retaddr;	//cntbf stores the goto address which is calculated later
	char a[5],b[5],cbe[5],splstr[10],tmpstr[20],cntstr[2],tmpstr1[20],initial[10],condn[10],incr[10];	//cbe stores the character before =
	fscanf(fp,"%s",str);
	for(i=1;str[i]!=';';i++)
	{
		initial[inicnt++]=str[i];
	}
	initial[inicnt]='\0';
	i++;
	for(;str[i]!=';';i++)
	{
		condn[concnt++]=str[i];
	}
	condn[concnt]='\0';
	i++;
	for(;str[i]!=')';i++)
	{
		incr[incrcnt++]=str[i];
	}
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],": ");
	strcat(icg[icgcnt],initial);
	icgcnt++;
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],": ");
	strcat(icg[icgcnt],"if ");
	strcat(icg[icgcnt],condn);
	strcat(icg[icgcnt]," goto ");
	sprintf(tmpstr,"%d",(icgcnt+102));
	strcat(icg[icgcnt],tmpstr);
	retaddr=icgcnt;	//starting addr of for is stored
	icgcnt++;
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],"goto ");
	retbak=icgcnt;	//should return here to store the address of else
	icgcnt++;
	fscanf(fp,"%s",str);
	fscanf(fp,"%s",str);
	while(strcmp(str,"}")!=0)
	{
		if(str[1]=='=')
			assignment();
		else if(str[0]=='i'&&str[1]=='f')
			handleif();
		else if(!strcmp(str,"for"))
			handlefor();
		else if(!strcmp(str,"while"))
			handlewhile();
		fscanf(fp,"%s",str);
	}
	if(incr[1]!='=')
	{
		splstr[0]=incr[0];splstr[1]='=';splstr[2]=incr[0];splstr[3]=incr[1];splstr[4]='1';splstr[5]='\0';
	}
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],": ");
	if(condn[1]!='=')
		strcat(icg[icgcnt],splstr);
	else
		strcat(icg[icgcnt],incr);
	icgcnt++;
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],": ");
	strcat(icg[icgcnt],"goto ");
	sprintf(tmpstr,"%d",(retaddr+100));
	strcat(icg[icgcnt],tmpstr);
	icgcnt++;
	sprintf(tmpstr,"%d",(icgcnt+100));
	strcat(icg[retbak],tmpstr);	//address for else stored
}

void handlewhile()
{
	int i,j,k,l,cntbf,retbak,retaddr;//cntbf stores the goto address which is calculated later; retback fills else;retaddr stores addr of stmt after while
	char a[5],b[5],cbe[5],tmpstr[20],cntstr[2],tmpstr1[20];	//cbe stores the character before =
	fscanf(fp,"%s",str);
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],": ");
	strcat(icg[icgcnt],"if ");
	strcat(icg[icgcnt],str);
	strcat(icg[icgcnt],"goto ");
	sprintf(tmpstr,"%d",(icgcnt+102));
	strcat(icg[icgcnt],tmpstr);
	retaddr=icgcnt;	//addr of starting of while is stored
	icgcnt++;
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],"goto ");
	retbak=icgcnt;	//should return here to store the address of else
	icgcnt++;
	fscanf(fp,"%s",str);
	fscanf(fp,"%s",str);
	while(strcmp(str,"}")!=0)
	{
		if(str[1]=='=')
			assignment();
		else if(str[0]=='i'&&str[1]=='f')
			handleif();
		else if(!strcmp(str,"for"))
			handlefor();
		else if(!strcmp(str,"while"))
			handlewhile();
		fscanf(fp,"%s",str);
	}
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],"goto ");
	sprintf(tmpstr,"%d",(retaddr+100));
	strcat(icg[icgcnt],tmpstr);
	icgcnt++;
	sprintf(tmpstr,"%d",(icgcnt+100));
	strcat(icg[retbak],tmpstr);	//address for else stored
}

void handleif()
{
	int i,j,k,l,cntbf,retbak;	//cntbf stores the goto address which is calculated later
	char a[5],b[5],cbe[5],tmpstr[20],cntstr[2],tmpstr1[20];	//cbe stores the character before =
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],str);
	strcat(icg[icgcnt],"\t");
	strcat(icg[icgcnt],"goto ");
	sprintf(tmpstr,"%d",(icgcnt+102));
	strcat(icg[icgcnt],tmpstr);
	icgcnt++;
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],"goto ");
	retbak=icgcnt;	//should return here to store the address for else
	icgcnt++;
	fscanf(fp,"%s",str);
	while(strcmp(str,"}")!=0)
	{
		if(str[1]=='=')
			assignment();
		else if(str[0]=='i'&&str[1]=='f')
			handleif();
		else if(!strcmp(str,"for"))
			handlefor();
		else if(!strcmp(str,"while"))
			handlewhile();
		fscanf(fp,"%s",str);
	}
	sprintf(tmpstr,"%d",(icgcnt+100));
	strcat(icg[retbak],tmpstr);	//address for else stored	
}

void convert2icg()
{
	int i,j,k,l,cntbf,retbak;	//cntbf stores the goto address which is calculated later
	char a[5],b[5],cbe[5],tmpstr[20],cntstr[2],tmpstr1[20];	//cbe stores the character before =
	while(strcmp(str,"}")!=0)
	{
		if(str[1]=='=')
		{
			assignment();
		}
		else if(str[0]=='i'&&str[1]=='f')
		{
			handleif();	
		}
		else if(!strcmp(str,"while"))
			handlewhile();
		else if(!strcmp(str,"for"))
			handlefor();
		fscanf(fp,"%s",str);
	}
	sprintf(icg[icgcnt],"%d",(icgcnt+100));
	strcat(icg[icgcnt],":");
	strcat(icg[icgcnt],"Stop");
	for(i=0;i<=icgcnt;i++)
		printf("%s\n",icg[i]);
}

main()
{
	fp=fopen("input.txt","r");
	fscanf(fp,"%s",str);
	fscanf(fp,"%s",str);
	convert2icg();
}
