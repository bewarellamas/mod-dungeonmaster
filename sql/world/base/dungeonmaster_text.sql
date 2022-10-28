
SET @TEXT_ID = 197760,
@TEXT= 'You want to go to a dungeon? I have explored all over the world and can get you where you need to go. I am not responsible for any death or dismemberment that may occure by going where you shouldn\'t';



DELETE FROM `npc_text` WHERE `ID` IN (@TEXT_ID);

INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES (@TEXT_ID, @TEXT);