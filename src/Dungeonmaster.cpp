/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"

enum zones
{
    DUNGEON_EK = 1,
    DUNGEON_KAL = 2,
    DUNGEON_BC = 3,
    DUNGEON_WOTLK = 4,
    RAID_CLASS = 5,
    RAID_BC = 6,
    RAID_WOTLK = 7

};

enum dungeon
{
    //Classic Dungeons
    RFC = 2230,     //Ragefire Chasm
    VC = 78,        //Deadmines
    WC = 228,       //Wailing Caverns
    SFK = 145,      //Shadowfang Keep
    Stocks = 101,   //Stormwind Stockade
    BFD = 257,      //Blackfathom Deeps
    Gnomer = 324,   //Gnomergan
    SM_GY = 45,     //Scarlet Monastery Graveyard
    SM_Lib = 614,   //Scarlet Monastery Library
    SM_Arm = 612,   //Scarlet Monastery Armory
    SM_Cath = 610,  //Scarlet Monastery Cathedral
    RFK = 244,      //Razorfen Kraul
    MaraP = 3126,   //Maraudon Purple Crystals
    MaraO = 3133,   //Maraudon Orange Crystals
    RFD = 442,      //Razorfen Downs
    DM_W = 3187,    //Dire Maul West
    DM_E = 3183,    //Dire Maul East
    DM_N = 3189,    //Dire Maul North VERIFY
    Scholo = 2567,  //Scholomance
    Ulda = 286,     //Uldaman
    ZF = 924,       //Zul'Farrak
    Strat_L = 2216, //Stratholme Live
    Strat_UD = 2214,//Stratholme Undead
    BRD = 1466,     //Blackrock Depths
    ST = 446,       //Sunken Temple
    BRS = 1468,     //Blackrock Spire (LBRS and UBRS)


    //Classic Raids
    AQ20 = 4008,    //Ruins of Ahn'Qiraj
    AQ40 = 4010,    //Ahn'Qiraj
    MC = 3528,      //Molten Core
    BWL = 3726,     //Blackwing Lair

    //Burning Crusade Dungeons
    Ramps = 4150,   //Hellfire Ramparts
    BF = 4152,      //Blood Furnace
    SP = 4365,      //Slave Pens
    UB = 4363,      //Underbog
    MT = 4405,      //Mana Tombs
    AC = 4404,      //Auchenai Crypts
    Durn = 4321,    //Caverns of Time: Old Hillsbrad
    Seth = 4406,    //Sethekk Halls
    SL = 4407,      //Shadow Labyrinth
    SH = 4151,      //Shattered Halls
    Bot = 4467,     //Botanica
    Mech = 4469,    //Mechanar
    SV = 4364,      //Steamvault
    MGT = 4887,     //Magisters' Terrace
    BM = 4320,      //Caverns of Time: Black Morass
    Arca = 4468,     //Arcatraz

    //Burning Crusage Raids
    Kara = 4131,    //Karazan
    Gruul = 4535,   //Gruul's Lair
    Mags = 4153,    //Magtheridon's Lair
    SSC = 4416,     //Serpentshrine Cavern
    TK = 4470,      //Tempest Keep, The Eye
    Hyjal = 4319,   //Caverns of Time: Mount Hyjal
    BT = 4598,      //Black Temple
    SWP = 4889,     //Sunwell Plateau
    ZA = 4738,      //Zul'Aman

    //Wrath Dungeons
    UK = 4745,      //Utgarde Keep
    Nex = 4983,     //Nexus
    AZN = 5117,     //Azjol-Nerub
    ANK = 5215,     //Ahn'kahet
    DTK = 4998,     //Drak'Tharon Keep
    VH = 5209,      //Violet Hold
    GD = 5206,      //Gundrak
    HOS = 5010,     //Halls of Stone
    HOL = 5093,     //Halls of Lightning
    UP = 4747,      //Utgarde Pinnacle
    Occ = 5246,     //The Oculus
    COS = 5150,     //Caverns of Time: Culling of Stratholme
    TOC = 5505,     //Trial of the Champion
    HOR = 5636,     //Halls of Reflection
    POS = 5637,     //Pit of Sauron
    FOS = 5635,     //Forge of Souls

    //Wrath Raids
    Naxx = 5191,    //Naxxramas
    OS = 5243,      //Obsidian Sanctum
    VOA = 5258,     //Vault of Archavon
    EOE = 5290,     //Eye of Eternity
    ULD = 5379,     //Ulduar
    TC = 5503,      //Trial of the Crusader
    Ony = 2848,     //Onyxia
    RS = 5869,      //Ruby Sanctum
    ICC = 5670      //Icecrown Citadel

    //Vault = 107 stormwind vault (unused)
};

uint32 gossip_text = 601083;

// Add player scripts
class DungeonMaster : public CreatureScript
{
public:
    DungeonMaster() : CreatureScript("npc_dungeonmaster") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PlayerTalkClass->ClearMenus();

        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Eastern Kingdoms Dungeons", GOSSIP_SENDER_MAIN, DUNGEON_EK);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Kalimdor Dungeons", GOSSIP_SENDER_MAIN, DUNGEON_KAL);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Burning Crusade Dungeons", GOSSIP_SENDER_MAIN, DUNGEON_BC);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Wrath of the Lich King Dungeons", GOSSIP_SENDER_MAIN, DUNGEON_WOTLK);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Classic Raids", GOSSIP_SENDER_MAIN, RAID_CLASS);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Burning Crusade Raids", GOSSIP_SENDER_MAIN, RAID_BC);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Wrath of the Lich King Raids", GOSSIP_SENDER_MAIN, RAID_WOTLK);



        SendGossipMenuFor(player, gossip_text, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 Sender, uint32 areaid)
    {

        if (areaid < 20)
        {
            switch (areaid)
            {
            case DUNGEON_EK:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Deadmines", GOSSIP_SENDER_MAIN, VC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Shadowfang Keep", GOSSIP_SENDER_MAIN, SFK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Stormwind Stockade", GOSSIP_SENDER_MAIN, Stocks);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Gnomergan", GOSSIP_SENDER_MAIN, Gnomer);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scarlet Monastery: Graveyard", GOSSIP_SENDER_MAIN, SM_GY);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scarlet Monastery: Library", GOSSIP_SENDER_MAIN, SM_Lib);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scarlet Monastery: Armory", GOSSIP_SENDER_MAIN, SM_Arm);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scarlet Monastery: Cathedral", GOSSIP_SENDER_MAIN, SM_Cath);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scholomance", GOSSIP_SENDER_MAIN, Scholo);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Uldaman", GOSSIP_SENDER_MAIN, Ulda);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Stratholme (Live)", GOSSIP_SENDER_MAIN, Strat_L);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Stratholme (Undead)", GOSSIP_SENDER_MAIN, Strat_UD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Blackrock Depths", GOSSIP_SENDER_MAIN, BRD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Sunken Temple", GOSSIP_SENDER_MAIN, ST);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Blackrock Spire", GOSSIP_SENDER_MAIN, BRS);
                break;

            case DUNGEON_KAL:
                //dm w e n, zf
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ragefire Chasm", GOSSIP_SENDER_MAIN, RFC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Wailing Caverns", GOSSIP_SENDER_MAIN, WC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Blackfathom Deeps", GOSSIP_SENDER_MAIN, BFD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Razorfen Kraul", GOSSIP_SENDER_MAIN, RFK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Maraudon (Orange Crystals)", GOSSIP_SENDER_MAIN, MaraO);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Maraudon (Purple Crystals)", GOSSIP_SENDER_MAIN, MaraP);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Razorfen Downs", GOSSIP_SENDER_MAIN, RFD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Dire Maul (West)", GOSSIP_SENDER_MAIN, DM_W);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Dire Maul (East)", GOSSIP_SENDER_MAIN, DM_E);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Dire Maul (North)", GOSSIP_SENDER_MAIN, DM_N);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Zul'Farrak", GOSSIP_SENDER_MAIN, ZF);
                break;

            case RAID_CLASS:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Molten Core", GOSSIP_SENDER_MAIN, MC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Blackwing Lair", GOSSIP_SENDER_MAIN, BWL);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ruins of Ahn'Qiraj", GOSSIP_SENDER_MAIN, AQ20);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ahn'Qiraj", GOSSIP_SENDER_MAIN, AQ40);
                break;

            case DUNGEON_BC:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Hellfire Ramparts", GOSSIP_SENDER_MAIN, Ramps);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Blood Furnace", GOSSIP_SENDER_MAIN, BF);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Slave Pens", GOSSIP_SENDER_MAIN, SP);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Underbog", GOSSIP_SENDER_MAIN, UB);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Mana Tombs", GOSSIP_SENDER_MAIN, MT);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Auchenai Crypts", GOSSIP_SENDER_MAIN, AC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Caverns of Time: Old Hillsbrad", GOSSIP_SENDER_MAIN, Durn);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Sethekk Halls", GOSSIP_SENDER_MAIN, Seth);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Shadow Labyrinth", GOSSIP_SENDER_MAIN, SL);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Shattered Halls", GOSSIP_SENDER_MAIN, SH);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Botanica", GOSSIP_SENDER_MAIN, Bot);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Mechanar", GOSSIP_SENDER_MAIN, Mech);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Steamvault", GOSSIP_SENDER_MAIN, SV);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Magisters' Terrace", GOSSIP_SENDER_MAIN, MGT);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Caverns of Time: Black Morass", GOSSIP_SENDER_MAIN, BM);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Arcatraz", GOSSIP_SENDER_MAIN, Arca);
                break;

            case RAID_BC:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Karazan", GOSSIP_SENDER_MAIN, Kara);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Gruul's Lair", GOSSIP_SENDER_MAIN, Gruul);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Magtheridon's Lair", GOSSIP_SENDER_MAIN, Mags);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Serpentshrine Cavern", GOSSIP_SENDER_MAIN, SSC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Tempest Keep: The Eye", GOSSIP_SENDER_MAIN, TK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Caverns of Time: Mount Hyjal", GOSSIP_SENDER_MAIN, Hyjal);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Black Temple", GOSSIP_SENDER_MAIN, BT);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Sunwell Plateau", GOSSIP_SENDER_MAIN, SWP);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Zul'Aman", GOSSIP_SENDER_MAIN, ZA);
                break;

            case DUNGEON_WOTLK:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Utgarde Keep", GOSSIP_SENDER_MAIN, UK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Nexus", GOSSIP_SENDER_MAIN, Nex);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Azjol-Nerub", GOSSIP_SENDER_MAIN, AZN);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ahn'kahet", GOSSIP_SENDER_MAIN, ANK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Drak'Tharon Keep", GOSSIP_SENDER_MAIN, DTK);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Violet Hold", GOSSIP_SENDER_MAIN, VH);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Gundrak", GOSSIP_SENDER_MAIN, GD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Halls of Stone", GOSSIP_SENDER_MAIN, HOS);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Halls of Lightning", GOSSIP_SENDER_MAIN, HOL);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Utgarde Pinnacle", GOSSIP_SENDER_MAIN, UP);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "The Oculus", GOSSIP_SENDER_MAIN, Occ);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Caverns of Time: Culling of Stratholme", GOSSIP_SENDER_MAIN, COS);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Trial of the Champion", GOSSIP_SENDER_MAIN, TOC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Halls of Reflection", GOSSIP_SENDER_MAIN, HOR);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Pit of Sauron", GOSSIP_SENDER_MAIN, POS);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Forge of Souls", GOSSIP_SENDER_MAIN, FOS);
                break;

            case RAID_WOTLK:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Nazzramas", GOSSIP_SENDER_MAIN, Naxx);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Obsidian Sanctum", GOSSIP_SENDER_MAIN, OS);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Vault of Archavon", GOSSIP_SENDER_MAIN, VOA);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Eye of Eternity", GOSSIP_SENDER_MAIN, EOE);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ulduar", GOSSIP_SENDER_MAIN, ULD);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Trial of the Crusader", GOSSIP_SENDER_MAIN, TC);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Onyxia", GOSSIP_SENDER_MAIN, Ony);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ruby Sanctum", GOSSIP_SENDER_MAIN, RS);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Icecrown Citadel", GOSSIP_SENDER_MAIN, ICC);
                break;
            }
            SendGossipMenuFor(player, gossip_text, creature->GetGUID());
        }





        if (areaid > 20)
        {
            CloseGossipMenuFor(player);
            TeleportToDungeon(player, areaid);

        }

        return true;
    }

    void TeleportToDungeon(Player* player, uint32 areaid)
    {
        AreaTriggerTeleport const* area = sObjectMgr->GetAreaTriggerTeleport(areaid);

        uint32 mapid = area->target_mapId;
        float x = area->target_X;
        float y = area->target_Y;
        float z = area->target_Z;
        float orientation = area->target_Orientation;


        player->TeleportTo(mapid, x, y, z, orientation, 0, nullptr, mapid == player->GetMapId());

    }

};

// Add all scripts in one
void AddMyPlayerScripts()
{
    new DungeonMaster();
}
