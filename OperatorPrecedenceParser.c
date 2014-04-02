#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct leading
{
	char nont[10];
	char leadi[10][10];
	int leadd1;
}lead[10];

struct trailing
{
	char nont1[10];
	char traili[10][10];
	int traill1;
}trail[10];

struct less
{
	char lhsl[10];
	char rhsl[10][10];
	int rlcount;
}lesst[10];

struct great
{
	char lhsg[10][10];
	char rhsg[10];
	int  lgcount;
}greatt[10];

struct equal
{
	char lhse[10];
	char rhse[10];
}equalt[10];

int non=1,leadd=0,traill=0,point[10],pt=0,lcount=0,gcount=0,ecount=0;;
FILE *fp,*fp1;
char str[50];

void parse()
{
	int tos=0,aflag=0,flag=0,flag1=0,gflag=0,i,j,k;
	char stack[20][20],str[20],cmpstr1[10],cmpstr2[10];
	FILE *fp2;
	strcpy(stack[tos++],"$");
	fp2=fopen("string.txt","r");
	while(1)
	{
		flag=0;flag1=0;
		fscanf(fp2,"%s",str);
		strcpy(cmpstr1,stack[tos-1]);
		strcpy(cmpstr2,str);
		if(!strcmp(cmpstr1,"$")&&!strcmp(cmpstr2,"$"))
			break;
		for(i=0;i<lcount;i++)
		{
			if(!strcmp(cmpstr1,lesst[i].lhsl))
			{
				flag++;
				for(j=0;j<lesst[i].rlcount;j++)
				{
					if(!strcmp(cmpstr2,lesst[i].rhsl[j]))
					{
						flag1++;
						strcpy(stack[tos++],str);
						break;
					}
				}
				break;
			}
		}
		if(flag==0||flag1==0)
		{
			flag=0;flag1=0;
			for(i=0;i<ecount;i++)
			{
				if(!strcmp(cmpstr1,equalt[i].lhse)&&!strcmp(cmpstr2,equalt[i].rhse))
				{
					flag++;flag1++;
					strcpy(stack[tos++],str);
				}
			}
		}
		if(flag==0||flag1==0)
		{
			flag=0;flag1=0;
			for(i=0;i<gcount;i++)
			{
				if(!strcmp(cmpstr2,greatt[i].rhsg))
				{
					flag1++;
					for(j=0;j<greatt[i].lgcount;j++)
					{
						if(!strcmp(cmpstr1,greatt[i].lhsg[j]))
						{
							flag++;
							tos--;
							break;
						}
					}
					break;
				}
			}
		}
		if(flag==0||flag1==0)
		{
			aflag++;
			break;
		}
	}
	if(aflag==0)
		printf("\n\nAccepted\n\n");
	else
		printf("\n\nNot Accepted\n\n");
}

void final()
{
	int i,t,j,flag;
	char str1[5],str2[5];
	lesst[lcount].rlcount=0;
	strcpy(lesst[lcount].lhsl,"$");
	for(t=0;t<lead[0].leadd1;t++)
	{
		strcpy(lesst[lcount].rhsl[(lesst[lcount].rlcount)++],lead[0].leadi[t]);
	}
	lcount++;
	for(i=0;i<pt;i++)
	{
		flag=0;
		fseek(fp,point[i],SEEK_SET);
		for(t=0;t<3;t++)
			fscanf(fp,"%s",str);
		for(j=0;j<strlen(str)&&str[j]!='|';j++)
		{
			if((str[j]=='+'||str[j]=='-'||str[j]=='*'||str[j]=='/'||str[j]=='('||str[j]==')')&&isupper(str[j+1]))
			{
				flag++;
				str1[0]=str[j];
				str1[1]='\0';
				str2[0]=str[j+1];
				str2[1]='\0';
				break;
			}
		}
		if(flag!=0)
		{
			strcpy(lesst[lcount].lhsl,str1);
			lesst[lcount].rlcount=0;
			for(j=0;j<leadd;j++)
			{
				if(!strcmp(str2,lead[j].nont))
				{
					for(t=0;t<lead[j].leadd1;t++)
					{
						strcpy(lesst[lcount].rhsl[(lesst[lcount].rlcount)++],lead[j].leadi[t]);
					}
					break;
				}
			}
			lcount++;
		}
	}
	greatt[gcount].lgcount=0;
	strcpy(greatt[gcount].rhsg,"$");
	for(t=0;t<trail[0].traill1;t++)
	{
		strcpy(greatt[gcount].lhsg[(greatt[gcount].lgcount)++],trail[0].traili[t]);
	}
	gcount++;
	for(i=0;i<pt;i++)
	{
		flag=0;
		fseek(fp,point[i],SEEK_SET);
		for(t=0;t<3;t++)
			fscanf(fp,"%s",str);
		for(j=0;j<strlen(str)&&str[j]!='|';j++)
		{
			if((str[j+1]=='+'||str[j+1]=='-'||str[j+1]=='*'||str[j+1]=='/'||str[j+1]=='('||str[j+1]==')')&&isupper(str[j]))
			{
				flag++;
				str1[0]=str[j];
				str1[1]='\0';
				str2[0]=str[j+1];
				str2[1]='\0';
				break;
			}
		}
		if(flag!=0)
		{
			strcpy(greatt[gcount].rhsg,str2);
			greatt[gcount].lgcount=0;
			for(j=0;j<traill;j++)
			{
				if(!strcmp(str1,trail[j].nont1))
				{
					for(t=0;t<trail[j].traill1;t++)
					{
						strcpy(greatt[gcount].lhsg[(greatt[gcount].lgcount)++],trail[j].traili[t]);
					}
					break;
				}
			}
			gcount++;
		}
	}
	for(i=0;i<pt;i++)
	{
		flag=0;
		fseek(fp,point[i],SEEK_SET);
		for(t=0;t<3;t++)
			fscanf(fp,"%s",str);
		for(j=0;j<strlen(str)&&str[j+2]!='|';j++)
		{
			if((str[j]=='+'||str[j]=='-'||str[j]=='*'||str[j]=='/'||str[j]=='('||str[j]==')')&&isupper(str[j+1])&&(str[j+2]=='+'||str[j+2]=='-'||str[j+2]=='*'||str[j+2]=='/'||str[j+2]=='('||str[j+2]==')'))
			{
				flag++;
				str1[0]=str[j];str1[1]='\0';
				str2[0]=str[j+2];str2[1]='\0';
				break;
			}
		}
		if(flag!=0)
		{
			strcpy(equalt[ecount].lhse,str1);
			strcpy(equalt[ecount].rhse,str2);
			ecount++;
		}
	}
}		
void leading()
{
	int i,j,k,l,count,mcount,count1,mcount1,m,j1;
	char tmpstr[20],tmpstr1[20],rtmpstr[20],sptmpstr[20];
	fp=fopen("input.txt","r");
	for(i=0;i<pt;i++)
	{
		count=0;mcount=0;k=0,m=0;
		fseek(fp,point[i],SEEK_SET);
		fscanf(fp,"%s",str);
		strcpy(lead[leadd].nont,str);
		lead[leadd].leadd1=0;
		fscanf(fp,"%s",str);
		fscanf(fp,"%s",str);
		for(j=0;j<strlen(str);j++)
		{
			if(str[j]=='|')
				count++;
		}
		if(count>0)
		{
			j=0;
			while(mcount<=count)
			{
				k=0;
				for(;(str[j]!='|')&&(j<strlen(str));j++)
				{
					tmpstr[k++]=str[j];
				}
				tmpstr[k]='\0';
				if(strlen(tmpstr)==3)
				{
					if(islower(tmpstr[1])||tmpstr[1]=='+'||tmpstr[1]=='-'||tmpstr[1]=='*'||tmpstr[1]=='/'||tmpstr[1]=='('||tmpstr[1]==')')
					{
						tmpstr1[0]=tmpstr[1];tmpstr1[1]='\0';
					}
					else if(isupper(tmpstr[1]))
					{
						tmpstr1[0]=tmpstr[0];tmpstr1[1]='\0';
					}
					strcpy(lead[leadd].leadi[(lead[leadd].leadd1)++],tmpstr1);	
				}
				else if(islower(tmpstr[0]))
				{
					strcpy(lead[leadd].leadi[(lead[leadd].leadd1)++],tmpstr);
				}
				else if(strlen(tmpstr)==1&&isupper(tmpstr[0]))
				{
					a:
					for(l=0;l<pt;l++)
					{
						fseek(fp,point[l],SEEK_SET);
						fscanf(fp,"%s",sptmpstr);
						if(!strcmp(tmpstr,sptmpstr))
							break;
					}
					fscanf(fp,"%s",sptmpstr);
					fscanf(fp,"%s",sptmpstr);
					l=0;count1=0;mcount1=0;
					for(m=0;m<strlen(sptmpstr);m++)
					{
						if(sptmpstr[m]=='|')
							count1++;
					}
					if(count1>0)
					{
						j1=0;
						while(mcount1<=count1)
						{
							k=0;
							for(;(sptmpstr[j1]!='|')&&(j1<strlen(sptmpstr));j1++)
							{
								tmpstr[k++]=sptmpstr[j1];
							}
							tmpstr[k]='\0';
							if(strlen(tmpstr)==3)
							{
								if(islower(tmpstr[1])||tmpstr[1]=='+'||tmpstr[1]=='-'||tmpstr[1]=='*'||tmpstr[1]=='/'||tmpstr[1]=='('||tmpstr[1]==')')
								{
									tmpstr1[0]=tmpstr[1];tmpstr1[1]='\0';
								}
								else if(isupper(tmpstr[1]))
								{
									tmpstr1[0]=tmpstr[0];tmpstr1[1]='\0';
								}
								strcpy(lead[leadd].leadi[(lead[leadd].leadd1)++],tmpstr1);	
							}
							else if(islower(tmpstr[0]))
							{
								strcpy(lead[leadd].leadi[(lead[leadd].leadd1)++],tmpstr);
							}
							else if(strlen(tmpstr)==1&&isupper(tmpstr[0]))
								goto a;
							mcount1++;j1++;
						}
					}
					else
					{
					}
				}
				mcount++;j++;
			}
		}
		else
		{
		}
		leadd++;
	}
}

void trailing()
{
	int i,j,k,l,count,mcount,count1,mcount1,m,j1;
	char tmpstr[20],tmpstr1[20],rtmpstr[20],sptmpstr[20];
	fp=fopen("input.txt","r");
	for(i=0;i<pt;i++)
	{
		count=0;mcount=0;k=0,m=0;
		fseek(fp,point[i],SEEK_SET);
		fscanf(fp,"%s",str);
		strcpy(trail[traill].nont1,str);
		trail[traill].traill1=0;
		fscanf(fp,"%s",str);
		fscanf(fp,"%s",str);
		for(j=0;j<strlen(str);j++)
		{
			if(str[j]=='|')
				count++;
		}
		if(count>0)
		{
			j=0;
			while(mcount<=count)
			{
				k=0;
				for(;(str[j]!='|')&&(j<strlen(str));j++)
				{
					tmpstr[k++]=str[j];
				}
				tmpstr[k]='\0';
				if(strlen(tmpstr)==3)
				{
					if(islower(tmpstr[1])||tmpstr[1]=='+'||tmpstr[1]=='-'||tmpstr[1]=='*'||tmpstr[1]=='/'||tmpstr[1]=='('||tmpstr[1]==')')
					{
						tmpstr1[0]=tmpstr[1];tmpstr1[1]='\0';
					}
					else if(isupper(tmpstr[1]))
					{
						tmpstr1[0]=tmpstr[2];tmpstr1[1]='\0';
					}
					strcpy(trail[traill].traili[(trail[traill].traill1)++],tmpstr1);	
				}
				else if(islower(tmpstr[0]))
				{
					strcpy(trail[traill].traili[(trail[traill].traill1)++],tmpstr);
				}
				else if(strlen(tmpstr)==1&&isupper(tmpstr[0]))
				{
					a:
					for(l=0;l<pt;l++)
					{
						fseek(fp,point[l],SEEK_SET);
						fscanf(fp,"%s",sptmpstr);
						if(!strcmp(tmpstr,sptmpstr))
							break;
					}
					fscanf(fp,"%s",sptmpstr);
					fscanf(fp,"%s",sptmpstr);
					l=0;count1=0;mcount1=0;
					for(m=0;m<strlen(sptmpstr);m++)
					{
						if(sptmpstr[m]=='|')
							count1++;
					}
					if(count1>0)
					{
						j1=0;
						while(mcount1<=count1)
						{
							k=0;
							for(;(sptmpstr[j1]!='|')&&(j1<strlen(sptmpstr));j1++)
							{
								tmpstr[k++]=sptmpstr[j1];
							}
							tmpstr[k]='\0';
							if(strlen(tmpstr)==3)
							{
								if(islower(tmpstr[1])||tmpstr[1]=='+'||tmpstr[1]=='-'||tmpstr[1]=='*'||tmpstr[1]=='/'||tmpstr[1]=='('||tmpstr[1]==')')
								{
									tmpstr1[0]=tmpstr[1];tmpstr1[1]='\0';
								}
								else if(isupper(tmpstr[1]))
								{
									tmpstr1[0]=tmpstr[2];tmpstr1[1]='\0';
								}
								strcpy(trail[traill].traili[(trail[traill].traill1)++],tmpstr1);	
							}
							else if(islower(tmpstr[0]))
							{
								strcpy(trail[traill].traili[(trail[traill].traill1)++],tmpstr);
							}
							else if(strlen(tmpstr)==1&&isupper(tmpstr[0]))
								goto a;
							mcount1++;j1++;
						}
					}
					else
					{
					}
				}
				mcount++;j++;
			}
		}
		else
		{
		}
		traill++;
	}
}

main()
{
	int flag=0,i,j;
	fp=fopen("input.txt","r");
	point[pt++]=ftell(fp);
	fscanf(fp,"%s",str);
	while(1)
	{
		for(i=0;i<2;i++)
		{
			fscanf(fp,"%s",str);
		}
		point[pt++]=ftell(fp);
		fscanf(fp,"%s",str);
		if(feof(fp))
			break;
	}
	pt--;
	leading();
	trailing();
	final();
	printf("\nLeading of the non-terminals\n");
	for(i=0;i<leadd;i++)
	{
		printf("\n%s",lead[i].nont);
		for(j=0;j<lead[i].leadd1;j++)
		{
			printf("\t%s\n",lead[i].leadi[j]);
		}
	}
	printf("\nTrailing of the non-terminals\n");
	for(i=0;i<traill;i++)
	{
		printf("\n%s",trail[i].nont1);
		for(j=0;j<trail[i].traill1;j++)
		{
			printf("\t%s\n",trail[i].traili[j]);
		}
	}
	printf("\nless than...\n");
	for(i=0;i<lcount;i++)
	{
		for(j=0;j<lesst[i].rlcount;j++)
		{
			printf("%s",lesst[i].lhsl);
			printf("\t<\t%s\n",lesst[i].rhsl[j]);
		}
	}
	printf("\ngreater than...\n");
	for(i=0;i<gcount;i++)
	{
		for(j=0;j<greatt[i].lgcount;j++)
		{
				printf("%s\t>\t",greatt[i].lhsg[j]);
				printf("%s\n",greatt[i].rhsg);
		}
	}
	printf("\nEqual to...\n");
	for(i=0;i<ecount;i++)
	{
		printf("%s\t=\t%s\n",equalt[i].lhse,equalt[i].rhse);
	}
	parse();
	fclose(fp);
}
