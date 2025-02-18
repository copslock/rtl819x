#ifndef HS2_H
#define HS2_H

#include <netdb.h>

extern unsigned int HS_debug_info;

#define DEBUG_INFO(level, fmt, args...) \
	if (HS_debug_info >= level) \
		printf(fmt, ## args)
#define DEBUG_ERR(fmt, args...) (printf("[%s %d]"fmt,__func__,__LINE__,## args))

#define FIFO_HEADER_LEN 		5
#define MACADDRLEN				6
#define MAX_STA_NUM				10
#define MAXRSNIELEN				600
#define MAX_MSG_SIZE			1600
#define SIOCGIWIND      		0x89ff
#define MAX_GAS_CONTENTS_LEN 	65535

#define _GAS_INIT_REQ_ACTION_ID_    10
#define _GAS_INIT_RSP_ACTION_ID_    11
#define _GAS_COMBACK_REQ_ACTION_ID_ 12
#define _GAS_COMBACK_RSP_ACTION_ID_ 13

#define _NTX_BSSID_CAPABILITY_IE		83	// element ID of Nontransmitted BSSID Capability
#define _SSID_IE						0   // element ID of SSID
#define _MBSSID_INDEX_IE				85

#define SUCCESS                         0
#define GAS_ADVT_PROTO_NOT_SUPPORT      59
#define NO_OUTSTANDING_GAS_REQ          60
#define GAS_RSP_NOT_RDV_FROM_ADVTSERVER 61
#define ADVTSERVER_NOT_REACHABLE		65
#define GAS_RSP_LARGER_REQ_LIMIT        63
#define TX_FAIL                         79

#define PROGRAM_NAME                "hs2"
#define VERSION_STR                 "v0.2"
#define DEFAULT_PID_FILENAME        ("/var/run/"PROGRAM_NAME)
#define DEFAULT_FIFO_FILENAME		("/var/"PROGRAM_NAME)
//#define HS2_WLAN0_FIFO	"/var/hs2-wlan0.fifo"
#define FILE_MODE		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define TMPTSM_EN		"/var/tsmen"
#define	TMPTSM_FILE		"/var/tsm"

//#define TIMEZONE_SUPPORT

enum {ANQP_QUERY=256, ANQP_CAP=257, VENUE_INFO=258, NET_AUTH_INFO=260, ROAM_LIST=261, IP_TYPE=262, NAI_LIST=263, 
		CELL_NET=264, DOMAIN_LIST=268, MAX_ANQP=8, VENDOR_LIST=56797, 
		HS2_QUERY=1, HS2_CAP=2, HS2_OP_NAME=3, HS2_WAN=4, HS2_CONN_CAP=5, NAI_QUERY=6, OP_BAND=7,
		HS_OSU_PROVIDER_LIST = 8, HS_Anonymous_NAI = 9, HS_ICON_REQ=10, HS_ICON_BIN_FILE = 11};

enum {SET_IE_FLAG_INTERWORKING=1, SET_IE_FLAG_ADVT_PROTO=2, SET_IE_FLAG_ROAMING=3,
        SET_IE_FLAG_HS2=4, SET_IE_FLAG_TIMEADVT=5, SET_IE_FLAG_TIMEZONE=6, SET_IE_FLAG_PROXYARP=7,
        SET_IE_FLAG_MBSSID=8, SET_IE_FLAG_REMEDSVR=9, SET_IE_FLAG_MMPDULIMIT=10, SET_IE_FLAG_ICMPv4ECHO=11,
        SET_IE_FLAG_SessionInfoURL=12, SET_IE_FLAG_QOSMAP=13};

#if 0
enum anqp_cap_bitmask {
	ANQP_QUERY_BIT		= 0x00000001,
	ANQP_CAPLIST_BIT	= 0x00000002,
	ANQP_VENUENAME_BIT	= 0x00000004,
	ANQP_EMERGY_BIT		= 0x00000008,
	ANQP_NETAUTH_BIT	= 0x00000010,
	ANQP_ROAM_BIT		= 0x00000020,
	ANQP_IPTYPE_BIT		= 0x00000040,
	ANQP_NAILIST_BIT	= 0x00000080,
	ANQP_3GPP_BIT		= 0x00000100,
	ANQP_GESLOC_BIT		= 0x00000200,
	ANQP_CIVILOC_BIT	= 0x00000400,
	ANQP_LOCURI_BIT		= 0x00000800,
	ANQP_DOMAIN_BIT		= 0x00001000,
	ANQP_EMERGYURI_BIT	= 0x00002000,
	ANQP_EMERGYNAI_BIT	= 0x00004000,
	HS_ANQP_QUERY_BIT	= 0x00010000,
	HS_ANQP_CAPLIST_BIT	= 0x00020000,
	HS_ANQP_OPNAME_BIT	= 0x00040000,
	HS_ANQP_WAN_BIT		= 0x00080000,
	HS_ANQP_CONNCAP_BIT	= 0x00100000,
	HS_ANQP_NAIREALM_BIT= 0x00200000,
	HS_ANQP_OPBAND_BIT	= 0x00400000
};
#endif

typedef enum{
        DOT11_EVENT_NO_EVENT = 1,
        DOT11_EVENT_REQUEST = 2,
        DOT11_EVENT_ASSOCIATION_IND = 3,
        DOT11_EVENT_ASSOCIATION_RSP = 4,
        DOT11_EVENT_AUTHENTICATION_IND = 5,
        DOT11_EVENT_REAUTHENTICATION_IND = 6,
        DOT11_EVENT_DEAUTHENTICATION_IND = 7,
        DOT11_EVENT_DISASSOCIATION_IND = 8,
        DOT11_EVENT_DISCONNECT_REQ = 9,
        DOT11_EVENT_SET_802DOT11 = 10,
        DOT11_EVENT_SET_KEY = 11,
        DOT11_EVENT_SET_PORT = 12,
        DOT11_EVENT_DELETE_KEY = 13,
        DOT11_EVENT_SET_RSNIE = 14,
        DOT11_EVENT_GKEY_TSC = 15,
        DOT11_EVENT_MIC_FAILURE = 16,
        DOT11_EVENT_ASSOCIATION_INFO = 17,
        DOT11_EVENT_INIT_QUEUE = 18,
        DOT11_EVENT_EAPOLSTART = 19,

        DOT11_EVENT_ACC_SET_EXPIREDTIME = 31,
        DOT11_EVENT_ACC_QUERY_STATS = 32,
        DOT11_EVENT_ACC_QUERY_STATS_ALL = 33,
        DOT11_EVENT_REASSOCIATION_IND = 34,
        DOT11_EVENT_REASSOCIATION_RSP = 35,
        DOT11_EVENT_STA_QUERY_BSSID = 36,
        DOT11_EVENT_STA_QUERY_SSID = 37,
        DOT11_EVENT_EAP_PACKET = 41,

#ifdef RTL_WPA2_PREAUTH
        DOT11_EVENT_EAPOLSTART_PREAUTH = 45,
        DOT11_EVENT_EAP_PACKET_PREAUTH = 46,
#endif

#ifdef RTL_WPA2_CLIENT
		DOT11_EVENT_WPA2_MULTICAST_CIPHER = 47,
#endif

		DOT11_EVENT_WPA_MULTICAST_CIPHER = 48,

#ifdef AUTO_CONFIG
		DOT11_EVENT_AUTOCONF_ASSOCIATION_IND = 50,
		DOT11_EVENT_AUTOCONF_ASSOCIATION_CONFIRM = 51,
		DOT11_EVENT_AUTOCONF_PACKET = 52,
		DOT11_EVENT_AUTOCONF_LINK_IND = 53,
#endif

#ifdef WIFI_SIMPLE_CONFIG
		DOT11_EVENT_WSC_SET_IE = 55,
		DOT11_EVENT_WSC_PROBE_REQ_IND = 56,
		DOT11_EVENT_WSC_PIN_IND = 57,
		DOT11_EVENT_WSC_ASSOC_REQ_IE_IND = 58,
		DOT11_EVENT_WSC_START_IND = 70,
		DOT11_EVENT_WSC_MODE_IND = 71,
		DOT11_EVENT_WSC_STATUS_IND = 72,
		DOT11_EVENT_WSC_METHOD_IND = 73,
		DOT11_EVENT_WSC_STEP_IND = 74,
		DOT11_EVENT_WSC_OOB_IND = 75,
#endif
		DOT11_EVENT_WSC_PBC_IND = 76,
		// for WPS2DOTX
		DOT11_EVENT_WSC_SWITCH_MODE = 100,	// for P2P P2P_SUPPORT
		DOT11_EVENT_WSC_STOP = 101	,
		DOT11_EVENT_WSC_SET_MY_PIN = 102,		// for WPS2DOTX
		DOT11_EVENT_WSC_SPEC_SSID = 103,
		DOT11_EVENT_WSC_SPEC_MAC_IND = 104,
		DOT11_EVENT_WSC_CHANGE_MODE = 105,	

		DOT11_EVENT_GAS_INIT_REQ = 110,
		DOT11_EVENT_GAS_COMEBACK_REQ = 111,
		DOT11_EVENT_HS2_SET_IE = 112,
		DOT11_EVENT_HS2_GAS_RSP = 113,
		DOT11_EVENT_HS2_GET_TSF = 114,
		DOT11_EVENT_HS2_TSM_REQ = 115,
		DOT11_EVENT_HS2_GET_RSN = 116,
		DOT11_EVENT_HS2_GET_MMPDULIMIT=117,
		DOT11_EVENT_WNM_DEAUTH_REQ = 118,
} DOT11_EVENT;

typedef struct _DOT11_REQUEST{
    unsigned char   EventId;
}DOT11_REQUEST;

typedef struct _ANQP_FORMAT_ {
    unsigned char  	InfoIDL;
    unsigned char  	InfoIDH;
    unsigned char  	LengthL;
    unsigned char  	LengthH;
    unsigned char   contents[256];
} ANQP_FORMAT;

typedef struct _DOT11_SET_HS2 {
    unsigned char 	EventId;
    unsigned char	IsMoreEvent;
    unsigned short 	Flag;
    unsigned short 	RSNIELen;
    unsigned char  	RSNIE[MAXRSNIELEN];
    unsigned char  	MACAddr[MACADDRLEN];
}DOT11_SET_HS2;

typedef struct _DOT11_HS2_GAS_REQ{
    unsigned char   EventId;
    unsigned char   IsMoreEvent;
    unsigned char	Dialog_token;
    unsigned char   MACAddr[MACADDRLEN];
    unsigned char	Advt_proto;
    unsigned short	Reqlen;
    unsigned char   Req[MAX_GAS_CONTENTS_LEN];
}DOT11_HS2_GAS_REQ;

typedef struct _DOT11_HS2_GAS_RSP{
    unsigned char   EventId;
    unsigned char   IsMoreEvent;
    unsigned char	Dialog_token;
    unsigned char	Action;
    unsigned char   MACAddr[MACADDRLEN];
    unsigned short	StatusCode;
    unsigned short	Comeback_delay;
    unsigned char	Rsp_fragment_id;
    unsigned char	Advt_proto;
    unsigned short	Rsplen;
    unsigned char   Rsp[MAX_GAS_CONTENTS_LEN];
}DOT11_HS2_GAS_RSP;

typedef struct sta_ctx
{
	DOT11_HS2_GAS_RSP	gas_rsp;
	int					need_free;
	int					expire_time;
	int					rsp_index;
	//unsigned char		query_rsp[1024];
} STA_CTX, *pSTA_CTX;

struct hs2_eap_method {
	struct hs2_eap_method	*next;
	unsigned char			method;
	unsigned char			auth_id[10];
	unsigned char			auth_val[10][8];
	unsigned char			auth_cnt;
};

struct hs2_realm {
	struct hs2_realm		*next;
	unsigned char			name[255];
	unsigned char			eap_method_cnt;
	struct hs2_eap_method	*eap_method;	
};

struct proto_port {
	struct proto_port	*next;
	unsigned char		ip_proto;
	unsigned short		port;
	unsigned char		status;
};

struct wan_metric {
	unsigned char		waninfo;
	unsigned int		dlspeed;
	unsigned int		ulspeed;
	unsigned char		dlload;
	unsigned char		ulload;
	unsigned short		lmd;
};

struct hs2_OSU_FName {
	struct hs2_OSU_FName *next;
	unsigned char LangCode[4]; // Language Code
	unsigned char OSU_FName[253]; // OSU Friendly Name
};
struct hs2_IconMetadata {
	struct hs2_IconMetadata *next;	
	unsigned short Width;
	unsigned short Height;
	unsigned char LangCode[4];
	unsigned char IconType[256];
	unsigned char FileName[256]; // maximum length = 255 + '\0' = 256
};
struct hs2_OSU_Desc {
	struct hs2_OSU_Desc *next;
	unsigned char LangCode[4];	 // maximum length = 3 + '\0' = 4
	unsigned char OSU_Desc[253]; // maximum length = 252 + '\0' = 253
};
struct hs2_OSUProvider {
	struct hs2_OSUProvider	*next;	
	struct hs2_OSU_FName 	*FName_list; // OSU Friendly Name
	unsigned char 			OSU_URI[256]; // OSU Server URI
	struct hostent *OSUhost;
	unsigned char 			OSU_Methods[10]; // OSU Method List (0: OMA-DM, 1: SOAP-XML SPP, others: reserved)
											 // 10 is a value for future spec extensioin.
											 // When the number of OSU Methods > 10, the number
											 // should be modified.
	struct hs2_IconMetadata *metadata_List;	// Icon Metadata
	unsigned char 			OSU_NAI[256]; // OSU NAI
	struct hs2_OSU_Desc 	*descList;	// OSU Service Description 
};

struct hs2_plmn {
	struct hs2_plmn		*next;
	unsigned char		mcc[3];
	unsigned char		mnc[3];
};

struct hs2_config {
	int					iw_enable;
	int                 readfifo;
	unsigned char       fifo_name[30];
//below parser configure parameters=================
	int					anqp_enable;
	unsigned int                 mmpdu_limit;
    unsigned char       enableGASComeback;
    int                 comeback_delay;
	int					l2_inspect;
	int					sigma_test;
	unsigned char		redir_mac[20];
	unsigned char		ant;
	unsigned char		internet;
	unsigned char		venue_group;
    unsigned char		venue_type;
	unsigned char		advtid;
	unsigned char		wlan_iface[16];
	unsigned char		OSU_iface[4][16]; // release 2
	unsigned char		remedSvrURL[256];
	unsigned char		SessionInfoURL[256];
	unsigned char		venue_name[10][512];
	unsigned char		venue_cnt;
	unsigned char		domain_name[10][256];
	unsigned char		domain_cnt;
	unsigned char		netauth_type[10];
	unsigned char		netauth_cnt;
	unsigned char		redirectURL[10][256];
	unsigned char		ipv4type;
	unsigned char		ipv6type;
    unsigned char		hessid[6];
    unsigned char		roi[10][10];
	unsigned char		roi_len[10];
    unsigned char		roi_cnt;
	unsigned char       op_name[10][256];
	unsigned char		anonymous_nai[256]; // release 2
//	unsigned char		iconname[256]; 		// release 2	
	
	unsigned char		iconStatusCode;		// release 2
//	unsigned char		iconType[128];		// release 2
	unsigned short      icondata_Len;		// release 2
	void				*icondata; 			// release 2
	struct hs2_OSUProvider	*OSUProviderList;	
	unsigned char           OSU_cnt;		// Release 2
	unsigned char			OSU_SSID[4][33]; // release 2
	unsigned char			L_OSU_SSID[33]; // release 2
	unsigned char			MBSSID_Index[4];  // release 2
	unsigned char			MBSSID_INDICATOR; // release 2
	unsigned char			MBSSID_CAP; // release 2
    unsigned char       op_cnt;
	unsigned char		opband[10];
	unsigned char		opband_len;
	struct  wan_metric	wan_ie;
	struct	proto_port	*proto;
	struct	hs2_realm	*realm;
	struct	hs2_plmn	*plmn;
//end of parser configure parameters================
    unsigned char		hs2_ie[20];
    unsigned char		hs2_ielen;
    unsigned char		iw_ie[20];
	unsigned char		iw_ielen;
	unsigned char		nQoSMAP;
	unsigned char		QoSMap_ie[2][30];
	unsigned char 		QoSMap_ielen[2];
    unsigned char		advt_ie[10];
    unsigned char		advt_ielen;
    unsigned char		roam_ie[40];
    unsigned char		roam_ielen;
    unsigned char		timeadvt_ie[20];
    unsigned char		timeadvt_ielen;
    unsigned char		timezone_ie[10];
    unsigned char		timezone_ielen;
	unsigned char		MBSSID_ie[20];	// release 2
	unsigned char		MBSSID_ielen;	// release 2
	unsigned char		rsn_ie[4][256];	
	unsigned char		rsnielen[4];
    unsigned char		utc_countdown;
    unsigned char		proxy_arp;
	unsigned char		ICMPv4ECHO;
	unsigned char		dgaf_disable;
	unsigned char		OSU_Present;	// release 2
	unsigned char		ReleaseNumber;  // release 2
#if !defined(PC_TEST)
    time_t				tsf;
#endif
	STA_CTX				*sta[MAX_STA_NUM];
};

typedef struct hs2_context {
    unsigned char		RecvBuf[MAX_MSG_SIZE];
	unsigned char		cfg_num;
	unsigned char		pid_filename[100];
	unsigned char		cfg_filename[8][100];
	struct hs2_config	hs2conf[8];
} HS2CTX, *pHS2CTX;

//Function declartion
char *get_token(char *data, char *token);
int get_value(char *data, char *value);
unsigned char convert_atob(char *data, int base);
int isFileExist(char *file_name);
unsigned short convert_atob_sh(char *data, int base);
void * getIconData(unsigned char *iconName, struct hs2_config *config, unsigned short *iconLen, unsigned char *statusCode, unsigned char *iconType);

#endif /* HS2_H */
