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
    Arc = 4468,     //Arcatraz

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


// Add player scripts
class DungeonMaster : public CreatureScript
{
public:
    DungeonMaster() : CreatureScript("npc_dungeonmaster") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PlayerTalkClass->ClearMenus();




        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 Sender, uint32 areaid)
    {



        if (areaid < 20)
        {
            switch (areaid)
            {
            case INSTANCE_EK:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Test Instance", GOSSIP_SENDER_MAIN, 78);



            }
        }





        if (areaid > 20)
        {
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
