#include<stdio.h>
#include<string.h>

char lineno[50][50],stmt[50][50],str[50];
int linenocnt=0,stmtcnt=0;

FILE *fp;

int isnum(char a)
{
	if(a=='0'||a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9')
		return 1;
	else 
		return 0;
}

void deadcode()
{
	int i=0,j,k,l,m,n,o,flag,flag1,count,splflag=0;
	char lhs[10],op1[10],op2[10];
	while(1)
	{
	splflag=0;
	for(i=0;i<(stmtcnt-1);i++)
	{
		//printf("%s followed by %s ",stmt[i],stmt[i+1]);
		flag=1;
			if(stmt[i][2]!=' '&&stmt[i][4]!=' '&&stmt[i][0]!='s')
			{
				//printf("entered %s successor\n\n",stmt[i],stmt[i+1]);
				for(j=0;stmt[i][j]!='=';j++)
					lhs[j]=stmt[i][j];
				lhs[j]='\0';
		//		printf("\nlhs\t%s\n",lhs);
				flag=0;
				for(j=(i+1);j<stmtcnt;j++)
				{
					if(stmt[j][2]!=' '&&stmt[j][4]!=' '&&stmt[j][0]!='s')
					{
						//printf("lhs is %s entered successor %s\t",lhs,stmt[j]);
						k=0;l=0;m=0;
						while(stmt[j][k]!='=')
							k++;
						k++;
						while((stmt[j][k]!='\0')&&(stmt[j][k]!='+'&&stmt[j][k]!='-'&&stmt[j][k]!='*'&&stmt[j][k]!='/'))
							op1[l++]=stmt[j][k++];
						op1[l]='\0';
						//printf("op1 %s\t",op1);
						//printf("lhs's last char is %c op1's last char is %c\n",lhs[strlen(lhs)-1],op1[strlen(op1)-2]);
						if(!isalpha(op1[strlen(op1)-1])&&!isnum(op1[strlen(op1)-1]))
							op1[strlen(op1)-1]='\0';
						if(strcmp(lhs,op1)==0)
						{
							//printf("\nequal! %s=%s",op1,lhs);
							flag++;
						}
						if(stmt[j][k]!='\0')
						{
							k++;
							while(stmt[j][k]!='\0')
								op2[m++]=stmt[j][k++];
							op2[m]='\0';
							//printf("op2 %s",op2);
							if(!strcmp(op2,lhs))
								flag++;
						}
						//printf("\n");
					}
					else if(stmt[j][0]=='i'&&stmt[j][1]=='f')
					{
					//	printf("if\t");
						k=3;l=0;m=0;
						while(stmt[j][k]!='<'&&stmt[j][k]!='>'&&stmt[j][k]!='=')
							op1[l++]=stmt[j][k++];
						op1[l]='\0';
					//	printf("op1 %s\t",op1);
						k++;
						while(stmt[j][k]!=' ')
							op2[m++]=stmt[j][k++];
						op2[m]='\0';
					//	printf("op2 %s\n\n",op2);
						if(!strcmp(op1,lhs)||!strcmp(op2,lhs))
							flag++;
					}
					if(flag!=0)
						break;
				}
				if((flag==0)&&stmt[i][2]!=' '&&stmt[i][4]!=' '&&stmt[i][0]!='s')
				{
					//code at i should be eliminated
					//printf("\n%s eliminated\n",stmt[i]);
					//for(j=i;j<(stmtcnt-1);j++)
					//	strcpy(stmt[j],stmt[j+1]);
					//stmtcnt--;
					if(stmt[i+1][4]==' ')
					{
						flag1=0;
						for(j=0;j<i;j++)
						{
							if(stmt[j][0]=='i'&&stmt[j][1]=='f')
							{
								//printf("if\t");
								k=3;l=0;m=0;
								while(stmt[j][k]!='<'&&stmt[j][k]!='>'&&stmt[j][k]!='=')
									op1[l++]=stmt[j][k++];
								op1[l]='\0';
						//		printf("op1 %s\t",op1);
								k++;
								while(stmt[j][k]!=' ')
									op2[m++]=stmt[j][k++];
								op2[m]='\0';
						//		printf("op2 %s\n\n",op2);
								if(!strcmp(op1,lhs)||!strcmp(op2,lhs))
									flag1++;
							}
						}
						if(flag1==0)
						{
							splflag++;
							strcpy(stmt[i],"To be eliminated");
						}
					}
					else
					{
						splflag++;
						strcpy(stmt[i],"To be eliminated");
					}
				}
			}
	}
	i=0;
	while(i<(stmtcnt-1))
	{
		if(!strcmp(stmt[i],"To be eliminated"))
		{
			for(j=i;j<stmtcnt;j++)
				strcpy(stmt[j],stmt[j+1]);
			stmtcnt--;
		}
		else
			i++;
	}
	if(splflag==0)
		break;
	}	
	//for(i=0;i<stmtcnt;i++)
	//	printf("%s\n",stmt[i]);
}

void commsub()
{
	int i,j,k,l,m,n,o,p,q,r;
	char *posn;
	int index;
	char lhs1[10],lhs[10],rhs[10],rhs1[10],op1[10],op2[10];	//lhs1 is the lhs to be replaced
	for(i=0;i<stmtcnt;i++)
	{
		if(stmt[i][2]!=' '&&stmt[i][4]!=' '&&stmt[i][0]!='s'&&stmt[i][0]!='$')
		{
			for(j=0;stmt[i][j]!='=';j++)
				lhs[j]=stmt[i][j];
			lhs[j]='\0';
			j++;k=0;
			while(stmt[i][j]!='\0')
				rhs[k++]=stmt[i][j++];
			rhs[k]='\0';
			if(!isalpha(rhs[strlen(rhs)-1])&&!isnum(rhs[strlen(rhs)-1]))
				rhs[strlen(rhs)-1]='\0';
			for(j=(i+1);j<stmtcnt;j++)	//searches for equivalent rhs in successive statements
			{
				if(stmt[j][2]!=' '&&stmt[j][4]!=' '&&stmt[j][0]!='s'&&stmt[j][0]!='$')
				{
					k=0;
					while(stmt[j][k]!='=')
						lhs1[k]=stmt[j][k++];
					lhs1[k]='\0';
					k++;l=0;
					while(stmt[j][k]!='\0')
						rhs1[l++]=stmt[j][k++];
					rhs1[l]='\0';
					if(!isalpha(rhs1[strlen(rhs1)-1])&&!isnum(rhs1[strlen(rhs1)-1]))
						rhs1[strlen(rhs1)-1]='\0';
					if(!strcmp(rhs,rhs1))		//if found replaces the lhs1 found in successive statements with lhs 
					{
						strcpy(stmt[j],"$");
						for(m=j+1;m<stmtcnt;m++)
						{
							if((posn=strstr(stmt[m],lhs1))!=NULL)
							{
								index=stmt[m]-posn;index=-index;
								for(n=index,o=0;o<strlen(lhs);o++,n++)
									stmt[m][n]=lhs[o];
							}
						}
					}
				}
			}
		}
	}
	i=0;
	while(i<(stmtcnt-1))
	{
		if(!strcmp(stmt[i],"$"))
		{
			for(j=i;j<stmtcnt;j++)
				strcpy(stmt[j],stmt[j+1]);
			stmtcnt--;
		}
		else
			i++;
	}
	//for(i=0;i<stmtcnt;i++)
	//	printf("%s\n",stmt[i]);	
}

void carps()
{
	int i,j,n,o,index;
	char *posn;
	for(i=0;i<stmtcnt;i++)
	{
		if((posn=strstr(stmt[i],"+"))!=NULL)
		{
			index=stmt[i]-posn;index=-index;
			if(stmt[i][index+1]=='0')
				stmt[i][index]='\0';
		}
		else if((posn=strstr(stmt[i],"-"))!=NULL)
		{
			index=stmt[i]-posn;index=-index;
			if(stmt[i][index+1]=='0')
				stmt[i][index]='\0';
		}
		else if((posn=strstr(stmt[i],"*"))!=NULL)
		{
			index=stmt[i]-posn;index=-index;
			if(stmt[i][index+1]=='1')
				stmt[i][index]='\0';
		}
		else if((posn=strstr(stmt[i],"/"))!=NULL)
		{
			index=stmt[i]-posn;index=-index;
			if(stmt[i][index+1]=='1')
				stmt[i][index]='\0';
		}
		else if((posn=strstr(stmt[i],"^"))!=NULL)
		{
			index=stmt[i]-posn;index=-index;
			if(stmt[i][index+1]=='1')
				stmt[i][index]='\0';
		}
	}
}

main()
{
	int i;
	fp=fopen("input.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%s",str);strcpy(lineno[linenocnt++],str);
		fgets(str,25,fp);
		for(i=0;i<(strlen(str)-1);i++)
			str[i]=str[i+1];
		str[i]='\0';
		strcpy(stmt[stmtcnt++],str);
	}
	fclose(fp);
	linenocnt--;stmtcnt--;
	//for(i=0;i<stmtcnt;i++)
	//	printf("%s%s\n",lineno[i],stmt[i]);
	//printf("\n\n");
	deadcode();
	commsub();
	carps();
	linenocnt=stmtcnt;
	for(i=0;i<stmtcnt;i++)
		printf("%s%s\n",lineno[i],stmt[i]);
}
