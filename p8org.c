//	p8.org		1996 apr 21	last modified 1998 jun 01
//
//	Shows organization of dan's p8.c.
//

#include "p8.h"

int main( int argc,char **argv )
{
	void parse( void ),scan( void );

	if ( (argc < 2) || (3 < argc) ) {
		puts( "** use is >p8 [-y] sourcefilename **" );
		exit( 1 );
	}
	if ( argc == 3 ) {
		if ( strcmp( *++argv,"-y" ) == 0 ) {
			sopt = 1;
		} else {
			printf( "** illegal option: [%s] **\n",*argv );
			exit( 1 );
		}
	}
	if ( (fps = fopen( fname = *++argv,"rt" )) == (FILE *)NULL ) {
		printf( "** can't open %s **\n",fname );
		exit( 1 );
	}
	if ( (fpe = fopen( "$$err$$","wt" )) == (FILE *)NULL ) {
		puts( "** can't open \"$$err$$\" for writing errors **" );
		exit( 1 );
	}
	scan();
	if ( nerr == 0 ) {
		parse();
	}
	return( 0 );
}

long double atold( char *a )
{
	long double tento( int );

	long double y;
	int n,p,s;
	y=(long double)0;
	/* this statement is completely legal in c */
	n = p = s = 0;
	// Danny - I can't tell if this is a space or just supposed to be nothing '' 
	/* Miguel - looks like a space chararecter */
	while ((*a==' ')||(*a=='\t'))
	{
		a++;
	}
	
	if(*a=='-')
	{
		a++;
		s++;
	}
	
	while(isdigit(*a))
	{
		y=((long double)10*y+(long double)((a++)-'0'));
	}
	
	if(*a=='.')
	{
		a++;
		while(isdigit(*a))
		{
 			p++;
 			y=((long double)10*y+(long double)((a++)-'0'));
		}
	}
	if ((*a=='e')||(*a=='E'))
	{  
		/* Miguel - atoi is a function of see that converts ascii chars to integers */           
		// Danny - what the hell is atoi
		n=atoi(++a);
	}
	y=y*tento(n-p);
	
return(s ? -y : y);

}

void baddigitstr( char *t )
{
	fprintf( fpe, e2, line,t );
	nerr++;
	lsymb = symbol[nsymb++] = 0; 
}

void closeout( void )
{
	void makename( char *,char *,char * );

	int i;
	char fasm[13];
	
	fputs("\tret\n_main\tendp\ntext\tends\n_data\tsegment\tword public 'data'\n",fpc);
	for(i = 0; i < nrlit; i++){
		/* the part in this line \treal im not sure if its \treal10 or \treall0 */
		fprintf( fpc, "c%.2d\treal10\t%21.14e\n", i, (double)rlit[i] );
	}
	
	for(i = 0; i < nilit; i++){
		fprintf( fpc, "c%.2d\tdd\t%ld\n", 50+i, ilit[i] );
	}
	
	for(i = 0; i < nrvar; i++){
		fprintf( fpc, "v%.2d\treal10\t0.0\t;%-s\n", i, var[i]);
	}
	
	for(i = 0; i < nivar; i++){
		fprintf( fpc, "v%.2d\tdd\t0\t;%-s\n", 50+i, var[50+i]);
	}
	
	fputs("_data\tends\nstack\tsegment\tstack\n\tdw\t100h dup(?)\nstack\tends\n", fpc);
	
	if(inf){
		fputs("\textern\t_inf:near\n", fpc);
	}
	if(ini){
		fputs("\textern\t_ini:near\n", fpc);
	}
	if(ouf){
		fputs("\textern\t_outf:near\n", fpc);
	}
	if(oui){
		fputs("\textern\t_outi:near\n", fpc);
	}
	fputs("\tend\n", fpc);
	
	if(fclose(fpc)){
		printf("** can't close %s**\n", fcode);
		exit(1);
	}
	makename(fname, "asm", fasm);
	if(fopen( fasm,"rt" != (FILE*)NULL)){
		unlink(fasm);
	}
	rename(fcode,fasm);
}

int comp( int s,int *p )
{
	for(modes = (int)mode[s]; *p && s; p++ ){
		if(symbol[--s] != *p){
			return 2;
		}
		else if(2 < (modes |= (int)mode[s])){
			return 1;
		}
	}
	return 0;
}    

void delimiter( void )
{
	lsymb = symbol[nsymb++] = 350+(int)delim[(int)ch & 0x00ff];
	if( ch == ';')
	{
		lrw = 0;
	}
}

void emit0( int n )
{
	if(n < 100){
		fprintf(fpc,"%s",reg[n]);
	}
	else{
		if( n < 200){
			fprintf(fpc, "v%.2d", n-100);
		}
		else{
			fprintf(fpc, "c%.2d",n-200);
		}
	}
}

void emit1( int i )
{ 
	fprintf ( fpc, "\t%s\n", inst[i] );
}

void emit2( int i,int j )
{
	void emit0( int );
	
	fprintf ( fpc, "\t%s\t",inst[i] );
	emit0( j );
	fputs ( "\n", fpc );	
}

void emit3( int i,int j,int k )
{
	void emit0( int );
	
	emit0(j);
	fputs ( ",", fpc);
	emit0 ( k );
	fputs ( "\n" , fpc);	
}

void extradot( int d,char *t )
{
	fprintf( fpe,e0,line,d,t );
	nerr++;
	lsymb = symbol[nsymb++] = 0;
}

void floatstr( char *t )
{
	long double atold( char * );

	double x;
	int i;
	
	if(!isdigit(*(t+strlen(t)-1)))
	{
		fprintf(fpe,e2,line,t);
		nerr++;
		lsymb = symbol[nsymb++]= 0;
		return;
	}
	
	x=atold(t);
	for(i=0; i < nrlit; i++)
	{
		if(x==rlit[i])
		{
			lsymb = symbol[nsymb++] = 200+i;
			return;
		}
	}
		/* the else wasn't necessary - Miguel  */
		/* If i isnt less then nrlit then it'll go to the if statement below
			 which will then lead us to the end of the function */
	//I dont know if I need the else here but it looks like I may - Danny
	if(50<=nrlit)
	{
		puts("** too many real literals **");
		exit(1);
	}
	else
	{
		rlit[nrlit++] = x;
		lsymb=symbol[nsymb++]=199+nrlit;
	}
}

void gencode( void )
{
	int nextr( void );
	void emit1( int ),emit2( int,int ),emit3( int,int,int );

	int l,r;
	switch ( row ) {
			case  0: if ( modes == 1 ) {
					if ( OP2 < 6 ) {
						emit3( 14,OP0,OP2 );
						rbu[OP2] = (char)0;
					} else {
						emit3( 14,0,OP2 );
						emit3( 14,OP0,0 );
					}
				} else {
					if ( sd ) {
						emit2( 34,OP0 );
						sd = 0;
					} else {
						emit2( 31,OP2 );
						emit2( 34,OP0 );
					}
				}
				break;
			case  1:
			case 35: if ( modes == 1 ) {
					if ( 100 <= OP2 ) {
						emit3( 14,0,OP2 );
					}
					fputs( "\tcall\t_outi\n",fpc );
					*rbu = (char)0;
					oui = (char)1;
				} else {
					if ( OP2 != 0 ) {
						emit2( 31,OP2 );
					}
					fputs( "\tcall\t_outf\n",fpc );
					sd = 0;					
					ouf = (char)1;
				}
				break;
			case  3:
			case 36: if ( modes == 1 ) {
					if ( 100 <= OP1 ) {
						emit3( 14,0,OP1 );
					}
					fputs( "\tcall\t_outi\n",fpc );
					*rbu = (char)0;
					oui = (char)1;
				} else {
					if ( OP1 != 0 ) {
						emit2( 31,OP1 );
					}
					fputs( "\tcall\t_outf\n",fpc );
					sd = 0;
					ouf = (char)1;
				}
				break;
			case  5: if ( bstop < brk ) {
					bug = 6;
				} else {
					*bstop |= 1;
					fprintf( fpc,"\tjmp\t_%d\n",*bstop >> 1 );
				}
				break;
			case  6: fputs( "\tret\n",fpc );
				break;
			case  7: fprintf( fpc,"_%d:\n",OP0 );
				OP0 = 0;
				break;
			case  9: if (alpha != 308 ) {			// else 
					fprintf( fpc,"_%d:\n",OP0 );
					OP0 = 0;
				} else {
					fprintf( fpc,"\tjmp\t_%d\n_%d:\n",++label,OP0 );
					OP0 = label;
				}
				break;
			case 10: fprintf( fpc,"\tjmp\t_%d\n",OP0 );
				OP0 = 0;
				break;
			case 11: label++;
				fprintf( fpc,"\tpop\teax\n\tdec\teax\n\tjle\t_%d\n"
					"\tjmp\t_%d\n_%d:\n",label,OP0,label );
				OP0 = 0;
				break;
			case 14:
			case 15: if ( modes == 1 ) {
					fputs( "\tcall\t_ini\n",fpc );
					emit3( 14,aux[top+16-row],0 );
					ini = (char)1;
				} else {
					fputs( "\tcall\t_inf\n",fpc );
					emit2( 34,aux[top+16-row] );
					inf = (char)1;
				}
				break;
			case 18: if ( modes == 1 ) {
					if ( OP1 < 6 ) {
						emit3( 3,OP1,OP3 );
						rbu[OP1] = (char)0;
						if ( OP3 < 6 ) {
							rbu[OP3] = (char)0;
						}
					} else {
						if ( OP3 < 6 ) {
							emit3( 3,OP1,OP3 );
							rbu[OP3] = (char)0;
						} else {
							emit3( 14,0,OP1 );
							emit3( 3,0,OP3 );
						}
					}
				} else {
					if ( (OP1 == 0) && (OP3 != 0) ) {
						emit2( 31,OP3 );
					}
					if ( (OP0 != 0) && (OP3 == 0) ) {
						emit2( 31,OP1 );
						emit1( 40 );
					}
					if ( (OP1 != 0) && (OP3 != 0) ) {
						emit2( 31,OP1 );
						emit2( 31,OP3 );
					}
					emit1( 26 );
					emit1( 35 );
					emit1( 18 );
					sd = 0;
				}
				fprintf( fpc,"\t%s\t_%d\n",inst[OP2],++label );
				fprintf( fpc,"\tjmp\t_%d\n",++label );
				fprintf( fpc,"_%d:\n",label-1 );
				OP0 = label;
				break; 
			case 19: if ( modes == 2 ) {
					bug = 5;
					break;
				} 
				if ( OP2 == 0 ) {
					*rbu = (char)0;
				} else {
					emit3( 14,0,OP2 );
				}
				fprintf( fpc,"_%d:\n\tpush\teax\n",++label );
				OP0 = label;
				break;
			case 20: label++;
				*++bstop = label+label;
				break;
			case 22: if ( modes == 1 ) {
					if ( OP0 < 6 ) {
						emit3( 0,OP0,OP2 );
						if ( OP2 < 6 ) {
							rbu[OP2] = (char)0;
						}
						break;
					}
					if ( OP2 < 6 ) {
						emit3( 0,OP2,OP0 );
						OP0 = OP2;
						break;
					}
					r = nextr();
					emit3( 14,r,OP0 );
					emit3( 0,r,OP2 );
					OP0 = r;
					break;
				}
				if ( (OP0 == 0) && (OP2 == 0) ) {
					emit1( 21 );
					--sd;
					break;
				}
				if ( 7 < sd ) {
					bug = 4;
					break;
				}
				if ( OP0 == 0 ) {
					emit2( 31,OP2 );
					emit1( 21 );
					break;
				}
				if ( OP2 == 0 ) {
					emit2( 31,OP0 );
					emit1( 21 );
					OP0 = 0;
					break;
				}
				if ( 7 < ++sd ) {
					bug = 4;
					break;
				}
				emit2( 31,OP0 );
				emit2( 31,OP2 );
				emit1( 21 );
				OP0 = 0;
				break;
			case 23: if ( modes == 1 ) {
					if ( OP0 < 6 ) {
						emit3( 19,OP0,OP2 );
						if ( OP2 < 6 ) {
							rbu[OP2] = (char)0;
						}
						break;
					}
					r = nextr();
					if ( OP2 < 6 ) {
						emit2( 17,OP2 );
						emit3( 14,OP2,OP0 );
						emit2( 16,r );
						emit3( 19,OP2,r );
						rbu[r] = (char)0;
						OP0 = OP2;
						break;
					}
					emit3( 14,r,OP0 );
					emit3( 19,r,OP2 );
					OP0 = r;
					break;
				}
				if ( (OP0 == 0) && (OP2 == 0) ) {
					emit1( 36 );
					--sd;
					break;
				}
				if ( 7 < sd ) {
					bug = 95;
					break;
				}
				if ( OP0 == 0 ) {
					emit2( 31,OP2 );
					emit1( 36 );
					break;
				}
				if ( OP2 == 0 ) {
					emit2( 31,OP0 );
					emit1( 38 );
					OP0 = 0;
					break;
				}
				if ( 7 < ++sd ) {
					bug = 4;
					break;
				}
				emit2( 31,OP0 );
				emit2( 31,OP2 );
				emit1( 36 );
				OP0 = 0;
				break;
			case 24: if ( modes == 1 ) {
					if ( OP1 < 6 ) {
						emit2( 15,OP1 );
						OP0 = OP1;
					} else {
						r = nextr();
						emit3( 14,r,OP1 );
						emit2( 15,r );
						OP0 = r;
					}
				} else {
					if ( OP1 == 0 ) {
						emit1( 23 );
						OP0 = 0;
					} else {
						if ( 8 < ++sd ) {
							bug = 4;
						} else {
							emit2( 31,OP1 );
							emit1( 23 );
							OP0 = 0;
						}
					}
				}
				mode[top] = (char)modes;
				break;
			case 26: if ( modes == 1 ) {
					if ( OP0 < 6 ) {
						if ( OP2 < 6 ) {
							rbu[OP2] = (char)0;
							switch ( OP0 ) {
								case 0: emit2( 6,OP2 );
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,OP0,0);
									emit2( 16,0 );
									break;
								case 3: emit2( 17,0 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,3,0);
									emit2( 16,0 );
									break;
								case 4: emit2( 17,0 );
									emit2( 17,3 );
									emit3( 14,0,4 );
									emit2( 6,OP2 );
									emit3( 14,4,0 );
									emit2( 16,3 );
									emit2( 16,0 );
									break;
								case 5: bug = 4;
							}
						} else {
							switch ( OP0 ) {
								case 0: emit2( 6,OP2 );
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,OP0,0);
									emit2( 16,0 );
									break;
								case 3: emit2( 17,0 );
									emit3( 14,0,3 );
									emit2( 6,OP2 );
									emit3( 14,3,0 );
									emit2( 16,0 );
									break;
								case 4: 
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,OP0,0);
									emit2( 16,3 );
									emit2( 16,0 );
							}
						}
					} else {
						if ( OP2 < 6 ) {
							switch ( OP2 ) {
								case 0: emit2( 6,OP0 );
									OP0 = 0;
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,OP2,0);
									emit2( 16,0 );
									OP0 = OP2;
									break;
								case 3: emit2( 17,0 );
									emit3(14,0,OP0);
									emit2( 6,3 );
									emit3( 14,3,0 );
									emit2( 16,0 );
									break;
								case 4: 
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3(14,OP2,0);
									emit2( 16,3 );
									emit2( 16,0 );
							}
						} else {
							r = nextr();
							switch ( r ) {
								case 0: emit3(14,0,OP0);
									emit2( 6,OP2 );
									OP0 = 0;
									break;
								case 1:
								case 2:
								case 3: emit2( 17,0 );
	 								emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3( 14,r,0 );
									emit2( 16,0 );
									OP0 = r;
									break;
								case 4:
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit2( 6,OP2 );
									emit3( 14,r,0 );
									emit2( 16,3 );
									emit2( 16,0 );
									OP0 = r;
							}
						}
					}
					break;
				}
				if ( (OP0 == 0) && (OP2 == 0) ) {
					emit1( 32 );
					--sd;
					break;
				}
				if ( 7 < sd ) {
					bug = 4;
					break;
				}
				if ( OP0 == 0 ) {
					emit2( 31,OP2 );
					emit1( 32 );
					break;
				}
				if ( OP2 == 0 ) {
					emit2( 31,OP0 );
					emit1( 32 );
					OP0 = 0;
					break;
				}
				if ( 7 < ++sd ) {
					bug = 4;
					break;
				}
				emit2( 31,OP0 );
				emit2( 31,OP2 );
				emit1( 32 );
				OP0 = 0;
				break;
			case 27: if ( modes == 1 ) {
					if ( OP0 < 6 ) {
						if ( OP2 < 6 ) {
							rbu[OP2] = (char)0;
							switch ( OP0 ) {
								case 0: emit1( 2 );
									emit2( 5,OP2 );
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3(14,OP0,0);
									emit2( 16,0 );
									break;
								case 3: emit2( 17,0 );
									emit3( 14,0,3 );
									emit1( 2 );
									emit2( 5,OP2 );
									emit3( 14,3,0 );
									emit2( 16,0 );
									break;
								case 4: emit2( 17,0 );
									emit2( 17,3 );
									emit3( 14,0,4 );
									emit1( 2 );
									emit2( 5,OP2 );
									emit3( 14,4,0 );
									emit2( 16,3 );
									emit2( 16,0 );
									break;
								case 5: bug = 4;
							}
						} else {
							switch ( OP0 ) {
								case 0: emit1( 2 );
									emit2( 5,OP2 );
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3(14,OP0,0);
									emit2( 16,0 );
									break;
								case 3: emit2( 17,0 );
									emit3( 14,0,3 );
									emit1( 2 );
									emit2( 5,OP2 );
									emit3( 14,3,0 );
									emit2( 16,0 );
									break;
								case 4: 
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3(14,OP0,0);
									emit2( 16,3 );
									emit2( 16,0 );
							}
						}
					} else {
						if ( OP2 < 6 ) {
							switch ( OP2 ) {
								case 0: emit3( 14,1,0 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,1 );
									OP0 = 0;
									break;
								case 1:
								case 2: emit2( 17,0 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3(14,OP2,0);
									emit2( 16,0 );
									OP0 = OP2;
									break;
								case 3: emit2( 17,0 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,3 );
									emit3( 14,3,0 );
									emit2( 16,0 );
									OP0 = 3;
									break;
								case 4: 
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3(14,OP2,0);
									emit2( 16,3 );
									emit2( 16,0 );
									OP0 = OP2;
							}
						} else {
							r = nextr();
							switch ( r ) {
								case 0: emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									OP0 = 0;
									break;
								case 1:
								case 2:
								case 3: emit2( 17,0 );
	 								emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3( 14,r,0 );
									emit2( 16,0 );
									OP0 = r;
									break;
								case 4:
								case 5: emit2( 17,0 );
									emit2( 17,3 );
									emit3(14,0,OP0);
									emit1( 2 );
									emit2( 5,OP2 );
									emit3( 14,r,0 );
									emit2( 16,3 );
									emit2( 16,0 );
									OP0 = r;
							}
						}
					}
					break;
				}
				if ( (OP0 == 0) && (OP2 == 0) ) {
					emit1( 27 );
					--sd;
					break;
				}
				if ( 7 < sd ) {
					bug = 4;
					break;
				}
				if ( OP0 == 0 ) {
					emit2( 31,OP2 );
					emit1( 27 );
					break;
				}
				if ( OP2 == 0 ) {
					emit2( 31,OP0 );
					emit1( 29 );
					OP0 = 0;
					break;
				}
				if ( 7 < ++sd ) {
					bug = 4;
					break;
				}
				emit2( 31,OP0 );
				emit2( 31,OP2 );
				emit1( 27 );
				OP0 = 0;
				break;
			case 33: aux[top] = label;
				break;
			case 34: *++bstop = label+label+1;	// OP1 == label
				break;
			case 41: l = *bstop--;
				if ( l & 1 ) {
					fprintf( fpc,"_%d:\n",l >> 1 );
				}
				break;
			case 49:
			case 50:
			case 51:
			case 52: OP0 = (int)(modes == 1 ? comi[row-49] : comf[row-49]);
				break;
			default: printf( "** bad row [%d] in gencode **\n",row );
				exit( 1 );
		}
}

void getsymbol( void )
{
	if (nsymb <= isymb){
        eos++;
	 }
	else{
	  	do{
				if (nsymb >= ++isymb){
					eos++;
				}
				else{ 
					if (400 < (alpha = symbol[isymb])){
	        	line = alpha - 400;
					}
	    	}
			} while( (400 < alpha) && !eos );
			if (!eos){
				clj = (alpha < 300 ? alpha/100-1 : alpha-(alpha < 310 ? 298 : 338));
     	}
  }
}
//
//	If string s is new, return -(hash+1)
//	else if found, return hash.
//	Thus (in calling function):
//		if return value y < 0, then hash = -(y+1)
//				       else hash = y.
//

int hash( char *s )
{
	int h,q;
	char *p;
	/* I cant remember but can we just leave a for loop without braces? */
	for( p = s, q = 0; *p; q = q+(int)*p, p++)
	
	h = ( q % HSIZE ) - 1;
	
	for(q=0;;){
		if(HSIZE <= ++h){
			h = 0;
		}
		else if( hashp[h].ptss == (char*)NULL){
			return( -(h+1));
		}
		else if( strcmp( s, hashp[h].ptss) == 0){
			return( h );
		}
		else if( HSIZE <= ++q ){
			puts( "** hash table overflow **");
			exit(1);
		}
	}
}

void illegalch( void )
{
	fprintf( fpe,e1,line,ch );
	nerr++;
	lsymb = symbol[nsymb++] = 0;
}

void initparse( void ) // By Devin 2/26
{
	int r;
	
	if (( fpc = fopen( fcode, "wt" )) == (FILE*)NULL ) {
		printf( "** can't open %s **\n", fcode );
		exit(1);
	}
	
	fputs("\t.386\n\t.model\tflat.stdcall\n\t.code\nmain\tproc\n", fpc); 
	
	if ( nrvar || nrlit ) {
		fputs( "\tfinit\n", fpc );
	}
	
	isymb = label = maxtop = top = -1;
	inf = ini = ouf = oui = (char)bug = eos = sd = 0;
	bstop = brk-1;
	
	for ( r = 0; r < 6; r++ ) {
		rbu[r] = (char)0;
	}
}


void initscan( void )// By Miguel - 2/16 @ 12:10 PM  added initscan function.
{
	int hash( char * );

	int h,i;
	
	ch = NEWL;
	line = nerr = nilit = nivar = nrlit = nvar = nsymb = 0;
	hash = (HASHREC *)malloc( HSIZE*sizeof( HASHREC));
	
	if( hashp == (HASHREC *)NULL )
	{
		puts( "** can't allocate hash table **" );
		exit( 1 );
	}
	
	ssp = (char *)malloc( SSIZE );
	
	if( ssp == (char *)NULL )
	{
		puts( "** can't allocate string space **");
		exit( 1 );
	}
	
	ssp1 = ssp+SSIZE;
	for(i = 0; i < HSIZE; i++)
	{
		hashp[i].ptss = (char *)NULL;
	}
	
	for( i = 0; i < sizeof( trw )/sizeof( char *); i++)
	{
		h = -(hash( trw[i] + 1));
		hashp[h].ptss = trw[i];
		hashp[h].icod = 300 + i;
	}
}

void intstr( char *t )// By Miguel - 02/16 @04:23 am - I know im up late again :P
{
	long atol( char * );

	long x;
	int i;

	x = atol( t );
	for(i = 0; i < nilit; i++)
	{
		if( x == ilit[i] )
		{
			lsymb = symbol[nsymb++] = 250 + i;
			return;
		}
	}
	else{
		if( 50 <= nilit )
		{
			puts( "** too many int literals **" );
			exit(1);
		}
	  else
		{
			ilit[nilit++] = x;
			lsymb = symbol[nsymb++] = 249 + nilit;
		}
	}
}

void letterstr( char *t )
{
	int hash( char * );

	int h,i;
	char *p;
	
	h = hash( t );
	
	if( 0 <= h){
		i = hashp[h].icod;
		if( i == 0 ){
			fprintf( fpe, e4, line, t );
			nerr++;
		}
	else
	{
		if((i < 200) && ((lrw == 300) || (lrw == 301))){
			fprintf( fpe, e3, line, t );
			nerr++;
		}
		else{
			if( 300 <= i)
				lrw = i;
			else
				lsymb = symbol[nsymb++] = i;
		}
	 }
	}
	else{
		if( ssp1 <= ssp+strlen( t ) ){
			puts( "** out of string space **" );
			unlink( "$$err$$");
			fclose( fps );
			exit(1);
		}
		else{
			h = -(h + 1);
			hashp[h].ptss = ssp;
			p = t;
			
			while( (*ssp++ = *p++) != EOS);
			
			if( lrw == 300 ){
				var[nrvar] = hashp[h].ptss;
				lsymb = symbol[nsymb++] = hashp[h].icod = 100 + (nivar++);
				return;
			}
			else{
				if( lrw == 301 ){
					var[50+nivar] = hashp[h].ptss;
					lsymb = symbol[nsymb++] = hashp[h].icod = 150 + (nivar++);
					return;
				}
				else{
					fprintf( fpe, e4, line, t);
					nerr++;
					lsymb = symbol[nsymb++] = hashp[h].icod = 0;
				}
			}
		}
	}
}

void makename( char *p,char *q,char *r )
{
	for(; *p && (*p != '.');){
		*r++ = *p++;
	}
	
	*r++ = '.';
	
	for(; *q;){
		*r++ = *q++;
	}
	
	*r = EOS;
}

void match( void )
{
	void gencode( void );
	
	/* implemented by Miguel */
	if( row < 37 )
	{
		top -= subtop[row];
	}
	
	symbol[top] = sigma = newsigma[row] + 400;
	eli = newsigma[row] + 27;
	
	if( row == 0)
	{
		mode[top] = (char)0;
	}
	else
	{
		if( row == 21)
		{
			aux[top] = aux[top + 1];
			mode[top] = (char)modes;
		}
	}
	
	if( code[row] )
	{
		gencode();
	}
	
}

int nextr( void )
{
	int r;
	
	/* implemented by Miguel */
	for( r = 0; rbu[r]; r++)
	
	if( 5 < r )
	{
		bug = 4;
		return( 0 );
	}
	else
	{
		rbu = (char)1;
		return( r );
	}
}
//
//	st is as follows:
//	      -st : last symbol in string (here 0 < st)
//		0 : empty string (last, following a terminal fter)
//		1 : illegal char
//		2 : delimiter
//		3 : letterstring (possibly containing digits)
//		4 : letter in digitstring
//		5 : integer
//		6 : real
//	  7,8,... : too many dots (st-5 dots)
//

int nexts( char *s,char *t )
{
	int ch2,e,st;
	static char *p;
	e = st = 0;
	
	if (ch == NEWL){
		p=s;
	}
	while (l) // that's and L
	{
       /* forgot this */
		ch = *p;
		ch2 = (((int)ch)<< 8) + ((int)*(p+1));

		switch(ch2)
		{ 
			/* Forgot to add p++ to the cases Also it seems that NEWL is defined in p8.h */
			case 0x2f2f: ch = NEWL; break;		// "//" also we may need to define NEWL somewhere
			case 0x3c3d: ch = (char)128; p++; break; // "<="
			case 0x3d3d: ch = (char)129; p++; break; // "=="
			case 0x213d: ch = (char)130; p++; break; // "!="
			/* I dont see this on page one anywhere Danny - Miguel */
			/*case 0x3e3d: ch = (char)131; break; // ">=" for p8'*/
			default:		
				switch( (int)kind[(int)ch & 0x00ff])
				{
					case 0:	*t = EOS; 
								 	return (-st);

					case 1:	if (st == 0){
									st = 3;
									}
									
									if (((ch == 'e')||(ch == 'E')) && ((st == 5) || (st==6)) 
										&& (e==0))
									{
										st =6;
										e++;
									}
 									
									else
									{
										if (4 < st){
											st = 4;
										}
									}

				 case 2: 	if (st==0)
								 	{
										st=5;
									}
									p++; 
									*t++=ch;
 									break;

				 case 3: 	if (st==0)
 									{
										*t++=ch;
 										p++;
                    //364 may need to be modified for p8'
										if ((ch=='-')&&isdigit(*p) && ((lsymb==303)||(lsymb ==352)||(lsymb==354)||
											((358<lsymb)&&(lsymb<364))))
										{
											st = 5;
											break;
 										}
										else
 										{
											*t=EOS;
											return (2);
										}
									}
 									else
									{
										if(st==3)
										{
											*t=EOS;
											return(3);
										}
										else
 										{
											if((ch=='-')&&((*(t-1)=='e')||(*(t-1)=='E')))
											{
												p++;
												*t++=ch;
												break;
											}
											else
											{
 												if(ch=='.')
												{
													*t++=ch;
													p++;
													
													if(4 < st)
													{
														st++;
													}
													break;
												}
												else
												{
													*t=EOS;
													return (st);
												}
											}
										}
									}
				 case 4:
 								p++;
								if(st)
								{
									*t=EOS;
									return(st);
								}
								else
									break;
				 case 5:
								if (st == 0)
								{
									p++;
									return(l);
								}
								else
								{
 									*t=EOS;
									return(st);
								}
			  }
 		}
  }
}

void ouch( int c )
{
	putchar( c );
}

void outscan( void ) // By Devin 2/26
{
	void makename( char *,char *,char * ),ouch( int );

	int c,i,j,k;
	char fsym[13];
	
	fclose( fpe );
	free( (void *)hashp );
	
	if (nerr)
	{
		printf("\n\n%d error%sdetected in scan\n\n",
			   nerr, (nerr < 2 ? " " : "s "));
		
		while ((c = getc( fpe )) != EOF) {
			ouch(c);
		}
		
		fclose( fpe );
		puts( "\n" );
	}

	if (sopt) { // goes to a
		makename( fname, "sym", fsym );
		
		if ((fps = fopen( fsym, "wt" )) == (FILE *)NULL) {
			printf("** can't open %s **", fsym );
			exit( 1 );
		}
		
		fprintf( fps, "\t\t\t\tSymbol tables: %s\n", fname );
		
		if (nrvar) {
			fputs( "\n\nreal variables\n\n", fps );
			for (i = 0; i < nrvar; i++) {
				fprintf( fps, "%6d	%s\n",
						100 + i, var[i] );
			}
		}
		
		if (nivar) {
			fputs( "\n\ninteger variables\n\n", fps );
			for ( i = 0; i < nivar; i++ ) {
				fprintf( fps, "%6d	%s\n",
						150 + i, var[50+i] );
			}
		}
		
		if (nrlit) {
			fputs( "\n\nreal literals\n\n", fps );
			for ( i = 0; i < nrlit; i++ ) {
				fprintf( fps, "%6d%25.14e\n",
						200 + i, (double)rlit[i] );
			}
		}
		
		if (nilit) {
			fputs( "\n\ninteger literals\n\n", fps );
			for ( i = 0; i < nilit; i++ ) {
				fprintf( fps, "%6d%15ld\n",
						250 + i, ilit[i] );
			}
		}
		
		if (nerr) {
			fprintf( fps, "\n\n%d error%sdetected in scan\n\n",
					nerr, (nerr < 2 ? " " : "s "));
			fpe = fopen( "$$err$$", "rt" );
			
			while ((c = getc( fpe )) != EOF ) {
				fputc( c, fps );
			}
			
			fclose( fpe );
			fputs( "\n", fps );
		}
		
		fprintf( fps, "\t\t\tinternal form: %d symbols\n\n",nsymb );
		
		for (i = 0; i < nsymb; i++) {
			k = symbol[i];
			
			if (400 < k) {
				fprintf( fps, "\n%6d", k );
				j = 0;
			}
			
			else {
								
				if (SYMLIN < ++j) {
					fprintf( fps, "\n	" );
					j = 1;
				}
				
				fprintf( fps, "%5d", k );
			}
		}
		
		fputc( (int)NEWL, fps );
		fclose( fps );
	}
	
	if (unlink( "$$err$$" ) != 0 ) {
		puts( "** cannot delete \"$$err$$\" **" );
	}
	
}

void parse( void )
{
	void closeout( void ),getsymbol( void ),initparse( void ),
		reduce( void ),reportbug( void ),shift( void );
	
	initparse();
	getsymbol();
	
	if( alpha != 350 ){
		bug = 3;
		reportbug();
		return;
	}
	else{
		shift();
		getsymbol();
		
		do{
			if(eos){
				if((top == 0) && (sigma == 400)){
					break; /* break to B  out of while do-while*/
				}
				else{
					reduce();
				}
			}
			else{
				switch((int)c1[c1i][c1j]){
					case 0:
						shift();
						getsymbol();
						break; /* break to A */
					case 1:
						reduce();
						break; /* break to A */
					default:
						bug = 10+(int)c1[c1i][c1j];
				}
			}
		} while( !bug ); /* THIS IS A */
		if(bug){ /*This is B */
			reportbug();
		}
		else{
			closeout();
		}
	}
}

void reduce( void )
{
	int comp( int,int * );
	void match( void );
	
	row = first[cli];
	if( row < 37 ){
		while(1){
			if((bug = comp( top, c2+c2ptr[row])) < 2){
				break; /* back to A */
			}
			else{
				if(same[++row] != sigma){
					bug = 2;
					break; /* back to A */
				}
				else{
					if((row == 16) && (symbol[top-1] != 403)){
						row++;
					}
				}
			}
		}
	}
	/* this is A */
	if( bug == 0){
		match();
	}
}

void reportbug( void ) // By Devin 2/26
{
	void ouch( int );

	int i,j,k;
	
	fclose( pfc );
	unlink( fcode );
	
	if( bug < 7 )
	{
		printf("\n\n** line %d: %s **", (bug == 3 ? line : eline), bugm[bug-1]);
		return;
	}
	
	printf( "\n\n** bug at or near line %d: numbug = %d **\n\n sigma = %4d\n alpha =%4d \n\n isymb =%4d \n top =%4d\n\n cli =%4d \n clj =%4d \n\n", eline, bug, sigma, alpha, isymb, top, cli, clj );

	if((j = top - 9) < 1)
	{
		j = 0;
	}
	
	printf( " stack[%4d - top ] = ", j );
	
	for ( i = j; i <= top; i++ ) {
		printf( "%5d", symbol[i] );
	}
	
	ouch( (int)NEWL );
	
	if ( isymb < nsymb ) {
		if ((nsymb <= ( k = isymb + 9 ))) {
			k = nsymb - 1;
		}
		
		printf( "string[%4d - %4d] = ", isymb, k );
		
		for ( i = isymb; i <= k; i++ ) {
			printf( "%5d", symbol[i] );
		}
		
		ouch( (int)NEWL );
	}
	
	printf( "\n\nmaxtop = %d\n\n", maxtop );
	
}

void scan( void )
{
	int nexts( char *,char * );
	void baddigitstr( char * ),delimiter( void ),extradot( int,char * ),
		floatstr( char * ),illegalch( void ),initscan( void ),
		intstr( char * ),letterstr( char * ),outscan( void );

	int st;
	char s[MAXL+1],t[MAXL+1];
	/* Implemented by Miguel */
	
	initscan();
	
	while(fgets( s, MAXL+1, fps ) != (char*)NULL)
	{
		line++;
		lsymb = symbol[nsymb++] = 400+line;
		
		do{
				if(( st = nexts( s,t )) != 0)
				{
					switch( 0 < st ? st : -st ){
							case 1:	illegalch();
							break;
							
							case 2: delimiter();
							break;
							
							case 3: letterstr( t );
							break;
							
							case 4: baddigitstr( t );
							break;
						  
							case 5: instr( t );
							break;
											
							case 6: floatstr( t );
							break;
							
							default: extradot( st - 5, t);
					}
				}
		}while( 0 < st );
	}
	if(fclose( fps ))
	{
		print( "** can't close %s **\n", fname);
		exit(1);
	}
	outscan();
}

void shift( void )
{ 
	/* implemented by Miguel  on Feb 22 */
	if( maxtop < ++top )
	{
		maxtop = top;
	}
	sigma = (300 <= alpha ? alpha : 100*(alpha/100));
	symbol[top] = sigma;
	
	if( 300 <= alpha )
	{
		mode[top] = (char)(aux[top] = 0);
	}
	else
	{
		aux[top] = alpha;
		mode[top] = (char)(((alpha - sigma) < 50) + 1);
	}
	
	if( alpha == 306)
	{
		fprintf( fpc,"_%d:\n",++label );
		aux[top] = label;
	}
	
	cli = clj;
	eline = line;
}

long double tento( int n )
{
	long double y,z;
	
	if( n < 0 ){
		/* not sure if its an l or a 1 for now im going with one */
		return((long double)1 / tento(-n));
	}
	else{
		z = (long double)10;
		y = (n & 1 ? z : (long double)1 );
		
		for(; n >>= 1;){
			z = z*z;
			if( n & 1){
				y = y*z;
			}
		}
		return ( y );
	}
}