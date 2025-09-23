#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXROW 10000
int plot_histogram(int rownum,char **sectorname, unsigned short int histo[32][MAXROW]);
int main(int argc, char **argv){
  FILE *fp;
  int i, ii, res, IN, startrow, maxrow, rownum, debug=0;
  int pos = 0, len = 31;
  char subs[32];
  size_t linelen;
  char *line;
  char * secstart = "Reading SECTORS table in HDU 3:";
  
  if (argc<2){
    fprintf(stderr,"usage: %s <asciifile>\n", argv[0]);
    return 1;
  }
    maxrow=2119;
    long long raw[maxrow];
    long long pktnumb[maxrow];    
  	unsigned char sid[maxrow];
	unsigned char nsectors[maxrow];
	unsigned short acctime[maxrow];
	unsigned char dflag[maxrow];
	unsigned char sflag[maxrow];
	unsigned short shutfreq[maxrow];
	unsigned short hv1_cur[maxrow];
	unsigned short hv2_cur[maxrow];
	unsigned short hvmcpcur[maxrow];
	unsigned short mcp_temp[maxrow];
	unsigned short h_ch01[maxrow];
	unsigned short h_ch02[maxrow];
	unsigned short h_ch03[maxrow];
	unsigned short h_ch04[maxrow];
	unsigned short h_ch05[maxrow];
	unsigned short h_ch06[maxrow];
	unsigned short h_ch07[maxrow];
	unsigned short h_ch08[maxrow];
	unsigned short h_ch09[maxrow];
	unsigned short h_ch10[maxrow];
	unsigned short h_ch11[maxrow];
	unsigned short h_ch12[maxrow];
	unsigned short h_ch13[maxrow];
	unsigned short h_ch14[maxrow];
	unsigned short h_ch15[maxrow];
	unsigned short h_ch16[maxrow];
	unsigned short h_ch17[maxrow];
	unsigned short h_ch18[maxrow];
	unsigned short h_ch19[maxrow];
	unsigned short h_ch20[maxrow];
	unsigned short h_ch21[maxrow];
	unsigned short h_ch22[maxrow];
	unsigned short h_ch23[maxrow];
	unsigned short h_ch24[maxrow];
	unsigned short h_ch25[maxrow];
	unsigned short h_ch26[maxrow];
	unsigned short h_ch27[maxrow];
	unsigned short h_ch28[maxrow];
	unsigned short h_ch29[maxrow];
	unsigned short h_ch30[maxrow];
	unsigned short h_ch31[maxrow];
	unsigned short h_ch32[maxrow];
	unsigned short mark[maxrow];
	double time[maxrow];
    char *sectorname[32];
    sectorname[0]="Ch_01";sectorname[1]="Ch_02";sectorname[2]="Ch_03";sectorname[3]="Ch_04";sectorname[4]="Ch_05";sectorname[5]="Ch_06";sectorname[6]="Ch_07";sectorname[7]="Ch_08";
    sectorname[8]="Ch_09";sectorname[9]="Ch_10";sectorname[10]="Ch_11";sectorname[11]="Ch_12";sectorname[12]="Ch_13";sectorname[13]="Ch_14";sectorname[14]="Ch_15";sectorname[15]="Ch_16";
    sectorname[16]="Ch_17";sectorname[17]="Ch_18";sectorname[18]="Ch_19";sectorname[19]="Ch_20";sectorname[20]="Ch_21";sectorname[21]="Ch_22";sectorname[22]="Ch_23";sectorname[23]="Ch_24";
    sectorname[24]="Ch_25";sectorname[25]="Ch_26";sectorname[26]="Ch_27";sectorname[27]="Ch_28";sectorname[28]="Ch_29";sectorname[29]="Ch_30";sectorname[30]="Ch_31";sectorname[31]="Ch_32";
  unsigned short histo[32][MAXROW];
  char *fname = argv[1];
  linelen = 1024;
  line = (char *)malloc(linelen*sizeof(char));
  fp=fopen(fname,"r");
  i=0; IN=0;
  while(getline(&line,&linelen,fp)>0){
     strncpy(subs, line + pos, len);
    /* Null terminate the substring */
    subs[len] = '\0';
    res = strcmp(subs,secstart);
    if (res==0){
      startrow=i;
      if (debug) printf("i = %d\n", i); 
      IN=1;
    }
    if ((IN==1)&&((i>=(startrow+3))&&(i<=(startrow+maxrow+2)))){
		if (debug) printf("line: %s",line);
		ii=i-(startrow+3);
	    sscanf(line,"%lld %lld %hhu %hhu %hu %hhu %hhu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu \
	    %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %lf",&raw[ii],&pktnumb[ii],&sid[ii], &nsectors[ii], &acctime[ii], &dflag[ii], &sflag[ii],\
        &shutfreq[ii],&hv1_cur[ii], &hv2_cur[ii],&hvmcpcur[ii], &mcp_temp[ii], &h_ch01[ii], &h_ch02[ii],&h_ch03[ii],&h_ch04[ii],&h_ch05[ii], \
        &h_ch06[ii],&h_ch07[ii],&h_ch08[ii],&h_ch09[ii],&h_ch10[ii],&h_ch11[ii],&h_ch12[ii],&h_ch13[ii],&h_ch14[ii],&h_ch15[ii],&h_ch16[ii],&h_ch17[ii],&h_ch18[ii], \
        &h_ch19[ii],&h_ch20[ii],&h_ch21[ii],&h_ch22[ii],&h_ch23[ii],&h_ch24[ii],&h_ch25[ii],&h_ch26[ii],&h_ch27[ii],&h_ch28[ii],&h_ch29[ii],&h_ch30[ii],\
        &h_ch31[ii],&h_ch32[ii],&mark[ii],&time[ii] );
        if (debug) printf("%hhu %hhu %hu %hhu %hhu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu\
 %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %lf\n",sid[ii], nsectors[ii], acctime[ii],\
        dflag[ii], sflag[ii],shutfreq[ii],hv1_cur[ii], hv2_cur[ii],hvmcpcur[ii], mcp_temp[ii], h_ch01[ii], h_ch02[ii],h_ch03[ii],h_ch04[ii],h_ch05[ii], \
        h_ch06[ii],h_ch07[ii],h_ch08[ii],h_ch09[ii],h_ch10[ii],h_ch11[ii],h_ch12[ii],h_ch13[ii],h_ch14[ii],h_ch15[ii],h_ch16[ii],h_ch17[ii],h_ch18[ii], \
        h_ch19[ii],h_ch20[ii],h_ch21[ii],h_ch22[ii],h_ch23[ii],h_ch24[ii],h_ch25[ii],h_ch26[ii],h_ch27[ii],h_ch28[ii],h_ch29[ii],h_ch30[ii],\
        h_ch31[ii],h_ch32[ii],mark[ii],time[ii] );
        histo[0][ii] = h_ch01[ii];histo[1][ii] = h_ch02[ii];histo[2][ii] = h_ch03[ii];histo[3][ii] = h_ch04[ii];histo[4][ii] = h_ch05[ii];histo[5][ii] = h_ch06[ii];histo[6][ii] = h_ch07[ii];histo[7][ii] = h_ch08[ii];
        histo[8][ii] = h_ch09[ii];histo[9][ii] = h_ch10[ii];histo[10][ii] = h_ch11[ii];histo[11][ii] = h_ch12[ii];histo[12][ii] = h_ch13[ii];histo[13][ii] = h_ch14[ii];histo[14][ii] = h_ch15[ii];histo[15][ii] = h_ch16[ii];
        histo[16][ii] = h_ch17[ii];histo[17][ii] = h_ch18[ii];histo[18][ii] = h_ch19[ii];histo[19][ii] = h_ch20[ii];histo[20][ii] = h_ch21[ii];histo[21][ii] = h_ch22[ii];histo[22][ii] = h_ch23[ii];histo[23][ii] = h_ch24[ii];
        histo[24][ii] = h_ch25[ii];histo[25][ii] = h_ch26[ii];histo[26][ii] = h_ch27[ii];histo[27][ii] = h_ch28[ii];histo[28][ii] = h_ch29[ii];histo[29][ii] = h_ch30[ii];histo[30][ii] = h_ch31[ii];histo[31][ii] = h_ch32[ii];
    }
    ++i;
  }
  if (debug) printf("read %d lines", i);
  free(line);
  fclose(fp);
  rownum = atoi(argv[2]);
  res = plot_histogram(rownum,sectorname,histo);
  return 0;
}

int plot_histogram(int rownum, char **sectorname,unsigned short histo[32][MAXROW]){
  int i;
  FILE *fp;
  char fname[50], line[128], cmd[64];
  sprintf(fname, "%s%d%s","histogram",rownum,".plt");
  fp = fopen(fname, "w");
  fprintf(fp, "reset\n");
  fprintf(fp, "set term wxt\n");
  fprintf(fp, "set xlabel 'sectors'\n");
  fprintf(fp, "set ylabel 'counts'\n");
  fprintf(fp, "set style data histograms\n");
  fprintf(fp, "set style fill solid 1.0 border -1\n");
  fprintf(fp, "set xtics rotate by 90 right\n");
  fprintf(fp, "$file1 << EOD\n");
  for(i=0;i<32;++i){	
    fprintf(fp,"%d %u\n", i+1,histo[i][rownum]);
  }
  fprintf(fp, "EOD\n");
  sprintf(line, "plot $file1 using 2:xtic(1) title 'histogram%d' \n",rownum);
  fprintf(fp, line);
  fclose(fp);
  sprintf(cmd, "gnuplot -p %s\n", fname);
  printf(cmd);
  system(cmd); 
  return 0;	
}
