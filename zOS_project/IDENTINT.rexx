/* REXX */
/*
 * Description:
 * ============
 *
 *
 *
 * Notes:
 * ======
 *  - Check out the 'ToDo' occurrences if you are looking for work.
 *
 *  - It turned out to have a bit more difficalties
 *     o 04.4005 may not be followed by 04.4006
 *     o there might be multiple consecutive 04.4006 records in GTF
 *     o some records might be omitted in GTF at all - 03/04 records are in GTF
 *       in such cases
 *    As a result:
 *     o GTF might be not accurate (so INTTBL as well)
 *     o we can't guarantee that specific 04.4005 record matches to
 *       a specific 04.4006 record
 */

/* Initialize variables. */
Call Initialize

Call Put_IntTable_Header

Call Put_debug 'Start main processing'

/* Begin processing of the Trace and Listing files
 * and making the Interval Table output records
 */
prevSlipRecIsStd = 0
Do Forever
  Call Read_Trace_Rec
  If result /= 0 Then
    If result /= 4 Then Exit 9            /* DS not allocated or I/O error */
    Else Leave                              /* all records have been read */

  rec_FID  = c2x(Substr(trcRec,bnum_FID,1))
  rec_EID  = c2x(Substr(trcRec,bnum_EID,2))

  /* It's supposed to be one of the following records */
  Select
    When rec_FID = '04' & rec_EID = '4005' Then Do  /* SLIP std + usr trc rec */
      timeStmp = c2x(Substr(trcRec,bnum_timeStmp,8))
      Call Proc_SLIP_STDnUSR_Rec
      prevSlipRecIsStd = 1
    End
    When rec_FID = '04' & rec_EID = '4006' Then Do /* SLIP usr trc rec */
      If prevSlipRecIsStd = 1 Then Do
        Call Proc_SLIP_USR_Rec
        Call Put_Interval_Table_Entry
        Call Clear_Out_Variables
        prevSlipRecIsStd = 0
      End
    End
    When rec_FID = '01' Then Do               /* gtf control record */
      If Substr(trcRec,23,3) /= 'GTS' Then Do /* just to be sure */
        ts = c2x(Substr(trcRec,7,8))
        Call Put_debug 'Unrecognized GTF rec: FID=X''01'',',
                                          'eyec='Substr(trcRec,23,8)',',
                                            'ts='ts
      End
    End
    When rec_FID = '02' Then Do               /* some trc recs missed */
      If prevSlipRecIsStd = 1 Then Do
        Call Put_Interval_Table_Entry
        Call Clear_Out_Variables
        prevSlipRecIsStd = 0
      End

      ts = c2x(Substr(trcRec,7,8))
      queue 'WARN:'ts',FID=02,CNT=?'
      "EXECIO * DISKW INTTBL"
    End
    When rec_FID = '03' Then Do               /* entire block missed */
      If prevSlipRecIsStd = 1 Then Do
        Call Put_Interval_Table_Entry
        Call Clear_Out_Variables
        prevSlipRecIsStd = 0
      End

      ts = c2x(Substr(trcRec,7,8))
      queue 'WARN:'ts',FID=03,CNT=0'
      "EXECIO * DISKW INTTBL"
    End
    Otherwise Do
    /* we've met smth we are not familiar with; put SLIP Std Rec just in case */
      If prevSlipRecIsStd = 1 Then Do
        Call Put_Interval_Table_Entry
        Call Clear_Out_Variables
        prevSlipRecIsStd = 0
      End
      /* log the fact that unfamiliar rec has been met */
      Call Put_debug 'Unrecognized GTF rec: FID=X'''rec_FID''',trcRec='trcRec
    End
  End /* Select */
End /* Do Forever */

  If prevSlipRecIsStd = 1 Then Do
    Call Put_Interval_Table_Entry
    Call Clear_Out_Variables
    prevSlipRecIsStd = 0
  End

Call Be_Ready_To_Say_ByeBye
Call Put_debug 'We are here, so this is good enough'
Exit 0
/*******************************************************************************

*******************************************************************************/
Initialize:

Call Init_vars
Call Setup_debug

Return 0
/*******************************************************************************

*******************************************************************************/
Put_IntTable_Header:

header   = 'Interval table was generated on 'Date(U)' at 'Time(N)


/* ToDo: rework the way the variables below get put into the report header */
tblEntry = ''
tblEntry = tblEntry || 'timeStmp,'
tblEntry = tblEntry || ' jobName, pgmName, tcb@, modName, eyecatcher,'
tblEntry = tblEntry || ' inscode, ofstFr, brFr@,'
tblEntry = tblEntry || ' brTo@'  /* add %insCodeTo% and %ofstTo% */

queue header
queue ' '
queue tblEntry

"EXECIO * DISKW INTTBL"

Return 0
/*******************************************************************************
 Initialize work variables
*******************************************************************************/
Init_vars:

trcRecNum     = 1

bnum_FID      = 2                            /* L=1 Format identifier */
bnum_timeStmp = 3                            /* L=8 Time stamp        */
bnum_EID      = 11                           /* L=2 Event identifier  */
/* Fields from "SLIP standard + user trace record" */
bnum_jobName  = 19                           /* L=8 job name */
bnum_pgmName  = 33                           /* L=8 job step pgm name(U/A;N/A)*/
bnum_tcb@     = 41                           /* L=4 TCB address (or N/A)  */
bnum_modName  = 52                           /* L=8 load module name */
bnum_ofstFr   = 60                           /* L=4 offset in load module */
bnum_brFr@    = 64                           /* L=8 IADR */
bnum_insCode  = 72                           /* L=4 INS  */
bnum_brTo@    = 108                          /* L=8 OPSW field */
bnum_insCodeL = 116                          /* L=2 instruction code length */

/* Fields from "SLIP user trace record" */
bnum_dataLen  = 18                           /* L=2 */
bnum_data     = 20                           /* L=dataLen */
/* bnum_eyecLen and bnum_eyec are specific for the RTNBEGIN code */
bnum_eyecLen  = 24                           /* L=1 eyecatcher length */
bnum_eyec     = 25                           /* L=eyecLen eyecatcher */

/* Fields from Listing */
bnum_ltgLoc     = 2
bnum_ltgObjCode = 9
ltgCtchStrt     = 'Loc  Object Code    Addr1 Addr2  Stmt   Source Statement'
bnum_ltgCtchS   = 4
ltgCtchEnd      = 'Relocation Dictionary'
bnum_ltgCtchE   = 51
ltgSrchFr       = 0
ltgSrchTo       = 0
/*Call Set_Listing_Search_Indexes
If result /= 0 Then
  Return 8*/
Call Put_debug 'Init_vars: ltgSrchFr='ltgSrchFr', ltgSrchTo='ltgSrchTo

prtSymbols = '.()-/_#@ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'

Return 0
/*******************************************************************************

*******************************************************************************/
Setup_debug:

debugLevel    = 'trace'

Return 0
/*******************************************************************************

*******************************************************************************/
Put_debug:
parse arg debug_data

If debugLevel = 'trace' then
  do
    debug_data.1 = debug_data
    "EXECIO * DISKW DBG (STEM debug_data.)"
    drop debug_data.
  end

return 0
/*******************************************************************************
 Read a SLIP Trace record
*******************************************************************************/
Read_Trace_Rec:

"EXECIO 1 DISKR TRACEIN" trcRecNum
If trcRecNum = 1 Then
  If rc <> 0 Then                        /* DS not allocated or I/O error */
    Return 12
If rc <> 0 Then                          /* all records have been read - Exit */
  Do
    Return 4
  End
trcRecNum = trcRecNum + 1
Parse Pull trcRec                        /* get next trace record */
/*say trcRec*/
Return 0
/*******************************************************************************
 Process a "SLIP standard + user trace record"

 Note: c2x() returns string representing hex value
*******************************************************************************/
Proc_SLIP_STDnUSR_Rec:
/* Variables for an Interval Table record */
jobName      =   Space(Substr(trcRec,bnum_jobName,8))
pgmName      =   Space(Substr(trcRec,bnum_pgmName,8))
tcb@         =     c2x(Substr(trcRec,bnum_tcb@,4))
modName      =   Space(Substr(trcRec,bnum_modName,8))
ofstFr       =     c2x(Substr(trcRec,bnum_ofstFr,4))
insCodeL     = x2d(c2x(Substr(trcRec,bnum_insCodeL,2)))
insCode      =     c2x(Substr(trcRec,68,6))
brFr@        =     c2x(Substr(trcRec,bnum_brFr@,8))
brTo@        =     c2x(Substr(trcRec,bnum_brTo@,8))

say insCode
if Substr(insCode,11,2) = '40' then
  insCode = Substr(insCode,1,10)
say insCode
if Substr(insCode,9,2) = '40' then
  insCode = Substr(insCode,1,8)
say insCode
Return 0
/*******************************************************************************
 Process a "SLIP user trace record"
*******************************************************************************/
Proc_SLIP_USR_Rec:

/* Variables for an Interval Table record */

/* dataLen      = x2d(c2x(Substr(trcRec,bnum_dataLen,2)))
   data         =         Substr(trcRec,bnum_data,dataLen) */

eyecLen      = x2d(c2x(Substr(trcRec,bnum_eyecLen,1)))
eyecLen      = MIN(eyecLen,37) /* eyecatcher len is limited by SLIP trc parm */
eyecatcher   = Substr(trcRec,bnum_eyec,eyecLen)
If VERIFY(eyecatcher,prtSymbols,'N') /= 0 THEN /*dismiss invalid eye-catchers*/
  eyecatcher = ''

Return 0
/*******************************************************************************

*******************************************************************************/
Be_Ready_To_Say_ByeBye:

"EXECIO 0 DISKR LISTLIB (FINIS"
"EXECIO 0 DISKR TRACEIN (FINIS"
"EXECIO * DISKW INTTBL  (FINIS"
"EXECIO * DISKW DBG     (FINIS"

Return 0
/*******************************************************************************

*******************************************************************************/
Put_Interval_Table_Entry:

if eyecatcher = '' Then
  eyecatcher = 'None'

tblEntry = ''
tblEntry = tblEntry || timeStmp','
tblEntry = tblEntry || jobName','pgmName','tcb@','modName','eyecatcher','
tblEntry = tblEntry || insCode','ofstFr','brFr@','
tblEntry = tblEntry || brTo@  /* add %insCodeTo% and %ofstTo% */

/* say insCode  */

queue tblEntry
/* do not record listing entries for now
queue ltgRecFr
queue ltgRecTo                           */
"EXECIO * DISKW INTTBL"

Return 0
/*******************************************************************************

*******************************************************************************/
Clear_Out_Variables:

timeStmp = ''; jobName  = ''; pgmName = ''; tcb@ = ''; modName = '';
eyecatcher = ''; insCode  = ''; ofstFr   = ''; brFr@   = ''; brTo@   = '';

/* add %insCodeTo% and %ofstTo% */

Return 0
/*******************************************************************************

*******************************************************************************/
Put_drop_record_marker:

queue ' - - - - - > dropped record here'
"EXECIO * DISKW INTTBL"

Return 0