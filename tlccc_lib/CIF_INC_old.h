#ifndef YATLCCLC_CIFINC_H_INCLUDED
#define YATLCCLC_CIFINC_H_INCLUDED

/*
 * CVN Commissie C
 * bestand: CIF.INC
 * versie 12 oktober 2011
 */

typedef char  s_int8;  /* signed char 8 bits */
typedef short s_int16; /* signed integer 16 bits */
typedef long  s_int32; /* signed integer 32 bits */

#ifdef CIF_PUBLIC

					   /* MAXIMUM GRENZEN INTERFACEBUFFERS */
					   /* -------------------------------- */
#define CIF_AANT_IS_D   DPMAX	/* aantal detectie-ingangen	*/
#define CIF_AANT_IS_OV  ISMAX-DPMAX	/* aantal overige ingangen	*/
#define CIF_AANT_US_FC  FCMAX	/* aantal fasecycli		*/
#define CIF_AANT_US_OV  USMAX-FCMAX  /* aantal overige uitgangen	*/
#endif

#ifndef NO_CIF_DSI   
#define CIF_AANT_DSI    36 		/* grootte CIF_DSI[]-buffer   	*/
#endif

#define CIF_AANT_GPS    7		/* grootte CIF_GPS[]-buffer   	*/
#define CIF_AANT_WPS    7		/* grootte CIF_WPS[]-buffer   	*/
#define CIF_AANT_KLOK   9		/* grootte CIF_KLOK[]-buffer	*/

#ifdef CIF_PUBLIC
#define CIF_MAX_IBER    256		/* grootte CIF_IBER[]-buffer	*/
#define CIF_MAX_UBER    2048 	/* grootte CIF_UBER[]-buffer	*/

#ifndef NO_CIF_MON
#define CIF_MAX_MON_IBER    256	/* grootte CIF_MON_IBER[]-buffer */
#define CIF_MAX_MON_UBER   2048 	/* grootte CIF_MON_UBER[]-buffer */
#endif

#if !defined (NO_VLOG_200) & !defined (NO_CVN_40)
#define CIF_MAX_FILE_UBER  16384 	/* grootte CIF_FILE_UBER[]-buffer */
#define CIF_MAX_FILEEXT        5	/* grootte CIF_FILE_UBER_FILEEXT[]-buffer */
#endif /* NO_VLOG_200 en NO_CVN_40  */

#define CIF_AANT_PARM1  PARM1MAX	/* grootte CIF_PARM1[]-buffer	*/
#ifdef PARM2MAX
#define CIF_AANT_PARM2  PARM2MAX	/* grootte CIF_PARM2[]-buffer	*/
#else
#define CIF_AANT_PARM2  1		/* geen CIF_PARM2[]-buffer 	*/
#endif

#ifdef PARM4MAX
#define CIF_AANT_PARM4  PARM4MAX	/* grootte CIF_PARM4[]-buffer	*/
#endif

#endif	/* CIF_PUBLIC	*/

#ifndef NO_CIF_DSI   
   #define CIF_AANT_DSI    36 		/* grootte CIF_DSI[]-buffer   	*/
#endif

   #define CIF_AANT_GPS    7		/* grootte CIF_GPS[]-buffer   	*/
   #define CIF_AANT_WPS    7		/* grootte CIF_WPS[]-buffer   	*/
   #define CIF_AANT_KLOK   9		/* grootte CIF_KLOK[]-buffer	*/

# ifdef CIF_PUBLIC
s_int16 CIF_GUS [CIF_AANT_US_FC + CIF_AANT_US_OV]; /* CIF_GUS[ ]-buffer */
const s_int16 CIF_PB_AANT_US_FC = CIF_AANT_US_FC; /* aantal fasecycli in CIF_GUS- en
CIF_WUS-buffer */
const s_int16 CIF_PB_AANT_US_OV = CIF_AANT_US_OV; /* aantal overige uitgangen in
CIF_GUS- en CIF_WUS-buffer */
s_int16 CIF_WUS [CIF_AANT_US_FC + CIF_AANT_US_OV]; /* CIF_WUS[ ]-buffer */
s_int16 CIF_IS [CIF_AANT_IS_D + CIF_AANT_IS_OV]; /* CIF_IS[ ]-buffer */
const s_int16 CIF_PB_AANT_IS_D = CIF_AANT_IS_D; /* aantal detectoren in CIF_IS
buffer */
const s_int16 CIF_PB_AANT_IS_OV = CIF_AANT_IS_OV; /* aantal overige ingangen in CIF_IS
buffer */
s_int16 CIF_DSI[CIF_AANT_DSI]; /* CIF_DSI[] buffer */
const s_int16 CIF_PB_AANT_DSI= CIF_AANT_DSI; /* grootte CIF_DSI buffer */
s_int16 CIF_DSIWIJZ ; /* vlag CIF_DSI[]-buffer gewijzigd */
s_int16 CIF_GPS [CIF_AANT_GPS]; /* CIF_GPS[ ]-buffer */
const s_int16 CIF_PB_AANT_GPS = CIF_AANT_GPS; /* grootte CIF_GPS buffer */
s_int16 CIF_WPS [CIF_AANT_WPS]; /* CIF_WPS[ ]-buffer */
const s_int16 CIF_PB_AANT_WPS = CIF_AANT_WPS; /* grootte CIF_WPS buffer */
s_int8 CIF_UBER [CIF_MAX_UBER]; /* CIF_UBER[ ]-buffer */
const s_int16 CIF_PB_MAX_UBER= CIF_MAX_UBER; /* grootte CIF_UBER buffer */
s_int8 CIF_IBER [CIF_MAX_IBER]; /* CIF_IBER[ ]-buffer */
const s_int16 CIF_PB_MAX_IBER= CIF_MAX_IBER; /* grootte CIF_IBER buffer */
s_int8 *CIF_UBER_LEES; /* pointer naar te lezen bericht */

s_int8 *CIF_UBER_SCHRIJF; /* pointer naar te schrijven
bericht */
s_int8 *CIF_IBER_LEES; /* pointer naar te lezen bericht */
s_int8 *CIF_IBER_SCHRIJF; /* pointer naar te schrijven
bericht */

#ifndef NO_CIF_MON
s_int8 CIF_MON_IBER [CIF_MAX_MON_IBER]; /* CIF_MON_IBER[]-buffer */
const s_int16 CIF_PB_MAX_MON_IBER= CIF_MAX_MON_IBER; /* grootte CIF_MON_IBER buffer */
s_int8 *CIF_MON_IBER_LEES; /* pointer naar te lezen bericht */
s_int8 *CIF_MON_IBER_SCHRIJF; /* pointer naar te schrijven
bericht */
s_int8 CIF_MON_UBER [CIF_MAX_MON_UBER]; /* CIF_MON_UBER[]-buffer */
const s_int16 CIF_PB_MAX_MON_UBER= CIF_MAX_MON_UBER; /* grootte CIF_MON_UBER buffer */
s_int8 *CIF_MON_UBER_LEES; /* pointer naar te lezen bericht */
s_int8 *CIF_MON_UBER_SCHRIJF; /* pointer naar te schrijven
bericht */
s_int8 CIF_FILE_UBER[CIF_MAX_FILE_UBER]; /* CIF_FILE_UBER[ ] – buffer */
const s_int16 CIF_PB_MAX_FILE_UBER= CIF_MAX_FILE_UBER; /* grootte CIF_FILE_UBER buffer */
s_int8 *CIF_FILE_UBER_LEES; /* pointer naar te lezen bericht */
s_int8 *CIF_FILE_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int16 CIF_FILE_UBER_STATUS; /*status van fileopslag */
s_int8 *CIF_FILE_UBER_FILEWISSEL; /* pointer voor het aangeven van een filewisselpunt */
s_int16 CIF_PB_FILE_UBER_FILEWISSEL; /* aanvraag voor een (extra) filewisselpunt */
s_int8 CIF_FILE_UBER_FILEEXT[CIF_MAX_FILEEXT]; /* gewenste file-extensie */
/* (null-terminated string) */
#endif

s_int16 CIF_KLOK [CIF_AANT_KLOK]; /* CIF_KLOK[ ]-buffer */
const s_int16 CIF_PB_AANT_KLOK= CIF_AANT_KLOK; /* grootte CIF_KLOK buffer */
s_int16 CIF_PARM1 [CIF_AANT_PARM1]; /* CIF_PARM1[ ]-buffer */
const s_int16 CIF_PB_AANT_PARM1 = CIF_AANT_PARM1; /* grootte CIF_PARM1 buffer */
s_int32 CIF_PARM2 [CIF_AANT_PARM2]; /* CIF_PARM2[ ]-buffer */
const s_int16 CIF_PB_AANT_PARM2 = CIF_AANT_PARM2; /* grootte CIF_PARM2 buffer */
s_int16 CIF_ISWIJZ; /* vlag CIF_IS[ ]-buffer gewijzigd */
s_int16 CIF_WUSWIJZ; /* vlag CIF_WUS[ ]-buffer gewijzigd */
s_int16 CIF_WPSWIJZ; /* vlag CIF_WPS[ ]-buffer gewijzigd */
s_int16 CIF_GUSWIJZ; /* vlag CIF_GUS[ ]-buffer gewijzigd */
s_int16 CIF_GPSWIJZ; /* vlag CIF_GPS[ ]-buffer gewijzigd */
s_int16 CIF_PARM1WIJZPB; /* vlag CIF_PARM1[ ]-buffer gewijzigd
door */
s_int16 CIF_PARM2WIJZPB; /* vlag CIF_PARM2[ ]-buffer gewijzigd
door */
s_int16 CIF_PARM1WIJZAP; /* vlag CIF_PARM1[ ]-buffer gewijzigd
door */
s_int16 CIF_PARM2WIJZAP; /* vlag CIF_PARM2[ ]-buffer gewijzigd
door */
#ifdef CIF_WEL_OT
const s_int16 CIF_OT = 1; /* Gebruik ontruimingstijden in de interface */
#else
const s_int16 CIF_OT = 0; /* Geen gebruik ontruimingstijden in de interface */
#endif
#else
	extern s_int16 CIF_GUS[]; /* CIF_GUS[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_US_FC; /* aantal fasecycli in CIF_GUS- en CIF_WUS-buffer */
	extern const s_int16 CIF_PB_AANT_US_OV; /* aantal overige uitgangen in CIF_GUS- en`CIF_WUS-buffer */
	extern s_int16 CIF_WUS[]; /* CIF_WUS[ ]-buffer */
	extern s_int16 CIF_IS[]; /* CIF_IS[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_IS_D; /* aantal detectoren in CIF_IS buffer */
	extern const s_int16 CIF_PB_AANT_IS_OV; /* aantal overige ingangen in CIF_IS buffer */
	extern s_int16 CIF_DSI[]; /* CIF_DSI[] buffer */
	extern const s_int16 CIF_PB_AANT_DSI; /* grootte CIF_DSI buffer */
	extern s_int16 CIF_DSIWIJZ; /* vlag CIF_DSI[]-buffer gewijzigd */
	extern s_int16 CIF_GPS[]; /* CIF_GPS[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_GPS; /* grootte CIF_GPS buffer */
	extern s_int16 CIF_WPS[]; /* CIF_WPS[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_WPS; /* grootte CIF_WPS buffer */
	extern s_int8 CIF_UBER[]; /* CIF_UBER[ ]-buffer */
	extern const s_int16 CIF_PB_MAX_UBER; /* grootte CIF_UBER buffer */
	extern s_int8 CIF_IBER[]; /* CIF_IBER[ ]-buffer */
	extern const s_int16 CIF_PB_MAX_IBER; /* grootte CIF_IBER buffer */
	extern s_int8 *CIF_UBER_LEES; /* pointer naar te lezen bericht */
	extern s_int8 *CIF_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
	extern s_int8 *CIF_IBER_LEES; /* pointer naar te lezen bericht */
	extern s_int8 *CIF_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
	extern s_int8 CIF_MON_IBER[]; /* CIF_MON_IBER[]-buffer */
	extern const s_int16 CIF_PB_MAX_MON_IBER; /* grootte CIF_MON_IBER buffer */
	extern s_int8 *CIF_MON_IBER_LEES; /* pointer naar te lezen bericht */
	extern s_int8 *CIF_MON_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
	extern s_int8 CIF_MON_UBER[]; /* CIF_MON_UBER[]-buffer */
	extern const s_int16 CIF_PB_MAX_MON_UBER; /* grootte CIF_MON_UBER buffer */
	extern s_int8 *CIF_MON_UBER_LEES; /* pointer naar te lezen bericht */
	extern s_int8 *CIF_MON_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
	extern s_int8 CIF_FILE_UBER[]; /* CIF_FILE_UBER[]-buffer */
	extern const s_int16 CIF_PB_MAX_FILE_UBER; /* grootte CIF_FILE_UBER buffer */
	extern s_int8 *CIF_FILE_UBER_LEES; /* pointer naar te lezen bericht */
	extern s_int8 *CIF_FILE_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
	extern s_int16 CIF_FILE_UBER_STATUS; /*status van fileopslag */
	extern s_int8 *CIF_FILE_UBER_FILEWISSEL; /* pointer voor het aangeven van een filewisselpunt */
	extern s_int16 CIF_PB_FILE_UBER_FILEWISSEL; /* aanvraag voor een(extra) filewisselpunt */
	extern s_int8 CIF_FILE_UBER_FILEEXT[]; /* gewenste file-extensie */
										   /* (null-terminated string) */
	extern s_int16 CIF_KLOK[]; /* CIF_KLOK[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_KLOK; /* grootte CIF_KLOK buffer */
	extern s_int16 CIF_PARM1[]; /* CIF_PARM1[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_PARM1; /* grootte CIF_PARM1 buffer */
	extern s_int32 CIF_PARM2[]; /* CIF_PARM2[ ]-buffer */
	extern const s_int16 CIF_PB_AANT_PARM2; /* grootte CIF_PARM2 buffer */
	extern s_int16 CIF_ISWIJZ; /* vlag CIF_IS[ ]-buffer gewijzigd */
	extern s_int16 CIF_WUSWIJZ; /* vlag CIF_WUS[ ]-buffer gewijzigd */
	extern s_int16 CIF_WPSWIJZ; /* vlag CIF_WPS[ ]-buffer gewijzigd */
	extern s_int16 CIF_GUSWIJZ; /* vlag CIF_GUS[ ]-buffer gewijzigd */
	extern s_int16 CIF_GPSWIJZ; /* vlag CIF_GPS[ ]-buffer gewijzigd */
	extern s_int16 CIF_PARM1WIJZPB; /* vlag CIF_PARM1[ ]-buffer gewijzigd door */
	extern s_int16 CIF_PARM2WIJZPB; /* vlag CIF_PARM2[ ]-buffer gewijzigd door */
	extern s_int16 CIF_PARM1WIJZAP; /* vlag CIF_PARM1[ ]-buffer gewijzigd door */
	extern s_int16 CIF_PARM2WIJZAP; /* vlag CIF_PARM2[ ]-buffer gewijzigd door */
	extern const s_int16 CIF_OT; /* Gebruik ontruimingstijden in interface */

#endif

/* CIF_GUS[ ] en CIF_WUS[ ] */
#define CIF_ROOD    0 /* rood */
#define CIF_GROEN   1 /* groen / wit / wit knipperen */
#define CIF_GEEL    2 /* geel / groen knipperen */
#define CIF_KNIPWIT 3 /* wit knipperen */
#define CIF_GEDOOFD 4 /* lantaarn(s) gedoofd */
/* CIF_IS[ ] */
#define CIF_DET_BEZET       1 /* detectie bezet */
#define CIF_DET_STORING     2 /* detectie storing */
#define CIF_DET_BOVENGEDRAG 4 /* detectie bovengedrag */
#define CIF_DET_ONDERGEDRAG 8 /* detectie ondergedrag */
/* CIF_GPS [ ] en CIF_WPS [ ] */
#define CIF_PROG_STATUS 0 /* CIF_GPS en CIF_WPS */
/* programmastatus buffer */
#define CIF_PROG_FOUT 1 /* CIF_GPS en CIF_WPS */
/* programma-foutbuffer */
/* CIF_GPS [CIF_PROG_STATUS] */
/* en CIF_WPS [CIF_PROG_STATUS] */
#define CIF_STAT_ONGEDEF 0 /* ongedefinieerd */
#define CIF_STAT_GEDOOFD 1 /* gedoofd */
#define CIF_STAT_KP      2 /* knipperen */
#define CIF_STAT_GEEL    3 /* geel bij inschakelen */
#define CIF_STAT_AR      4 /* alles rood */
#define CIF_STAT_REG     5 /* regelen */
/* CIF_GPS [CIF_PROG_FOUT] */
#define CIF_GEEN_FOUT 0 /* geldt ook voor */
/* CIF_WPS [CIF_PROG_FOUT] en */
/* return-waarde */
/* applicatieprogramma() */
#define CIF_FB_FOUT  1 /* fasebewaking */
#define CIF_AP_FOUT2 2 /* procesbesturing wacht te lang met */
/* lezen van door het applicatie- */
/* programma geschreven informatie */
#define CIF_AP_FOUT3 4 /* applicatieprogramma leest een */
/* niet gedefinieerde code */
/* CIF_WPS [CIF_PROG_FOUT] */
#define CIF_PB_FOUT1 1 /* werkelijke uitgangssturing te lang */
/* ongelijk aan gewenste uitgangs- */
/* sturing */
#define CIF_PB_FOUT2 2 /* applicatieprogramma wacht te lang */
/* met lezen van door de proces- */
/* besturing geschreven informatie */
#define CIF_PB_FOUT3 4 /* procesbesturing leest een niet */
/* gedefinieerde code */
#define CIF_PB_FOUT4 8 /* applicatieprogramma duurt te lang */
/* CIF_KLOK[ ] */
#define CIF_JAAR        0 /* jaartal */
#define CIF_MAAND       1 /* maand 1..12 */
#define CIF_DAG         2 /* dag van de maand 1..31 */
#define CIF_DAGSOORT    3 /* dag van de week 0..6 */
#define CIF_UUR         4 /* uur van de dag 0..23 */
#define CIF_MINUUT      5 /* minuut 0..59 */
#define CIF_SECONDE     6 /* seconde 0..59 */
#define CIF_SEC_TELLER  7 /* seconden teller 0..32767 */
#define CIF_TSEC_TELLER 8 /* tienden sec teller 0..32767 */
/* CIF_KLOK[DAGSOORT] */
#define CIF_ZONDAG    0 /* zondag */
#define CIF_MAANDAG   1 /* maandag */
#define CIF_DINSDAG   2 /* dinsdag */
#define CIF_WOENSDAG  3 /* woensdag */
#define CIF_DONDERDAG 4 /* donderdag */
#define CIF_VRIJDAG   5 /* vrijdag */
#define CIF_ZATERDAG  6 /* zaterdag */

/* lees en schrijf vlaggen */
#define CIF_GESCHREVEN     1 /* in buffer geschreven */
#define CIF_GELEZEN        0 /* buffer gelezen */
#define CIF_GEEN_PARMWIJZ -1 /* geen wijzigingen in */
/* parameterbuffer */
#define CIF_MEER_PARMWIJZ -2 /* meerdere wijzigingen in */
/* parameterbuffer */
#define CIF_INIT_PARM     -3 /* initiele waarden in */
/* parameterbuffer */
/* aanroep en returnwaarde applicatieprogramma() */
#define CIF_GEEN_INIT 0 /* 'normale' aanroep */
#define CIF_INIT      1 /* init na programmastart */
/*
#define CIF_GEEN_FOUT 0 zie CIF_GPS[CIF_PROG_FOUT
*/
#define CIF_INIT_FOUT -1 /* initialisatie fout */
/* CIF_DSI */
/* codering van de elementen */
/* ------------------------- */
#define CIF_DSI_LUS    0 /* lusnummer */
#define CIF_DSI_VTG    1 /* voertuigcategorie */
#define CIF_DSI_LYN    2 /* lijnnummer */
#define CIF_DSI_WDNST  3 /* wagendienstnummer */
#define CIF_DSI_BEDR   4 /* bedrijfsnummer */
#define CIF_DSI_NUM    5 /* voertuignummer */
#define CIF_DSI_DIR    6 /* richtingsnummer */
#define CIF_DSI_STAT   7 /* voertuigstatus */
#define CIF_DSI_PRI    8 /* prioriteitsklasse */
#define CIF_DSI_STP    9 /* stiptheidsklasse */
#define CIF_DSI_TSTP  10 /* stiptheid [s] */
#define CIF_DSI_LEN   11 /* voertuiglengte [m] */
#define CIF_DSI_SPD   12 /* voertuigsnelheid [m/s] */
#define CIF_DSI_LSS   13 /* afstand tot stopstreep [m] */
#define CIF_DSI_TSS   14 /* passeertijd stopstreep [s] */
#define CIF_DSI_RIT   15 /* ritnummer */
#define CIF_DSI_RITC  16 /* ritcategorie */
#define CIF_DSI_ROUT  17 /* routenummer openbaar vervoer */
#define CIF_DSI_TYPE  18 /* type melding */
#define CIF_DSI_OVC   19 /* codering meldpunt */
/* openbaar vervoer */
#define CIF_DSI_XGRAD 20 /* breedtegraad graden */
#define CIF_DSI_XMIN  21 /* breedtegraad minuten */
#define CIF_DSI_XSEC  22 /* breedtegraad seconden */
#define CIF_DSI_XHSEC 23 /* breedtegraad honderdste seconden */
#define CIF_DSI_YGRAD 24 /* lengtegraad graden */
#define CIF_DSI_YMIN  25 /* lengtegraad minuten */
#define CIF_DSI_YSEC  26 /* lengtegraad seconden */
#define CIF_DSI_YHSEC 27 /* lengtegraad honderdste seconden */
#define CIF_DSI_JAAR  28 /* jaartal */
#define CIF_DSI_MND   29 /* maand */
#define CIF_DSI_DAG   30 /* dag */
#define CIF_DSI_UUR   31 /* uur */
#define CIF_DSI_MIN   32 /* minuten */
#define CIF_DSI_SEC   33 /* seconden */
#define CIF_DSI_RES1  34 /* reserve 1 */
#define CIF_DSI_RES2  35 /* reserve 2 */

/* afwijkende defaultwaarden */
/* ------------------------- */
#define CIF_DSI_TSTP_DEF 3600 /* defaultwaarde CIF_DSI_TSTP */
#define CIF_DSI_LSS_DEF  9999 /* defaultwaarde CIF_DSI_LSS */
#define CIF_DSI_TSS_DEF   255 /* defaultwaarde CIF_DSI_TSS */

/* voertuigcategorie */
/* ----------------- */
#define CIF_BUS  1 /* bus */
#define CIF_TRAM 2 /* tram */
#define CIF_POL  3 /* politie */
#define CIF_BRA  4 /* brandweer */
#define CIF_AMB  5 /* ambulance */
#define CIF_CVV  6 /* collectief vraagafhankelijk*/

/* vervoer */
#define CIF_TAXI 7 /* taxi */
#define CIF_URO 99 /* onbekend voertuig */

/* richting */
/* -------- */
#define CIF_RAF 201 /* rechtsaf */
#define CIF_LAF 202 /* linksaf */
#define CIF_RDR 203 /* rechtdoor */

/* voertuigstatus */
/* -------------- */
#define CIF_RIJD  1 /* rijden */
#define CIF_HALT  2 /* halteren */
#define CIF_START 3 /* vertrekmelding */
#define CIF_STOP  4 /* stilstand */

/* prioriteit */
/* ---------- */
#define CIF_PRI1 1 /* geen prioriteit */ /* alleen aanvraag */
#define CIF_PRI2 2 /* geconditioneerde prioriteit */
#define CIF_PRI3 3 /* absolute prioriteit */
#define CIF_SIR  4 /* sirene/zwaailicht */

/* stiptheid */
/* --------- */
#define CIF_TE_LAAT  1 /* te laat */
#define CIF_OP_TIJD  2 /* op tijd */
#define CIF_TE_VROEG 3 /* te vroeg */

/* ritcategorie */
/* ------------ */
#define CIF_DIENST 10 /* dienstregelingsrit */
#define CIF_MAT 11 /* materieelrit */
#define CIF_MATIN 12 /* materieelrit inrukrit */ /* naar remise */
#define CIF_MATUIT 13 /* materieelrit uitrukrit */ /* van remise */

/* type melding */
/* ------------ */
#define CIF_DSIN 1 /* inmelding */
#define CIF_DSUIT 2 /* uitmelding */
#define CIF_DSVOOR 3 /* voormelding */

/* declaratie functie applicatieprogramma */
s_int16 applicatieprogramma(s_int16);

#endif /* YATLCCLC_CIFINC_H_INCLUDED */