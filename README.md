# mod-dungeonmaster

## Description

Adds and NPC that will teleport you to any dungeon or raid.

Planned additions:
Settings to enable/disable instance groups or individual instaces.
Option to add a cost for teleports.
Update NPC and gossip menus.

## How to use ingame

Add the Dungeonmaster NPC to your world.
> .npc add 197762

Talk to the NPC to teleport to the enterance of any dungeon.

## Requirements

My_new_module requires:

- AzerothCore v4.0.0+


## Installation

```
1) Simply `git clone` the module under the `modules` directory of your AzerothCore source or copy paste it manually.
2) Import the SQL manually to the right Database (auth, world or characters) or with the `db_assembler.sh` (if `include.sh` provided).
3) Re-run cmake and launch a clean build of AzerothCore.
```

## Edit the module's configuration (optional)

No config available at this time.


## Credits

* Bewarellamas(https://github.com/bewarellamas) (author of the module)
* talamortis: Picked through their modules to figure out some code.
* AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
