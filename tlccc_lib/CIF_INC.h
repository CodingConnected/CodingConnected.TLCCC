#ifndef TLCCC_CIFINC_H_INCLUDED
#define TLCCC_CIFINC_H_INCLUDED

/*
 * CVN Commissie C
 * bestand: CIF.INC
 * versie: 12 juni 2024
 * versie: 6.2
 */

typedef char s_int8; /* signed char 8 bits */
typedef short s_int16; /* signed integer 16 bits */
typedef long s_int32; /* signed integer 32 bits */

#ifdef CIF_PUBLIC

s_int16 CIF_GUS[CIF_AANT_US_FC + CIF_AANT_US_OV]; /* CIF_GUS[ ]-buffer */
const s_int16 CIF_PB_AANT_US_FC = CIF_AANT_US_FC; /* aantal fasecycli in CIF_GUS- en CIF_WUS-buffer */
const s_int16 CIF_PB_AANT_US_OV = CIF_AANT_US_OV; /* aantal overige uitgangen in CIF_GUS- en CIF_WUS-buffer */
s_int16 CIF_WUS[CIF_AANT_US_FC + CIF_AANT_US_OV]; /* CIF_WUS[ ]-buffer */
s_int16 CIF_IS[CIF_AANT_IS_D + CIF_AANT_IS_OV]; /* CIF_IS[ ]-buffer */
const s_int16 CIF_PB_AANT_IS_D = CIF_AANT_IS_D; /* aantal detectoren in CIF_IS buffer */
const s_int16 CIF_PB_AANT_IS_OV = CIF_AANT_IS_OV; /* aantal overige ingangen in CIF_IS buffer */
s_int16 CIF_DSI[CIF_AANT_DSI]; /* CIF_DSI[] buffer */
const s_int16 CIF_PB_AANT_DSI = CIF_AANT_DSI; /* grootte CIF_DSI buffer */
s_int16 CIF_DSIWIJZ; /* vlag CIF_DSI[]-buffer gewijzigd */
s_int16 CIF_GPS[CIF_AANT_GPS]; /* CIF_GPS[ ]-buffer */
const s_int16 CIF_PB_AANT_GPS = CIF_AANT_GPS; /* grootte CIF_GPS buffer */
s_int16 CIF_WPS[CIF_AANT_WPS]; /* CIF_WPS[ ]-buffer */
const s_int16 CIF_PB_AANT_WPS = CIF_AANT_WPS; /* grootte CIF_WPS buffer */
s_int8 CIF_UBER[CIF_MAX_UBER]; /* CIF_UBER[ ]-buffer */
const s_int16 CIF_PB_MAX_UBER = CIF_MAX_UBER; /* grootte CIF_UBER buffer */
s_int8 CIF_IBER[CIF_MAX_IBER]; /* CIF_IBER[ ]-buffer */
const s_int16 CIF_PB_MAX_IBER = CIF_MAX_IBER; /* grootte CIF_IBER buffer */
s_int8* CIF_UBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int8* CIF_IBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int8 CIF_MON_IBER[CIF_MAX_MON_IBER]; /* CIF_MON_IBER[]-buffer */
const s_int16 CIF_PB_MAX_MON_IBER = CIF_MAX_MON_IBER; /* grootte CIF_MON_IBER buffer */
s_int8* CIF_MON_IBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_MON_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int8 CIF_MON_UBER[CIF_MAX_MON_UBER]; /* CIF_MON_UBER[]-buffer */
const s_int16 CIF_PB_MAX_MON_UBER = CIF_MAX_MON_UBER; /* grootte CIF_MON_UBER buffer */
s_int8* CIF_MON_UBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_MON_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int8 CIF_RIS_UBER[CIF_MAX_RIS_UBER]; /* CIF_RIS_UBER[]-buffer */
const s_int16 CIF_PB_MAX_RIS_UBER = CIF_MAX_RIS_UBER; /* grootte CIF_RIS_UBER buffer */
s_int8* CIF_RIS_UBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_RIS_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int8 CIF_FILE_UBER[CIF_MAX_FILE_UBER]; /* CIF_FILE_UBER[ ] – buffer */
const s_int16 CIF_PB_MAX_FILE_UBER = CIF_MAX_FILE_UBER; /* grootte CIF_FILE_UBER buffer */
s_int8* CIF_FILE_UBER_LEES; /* pointer naar te lezen bericht */
s_int8* CIF_FILE_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
s_int16 CIF_FILE_UBER_STATUS; /* status van fileopslag */
s_int8* CIF_FILE_UBER_FILEWISSEL; /* pointer voor het aangeven van een filewisselpunt */
s_int16 CIF_PB_FILE_UBER_FILEWISSEL; /* aanvraag voor een (extra) filewisselpunt */
s_int8 CIF_FILE_UBER_FILEEXT[CIF_MAX_FILEEXT]; /* gewenste file-extensie (null-terminated string) */
s_int16 CIF_KLOK[CIF_AANT_KLOK]; /* CIF_KLOK[ ]-buffer */
const s_int16 CIF_PB_AANT_KLOK = CIF_AANT_KLOK; /* grootte CIF_KLOK buffer */
s_int16 CIF_PARM1[CIF_AANT_PARM1]; /* CIF_PARM1[ ]-buffer */
const s_int16 CIF_PB_AANT_PARM1 = CIF_AANT_PARM1; /* grootte CIF_PARM1 buffer */
s_int32 CIF_PARM2[CIF_AANT_PARM2]; /* CIF_PARM2[ ]-buffer */
const s_int16 CIF_PB_AANT_PARM2 = CIF_AANT_PARM2; /* grootte CIF_PARM2 buffer */
s_int16 CIF_ISWIJZ; /* vlag CIF_IS[ ]-buffer gewijzigd */
s_int16 CIF_WUSWIJZ; /* vlag CIF_WUS[ ]-buffer gewijzigd */
s_int16 CIF_WPSWIJZ; /* vlag CIF_WPS[ ]-buffer gewijzigd */
s_int16 CIF_GUSWIJZ; /* vlag CIF_GUS[ ]-buffer gewijzigd */
s_int16 CIF_GPSWIJZ; /* vlag CIF_GPS[ ]-buffer gewijzigd */
s_int16 CIF_PARM1WIJZPB; /* vlag CIF_PARM1[ ]-buffer gewijzigd door */
s_int16 CIF_PARM2WIJZPB; /* vlag CIF_PARM2[ ]-buffer gewijzigd door */
s_int16 CIF_PARM1WIJZAP; /* vlag CIF_PARM1[ ]-buffer gewijzigd door */
s_int16 CIF_PARM2WIJZAP; /* vlag CIF_PARM2[ ]-buffer gewijzigd door */

#ifdef CIF_WEL_OT
const s_int16 CIF_OT = 1; /* Gebruik ontruimingstijden in de interface */
#else
const s_int16 CIF_OT = 0; /* Geen gebruik ontruimingstijden in de interface */
#endif

#else

extern s_int16 CIF_GUS[]; /* CIF_GUS[ ]-buffer */
extern const s_int16 CIF_PB_AANT_US_FC; /* aantal fasecycli in CIF_GUS- en CIF_WUS-buffer */
extern const s_int16 CIF_PB_AANT_US_OV; /* aantal overige uitgangen in CIF_GUS- en CIF_WUS-buffer */
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
extern s_int8* CIF_UBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int8* CIF_IBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int8 CIF_MON_IBER[]; /* CIF_MON_IBER[]-buffer */
extern const s_int16 CIF_PB_MAX_MON_IBER; /* grootte CIF_MON_IBER buffer */
extern s_int8* CIF_MON_IBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_MON_IBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int8 CIF_MON_UBER[]; /* CIF_MON_UBER[]-buffer */
extern const s_int16 CIF_PB_MAX_MON_UBER; /* grootte CIF_MON_UBER buffer */
extern s_int8* CIF_MON_UBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_MON_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int8 CIF_RIS_UBER[]; /* CIF_RIS_UBER[]-buffer */
extern const s_int16 CIF_PB_MAX_RIS_UBER; /* grootte CIF_RIS_UBER buffer */
extern s_int8* CIF_RIS_UBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_RIS_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int8 CIF_FILE_UBER[]; /* CIF_FILE_UBER[]-buffer */
extern const s_int16 CIF_PB_MAX_FILE_UBER; /* grootte CIF_FILE_UBER buffer */
extern s_int8* CIF_FILE_UBER_LEES; /* pointer naar te lezen bericht */
extern s_int8* CIF_FILE_UBER_SCHRIJF; /* pointer naar te schrijven bericht */
extern s_int16 CIF_FILE_UBER_STATUS; /* status van fileopslag */
extern s_int8* CIF_FILE_UBER_FILEWISSEL; /* pointer voor het aangeven van een filewisselpunt */
extern s_int16 CIF_PB_FILE_UBER_FILEWISSEL; /* aanvraag voor een (extra) filewisselpunt */
extern s_int8 CIF_FILE_UBER_FILEEXT[]; /* gewenste file-extensie (null-terminated string) */
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
#define CIF_ROOD 0 /* rood */
#define CIF_GROEN 1 /* groen / wit / wit knipperen */
#define CIF_GEEL 2 /* geel / groen knipperen */
#define CIF_KNIPWIT 3 /* wit knipperen */
#define CIF_GEDOOFD 4 /* lantaarn(s) gedoofd */

/* CIF_IS[ ] */
#define CIF_DET_BEZET 1 /* detectie bezet */
#define CIF_DET_STORING 2 /* detectie storing */
#define CIF_DET_BOVENGEDRAG 4 /* detectie bovengedrag */
#define CIF_DET_ONDERGEDRAG 8 /* detectie ondergedrag */
#define CIF_DET_FLUTTERGEDRAG 16 /* detectie fluttergedrag */

/* CIF_IS_SWICO[ ] */
#define CIF_IS_SWICO_GEEN 0 /* geen SWICO schakelaar ingesteld */
#define CIF_IS_SWICO_AF 1 /* SWICO schakelaar af ingesteld */
#define CIF_IS_SWICO_OP 2 /* SWICO schakelaar op ingesteld */

/* CIF_GPS [ ] en CIF_WPS [ ] */
#define CIF_PROG_STATUS 0 /* programmastatus */
#define CIF_PROG_FOUT 1 /* programmafout */
#define CIF_PROG_STATUS_BRON 2 /* bron programmafout */
#define CIF_PROG_CONTROL 3 /* control status */
#define CIF_PROG_PTP_FOUT 5 /* PTP-verbinding fout */

/* CIF_GPS [CIF_PROG_STATUS] en CIF_WPS [CIF_PROG_STATUS] */
#define CIF_STAT_ONGEDEF 0 /* ongedefinieerd */
#define CIF_STAT_GEDOOFD 1 /* gedoofd */
#define CIF_STAT_KP 2 /* knipperen */
#define CIF_STAT_INSCHAKELEN 3 /* inschakelen */
#define CIF_STAT_AR 4 /* alles rood */
#define CIF_STAT_REG 5 /* regelen */
#define CIF_STAT_UITSCHAKELEN 6 /* uitschakelen */
#define CIF_STAT_FATALE_FOUT 7 /* fatale fout */

/* CIF_WPS [CIF_PROG_STATUS_BRON] */
#define CIF_BRON_ONGEDEF 0 /* ongedefinieerd */
#define CIF_BRON_BEDIENPANEEL 1 /* bedieningspaneel */
#define CIF_BRON_CENTRALE 2 /* centrale */
#define CIF_BRON_APPLICATIE 3 /* applicatie */
#define CIF_BRON_KLOK 4 /* klok */
#define CIF_BRON_PROCESBESTURING 5 /* procesbesturing */
#define CIF_BRON_AUTONOMEBEWAKER 6 /* autonome bewaker */

/* CIF_GPS [CIF_PROG_FOUT] */
#define CIF_GEEN_FOUT 0 /* geldt ook voor */
/* CIF_WPS [CIF_PROG_FOUT] en */
/* return-waarde */
/* applicatieprogramma() */
#define CIF_FB_FOUT 1 /* fasebewaking */
#define CIF_AP_FOUT2 2 /* procesbesturing wacht te lang met */
/* lezen van door het applicatie- */
/* programma geschreven informatie */
#define CIF_AP_FOUT3 4 /* applicatieprogramma leest een */
/* niet gedefinieerde code *
* /* CIF_WPS [CIF_PROG_FOUT] */
#define CIF_PB_FOUT1 1 /* werkelijke uitgangssturing te lang */
/* ongelijk aan gewenste uitgangs- */
/* sturing */
#define CIF_PB_FOUT2 2 /* applicatieprogramma wacht te lang */
/* met lezen van door de proces- */
/* besturing geschreven informatie */
#define CIF_PB_FOUT3 4 /* procesbesturing leest een niet */
/* gedefinieerde code */
#define CIF_PB_FOUT4 8 /* applicatieprogramma duurt te lang */

/* CIF_CIF_GPS [CIF_PROG_CONTROL] */
#define CIF_CONTROL_ONGEDEF 0 /* ongedefinieerd */
#define CIF_CONTROL_NIET_GEREED 2 /* niet gereed – NotReady */
#define CIF_CONTROL_FOUT 7 /* fout – Error */

/* CIF_CIF_WPS [CIF_PROG_CONTROL] */
#define CIF_CONTROL_ONGEDEF 0 /* ongedefinieerd */
#define CIF_CONTROL_NIET_GECONFIG 1 /* niet geconfigureerd - NotConfig */
#define CIF_CONTROL_NIET_GEREED 2 /* niet gereed – Offline */
#define CIF_CONTROL_GEREED 3 /* gereed – ReadyToControl */
#define CIF_CONTROL_START_CONTROL 4 /* start control – StartControl */
#define CIF_CONTROL_INCONTROL 5 /* incontrol – InControl */
#define CIF_CONTROL_EINDE_CONTROL 6 /* einde control – EndControl */
#define CIF_CONTROL_FOUT 7 /* fout – Error */

/* CIF_GPS [CIF_PROG_PTP_FOUT] / CIF_WPS [CIF_PROG_PTP_FOUT] */
#define CIF_PTP1_FOUT 1 /* PTP-poort 1 fout */
#define CIF_PTP2_FOUT 2 /* PTP-poort 2 fout */
#define CIF_PTP3_FOUT 4 /* PTP-poort 3 fout */
#define CIF_PTP4_FOUT 8 /* PTP-poort 4 fout */

/* CIF_KLOK[ ] */
#define CIF_JAAR 0 /* jaartal */
#define CIF_MAAND 1 /* maand 1..12 */
#define CIF_DAG 2 /* dag van de maand 1..31 */
#define CIF_DAGSOORT 3 /* dag van de week 0..6 */
#define CIF_UUR 4 /* uur van de dag 0..23 */
#define CIF_MINUUT 5 /* minuut 0..59 */
#define CIF_SECONDE 6 /* seconde 0..59 */
#define CIF_SEC_TELLER 7 /* seconden teller 0..32767 */
#define CIF_TSEC_TELLER 8 /* tienden sec teller 0..32767 */
#define CIF_TSECONDE 9 /* tiende seconde 0..9 */

/* CIF_KLOK[DAGSOORT] */
#define CIF_ZONDAG 0 /* zondag */
#define CIF_MAANDAG 1 /* maandag */
#define CIF_DINSDAG 2 /* dinsdag */
#define CIF_WOENSDAG 3 /* woensdag */
#define CIF_DONDERDAG 4 /* donderdag */
#define CIF_VRIJDAG 5 /* vrijdag */
#define CIF_ZATERDAG 6 /* zaterdag */

/* lees en schrijf vlaggen */
#define CIF_GESCHREVEN 1 /* in buffer geschreven */
#define CIF_GELEZEN 0 /* buffer gelezen */
#define CIF_GEEN_PARMWIJZ -1 /* geen wijzigingen in parameterbuffer */
#define CIF_MEER_PARMWIJZ -2 /* meerdere wijzigingen in parameterbuffer */
#define CIF_INIT_PARM -3 /* initiele waarden in parameterbuffer */

/* aanroep en returnwaarde applicatieprogramma() */
#define CIF_GEEN_INIT 0 /* 'normale' aanroep */
#define CIF_INIT 1 /* init na programmastart */
#define CIF_INIT_FOUT -1 /* initialisatie fout */

/* CIF_DSI */
#define CIF_DSI_LUS 0 /* lusnummer */
#define CIF_DSI_VTG 1 /* voertuigcategorie */
#define CIF_DSI_LYN 2 /* lijnnummer */
#define CIF_DSI_WDNST 3 /* wagendienstnummer */
#define CIF_DSI_BEDR 4 /* bedrijfsnummer */
#define CIF_DSI_NUM 5 /* voertuignummer */
#define CIF_DSI_DIR 6 /* richtingsnummer */
#define CIF_DSI_STAT 7 /* voertuigstatus */
#define CIF_DSI_PRI 8 /* prioriteitsklasse */
#define CIF_DSI_STP 9 /* stiptheidsklasse */
#define CIF_DSI_TSTP 10 /* stiptheid [s] */
#define CIF_DSI_LEN 11 /* voertuiglengte [m] */
#define CIF_DSI_SPD 12 /* voertuigsnelheid [m/s] */
#define CIF_DSI_LSS 13 /* afstand tot stopstreep [m] */
#define CIF_DSI_TSS 14 /* passeertijd stopstreep [s] */
#define CIF_DSI_RIT 15 /* ritnummer */
#define CIF_DSI_RITC 16 /* ritcategorie */
#define CIF_DSI_ROUT 17 /* routenummer openbaar vervoer */
#define CIF_DSI_TYPE 18 /* type melding */
#define CIF_DSI_OVC 19 /* codering meldpunt openbaar vervoer */
#define CIF_DSI_XGRAD 20 /* breedtegraad graden */
#define CIF_DSI_XMIN 21 /* breedtegraad minuten */
#define CIF_DSI_XSEC 22 /* breedtegraad seconden */
#define CIF_DSI_XHSEC 23 /* breedtegraad honderdste seconden */
#define CIF_DSI_YGRAD 24 /* lengtegraad graden */
#define CIF_DSI_YMIN 25 /* lengtegraad minuten */
#define CIF_DSI_YSEC 26 /* lengtegraad seconden */
#define CIF_DSI_YHSEC 27 /* lengtegraad honderdste seconden */
#define CIF_DSI_JAAR 28 /* jaartal */
#define CIF_DSI_MND 29 /* maand */
#define CIF_DSI_DAG 30 /* dag */
#define CIF_DSI_UUR 31 /* uur */
#define CIF_DSI_MIN 32 /* minuten */
#define CIF_DSI_SEC 33 /* seconden */
#define CIF_DSI_RES1 34 /* reserve 1 */
#define CIF_DSI_RES2 35 /* reserve 2 */

/* afwijkende defaultwaarden */
#define CIF_DSI_TSTP_DEF 3600 /* defaultwaarde CIF_DSI_TSTP */
#define CIF_DSI_LSS_DEF 9999 /* defaultwaarde CIF_DSI_LSS */
#define CIF_DSI_TSS_DEF 255 /* defaultwaarde CIF_DSI_TSS */

/* voertuigcategorie */
#define CIF_BUS 1 /* bus */
#define CIF_TRAM 2 /* tram */
#define CIF_POL 3 /* politie */
#define CIF_BRA 4 /* brandweer */
#define CIF_AMB 5 /* ambulance */
#define CIF_CVV 6 /* collectief vraagafhankelijk vervoer */
#define CIF_TAXI 7 /* taxi */
#define CIF_POL1 69 /* politie (niet in uniform) */
#define CIF_MAR 70 /* marechaussee */
#define CIF_HOV 71 /* hoogwaardig openbaar vervoer (bus) */
#define CIF_URO 99 /* onbekend voertuig */

/* richting */
#define CIF_RAF 201 /* rechtsaf */
#define CIF_LAF 202 /* linksaf */
#define CIF_RDR 203 /* rechtdoor */

/* voertuigstatus */
#define CIF_RIJD 1 /* rijden */
#define CIF_HALT 2 /* halteren */
#define CIF_START 3 /* vertrekmelding */
#define CIF_STOP 4 /* stilstand */

/* prioriteit */
#define CIF_PRI1 1 /* geen prioriteit */
#define CIF_PRI2 2 /* geconditioneerde prioriteit */
#define CIF_PRI3 3 /* absolute prioriteit */
#define CIF_SIR 4 /* sirene/zwaailicht */

/* stiptheid */
#define CIF_TE_LAAT 1 /* te laat */
#define CIF_OP_TIJD 2 /* op tijd */
#define CIF_TE_VROEG 3 /* te vroeg */

/* ritcategorie */
#define CIF_DIENST 10 /* dienstregelingsrit */
#define CIF_MAT 11 /* materieelrit */
#define CIF_MATIN 12 /* materieelrit inrukrit naar remise */
#define CIF_MATUIT 13 /* materieelrit uitrukrit van remise */

/* type melding */
#define CIF_DSIN 1 /* inmelding */
#define CIF_DSUIT 2 /* uitmelding */
#define CIF_DSVOOR 3 /* voormelding */

/* declaratie functie applicatieprogramma */
s_int16 applicatieprogramma(s_int16);

/* FC_TIMING */
#define CIF_TIMING_MASK 0
#define CIF_TIMING_EVENTSTATE 1
#define CIF_TIMING_STARTTIME 2
#define CIF_TIMING_MINENDTIME 3
#define CIF_TIMING_MAXENDTIME 4
#define CIF_TIMING_LIKELYTIME 5
#define CIF_TIMING_CONFIDENCE 6
#define CIF_TIMING_NEXTTIME 7

/* Definitie bits in TIMING_MASK */
#define CIF_TIMING_MASK_EVENTSTATE 1 /* BIT0 - eventstatus */
#define CIF_TIMING_MASK_STARTTIME 2 /* BIT1 - startTime */
#define CIF_TIMING_MASK_MINENDTIME 4 /* BIT2 - minEndTime */
#define CIF_TIMING_MASK_MAXENDTIME 8 /* BIT3 - maxEndTime */
#define CIF_TIMING_MASK_LIKELYTIME 16 /* BIT4 - likelyTime */
#define CIF_TIMING_MASK_CONFIDENCE 32 /* BIT5 - confidence */
#define CIF_TIMING_MASK_NEXTTIME 64 /* BIT6 - nextTime */

/* Macrodefinities status EVENTSTATE */
#define CIF_TIMING_ONBEKEND 0 /* Unknown(0) */
#define CIF_TIMING_GEDOOFD 1 /* Dark(1) */
#define CIF_TIMING_ROOD_KNIPPEREN 2 /* stop - Then - Proceed(2) */
#define CIF_TIMING_ROOD 3 /* stop - And - Remain(3) */
#define CIF_TIMING_GROEN_OVERGANG 4 /* pre - Movement(4) - not used in NL */
#define CIF_TIMING_GROEN_DEELCONFLICT 5 /* permissive - Movement - Allowed(5) */
#define CIF_TIMING_GROEN 6 /* protected - Movement - Allowed(6) */
#define CIF_TIMING_GEEL_DEELCONFLICT 7 /* permissive - clearance(7) */
#define CIF_TIMING_GEEL 8 /* protected - clearance(8) */
#define CIF_TIMING_GEEL_KNIPPEREN 9 /* caution - Conflicting - Traffic(9) */
#define CIF_TIMING_GROEN_KNIPPEREN_DEELCONFLICT 10 /* permissive – Movement- PreClearance(10) */
#define CIF_TIMING_GROEN_KNIPPEREN 11 /* protected – Movement - PreClearance(11) */

/* FCTIMING - databuffer */
#define CIF_MAX_EVENT 16 /* maximum events in CIF_FC_TIMING[][][] */
#define CIF_MAX_TIMING 8 /* maximum (tijd)velden in CIF_FC_TIMING[][][] */

#ifdef CIF_PUBLIC
s_int16 CIF_FC_TIMING[CIF_AANT_US_FC][CIF_MAX_EVENT][CIF_MAX_TIMING];
#else
extern s_int16 CIF_FC_TIMING[][CIF_MAX_EVENT][CIF_MAX_TIMING];
#endif

/* Wijzigingsvlag voor CIF_FC_TIMING[][][] */
#ifdef CIF_PUBLIC
s_int16 CIF_FC_TIMING_WIJZ[CIF_AANT_US_FC];
#else
extern s_int16 CIF_FC_TIMING_WIJZ[];
#endif

/* REDEN VOOR EXTRA WACHTTIJD */
#define CIF_FC_RWT_OV_INGREEP 1 /* BIT0 - openbaar vervoer ingreep */
#define CIF_FC_RWT_HULPDIENST_INGREEP 2 /* BIT1 - hulpdienst ingreep */
#define CIF_FC_RWT_TREIN_INGREEP 4 /* BIT2 - trein ingreep */
#define CIF_FC_RWT_BRUG_INGREEP 8 /* BIT3 - brug ingreep */
#define CIF_FC_RWT_HOOGTEMELDING 16 /* BIT4 – hoogtemelding */
#define CIF_FC_RWT_WEERSINGREEP 32 /* BIT5 – weersingreep */
#define CIF_FC_RWT_FILE_INGREEP 64 /* BIT6 – file ingreep */
#define CIF_FC_RWT_TUNNEL_AFSLUITING 128 /* BIT7 – tunnel afsluiting */
#define CIF_FC_RWT_DOSEREN_ACTIEF 256 /* BIT8 - doseren actief */
#define CIF_FC_RWT_VRACHTVERKEER_INGREEP 512 /* BIT9 – vrachtverkeer ingreep */
#define CIF_FC_RWT_FIETS_PELOTON_INGREEP 1024 /* BIT10 – fiets peloton ingreep */
#define CIF_FC_RWT_VOERTUIG_PELOTON_INGREEP 2048 /* BIT11 – voertuig peloton ingreep */
#define CIF_FC_RWT_ONBEKEND -32768 /* BIT15 - onbekend */

/* reden voor extra wachttijd - databuffer */
#ifdef CIF_PUBLIC
s_int16 CIF_FC_RWT[CIF_AANT_US_FC];
#else
extern s_int16 CIF_FC_RWT[];
#endif

/* OMGEVINGSFACTOREN */
#define CIF_OMGEVING_REGEN 1 /* BIT0 - regen */
#define CIF_OMGEVING_MIST 2 /* BIT1 - mist */
#define CIF_OMGEVING_GLADHEID 4 /* BIT2 - kans op gladheid */

/* omgevingsfactoren - databuffer */
#define CIF_MAX_OMGEVING 1 /* grootte CIF_OMGEVING[]-buffer */
#ifdef CIF_PUBLIC
s_int16 CIF_OMGEVING[CIF_MAX_OMGEVING];
#else
extern s_int16 CIF_OMGEVING[];
#endif

#endif /* TLCCC_CIFINC_H_INCLUDED */