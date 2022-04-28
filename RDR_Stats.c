//List of stats - Counted 695 stats - Only tried in Multiplayer - Im Foxxyyy

//Not sure
Money //STAT 0
Honor //STAT 1
Fame //STAT 3
Bounty //STAT 222

//Combat
Animals killed //STAT 26
People killed //STAT 27
Unaffiliated criminals killed //STAT 34
Bollard Twins's gang killed //STAT 35
Walton's gang killed //STAT 36
Treasure hunters killed //STAT 37
Banditos killed //STAT 38
Rebels killed //STAT 39
Dutch's gang killed //STAT 40
Enemy horses killed //STAT 41
People killed with Semi-automatic shotgun //STAT 201
People killed with Rolling block rifle //STAT 202
People killed with Carcano rifle //STAT 203
People killed with Explosive Rifle //STAT 214
People killed with lasso //STAT 204
People killed with Knife //STAT 205
People killed with Fire bottle //STAT 206
People killed with dynamite //STAT 207
People killed with throwing Knife //STAT 208
People killed with Tomahawk //STAT 212
People killed with Gatling gun //STAT 209
People killed with Browning gun //STAT 210
People killed with cannon //STAT 211
Volcanic pistol headshots //STAT 140
Semi-automatic Pistol headshots //STAT 141
High Power Pistol headshots //STAT 142
Mauser Pistol headshots //STAT 143
Cattleman revolver headshots //STAT 144
Schofield revolver headshots //STAT 145
Double-action revolver headshots //STAT 146
Lemat revolver headshots //STAT 147
Repeater Carbine headshots //STAT 148
Winchester repeater headshots //STAT 149
Henry repeater headshots //STAT 150
Evans repeater headshots //STAT 151
Springfield rifle headshots //STAT 152
Bolt-action rifle headshots //STAT 153
Buffalo rifle headshots //STAT 154
Sawed-off shotgun headshots //STAT 155
Double-barreled shotgun headshots //STAT 156
Pump-action shotgun headshots //STAT 157
Semi-automatic shotgun headshots //STAT 158
Rolling block rifle headshots //STAT 159
Carcano rifle headshots //STAT 160
Explosive Rifle headshots //STAT 170
Lasso headshots //STAT 161
Knife headshots //STAT 162
Fire bottle headshots //STAT 163
Dynamite headshots //STAT 164
Throwing Knife headshots //STAT 165
Tomahawk headshots //STAT 169
Gatling gun headshots //STAT 166
Browning gun headshots //STAT 167
Cannon headshots //STAT 162
Knockouts //STAT 43
Headshots //STAT 42
Hatshots //STAT 45
Disarms //STAT 46
Longest headshot streak //STAT 47
Longest disarm streak //STAT 48

//Crimes
Counts of arson //STAT 230
Counts of assault //STAT 231
Counts of law officer assault //STAT 232
Counts of horse assault //STAT 233
Counts of livestock assault //STAT 234
Counts of cruelty to animals //STAT 235
Counts of murder //STAT 236
Counts of law officer murder //STAT 237
Counts of horse slaughter //STAT 238
Counts of livestock slaughter //STAT 239
Counts of animal slaughter //STAT 240
Counts of horse theft //STAT 241
Counts of vehicle theft //STAT 242
Biggest bounty //STAT 252
Times Public Enemy //STAT 386

//Collectibles
Values of herbs collected //STAT 273
Butterfly Weed //STAT 265
Desert Sage //STAT 264
Golden Currant //STAT 267
Hummingbird Sage //STAT 269
Prairie Poppy //STAT 266
Prickly Pear //STAT 263
Red Sage //STAT 271
Violet Snowdrop //STAT 270
Wooly Blue Curls //STAT 268
Wild Feverfew //STAT 272

//General
Total time played //STAT 264 (unsure)
Gang hideouts cleared //STAT 458
Twin Rocks hideout fastest clear time //STAT 459
Solomon's Folly hideout fastest clear time //STAT 460
Tumbleweed hideout fastest clear time //STAT 461
Pike's Basin hideout fastest clear time //STAT 462
Gaptooth Breach hideout fastest clear time //STAT 463
Fort Mercer hideout fastest clear time //STAT 464
Tesoro Azul hideout fastest clear time //STAT 465
Nosalida hideout fastest clear time //STAT 463
Rare Weapons //STAT 469

//Misc
Armadillos killed //STAT 313
Bats killed //STAT 314
Bears killed //STAT 315
Beavers killed //STAT 316
Bighorn killed //STAT 317
Boars killed //STAT 318
Bobcats killed //STAT 319
Buffalo killed //STAT 320
Chickens killed //STAT 321
Cougars killed //STAT 322
Cows killed //STAT 323
Coyote killed //STAT 324
Crows killed //STAT 325
Deer killed //STAT 326
Dogs killed //STAT 327
Ducks killed //STAT 328
Eagles killed //STAT 329
Elk killed //STAT 330
Foxes killed //STAT 331
Goats killed //STAT 332
Hawks killed //STAT 333
Domesticated horses killed //STAT 334
Wild horses killed //STAT 335
Mules killed //STAT 336
Owls killed //STAT 337
Pigs killed //STAT 338
Rabbits killed //STAT 339
Raccoons killed //STAT 340
Seagulls killed //STAT 341
Sheep killed //STAT 342
Skunks killed //STAT 343
Snakes killed //STAT 344
Songbirds killed //STAT 345
Vultures killed //STAT 346
Wolves killed //STAT 347
Jackalopes killed //STAT 349
Social Club animal 2s killed //STAT 350
Social Club animal 3s killed //STAT 351
Social Club animal 4s killed //STAT 352
Social Club animal 5s killed //STAT 353
Wild animal species killed //STAT 354
Multiplayer experience //STAT 487
Kill Chain //STAT 488

//Unsafe code to get/set stats values - should be simplified 
unsafe float GetStatValue(int statIndex)
{
	__getFrame(0);
	__getGlobalP(34581);
	__getArray(1);
	return __popF();
}
unsafe void SetStatValue(int statIndex, int statValue)
{
	__getFrame(1);
	__callNative(0x67116627, 1, 1);
	__getFrame(0);
	__getGlobalP(34581);
	__setArray(1);
}

//Didn't try
Global_34581[372] = UNK_0x5545C218(0);
Global_34581[373] = UNK_0x5545C218(1);
Global_34581[374] = UNK_0x5545C218(2);
Global_34581[375] = UNK_0x5545C218(3);
Global_34581[376] = UNK_0x5545C218(4);
Global_34581[377] = UNK_0x5545C218(5);
Global_34581[378] = UNK_0x5545C218(6);
Global_34581[379] = UNK_0xE623B382(1);
Global_34581[380] = UNK_0xE623B382(2);
Global_34581[381] = UNK_0x5545C218(7);
Global_34581[382] = UNK_0x5545C218(8);
Global_34581[383] = UNK_0x5545C218(9);
Global_34581[385] = UNK_0xE623B382(0);
Global_34581[387] = UNK_0x5545C218(10);
Global_34581[388] = UNK_0x5545C218(11);
Global_34581[394] = UNK_0x5545C218(12);
Global_34581[44] = UNK_0xE623B382(3);
Global_34581[392] = UNK_0xE623B382(4);
Global_34581[391] = UNK_0xE623B382(6);
Global_34581[393] = UNK_0xE623B382(5);
Global_34581[395] = UNK_0xE623B382(7);