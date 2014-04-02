#include<stdio.h>
#include<string.h>

struct gotos
{
	char from[5];
	char on[5];
	char dests[20][30];
	char to[5];
	int destcnt;
}gts[50];

struct goac
{
	int from[30];
	char on[30][5];
	int to[30];
	char aog[30][10];	//goto or action
	char sar[30][10];	//shift, accept or reduce(put N if neither)
	int count;
}gc[50];

struct fir
{
	char nont[5];
	char items[20];
	int count;
}first[30];

struct foll
{
	char nont[5];
	char items[20];
	int count;
}follow[30];
	
int gtscnt=0,nop,splcnt=0,splcheck,dcnt=1,splno[20],tos=-1,gcnt=0,firstcnt=0,followcnt=0,accfrom;
char io[10][30],prod[10][30],spl[20][20],stack[50][50];

void push(char *a)
{
	strcpy(stack[++tos],a);
}

void pop()
{
	tos--;
}

void stringparse()
{
	char tmp[5],str[30],str1[10],tmpchar[5],sym[5];
	int flag=1,i=0,conv,tmpno=0,tmpno1,j,k,l;	//tmpno always contains top of stack number
	printf("\nEnter the string to be parsed:");
	scanf("%s",str);
	sprintf(str1,"%d",0);
	push(str1);
	tmpchar[0]=str[i++];
	tmpchar[1]='\0';
	while(1)
	{
		tmpno=atoi(stack[tos]);
		for(j=0;j<gc[tmpno].count;j++)
		{
			flag=2;
			if(!strcmp(tmpchar,gc[tmpno].on[j]))
			{
				flag=1;
				if(!strcmp(gc[tmpno].sar[j],"S"))
				{
					push(tmpchar);
					tmpchar[0]=str[i++];
					tmpchar[1]='\0';
					sprintf(tmp,"%d",gc[tmpno].to[j]);
					push(tmp);
					break;
					//tmpno=atoi(stack[tos]);
				}
				else if(!strcmp(gc[tmpno].sar[j],"R"))
				{
					if(strlen(prod[(gc[tmpno].to[j])-1])<=4)
					{
						pop();
						strcpy(str1,stack[tos]);
						pop();
						str1[0]=prod[(gc[tmpno].to[j])-1][0];
						push(str1);
						tmpno1=atoi(stack[tos-1]);
						for(k=0;k<gc[tmpno1].count;k++)
						{
							if(!strcmp(stack[tos],gc[tmpno1].on[k]))
							{
								sprintf(tmp,"%d",gc[tmpno1].to[k]);
								push(tmp);
								break;
							}
						}
						//tmpchar[0]=str[i++];
						//tmpchar[1]='\0';
						//break;
					}
					else
					{
						printf("\nEntered spl case\n");
						sym[0]=prod[(gc[tmpno].to[j])-1][0];
						sym[1]='\0';
						printf("\n%s\n",sym);
						while(strcmp(stack[tos],sym)!=0)
						{
							printf("\npopping\n");
							pop();
						}
						for(k=0;k<gc[tos-1].count;k++)
						{
							if(!strcmp(stack[tos],gc[tos-1].on[k]))
							{
								sprintf(tmp,"%d",gc[tos-1].to[k]);
								push(tmp);
								break;
							}
						}
						printf("\n%s\n",tmpchar);
						//break;
					}
					break;
				}	
				else if(!strcmp(gc[tmpno].sar[j],"A"))
				{
					printf("\nEnters accepted\n");
					flag=0;break;
				}
			}
		}
		if(flag==2)
		{
			for(i=0;i<=tos;i++)
				printf("%s",stack[i]);
			printf("\nNot Accepted\n");
			break;
		}
		else if(flag==0)
		{
			printf("\nAccpted\n");
			break;
		}
				
	}
}
void firs()
{
	int i,j,k,l,m,ntcnt=0,flag;
	char nt[10],tmpstr[10];
	for(i=0;i<(nop-1);i++)	//stores list of non-terminals
	{
		if(i==0)
			nt[ntcnt++]=prod[i][0];
		else
		{
			flag=0;
			for(j=0;j<ntcnt;j++)
			{
				if(nt[j]==prod[i][0])
				{
					flag++;break;
				}
			}
			if(flag==0)
				nt[ntcnt++]=prod[i][0];
		}
	}
	printf("\nNon terminals are\n");
	for(i=0;i<ntcnt;i++)
		printf("%c\n",nt[i]);
	//generation of first for all non terminals
	for(i=(ntcnt-1);i>=0;i--)
	{
		first[firstcnt].count=0;
		first[firstcnt].nont[0]=nt[i];
		first[firstcnt].nont[1]='\0';
		for(j=0;j<(nop-1);j++)
		{
			if(nt[i]==prod[j][0])
			{
				if(isupper(prod[j][3]))
				{
					tmpstr[0]=prod[j][3];
					tmpstr[1]='\0';
					for(l=0;l<firstcnt;l++)
					{
						if(!strcmp(tmpstr,first[l].nont))
						{
							for(k=0;k<first[l].count;k++)
							{
								flag=0;
								for(m=0;m<first[firstcnt].count;m++)
								{
									if(first[l].items[k]==first[firstcnt].items[m])
									{
										flag++;break;
									}
								}
								if(flag==0)
									first[firstcnt].items[first[firstcnt].count++]=first[l].items[k];
							}
						}
					}
									
				}
				else
				{
					flag=0;
					for(k=0;k<first[firstcnt].count;k++)
					{
						if(prod[j][3]==first[firstcnt].items[k])
						{
							flag++;break;
						}
					}
					if(flag==0)
						first[firstcnt].items[first[firstcnt].count++]=prod[j][3];
				}
			}
		}
		first[firstcnt].items[first[firstcnt].count]='\0';
		firstcnt++;
	}
	printf("\nFirst of non terminals\n");
	for(i=0;i<firstcnt;i++)
	{
		printf("%s\t%s\n",first[i].nont,first[i].items);
	}
}

void follo()
{
	int i,j,k,l,m,n,ntcnt=0,flag,flag1;
	char nt[10],tmpstr[10];
	for(i=0;i<(nop-1);i++)	//stores list of non-terminals
	{
		if(i==0)
			nt[ntcnt++]=prod[i][0];
		else
		{
			flag=0;
			for(j=0;j<ntcnt;j++)
			{
				if(nt[j]==prod[i][0])
				{
					flag++;break;
				}
			}
			if(flag==0)
				nt[ntcnt++]=prod[i][0];
		}
	}
	//generate follow
	for(i=0;i<ntcnt;i++)
	{
		follow[followcnt].count=0;
		follow[followcnt].nont[0]=nt[i];
		follow[followcnt].nont[1]='\0';
		if(i==0)
			follow[followcnt].items[follow[followcnt].count++]='$';
		for(j=0;j<(nop-1);j++)
		{
			flag=0;
			for(k=3;k<strlen(prod[j]);k++)
			{
				if(prod[j][k]==nt[i])
				{
					flag++;break;
				}
			}
			if(flag!=0)
			{
				if(!(isupper(prod[j][k+1]))&&(prod[j][k+1]!='\0'))
					follow[followcnt].items[follow[followcnt].count++]=prod[j][k+1];
				else if(isupper(prod[j][k+1]))
				{
					tmpstr[0]=prod[j][k+1];
					tmpstr[1]='\0';
					for(l=0;l<firstcnt;l++)
					{
						if(!strcmp(first[l].nont,tmpstr))
						{
							for(m=0;m<first[l].count;m++)
							{
								flag1=0;
								for(n=0;n<follow[followcnt].count;n++)
								{
									if(follow[followcnt].items[n]==first[l].items[m])
									{
										flag1++;break;
									}
								}
								if(flag1==0)
									follow[followcnt].items[follow[followcnt].count++]=first[l].items[m];
							}
						}
					}
				}
				else if(prod[j][k+1]=='\0')
				{
					tmpstr[0]=prod[j][0];
					tmpstr[1]='\0';
					for(k=0;k<followcnt;k++)
					{
						if(!strcmp(tmpstr,follow[k].nont))
							break;
					}
					for(l=0;l<follow[k].count;l++)
					{
						flag1=0;
						for(m=0;m<follow[followcnt].count;m++)
						{
							if(follow[k].items[l]==follow[followcnt].items[m])
							{
								flag1++;break;
							}
						}
						if(flag1==0)
							follow[followcnt].items[follow[followcnt].count++]=follow[k].items[l];
					}
				}
			}
		}
		follow[followcnt].items[follow[followcnt].count]='\0';
		followcnt++;
	}
	printf("\n\nFollow of non terminals\n");
	for(i=0;i<followcnt;i++)
	{
		printf("%s\t%s\n",follow[i].nont,follow[i].items);
	}
}

void table()
{
	//part of table info already generated in fillgts function
	int i,j,k,l,m,flag,redno;
	char tmpstr[20],tmpstr1[5];
	gc[gcnt].count=0;
	for(i=0;i<gtscnt;i++)
	{
		if(atoi(gts[i].from)==0)
		{
			gc[gcnt].from[gc[gcnt].count]=0;
			strcpy(gc[gcnt].on[gc[gcnt].count],gts[i].on);
			gc[gcnt].to[gc[gcnt].count]=atoi(gts[i].to);
			if(isupper(gc[gcnt].on[gc[gcnt].count][0]))
			{
				strcpy(gc[gcnt].aog[gc[gcnt].count],"goto");
				strcpy(gc[gcnt].sar[gc[gcnt].count],"N");
			}
			else
			{
				strcpy(gc[gcnt].aog[gc[gcnt].count],"action");
				strcpy(gc[gcnt].sar[gc[gcnt].count],"S");
			}
			gc[gcnt].count++;
		}
	}
	gcnt++;
	for(i=0;i<gtscnt;i++)
	{
		gc[gcnt].count=0;
		for(j=0;j<gts[i].destcnt;j++)
		{
			if(gts[i].dests[j][strlen(gts[i].dests[j])-1]=='.')
			{
				//to be filled after finding follow
				if(gts[i].dests[j][1]=='\'')
				{
					gc[gcnt].from[gc[gcnt].count]=accfrom=(i+1);
					gc[gcnt].on[gc[gcnt].count][0]='$';
					gc[gcnt].on[gc[gcnt].count][1]='\0';
					gc[gcnt].to[gc[gcnt].count]=0;	//0 assigned to a to represents an accept
					strcpy(gc[gcnt].aog[gc[gcnt].count],"action");
					strcpy(gc[gcnt].sar[gc[gcnt].count],"A");
					gc[gcnt].count++;
				}
				else
				{
					strcpy(tmpstr,gts[i].dests[j]);
					tmpstr[strlen(tmpstr)-1]='\0';
					tmpstr1[0]=tmpstr[0];
					tmpstr1[1]='\0';
					for(k=0;k<(nop-1);k++)
					{
						if(!strcmp(prod[k],tmpstr))
						{
							redno=(k+1);
							break;
						}
					}
					for(k=0;k<followcnt;k++)
					{
						if(!strcmp(tmpstr1,follow[k].nont))
						{
							for(l=0;l<follow[k].count;l++)
							{
								gc[gcnt].from[gc[gcnt].count]=(i+1);
								gc[gcnt].on[gc[gcnt].count][0]=follow[k].items[l];
								gc[gcnt].on[gc[gcnt].count][1]='\0';
								gc[gcnt].to[gc[gcnt].count]=redno;
								strcpy(gc[gcnt].aog[gc[gcnt].count],"action");
								strcpy(gc[gcnt].sar[gc[gcnt].count],"R");
								gc[gcnt].count++;
							}
							break;
						}
					}
				}
			}
			else
			{
				strcpy(tmpstr,gts[i].dests[j]);
				for(k=0;tmpstr[k]!='.';k++)
				{}
				tmpstr[k]=tmpstr[k+1];
				tmpstr[k+1]='.';
				flag=0;
				for(l=0;l<gtscnt;l++)
				{
					if(!strcmp(gts[l].dests[0],tmpstr))
					{
						gc[gcnt].from[gc[gcnt].count]=(i+1);
						gc[gcnt].on[gc[gcnt].count][0]=tmpstr[k];
						gc[gcnt].on[gc[gcnt].count][1]='\0';
						gc[gcnt].to[gc[gcnt].count]=(l+1);
						if(isupper(gc[gcnt].on[gc[gcnt].count][0]))
						{
							strcpy(gc[gcnt].aog[gc[gcnt].count],"goto");
							strcpy(gc[gcnt].sar[gc[gcnt].count],"N");
						}
						else
						{
							strcpy(gc[gcnt].aog[gc[gcnt].count],"action");
							strcpy(gc[gcnt].sar[gc[gcnt].count],"S");
						}
						gc[gcnt].count++;	
					}
				}
			}
		}
		gcnt++;
	}
	//to display the table generated up until now
	printf("\n\n");
	for(i=0;i<gcnt;i++)
	{
		for(j=0;j<gc[i].count;j++)
		{
			printf("%s(%d,%s)=%s%d\n",gc[i].aog[j],gc[i].from[j],gc[i].on[j],gc[i].sar[j],gc[i].to[j]);
		}
		printf("\n");
	}
}
void fillgts()
{
	int i,count=1,j,k,l,m,n,o,flag,flag1;char no[5];
	char iotc[10],tmpstr[30],tmpstr1[30],spltmpstr1[10];int iotcnt=0;//stores characters after dots from augmented grammar
	char spltmpstr[10],splchar;//to maintain record of expanded productions
	int spltmpstrcnt,splflag=0;
	for(i=0;i<nop;i++)
	{
		flag=0;
		for(j=0;io[i][j]!='.';j++)
		{}
		j++;
		for(k=0;k<iotcnt;k++)
		{
			if(iotc[k]==io[i][j])
			{
				flag++;break;
			}
		}
		if(flag==0)
			iotc[iotcnt++]=io[i][j];
	}//characters after dots from i0 storage complete
	printf("\n");
	for(i=0;i<iotcnt;i++)
		printf("%c\n",iotc[i]);
	//calculating successive i* values
	for(i=0;i<iotcnt;i++)
	{
		sprintf(gts[gtscnt].from,"%d",0);
		gts[gtscnt].on[0]=iotc[i];
		gts[gtscnt].on[1]='\0';
		sprintf(gts[gtscnt].to,"%d",dcnt);
		dcnt++;
		gts[gtscnt].destcnt=0;
		for(j=0;j<nop;j++)
		{
			for(k=0;k<strlen(io[j]);k++)
			{
				spltmpstrcnt=0;
				if(io[j][k]=='.'&&io[j][k+1]==iotc[i])
				{
					strcpy(tmpstr,io[j]);	//shifting the dot and storing
					tmpstr[k]=tmpstr[k+1];
					tmpstr[k+1]='.';
					strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],tmpstr);
					if(isupper(tmpstr[k+2]))	//Expanding production of not already expanded
					{
						printf("\nEnters\n");
						strcpy(spl[splcnt],tmpstr);
						splno[splcnt++]=atoi(gts[gtscnt].to);
						printf("%s\n",tmpstr);
						if(spltmpstrcnt==0)
						{
							printf("\nEnters1\n");
							l=1;
							splchar=spltmpstr[spltmpstrcnt++]=tmpstr[k+2];
							while(1)
							{
								for(m=1;m<nop;m++)
								{
									if(io[m][0]==splchar)
									{
										strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],io[m]);
										if(io[m][4]!=io[m][0]&&isupper(io[m][4]))
											spltmpstr[spltmpstrcnt++]=io[m][4];
									}
								}
								if(l==(spltmpstrcnt))
									break;
								else
									splchar=spltmpstr[l++];
							}
						}
						else
						{
							printf("\nENters\n");
							flag=1;
							for(l=0;l<spltmpstrcnt;l++)
							{
								if(tmpstr[k+2]==spltmpstr[l])
									flag=0;
							}
							if(flag==1)
							{
								splchar=spltmpstr[spltmpstrcnt++]=tmpstr[k+2];
								while(1)
								{
									for(m=1;m<nop;m++)
									{
										if(io[m][0]==splchar)
										{
											strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],io[m]);
											if(io[m][4]!=io[m][0]&&isupper(io[m][4]))
											{
												flag1=0;
												for(n=0;n<spltmpstrcnt;n++)
												{
													if(io[m][4]==spltmpstr[n])
														flag1++;
												}
												if(flag1==0)
													spltmpstr[spltmpstrcnt++]=io[m][4];
											}
										}
									}
									if(l==spltmpstrcnt)
										break;
									else
										splchar=spltmpstr[l++];
								}
							}
						}		
					}
					else if(tmpstr[k+2]!='\0')
					{
						strcpy(spl[splcnt],tmpstr);
						splno[splcnt++]=atoi(gts[gtscnt].to);
					}	
				}
			}
		}
		gtscnt++;
	}
	for(i=0;i<gtscnt;i++)
	{
		printf("%s,%s\t%s\n",gts[i].from,gts[i].on,gts[i].to);
		for(j=0;j<gts[i].destcnt;j++)
		{
			printf("%s\n",gts[i].dests[j]);
		}
	}
	printf("\n\n");
	for(i=0;i<splcnt;i++)
	{
		printf("%s\n",spl[i]);
	}
	printf("%d\n",dcnt);
	while(1)
	{
		for(i=0;i<splcnt;i++)
		{
			spltmpstrcnt=0;
			for(k=0;spl[i][k]!='.';k++)
			{}
			if(spl[i][k+1]!='\0')
			{
				spl[i][k]=spl[i][k+1];
				spl[i][k+1]='.';
				strcpy(tmpstr,spl[i]);
				sprintf(gts[gtscnt].from,"%d",splno[i]);
				gts[gtscnt].on[0]=spl[i][k];
				gts[gtscnt].on[1]='\0';
				sprintf(gts[gtscnt].to,"%d",dcnt);
				gts[gtscnt].destcnt=0;
				strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],tmpstr);
				printf("\n\nspecial\n\n");
				printf("%s\t%s\n",spl[i],gts[splno[i]-1].dests[0]);
				for(j=1;j<gts[splno[i]-1].destcnt;j++)
				{
					for(l=0;l<strlen(gts[splno[i]-1].dests[j]);l++)
					{
						if(gts[splno[i]-1].dests[j][l]=='.'&&gts[splno[i]-1].dests[j][l+1]==spl[i][k])
						{
							strcpy(tmpstr1,gts[splno[i]-1].dests[j]);
							tmpstr1[l]=tmpstr1[l+1];
							tmpstr1[l+1]='.';
							if(strcmp(gts[gtscnt].dests[(gts[gtscnt].destcnt)-1],tmpstr1)!=0)
								strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],tmpstr1);
							break;
						}
					}
				}
				splno[i]=dcnt;
				dcnt++;
				if(isupper(tmpstr[k+2]))
				{
					if(spltmpstrcnt==0)
					{
						printf("\nEnters1\n");
						l=1;
						splchar=spltmpstr[spltmpstrcnt++]=tmpstr[k+2];
						while(1)
						{
							for(m=1;m<nop;m++)
							{
								if(io[m][0]==splchar)
								{
									strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],io[m]);
									if(io[m][4]!=io[m][0]&&isupper(io[m][4]))
										spltmpstr[spltmpstrcnt++]=io[m][4];
								}
							}
							if(l==(spltmpstrcnt))
								break;
							else
								splchar=spltmpstr[l++];
						}
					}
					else
					{
						printf("\nENters\n");
						flag=1;
						for(l=0;l<spltmpstrcnt;l++)
						{
							if(tmpstr[k+2]==spltmpstr[l])
								flag=0;
						}
						if(flag==1)
						{
							splchar=spltmpstr[spltmpstrcnt++]=tmpstr[k+2];
							while(1)
							{
								for(m=1;m<nop;m++)
								{
									if(io[m][0]==splchar)
									{
										strcpy(gts[gtscnt].dests[gts[gtscnt].destcnt++],io[m]);
										if(io[m][4]!=io[m][0]&&isupper(io[m][4]))
										{
											flag1=0;
											for(n=0;n<spltmpstrcnt;n++)
											{
												if(io[m][4]==spltmpstr[n])
													flag1++;
											}
											if(flag1==0)
												spltmpstr[spltmpstrcnt++]=io[m][4];
										}
									}
								}
								if(l==spltmpstrcnt)
									break;
								else
									splchar=spltmpstr[l++];
							}
						}
					}		
				}
			}
			gtscnt++;	
		}
		splflag=0;
		for(i=0;i<splcnt;i++)
		{
			for(j=0;spl[i][j]!='.';j++)
			{}
			if(spl[i][j+1]!='\0')
			{
				splflag++;
				break;
			}
		}
		if(splflag==0)
			break;
		else
			printf("\nDoesnt break\n");
	}
	printf("\n\n%d\n\n",dcnt);
	for(i=0;i<gtscnt;i++)
	{
		printf("\n\n%s,%s\t%s\n",gts[i].from,gts[i].on,gts[i].to);
		for(j=0;j<gts[i].destcnt;j++)
		{
			printf("%s\n",gts[i].dests[j]);
		}
	}		
}

main()
{
	int i,j,k,l=0;
	printf("\nEnter the number of productions:");
	scanf("%d",&nop);
	for(i=0;i<nop;i++)
	{
		printf("\nProduction %d:",i+1);
		scanf("%s",prod[i]);
	}
	nop++;
	//calculating io(Augmented grammar)
	for(i=0;i<nop;i++)
	{
		if(i==0)
			strcpy(io[i],"E'->.E");
		else
		{
			k=0;
			for(j=0;prod[l][j]!='>';j++)
			{
				io[i][k++]=prod[l][j];
			}
			io[i][k++]=prod[l][j++];
			io[i][k++]='.';
			while(j<strlen(prod[l]))
				io[i][k++]=prod[l][j++];
			io[i][k]='\0';
			l++;
		}
	}
	//Augmented grammar ends
	printf("\nAugmented Grammar\n");
	for(i=0;i<nop;i++)
		printf("%s\n",io[i]);
	firs();
	follo();
	fillgts();
	table();
	stringparse();
}
