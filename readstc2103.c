#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Every program which uses the CFITSIO interface must include the
  the fitsio.h header file.  This contains the prototypes for all
  the routines and defines the error status values and other symbolic
  constants used in the interface.  
*/
#include "fitsio.h"

int main( int argc, char **argv );
int readheader( char *fname );
int readtable( char *fname );
void printerror( int status);

int main(int argc, char **argv)
{
/*************************************************************************
   This is a simple main program that calls the following routines:

    readheader    - read and print the header keywords in every extension
    readtable     - read columns of data from ASCII and binary tables

**************************************************************************/
    int status=0;
    char *myfname=argv[1];
    status = readheader(myfname);
    status = readtable(myfname); 

    printf("\nAll the cfitsio routines ran successfully.\n");
    return 0;
}
/*--------------------------------------------------------------------------*/
int readheader ( char *fname )

    /**********************************************************************/
    /* Print out all the header keywords in all extensions of a FITS file */
    /**********************************************************************/
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */

    int status, nkeys, keypos, hdutype, ii, jj;
    char *filename  = fname;     /* name of existing FITS file   */
    char card[FLEN_CARD];   /* standard string lengths defined in fitsioc.h */

    status = 0;

    if ( fits_open_file(&fptr, filename, READONLY, &status) ) 
         printerror( status );

    /* attempt to move to next HDU, until we get an EOF error */
    for (ii = 1; !(fits_movabs_hdu(fptr, ii, &hdutype, &status) ); ii++) 
    {
        /* get no. of keywords */
        if (fits_get_hdrpos(fptr, &nkeys, &keypos, &status) )
            printerror( status );

        printf("Header listing for HDU #%d:\n", ii);
        for (jj = 1; jj <= nkeys; jj++)  {
            if ( fits_read_record(fptr, jj, card, &status) )
                 printerror( status );

            printf("%s\n", card); /* print the keyword card */
        }
        printf("END\n\n");  /* terminate listing with END */
    }

    if (status == END_OF_FILE)   /* status values are defined in fitsioc.h */
        status = 0;              /* got the expected EOF error; reset = 0  */
    else
       printerror( status );     /* got an unexpected error                */

    if ( fits_close_file(fptr, &status) )
         printerror( status );

    return 0;
}

/*--------------------------------------------------------------------------*/
int readtable( char *fname )

    /************************************************************/
    /* read and print data values from an ASCII or binary table */
    /************************************************************/
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
    int status, hdunum, hdutype, nfound, anynull, ii,j;
    int maxcol=59, maxcol2=3, maxrow=1;
    /*CCSDS Packet header data*/
    unsigned char vernum[maxrow];
    unsigned char pkttype[maxrow];
    unsigned char dfhflag[maxrow];
    unsigned char pid[maxrow];
    unsigned char cat[maxrow]; /* category */
    unsigned short apid[maxrow];
    unsigned char seqflag[maxrow];
    unsigned short srcseqcnt[maxrow];
    unsigned short pktlength[maxrow];
    unsigned char bytenull;
    /* Data Field Header Data */
    unsigned char spare0[maxrow];
    unsigned char pusver[maxrow];
    unsigned char spare1[maxrow];
    unsigned char type[maxrow];
    unsigned char subtype[maxrow];
    unsigned char dest[maxrow]; /* destination */
    unsigned short timemsw[maxrow];
    unsigned short timelsw[maxrow];
    unsigned short subsec[maxrow];
	double time[maxrow];
	/* Data Field*/
	unsigned short priv_sci_head_MSW[maxrow];
	unsigned short priv_sci_head_LSW[maxrow];
    unsigned short fr_lobt_msw[maxrow];
    unsigned short fr_lobt_lsw[maxrow];
    unsigned short fr_lobt_subs[maxrow];
    unsigned short rk_frame[maxrow];
    unsigned short stc_hk_00_01[maxrow];
    unsigned short stc_hk_02_03[maxrow];
    unsigned short stc_hk_04_05[maxrow];
    unsigned short stc_hk_06_07[maxrow];
    unsigned short stc_hk_08_09[maxrow];
    unsigned short stc_hk_10_11[maxrow];
    unsigned short stc_hk_12_13[maxrow];
    unsigned short stc_hk_14_15[maxrow];
    unsigned short stc_hk_16_17[maxrow];
    unsigned short stc_hk_18_19[maxrow];
    unsigned short stc_hk_20_21[maxrow];
    unsigned short stc_hk_22_23[maxrow];
    unsigned short stc_hk_24_25[maxrow];
    unsigned short stc_hk_26_27[maxrow];
    unsigned short stc_hk_28_29[maxrow];
    unsigned short stc_hk_30_31[maxrow];
    unsigned short stc_hk_32_33[maxrow];
    unsigned short stc_hk_34_35[maxrow];
    unsigned short stc_hk_36_37[maxrow];
    unsigned short stc_hk_38_39[maxrow];
    unsigned short stc_hk_40_41[maxrow];
    unsigned short stc_hk_42_43[maxrow];
    unsigned short stc_hk_44_45[maxrow];
    unsigned short stc_hk_46_47[maxrow];
    unsigned short stc_hk_48_49[maxrow];
    unsigned short stc_hk_50_51[maxrow];
    unsigned short stc_hk_52_53[maxrow];
    unsigned short stc_hk_54_55[maxrow];
    unsigned short stc_hk_56_57[maxrow];
    unsigned short stc_hk_58_59[maxrow];
    unsigned short stc_hk_60_61[maxrow];
    unsigned short stc_hk_62_63[maxrow];
    double fr_lobt[maxrow];
    unsigned int stc_sci[maxrow][1005];
    long frow, felem, nelem, longnull, pktnumb[maxrow];
    float floatnull; double doublenull;
    unsigned short uintnull;
    char strnull[10], *ttype[maxcol], *ttype2[maxcol2]; 

    char *filename  = fname;     /* name of existing FITS file   */
    status = 0;
    for (ii = 0; ii < maxcol; ii++)      /* allocate space for the column labels */
        ttype[ii] = (char *) malloc(FLEN_VALUE);  /* max label length = 69 */

    if ( fits_open_file(&fptr, filename, READONLY, &status) )
         printerror( status );

    for (ii = 0; ii < maxcol2; ii++)      // allocate space for the column labels 
        ttype2[ii] = (char *) malloc(FLEN_VALUE);  // max label length = 69 

      hdunum = 2;
      /* move to the HDU */
      if ( fits_movabs_hdu(fptr, hdunum, &hdutype, &status) ) 
           printerror( status );

          printf("\nReading PACKETS table in HDU %d:\n",  hdunum);

      /* read the column names from the TTYPEn keywords */
      fits_read_keys_str(fptr, "TTYPE", 1, maxcol, ttype, &nfound, &status);
	  printf("n. of keys found: %d\n", nfound);
      printf(" Row  %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s\n", ttype[0], ttype[1], ttype[2], \
      ttype[3], ttype[4], ttype[5], ttype[6], ttype[7], ttype[8], ttype[9], ttype[10], ttype[11],ttype[12],ttype[13],ttype[14],ttype[15],ttype[16],ttype[17], \
      ttype[18],ttype[19]);

      frow      = 1;
      felem     = 1;
      nelem     = maxrow;
      strcpy(strnull, " ");
      uintnull = 0;
      longnull  = 0;
      floatnull = 0.;
      doublenull = 0.;
      bytenull = 0;

      /*  read the columns: CCSDS HEADER */  
      fits_read_col(fptr, TINT32BIT, 1, frow, felem, nelem, &longnull, pktnumb,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 2, frow, felem, nelem, &bytenull,  vernum,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 3, frow, felem, nelem, &bytenull, pkttype,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 4, frow, felem, nelem, &bytenull, dfhflag,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 5, frow, felem, nelem, &bytenull, pid,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 6, frow, felem, nelem, &bytenull, cat,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 7, frow, felem, nelem, &uintnull, apid,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 8, frow, felem, nelem, &bytenull, seqflag,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 9, frow, felem, nelem, &uintnull, srcseqcnt,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 10, frow, felem, nelem, &uintnull, pktlength,
                    &anynull, &status);
      /*  read the columns: DATA FIELD HEADER */  
      fits_read_col(fptr, TBYTE, 11, frow, felem, nelem, &bytenull, spare0,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 12, frow, felem, nelem, &bytenull, pusver,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 13, frow, felem, nelem, &bytenull, spare1,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 14, frow, felem, nelem, &bytenull, type,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 15, frow, felem, nelem, &bytenull, subtype,
                    &anynull, &status);
      fits_read_col(fptr, TBYTE, 16, frow, felem, nelem, &bytenull, dest,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 17, frow, felem, nelem, &uintnull, timemsw,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 18, frow, felem, nelem, &uintnull, timelsw,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 19, frow, felem, nelem, &uintnull, subsec,
                    &anynull, &status);
      fits_read_col(fptr, TDOUBLE, 20, frow, felem, nelem, &doublenull, time,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 21, frow, felem, nelem, &uintnull, priv_sci_head_MSW,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 22, frow, felem, nelem, &uintnull, priv_sci_head_LSW,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 23, frow, felem, nelem, &uintnull, fr_lobt_msw,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 24, frow, felem, nelem, &uintnull, fr_lobt_lsw,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 25, frow, felem, nelem, &uintnull, fr_lobt_subs,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 26, frow, felem, nelem, &uintnull, rk_frame,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 27, frow, felem, nelem, &uintnull, stc_hk_00_01,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 28, frow, felem, nelem, &uintnull, stc_hk_02_03,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 29, frow, felem, nelem, &uintnull, stc_hk_04_05,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 30, frow, felem, nelem, &uintnull, stc_hk_06_07,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 31, frow, felem, nelem, &uintnull, stc_hk_08_09,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 32, frow, felem, nelem, &uintnull, stc_hk_10_11,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 33, frow, felem, nelem, &uintnull, stc_hk_12_13,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 34, frow, felem, nelem, &uintnull, stc_hk_14_15,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 35, frow, felem, nelem, &uintnull, stc_hk_16_17,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 36, frow, felem, nelem, &uintnull, stc_hk_18_19,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 37, frow, felem, nelem, &uintnull, stc_hk_20_21,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 38, frow, felem, nelem, &uintnull, stc_hk_22_23,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 39, frow, felem, nelem, &uintnull, stc_hk_24_25,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 40, frow, felem, nelem, &uintnull, stc_hk_26_27,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 41, frow, felem, nelem, &uintnull, stc_hk_28_29,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 42, frow, felem, nelem, &uintnull, stc_hk_30_31,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 43, frow, felem, nelem, &uintnull, stc_hk_32_33,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 44, frow, felem, nelem, &uintnull, stc_hk_34_35,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 45, frow, felem, nelem, &uintnull, stc_hk_36_37,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 46, frow, felem, nelem, &uintnull, stc_hk_38_39,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 47, frow, felem, nelem, &uintnull, stc_hk_40_41,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 48, frow, felem, nelem, &uintnull, stc_hk_42_43,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 49, frow, felem, nelem, &uintnull, stc_hk_44_45,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 50, frow, felem, nelem, &uintnull, stc_hk_46_47,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 51, frow, felem, nelem, &uintnull, stc_hk_48_49,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 52, frow, felem, nelem, &uintnull, stc_hk_50_51,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 53, frow, felem, nelem, &uintnull, stc_hk_52_53,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 54, frow, felem, nelem, &uintnull, stc_hk_54_55,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 55, frow, felem, nelem, &uintnull, stc_hk_56_57,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 56, frow, felem, nelem, &uintnull, stc_hk_58_59,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 57, frow, felem, nelem, &uintnull, stc_hk_60_61,
                    &anynull, &status);
      fits_read_col(fptr, TUSHORT, 58, frow, felem, nelem, &uintnull, stc_hk_62_63,
                    &anynull, &status);
      fits_read_col(fptr, TDOUBLE, 59, frow, felem, nelem, &doublenull, fr_lobt,
                    &anynull, &status);

    for (ii = 0; ii < maxcol; ii++)      /* free the memory for the column labels */
        free( ttype[ii] );

      for (ii = 0; ii < maxrow; ii++)
        printf("%d %10ld %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10.6f\n", ii + 1, pktnumb[ii], vernum[ii], pkttype[ii], dfhflag[ii], \
        pid[ii], cat[ii], apid[ii], seqflag[ii], srcseqcnt[ii], pktlength[ii], \
        spare0[ii], pusver[ii], spare1[ii], type[11], subtype[ii], dest[ii], timemsw[ii], timelsw[ii], subsec[ii], time[ii] );

    hdunum = 3;
    maxcol = 3;
/*    for (ii = 0; ii < maxcol; ii++)      // allocate space for the column labels
        ttype[ii] = (char *) malloc(FLEN_VALUE);  // max label length =  
*/
     printf("\nReading STC-SCI table in HDU %d:\n", hdunum); 
      /* move to the 3rd HDU */
      if ( fits_movabs_hdu(fptr, hdunum, &hdutype, &status) ) 
           printerror( status );
           
      /* read the column names from the TTYPEn keywords */
      fits_read_keys_str(fptr, "TTYPE", 1, maxcol, ttype, &nfound, &status);
	  printf("n. of keys found: %d\n", nfound);
      printf(" Row  %10s %10s %10s\n",ttype[0], ttype[1], ttype[2]);
           
      /*  read the columns: DATA FIELD */  
      fits_read_col(fptr, TINT32BIT, 1, frow, felem, nelem, &longnull, pktnumb,
                    &anynull, &status);
      printf("read packet number \n");
/*      fits_read_col(fptr, TDOUBLE, 2, frow, felem, nelem, &doublenull, fr_lobt,
                    &anynull, &status);*/
      nelem=1005;
      fits_read_col(fptr, TUINT, 3, frow, felem, nelem, &uintnull, *stc_sci,
                    &anynull, &status);
      printf("read stc_sci array \n");
	 // print the table 
      for (ii = 0; ii < maxrow; ii++){
        printf("%d %10ld %10.6f \n", ii + 1, pktnumb[ii],fr_lobt[ii] );
        for (j=0;j<1005;j++)
          printf("%4X \n", stc_sci[ii][j] );
  }
  
    for (ii = 0; ii < maxcol2; ii++)      // free the memory for the column labels 
        free( ttype2[ii] );
        /* free the memory for the string column */
           
          
    if ( fits_close_file(fptr, &status) ) 
         printerror( status );

    return status;
}
/*--------------------------------------------------------------------------*/
void printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/


    if (status)
    {
       fits_report_error(stderr, status); /* print error report */

       exit( status );    /* terminate the program, returning error status */
    }
    return;
}
