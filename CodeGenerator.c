#include<stdio.h>
#include<string.h>

FILE *fp;
char mc[100][100],str[50],rc[5],rr[10],op[5];	//rc stores the count of the registers
int mcnt,rcnt=0,sub=0;

int isnum(char a)
{
	if(a=='0'||a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9')
		return 1;
	else 
		return 0;
}

void handlegoto()
{
	char tmpstr[10];
	int min,res,final;
	fscanf(fp,"%s",str);
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	if(op[0]=='\0')
	{
		//to be filled
		strcat(mc[mcnt],"JMP ");
		//strcat(mc[mcnt],str);
		min=atoi(str);
		res=min-sub;
		res+=4;
		sprintf(tmpstr,"%d",(mcnt+1000+res));
		strcat(mc[mcnt],tmpstr);
	}
	else
	{
		if(!strcmp(op,"<"))
			strcat(mc[mcnt],"JLT ");
	
		else if(!strcmp(op,">"))
			strcat(mc[mcnt],"JGT ");
	
		else if(!strcmp(op,"="))
			strcat(mc[mcnt],"JEQ ");
		//strcat(mc[mcnt],str);
		sprintf(tmpstr,"%d",(mcnt+1000+2));
		strcat(mc[mcnt],tmpstr);
		
	}
	mcnt++;
	fscanf(fp,"%s",str);
	//printf("%s\t",str);
	str[strlen(str)-1]='\0';
	//printf("%s\t",str);
	sub=atoi(str);//printf("%d\n",min);
}

void handleif()
{
	int i=0,j;
	char a[5],b[5];
	fscanf(fp,"%s",str);
	while(str[i]!='<'&&str[i]!='>'&&str[i]!='=')
		a[i]=str[i++];
	a[i]='\0';
	op[0]=str[i];op[1]='\0';
	i++;
	while(i<strlen(str))
		b[j++]=str[i++];
	b[j]='\0';
	//first machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"CMP ");
	strcat(mc[mcnt],a);strcat(mc[mcnt],",");strcat(mc[mcnt],b);	//end of first machine code
	mcnt++;
	fscanf(fp,"%s",str);
	//second machine code
	handlegoto();
}

void handleop()
{
	int i,j;
	char a[10],b[10],c[10];	//operands
	for(i=0;str[i]!='=';i++)
		a[i]=str[i];
	a[i]='\0';
	i++;j=0;
	if(isnum(str[i]))
		b[j++]='#';
	while(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/')
		b[j++]=str[i++];
	b[j]='\0';
	op[0]=str[i];op[1]='\0';
	i++;j=0;
	if(isnum(str[i]))
		c[j++]='#';
	while(str[i]!='\0')
		c[j++]=str[i++];
	c[j]='\0';
	//end of storage of operands
	strcpy(rr,"R");
	if(rcnt==8)
		rcnt=0;
	sprintf(rc,"%d",rcnt++);
	strcat(rr,rc);
	//first machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"MOV ");
	strcat(mc[mcnt],rr);strcat(mc[mcnt],",");strcat(mc[mcnt],b);	//end of first machine code
	mcnt++;
	//second machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	if(!strcmp(op,"+"))
		strcat(mc[mcnt],"ADD ");
	else if(!strcmp(op,"-"))
		strcat(mc[mcnt],"SUB ");
	else if(!strcmp(op,"*"))
		strcat(mc[mcnt],"MUL ");
	else if(!strcmp(op,"/"))
		strcat(mc[mcnt],"DIV ");
	strcat(mc[mcnt],rr);strcat(mc[mcnt],",");strcat(mc[mcnt],c);	//end of second machine code
	mcnt++;
	//third machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"MOV ");
	strcat(mc[mcnt],a);strcat(mc[mcnt],",");strcat(mc[mcnt],rr);	//end of third machine code
	mcnt++;
	fscanf(fp,"%s",str);
}

void handlemov()
{
	int i,j,k;
	char a[10],b[10];
	for(i=0;str[i]!='=';i++)
		a[i]=str[i];
	a[i]='\0';i++;j=0;
	if(isnum(str[i]))
		b[j++]='#';
	while(i<strlen(str))
		b[j++]=str[i++];
	b[j]='\0';
	strcpy(rr,"R");
	if(rcnt==8)
		rcnt=0;
	sprintf(rc,"%d",rcnt++);
	strcat(rr,rc);
	//first machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"MOV ");
	strcat(mc[mcnt],rr);strcat(mc[mcnt],",");strcat(mc[mcnt],b);	//end of first machine code
	mcnt++;
	//second machine code
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"MOV ");
	strcat(mc[mcnt],a);strcat(mc[mcnt],",");strcat(mc[mcnt],rr);	//end of second machine code
	mcnt++;
	fscanf(fp,"%s",str); 
}

void convert2cg()
{
	char tmpstr[20];
	int i,j,flag=0;
	fscanf(fp,"%s",str);
	fscanf(fp,"%s",str);
	while(strcmp(str,"stop")!=0)
	{
		if(!strcmp(str,"if"))
			handleif();
		else if(!strcmp(str,"goto"))
		{
			op[0]='\0';
			handlegoto();
		}
		else
		{
			flag=0;
			for(i=0;i<strlen(str);i++)
			{
				if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
				{	
					flag++;
					handleop();
					break;
				}
			}
			if(flag==0)
				handlemov();
		}
		fscanf(fp,"%s",str);
	}
	sprintf(mc[mcnt],"%d",(mcnt+1000));
	strcat(mc[mcnt],": ");
	strcat(mc[mcnt],"HLT");
}


main()
{
	int i;
	fp=fopen("input.txt","r");
	convert2cg();
	fclose(fp);
	for(i=0;i<=mcnt;i++)
		printf("%s\n",mc[i]);
}
