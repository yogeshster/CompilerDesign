#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

main()
{
	FILE *fp,*fp1,*fp2,*fp3;
	int flagop,flagsp1,classc=0,sym=0,i,j,k,l,flagsp,count,flag,flag1,flag2;
	char splfinal[50],classn[50][50],spl[50],stab[50][50],op[10],str[50],str1[50],str2[50],str3[50],dup[50],temp[10];
	fp=fopen("input.cpp","r");
	fscanf(fp,"%s",str);
	fp2=fopen("symtab.txt","w");
	fprintf(fp2,"Symbols(or functions)\tdata type(or no.of arguments)\n");
	while(!feof(fp))
	{
		//fscanf(fp,"%s",str);
		if(str[0]=='#')//Checking preprocessor directive
		{
			printf("%s\tPreprocessor Directive\n",str);goto a1;
		}

		//Check keyword
		{
			flag=0;flag1=0;
			if(str[strlen(str)-1]==':')
			{
				str[strlen(str)-1]='\0';
				flag=1;
			}
			fp1=fopen("keywords.txt","r");
			while(!feof(fp1))
			{
				fscanf(fp1,"%s",str1);
				if(!strcmp(str,str1))
				{
					flag1++;
					printf("%s\tKeyword\n",str);
					//fclose(fp1);
					if(flag!=0)
						printf(":\tspecial character\n");
					//goto a1;
				}
			}
			if(!strcmp(str,"if"))
			{
				j=0;flagsp=0;flagsp1=0;
				fscanf(fp,"%s",str);
				printf("(\tSpecial Character\n");i=1;
				while(isalpha(str[i]))
				{
					dup[j++]=str[i++];
				}
				dup[j]='\0';
				if(isalpha(dup[0]))
					printf("%s\tIdentifier\n",dup);
				else
					printf("%s\tInvalid Identifier\n",dup);
				j=0;
				op[j++]=str[i++];
				op[j]='\0';
				fp3=fopen("operators.txt","r");
				fscanf(fp3,"%s",str1);
				while(!feof(fp3))
				{
					if(isalpha(str1[0]))
						strcpy(splfinal,str1);
					if(!strcmp(op,str1))
					{
						printf("%s\t%s Operator\n",op,splfinal);break;
					}
					fscanf(fp3,"%s",str1);
				}
				fclose(fp3);
				j=0;
				while(i<(strlen(str)-1))
					dup[j++]=str[i++];
				dup[j]='\0';
				for(i=0;i<strlen(dup);i++)
				{
					if(isalpha(dup[i]))
						flagsp++;
					else
						flagsp1++;
				}
				if(flagsp!=0&&flagsp1!=0)
				{
					if(!isalpha(dup[0]))
						printf("%s\tInvalid Identifier\n",dup);
				}
				else if(flagsp!=0)
				{
					printf("%s\tIdentifier\n",dup);
				}
				else
					printf("%s\tConstant\n",dup);
				printf(")\tSpecial Character\n");
			}				
			else if(!strcmp(str,"return"))
			{
				fscanf(fp,"%s",str);str[strlen(str)-1]='\0';
				if(str[0]=='(')
				{
					i=1;
					printf("(\tSpecial Character\n");
					while(1)
					{
						if(isalpha(str[i]))
							printf("%c",str[i]);
						else if(!isalpha(str[i])&&str[i]!=')')
						{
							temp[0]=str[i];
							temp[1]='\0';
							//printf("\n%s\n",temp);
							fp3=fopen("operators.txt","r");flag2=0;
							fscanf(fp3,"%s",str1);
							while(!feof(fp3))
							{
								if(isalpha(str1[0]))
									strcpy(splfinal,str1);
								if(!strcmp(temp,str1))
								{
									flag2++;break;
								}
								fscanf(fp3,"%s",str1);
							}
							fclose(fp3);
							if(flag2==0)
								printf("\tIdentifier\n,\tSpecial Character\n");
							else
								printf("\tIdentifier\n%s\t%s Operator\n",temp,splfinal);
						}
						else if(str[i]==')')
						{
							printf("\tIdentifier\n)\tSpecial Character\n");
							break;
						}
						i++;
					}
				}
				else if(isalpha(str[0]))
					printf("%s\tIdentifier\n",str);
				else
					printf("%s\tConstant\n",str);
				printf(";\tSpecial Character\n");
			}
			else if((!strcmp(str,"cout"))||(!strcmp(str,"cin")))
			{
				fscanf(fp,"%s",str);
				while(1)
				{
					//fscanf(fp,"%s",str);
					if(!strcmp(str,"<<"))
						printf("%s\tExtraction operator\n",str);
					else if(!strcmp(str,">>"))
						printf("%s\tInsertion Operator\n",str);
					else if(str[strlen(str-1)]==')')
					{
						i=0;j=0;k=0;
						while(str[i]!='(')
							str1[j++]=str[i++];
						str1[j]='\0';
						while(str[i]!=')')
							str2[k++]=str[i++];
						str2[k]='\0';
						for(i=0;str1[i]!='.';i++)
							printf("%c",str1[i]);
						printf("\tIdentifier\n");
						printf("%c\tSpecial Character\n",str1[i]);
						i++;
						for(;i<strlen(str1);i++)
							printf("%c",str1[i]);
						printf("\tIdentifier\n");
						
						i=0;j=0;k=0;
						printf("%c\tSpecial Character\n",str2[i++]);
						if(str2[i]!=')')
						{
							while(1)
							{
								while(str2[i]!=','||str2[i]!=')')
									printf("%c",str2[i++]);
								printf("\tIdentifier\n%c\tSpecial Character\n",str2[i]);
								i++;
								if(str2[i]==')')
								{
									printf("%c\tSpecial Character\n",str2[i]);
									break;
								}
							}
						}
					}
					/*else if(str[0]!='"')
						printf("%s\tIdentifier\n",str);*/
					else if(str[0]=='"')
					{
						printf("\"\tSpecial Character\n");
						for(i=1;str[i]!='"';i++)
						{
							str[i-1]=str[i];
						}
						str[i-1]='\0';
						printf("%s\tString\n",str);
						printf("\"\tSpecial Character\n");
					}
					else if(str[0]=='\'')
					{
						printf("\nEnters\n\n");
						printf("'\tSpecial Character\n");
                                                for(i=1;i<(strlen(str)-1);i++)
                                                {
                                                        str[i-1]=str[i];
                                                }
                                                str[i-1]='\0';
                                                printf("%s\tCharacter\n",str);
                                                printf("'\tSpecial Character\n");
					}
					else if(str[0]!='"')
						printf("%s\tIdentifier\n",str);
					fscanf(fp,"%s",str);
					if(str[strlen(str)-1]==';')
					{
						//printf("\nbreaking...\n");
						break;
					}
				}
				//printf("\nasdfg%s\n",str);
				str[strlen(str)-1]='\0';//printf("\n%s\n",str);
				if(str[strlen(str)-1]==')')
				{
					//printf("\nEnters\n");
					i=0;j=0;k=0;
					while(str[i]!='(')
						str1[j++]=str[i++];
					str1[j]='\0';
					while(str[i]!=')')
						str2[k++]=str[i++];
					str2[k++]=')';
					str2[k]='\0';
					for(i=0;str1[i]!='.';i++)
						printf("%c",str1[i]);
					printf("\tIdentifier\n");
					printf("%c\tSpecial Character\n",str1[i]);
					i++;
					for(;i<strlen(str1);i++)
						printf("%c",str1[i]);
					printf("\tIdentifier\n");
					
					i=0;j=0;k=0;
					printf("%c\tSpecial Character\n",str2[i++]);
					if(str2[i]!=')')
					{
						while(1)
						{
							while(str2[i]!=','||str2[i]!=')')
								printf("%c",str2[i++]);
							printf("\tIdentifier\n%c\tSpecial Character\n",str2[i]);
							i++;
							if(str2[i]==')')
							{
								printf("%c\tSpecial Character\n",str2[i]);
								break;
							}
						}
					}
					else
						printf(")\tSpecial Character\n");
				}
				else
				{
					//printf("\nEnters 1\n");
					printf("%s\tIdentifier\n",str);
				}
				printf(";\tSpecial Character\n");
				goto a1;
			}
			else if((!strcmp(str,"void"))||(!strcmp(str,"int"))||(!strcmp(str,"char")))
			{
				strcpy(dup,str);
				fscanf(fp,"%s",str);
				if(str[strlen(str)-1]==';')
				{
					if((str[strlen(str)-2]!=')')&&(str[strlen(str)-3]!='('))
					{
						i=j=k=l=0;
						while(str[i]!=';')
						{
							str1[j++]=str[i++];
							if(str[i]==',')
							{
								str1[j]='\0';j=0;
								//fprintf(fp2,"%s\t%s\n",str1,dup);
								if(isalpha(str1[0]))
								{
									strcpy(stab[sym++],str1);
									fprintf(fp2,"%s\t\t\t%s\n",str1,dup);
									printf("%s\tIdentifier\n%c\tSpecial Character\n",str1,str[i++]);
								}
								else
								{
									printf("%s\tInvalid Identifier\n%c\tSpecial Character\n",str1,str[i++]);
								}
							}
						}
						str1[j]='\0';
						if(isalpha(str1[0]))
						{
							fprintf(fp2,"%s\t\t\t%s\n",str1,dup);
							strcpy(stab[sym++],str1);
							printf("\n%s\tIdentifier\n%c\tSpecial Character\n",str1,str[i]);
						}
						else
						{
							printf("\n%s\tInvalid Identifier\n%c\tSpecial Character\n",str1,str[i]);
						}
						//goto a1;
					}
					else
					{
						count=0;i=j=k=0;
						for(i=0;str[i]!='(';i++)
						{
							str1[j++]=str[i];
						}
						str1[j]='\0';
						fprintf(fp2,"%s\t\t\t",str1);
						//strcpy(stab[sym++],str1);
						printf("%s\tIdentifier\n",str1);
						for(;str[i]!=';';i++)
						{
							str2[k++]=str[i];
						}
						str2[k]='\0';
						printf("(\tSpecial Character\n");
						i=1;j=k=l=0;
						while(str2[i]!=')')
						{
							str1[j++]=str2[i++];
                                                        if(str2[i]==',')
                                                        {
                                                                str1[j]='\0';j=0;
                                                                count++;
                                                                printf("%s\tKeyword\n%c\tSpecial CHaracter\n",str1,str2[i++]);
                                                        }
                                                }
						count++;
                                                str1[j]='\0';
                                                printf("%s\tKeyword\n%c\tSpecial Character\n",str1,str2[i]);
						sprintf(temp,"%d",count);
						fprintf(fp2,"%s\n",temp);
						printf(";\tSpecial Character\n");
                                                //goto a1;
					}
				}
				else if((str[strlen(str)-1]==')')&&(str[strlen(str)-2]=='('))
                                {
                                	//printf("(\tSpecial Character");
					for(i=0;str[i]!='(';i++)
					{
						str1[i]=str[i];
					}
					str1[i]='\0';
					if(strcmp(str1,"main")!=0)
					{
						if(isalpha(str1[0]))
						{
							fprintf(fp2,"%s\t\t\t0\n",str1);
							strcpy(stab[sym++],str1);
							printf("\n%s\tIdentifier\n",str1);
						}
					 
					}
					else
						printf("\nmain\tKeyword\n");
					printf("(\tSpecial Character\n)\tSpecial Character\n");
					//goto a1;
				}
				else
				{
					//printf("\nEnters\n");
					i=j=k=0;
					while(str[i]!=':')
						str1[j++]=str[i++];
					str1[j]='\0';
					printf("%s\tIdentifier\n",str1);
					printf("::\tScope resolution operator\n");
					i=i+2;
					j=0;
					while(i<strlen(str))
						str1[j++]=str[i++];
					str1[j]='\0';
					strcpy(stab[sym++],str1);
					//printf("\n\n\n%s\n\n\n",stab[sym-1]);
					printf("%s\tIdentifier\n",str1);
					fscanf(fp,"%s",str);
					printf("(\tSpecial Character\n");i=1;
					while(1)
					{
						j=k=l=0;
						while(i<strlen(str))
						{
							str1[j++]=str[i++];
						}
						i=0;
						str1[j]='\0';
						printf("%s\tKeyword\n",str1);
						fscanf(fp,"%s",str);
						if(str[strlen(str)-1]==')')
						{	
							for(i=0;str[i]!=')';i++)
								str2[i]=str[i];
							str2[i]='\0';
							if(isalpha(str2[0]))
							{
								fprintf(fp2,"%s\t\t\t",str2);
								strcpy(stab[sym++],str2);
								printf("%s\tIdentifier\n",str2);
								fprintf(fp2,"%s\n",str1);
							}
							else
								printf("%s\tInvalid Identifier\n",str2);
							printf(")\tSpecial Character\n");
							break;
						}
						else
						{
							while(str[i]!=',')
								str2[k++]=str[i++];
							str2[k]='\0';
							if(isalpha(str2[0]))
							{
								strcpy(stab[sym++],str2);
								fprintf(fp2,"%s\t\t\t",str2);
								printf("%s\tIdentifier\n",str2);
								fprintf(fp2,"%s\n",str1);
							}
							else
								printf("%s\tInvalid Identifier\n",str2);
							printf(",\tSpecial character\n");
							i++;
						}
					}
				}
				goto a1;
			}
			else if(!strcmp(str,"class"))
			{
				//printf("\n\nEnters\n\n");
				fscanf(fp,"%s",str);
				printf("%s\tIdentifier\n",str);
				strcpy(stab[sym++],str);
				strcpy(classn[classc++],str);
				goto a1;
			}			
			fclose(fp1);
			if(flag1!=0)
				goto a1;
		}
		
		//Check operator
		{
			flagop=0;
			fp1=fopen("operators.txt","r");
			while(!feof(fp1))
			{
				fscanf(fp1,"%s",str1);
				if(isalpha(str1[0]))
					strcpy(splfinal,str1);
				if(!strcmp(str,str1))
				{
					flagop++;
					printf("%s\t%s Operator\n",str,splfinal);
					fclose(fp1);
					break;
					//goto a1;
				}
			}
			if(flagop==0)
				fclose(fp1);
			else
			{
				flagsp1=0;
				fscanf(fp,"%s",str);
				strcpy(spl,str);
				spl[strlen(spl)-1]='\0';
				if(isalpha(str[0]))
				{
					//strcpy(spl,str);
					//spl[strlen(spl)-1]='\0';
					for(i=0;i<sym;i++)
					{
						if(!strcmp(spl,stab[i]))
						{
							flagsp1++;
							break;
						}
					}
					if(flagsp1==0)
						printf("%s\tUndeclared Identifier\n",spl);
					else
						printf("%s\tIdentifier\n",spl);
				}
				else
				{
					count=0;
					for(i=0;i<strlen(spl);i++)
					{
						if(spl[i]=='.')
							count++;
					}
					if(count>=0&&count<2)
						printf("%s\tConstant\n",spl);
					else
						printf("%s\tInvalid Constant\n",spl);
				}
				printf(";\tSpecial Character\n");
				goto a1;
			}
		}

		//Other possibilities
		{
			flagsp=0;
			//printf("%s\tto be processed\n",str);
			for(i=0;i<strlen(str);i++)
			{
				if(!isalpha(str[i]))
				{
					flagsp=1;
					break;
				}
			}
			if(flagsp==0)
			{
				flagsp1=0;
				for(i=0;i<sym;i++)
				{
					if(!strcmp(str,stab[i]))
					{
						flagsp1++;
						break;
					}
				}
				if(flagsp1==0)
					printf("%s\tUndeclared Identifier\n",str);
				else
				{
					printf("%s\tIdentifier\n",str);
					strcpy(str1,str);
					for(i=0;i<classc;i++)
					{
						if(!strcmp(str,classn[i]))
						{
							fscanf(fp,"%s",str);
							str[strlen(str)-1]='\0';
							strcpy(stab[sym++],str);
							printf("%s\tIdentifier\n",str);
							fprintf(fp2,"%s\t\t\t%s\n",str,str1);
							printf(";\tSpecial Character\n");
							break;
						}
					}
				}
			}
			else if(!strcmp(str,"};")||!strcmp(str,"{")||!strcmp(str,"}"))
			{
				if(strlen(str)>1)
					printf("}\tSpecial Character\n;\tSpecial Character\n");
				else
					printf("%s\tSpecial Character\n");
			}
			else if(str[strlen(str)-1]==';')
			{
				str[strlen(str)-1]='\0';
				if(isalpha(str[0]))
				{
					strcpy(stab[sym++],str);
					printf("%s\tIdentifier\n",str);
				}
				else if(str[0]=='(')
				{
					i=1;j=0;
					printf("(\tSpecial Character\n",str[0]);
					while(str[i]!=')')
					{
						if(str[i]==',')
						{
							str1[j]='\0';j=0;
							if(!isalpha(str1[0]))
								printf("%s\tConstant\n",str1);
							else
							{
								flagsp=0;
								for(k=0;k<sym;k++)
								{
									if(!strcmp(str1,stab[k]))
										flagsp++;
								}
								if(flagsp==0)
									printf("%s\tUndeclared Identifier\n",str1);
								else
									printf("%s\tIdentifier\n",str1);
							}
							printf(",\tSpecial Character\n");
						}
						else
							str1[j++]=str[i];
						i++;
					}
					str1[j]='\0';j=0;
                                        if(!isalpha(str1[0]))
                                        	printf("%s\tConstant\n",str1);
                                      	else
                       	                {
                                        	flagsp=0;
                                                for(k=0;k<sym;k++)
                                                {
                                	                if(!strcmp(str1,stab[k]))
                	                                        flagsp++;
       	                                        }
                                                if(flagsp==0)
                                         	       printf("%s\tUndeclared Identifier\n",str1);
                                                else
                                                       printf("%s\tIdentifier\n",str1);
                                         }
                                         printf(")\tSpecial Character\n;\tSpecial Character\n");
				}
			}	
			else if(flagsp!=0)
			{
				i=0;
				for(l=0;l<2;l++)
				{
					j=0;
					for(;(str[i]!='.')&&(i<strlen(str));i++)
						str1[j++]=str[i];
					str1[j]='\0';
					flagsp=0;
					for(k=0;k<sym;k++)
					{
						if(!strcmp(str1,stab[k]))
						{
							//printf("\n\nFOUND\n\n");
							flagsp++;
							break;
						}
					}
					if(flagsp==0)
						printf("%s\tUndeclared Identifier\n",str1);
					else
						printf("%s\tIdentifier\n",str1);
					if(l==0)
						printf(".\tIdentifier\n");
					i++;
				}
			}
		}
		a1:
		fscanf(fp,"%s",str);//printf("%s\n",str);
		//sfdasdfsdf
	}
	/*printf("\n\n\n");
	for(i=0;i<sym;i++)
	{
		printf("%s\n",stab[i]);
	}*/
	//printf("%s\n%s\n%s\n",stab[0],stab[1],stab[2]);
	fclose(fp);
	fclose(fp2);
}
