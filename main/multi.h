/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 *
 * Defines and exported variables for multi.c
 *
 */



#ifndef _MULTI_H
#define _MULTI_H

#ifdef SHAREWARE
#define MAX_MESSAGE_LEN 25
#else
#define MAX_MESSAGE_LEN 35
#define SHAREWARE_MAX_MESSAGE_LEN 25
#endif

#ifdef NETWORK

// Defines
#include "gameseq.h"
#include "piggy.h"

//added 03/05/99 Matt Mueller
#include "compare.h"
//end addition -MM

extern int netgame_d1x_only;

// What version of the multiplayer protocol is this?

#ifdef SHAREWARE
#define MULTI_PROTO_VERSION 	1
#else
#define MULTI_PROTO_VERSION	2
#endif
#define MULTI_PROTO_D1X_VER	(netgame_d1x_only?MULTI_PROTO_VERSION:3)

//edit 4/18/99 Matt Mueller - Needed to add data onto netgame_lite packet for flags.
//Incrementing this seems the only way possible.  Still stays backwards compitible.
#define MULTI_PROTO_D1X_MINOR	1
//end edit -MM

// How many simultaneous network players do we support?

#define MAX_NUM_NET_PLAYERS 8

#define MULTI_POSITION			0
#define MULTI_REAPPEAR   		1
#define MULTI_FIRE                      2
#define MULTI_KILL                      3
#define MULTI_REMOVE_OBJECT             4
#define MULTI_PLAYER_EXPLODE            5
#define MULTI_MESSAGE			6
#define MULTI_QUIT                      7
#define MULTI_PLAY_SOUND		8
#define MULTI_BEGIN_SYNC		9
#define MULTI_CONTROLCEN		10
#define MULTI_ROBOT_CLAIM		11
#define MULTI_END_SYNC			12
#define MULTI_CLOAK                     13
#define MULTI_ENDLEVEL_START            14
#define MULTI_DOOR_OPEN			15
#define MULTI_CREATE_EXPLOSION          16
#define MULTI_CONTROLCEN_FIRE           17
#define MULTI_PLAYER_DROP		18
#define MULTI_CREATE_POWERUP            19
#define MULTI_CONSISTENCY		20
#define MULTI_DECLOAK			21
#define MULTI_MENU_CHOICE		22
#ifndef SHAREWARE
#define MULTI_ROBOT_POSITION            23
#define MULTI_ROBOT_EXPLODE             24
#define MULTI_ROBOT_RELEASE             25
#define MULTI_ROBOT_FIRE                26
#define MULTI_SCORE                     27
#define MULTI_CREATE_ROBOT		28
#define MULTI_TRIGGER			29
#define MULTI_BOSS_ACTIONS		30
#define MULTI_CREATE_ROBOT_POWERUPS	31
#define MULTI_HOSTAGE_DOOR		32
#endif

#define MULTI_SAVE_GAME			33
#define MULTI_RESTORE_GAME		34

#define MULTI_REQ_PLAYER		35		// Someone requests my player structure
#define MULTI_SEND_PLAYER		36		// Sending someone my player structure

#define MULTI_PLAYER_POWERUP_COUNT	37
#define MULTI_START_POWERUP_COUNT	38


//======================================================
//Added/changed 8/28/98 by Geoff Coovert to insure packet transmission
#define MEKH_PACKET_NEEDACK             39
#define MEKH_PACKET_ACK                 40

//added 03/04/99 Matt Mueller - new ping method
#define MULTI_PING                      41
#define MULTI_PONG                      42
//end addition -MM

//added 03/05/99 Matt Mueller
#define MULTI_POS_FIRE                  43
#define MULTI_POS_PLAYER_EXPLODE	44
//end addition -MM

//added 04/19/99 Matt Mueller
#define MULTI_D1X_VER_PACKET            45
//end addition -MM

//added on 4/22/99 by Victor Rachels for alt vulcanfire
#define MULTI_ALT_VULCAN_ON             46
#define MULTI_ALT_VULCAN_OFF            47
//end this section addition - VR

//added on 6/7/99 by Victor Rachels for ingame reconfig message
#define MULTI_INGAME_CONFIG             48

#ifndef SHAREWARE
#define MULTI_MAX_TYPE                  48
#else
#define MULTI_MAX_TYPE                  25 //22
#endif

#define MAX_MULTI_MESSAGE_LEN  90 //didn't change it, just moved it up

#define MEKH_PACKET_MEM  30

typedef struct mekh_ackedpacket_history {
        ubyte   packet_type;
        int     player_num;
        fix     timestamp;
} mekh_ackedpacket_history;

typedef struct mekh_packet_stats {
        ubyte   packet_type;    
        fix     timestamp;      // GameTime ID of packet
        ubyte   packet_contents[MAX_MULTI_MESSAGE_LEN+4];
        int     len;
                                //Packet stuff to call send_data
        int    players_left[MAX_NUM_NET_PLAYERS];
                                //Playernums to get acks from
        fix     send_time[MAX_NUM_NET_PLAYERS];
                                //GameTime to resend this packet
} mekh_packet_stats;

mekh_packet_stats mekh_acks[MEKH_PACKET_MEM];
        //Info for packets that need an ack to come back

mekh_ackedpacket_history mekh_packet_history[MEKH_PACKET_MEM];
        //Remember last regdpackets we've gotten in case ack is late/dropped
        //and the packet gets resent, so we can ignore it.

extern void mekh_gotack(char *buf);
extern void mekh_process_packet(char *buf);
extern void mekh_resend_needack();
//extern void mekh_send_reg_data(unsigned char *buf, int len, int repeat);
extern void mekh_send_ack(mekh_ackedpacket_history p_info);
extern void mekh_prep_concat_send(ubyte *extradata, int len, ubyte *server, ubyte *node, ubyte *address, int short_packet);
extern void mekh_send_direct_packet(ubyte *buffer, int len, int plnum);
#define mekh_send_reg_data(buf,len,repeat) mekh_send_reg_data_needver(int32_greaterorequal,0,buf,len)
//End add -GC
//======================================================
//added 03/04/99 Matt Mueller - new direct send stuff
void mekh_send_direct_broadcast(ubyte *buffer, int len);//####
void mekh_send_broadcast_needver(int ver, ubyte *buf1, int len1, ubyte *buf2,int len2);
void mekh_send_reg_data_needver(compare_int32_func compare,int ver,unsigned char *buf, int len);
//end addition -MM
//added 03/07/99 Matt Mueller - new direct send stuff
void mekh_send_direct_reg_data(unsigned char *buf, int len,int plnum);
//end addition -MM

#ifdef SHAREWARE
#define MAX_NET_CREATE_OBJECTS 19 
#else
#define MAX_NET_CREATE_OBJECTS 20
#endif


// Exported functions

int objnum_remote_to_local(int remote_obj, int owner);
int objnum_local_to_remote(int local_obj, sbyte *owner);
void map_objnum_local_to_remote(int local, int remote, int owner);
void map_objnum_local_to_local(int objnum);

void multi_init_objects(void);
void multi_show_player_list(void);
void multi_do_frame(void);

void multi_send_fire(int pl);
void multi_send_destroy_controlcen(int objnum, int player);
void multi_send_endlevel_start(int);
void multi_send_player_explode(char type);
void multi_send_message(void);
void multi_send_position(int objnum);
void multi_send_reappear();
void multi_send_kill(int objnum);
void multi_send_remobj(int objnum);
void multi_send_quit(int why);
void multi_send_door_open(int segnum, int side);
void multi_send_create_explosion(int player_num);
void multi_send_controlcen_fire(vms_vector *to_target, int gun_num, int objnum);
void multi_send_cloak(void);
void multi_send_decloak(void);
void multi_send_create_powerup(int powerup_type, int segnum, int objnum, vms_vector *pos);
void multi_send_play_sound(int sound_num, fix volume);
void multi_send_audio_taunt(int taunt_num);
void multi_send_score(void);
void multi_send_trigger(int trigger);
void multi_send_hostage_door_status(int wallnum);
void multi_send_netplayer_stats_request(ubyte player_num);
void multi_send_player_powerup_count();
void multi_send_start_powerup_count();

void multi_endlevel_score(void);
void multi_prep_level(void);
int multi_endlevel(int *secret);
int multi_menu_poll(void);
void multi_leave_game(void);
void multi_process_data(char *dat, int len);
void multi_process_bigdata(char *buf, int len);		
void multi_do_death(int objnum);
void multi_send_message_dialog(void);
int multi_delete_extra_objects(void);
void multi_make_ghost_player(int objnum);
void multi_make_player_ghost(int objnum);
void multi_define_macro(int key);
void multi_send_macro(int key);
int multi_get_kill_list(int *plist);
void multi_new_game(void);
void multi_sort_kill_list(void);
int multi_choose_mission(int *anarchy_only);
void multi_reset_stuff(void);

//edit 03/04/99 Matt Mueller - some debug code.. ignore if you wish.
void 
 multi_send_data_real(unsigned char *buf, int len, int repeat,char *file,char *func,int line);
#ifndef __FUNCTION__
#define __FUNCTION__ ((char *) 0)
#endif
//multi_send_data(unsigned char *buf, int len, int repeat);
#define multi_send_data(buf, len, repeat) multi_send_data_real(buf, len, repeat, __FILE__,__FUNCTION__,__LINE__)
//end edit -MM

int get_team(int pnum);

// Exported variables

extern int Network_active;
extern int Network_laser_gun;
extern int Network_laser_fired;
extern int Network_laser_level;
extern int Network_laser_flags;

extern int message_length[MULTI_MAX_TYPE+1];
extern int mekh_insured_packets[MULTI_MAX_TYPE+1];//#####

extern unsigned char multibuf[MAX_MULTI_MESSAGE_LEN+4];
extern short Network_laser_track;

extern int who_killed_controlcen;

extern int Net_create_objnums[MAX_NET_CREATE_OBJECTS];
extern int Net_create_loc;

extern short kill_matrix[MAX_NUM_NET_PLAYERS][MAX_NUM_NET_PLAYERS];
extern short team_kills[2];

extern int multi_goto_secret;

//do we draw the kill list on the HUD?
extern int Show_kill_list;
extern int Show_reticle_name;
extern fix Show_kill_list_timer;

// Used to send network messages

extern char	Network_message[MAX_MESSAGE_LEN];
extern char Network_message_macro[4][MAX_MESSAGE_LEN];
extern int Network_message_reciever;

// Used to map network to local object numbers

extern short remote_to_local[MAX_NUM_NET_PLAYERS][MAX_OBJECTS];  // Network object num for each 
extern short local_to_remote[MAX_OBJECTS];   // Local object num for each network objnum
extern sbyte object_owner[MAX_OBJECTS]; // Who 'owns' each local object for network purposes

extern int multi_in_menu; // Flag to tell if we're executing GameLoop from within a newmenu.
extern int multi_leave_menu;
extern int multi_quit_game;

extern int multi_sending_message;
extern int multi_defining_message;
extern void multi_message_input_sub( int key );
extern void multi_send_message_start();
extern void multi_message_feedback();

extern int control_invul_time;

#define N_PLAYER_SHIP_TEXTURES 6

extern bitmap_index multi_player_textures[MAX_NUM_NET_PLAYERS][N_PLAYER_SHIP_TEXTURES];

#define NETGAME_FLAG_CLOSED 	1
#define NETGAME_FLAG_SHOW_ID	2
#define NETGAME_FLAG_SHOW_MAP 4

#define NETGAME_NAME_LEN				15

#define NETPLAYER_ORIG_SIZE	22
#define NETPLAYER_D1X_SIZE	22 /* D1X version removes last char from callsign */

typedef struct netplayer_info {
	char		callsign[CALLSIGN_LEN+1];
	ubyte		server[4];
	ubyte		node[6];
	ushort	socket;
	sbyte 		connected;
#ifndef SHAREWARE
	/* following D1X only */
	ubyte		sub_protocol;
#endif
} __pack__ netplayer_info;

typedef struct netgame_info {
	ubyte					type;
	char					game_name[NETGAME_NAME_LEN+1];
	char					team_name[2][CALLSIGN_LEN+1];
	ubyte					gamemode;
        ubyte                                   difficulty;
        ubyte                                   game_status;
	ubyte					numplayers;
	ubyte					max_numplayers;
	ubyte					game_flags;
        netplayer_info                          players[MAX_PLAYERS];
	int					locations[MAX_PLAYERS];
	short					kills[MAX_PLAYERS][MAX_PLAYERS];
	int					levelnum;
	ubyte					protocol_version;
	ubyte					team_vector;
        ushort                                  segments_checksum;
	short					team_kills[2];
	short					killed[MAX_PLAYERS];
	short					player_kills[MAX_PLAYERS];
#ifndef SHAREWARE
	fix					level_time;
	int					control_invul_time;
	int 					monitor_vector;
	int					player_score[MAX_PLAYERS];
	ubyte					player_flags[MAX_PLAYERS];
	char					mission_name[9];
	char					mission_title[MISSION_NAME_LEN+1];
// from protocol v 3.0
	ubyte					packets_per_sec;
	uint					flags;
	ubyte					subprotocol; // constant for given version
	ubyte					required_subprotocol; // depends on game mode etc.
#endif
} __pack__ netgame_info;

extern struct netgame_info Netgame;

int network_i_am_master(void);
void change_playernum_to(int new_pnum);

extern uint multi_allow_powerup;

extern void HUD_init_message(char * format, ...);

//added on 10/15/98 by Victor Rachels to add effeciency stuff
extern int multi_kills_stat;
extern int multi_deaths_stat;
//end this section addition

#endif

#endif
