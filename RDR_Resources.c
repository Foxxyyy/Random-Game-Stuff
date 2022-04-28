/*
	Listener :
	
	No CPed, no CObject and no CVehicle either. Instead, there is the concept of an actor, which, depending on the assigned handlers, can be human, animal,
	or vehicle. As a result, everything connected with actors is not a bit like what it was before.

	But this only applies to game logic. The principles of working with the map remained the same: in the same way we have a play space,
	in the same way it is divided into sectors... Except that the format has been heavily cleaned up.

	The .ipl role was taken over by .xsi. (sagSectorInfo) It describes the region (from a single interior to the entire map).
	The main difference is that .ipl did not overlap, but .xsi covers the sector, while descriptions of sub-sectors can be placed in separate files
	(which, in turn, may contain sub-sectors), or can be located in the same resource.
	The root resource is swAll.xsi, which covers the entire map. It (in the version that I have) is divided into 106 zones
	(in others, this number may differ slightly, because some of the zones are reserved for DLC).
	At the same time, sub-sectors can also overlap (the main thing is that they cannot go beyond the boundaries of the parent sector).

	Presumably, this is done in order to be able to describe some blocks into several sub-sectors at once, without intermediate division into pieces
	(for example, a sub-sector with the speaking name swTerrain.xsi covers the entire territory in swAll).

	The main difference from .ipl is that inside .xsi there can be models and collisions and do not forget that when you change the border of the zone,
	you also need to correct the parent sectors.

	Terrain and static objects are collected in VolumeData - a very simple object, which, in fact, is a bunch of xdd and xtd.
	Different LODs are moved to separate .xvd files. The vegetation has been moved to separate .xsg resources.

	Dynamic objects use .xft and .xfd, slightly different from those used in MP3

	To summarize, we can say that no problems with resources are expected, even if R* completely transitions to the ideology used in RDR.
	Yes, there will be big problems with scripting first. the fundamental approach to game objects has changed, but this is also a solvable problem.
*/

//Im Foxxyyy - MagicRDR 1.0
#XTD - Xbox Texture Dictionary //Done
#XVD - Xbox Volume Data //Done
#XBD - Xbox Bounds Dictionary //Partially done
#XFT - Xbox Fragment Type //Done
#XFD - Xbox Fragment Drawable //Done
#XSC - Xbox Script Container //Done
#XST - Xbox String Table //Done
#XSP - Xbox Speed Tree
#XTB - Xbox Terrain Bounds
#XSI - Xbox Sector Info //Partially done
#XAS - Xbox Anim Set
#XAD - Xbox Anim Dictionary
#XAT - Xbox Action Tree
#XGD - Xbox Gringo Dictionary
#XNM - Xbox Nav Mesh

//SC-CL
enum RDR_Opcodes
{
	  RO_Nop = 0
	, RO_Add = 1
	, RO_Sub = 2
	, RO_Mult = 3
	, RO_Div = 4
	, RO_Mod = 5
	, RO_Not = 6
	, RO_Neg = 7
	, RO_CmpEq = 8
	, RO_CmpNe = 9
	, RO_CmpGt = 10
	, RO_CmpGe = 11
	, RO_CmpLt = 12
	, RO_CmpLe = 13
	, RO_fAdd = 14
	, RO_fSub = 15
	, RO_fMult = 16
	, RO_fDiv = 17
	, RO_fMod = 18
	, RO_fNeg = 19
	, RO_fCmpEq = 20
	, RO_fCmpNe = 21
	, RO_fCmpGt = 22
	, RO_fCmpGe = 23
	, RO_fCmpLt = 24
	, RO_fCmpLe = 25
	, RO_vAdd = 26
	, RO_vSub = 27
	, RO_vMult = 28
	, RO_vDiv = 29
	, RO_vNeg = 30
	, RO_And = 31
	, RO_Or = 32
	, RO_Xor = 33
	, RO_ItoF = 34
	, RO_FtoI = 35
	, RO_FtoV = 36
	, RO_PushB = 37
	, RO_PushB2 = 38
	, RO_PushB3 = 39
	, RO_Push = 40
	, RO_PushF = 41
	, RO_Dup = 42
	, RO_Drop = 43
	, RO_CallNative = 44
	, RO_Function = 45
	, RO_Return = 46
	, RO_pGet = 47
	, RO_pSet = 48
	, RO_pPeekSet = 49
	, RO_ToStack = 50
	, RO_FromStack = 51
	, RO_GetArrayP1 = 52
	, RO_GetArray1 = 53
	, RO_SetArray1 = 54
	, RO_GetFrameP1 = 55
	, RO_GetFrame1 = 56
	, RO_SetFrame1 = 57
	, RO_GetStaticP1 = 58
	, RO_GetStatic1 = 59
	, RO_SetStatic1 = 60
	, RO_Add1 = 61
	, RO_GetImm1 = 62
	, RO_SetImm1 = 63
	, RO_Mult1 = 64
	, RO_PushS = 65
	, RO_Add2 = 66
	, RO_GetImm2 = 67
	, RO_SetImm2 = 68
	, RO_Mult2 = 69
	, RO_GetArrayP2 = 70
	, RO_GetArray2 = 71
	, RO_SetArray2 = 72
	, RO_GetFrameP2 = 73
	, RO_GetFrame2 = 74
	, RO_SetFrame2 = 75
	, RO_GetStaticP2 = 76
	, RO_GetStatic2 = 77
	, RO_SetStatic2 = 78
	, RO_GetGlobalP2 = 79
	, RO_GetGlobal2 = 80
	, RO_SetGlobal2 = 81
	, RO_Call2 = 82
	, RO_Call2h1 = 83
	, RO_Call2h2 = 84
	, RO_Call2h3 = 85
	, RO_Call2h4 = 86
	, RO_Call2h5 = 87
	, RO_Call2h6 = 88
	, RO_Call2h7 = 89
	, RO_Call2h8 = 90
	, RO_Call2h9 = 91
	, RO_Call2hA = 92
	, RO_Call2hB = 93
	, RO_Call2hC = 94
	, RO_Call2hD = 95
	, RO_Call2hE = 96
	, RO_Call2hF = 97
	, RO_Jump = 98
	, RO_JumpFalse = 99
	, RO_JumpNE = 100
	, RO_JumpEQ = 101
	, RO_JumpLE = 102
	, RO_JumpLT = 103
	, RO_JumpGE = 104
	, RO_JumpGT = 105
	, RO_GetGlobalP3 = 106
	, RO_GetGlobal3 = 107
	, RO_SetGlobal3 = 108
	, RO_PushI24 = 109
	, RO_Switch = 110
	, RO_PushString = 111
	, RO_PushArrayP = 112
	, RO_PushStringNull = 113
	, RO_StrCopy = 114
	, RO_ItoS = 115
	, RO_StrAdd = 116
	, RO_StrAddi = 117
	, RO_MemCopy = 118
	, RO_Catch = 119
	, RO_Throw = 120
	, RO_pCall = 121
	, RO_ReturnP0R0 = 122
	, RO_ReturnP0R1 = 123
	, RO_ReturnP0R2 = 124
	, RO_ReturnP0R3 = 125
	, RO_ReturnP1R0 = 126
	, RO_ReturnP1R1 = 127
	, RO_ReturnP1R2 = 128
	, RO_ReturnP1R3 = 129
	, RO_ReturnP2R0 = 130
	, RO_ReturnP2R1 = 131
	, RO_ReturnP2R2 = 132
	, RO_ReturnP2R3 = 133
	, RO_ReturnP3R0 = 134
	, RO_ReturnP3R1 = 135
	, RO_ReturnP3R2 = 136
	, RO_ReturnP3R3 = 137
	, RO_Push_Neg1 = 138
	, RO_Push_0 = 139
	, RO_Push_1 = 140
	, RO_Push_2 = 141
	, RO_Push_3 = 142
	, RO_Push_4 = 143
	, RO_Push_5 = 144
	, RO_Push_6 = 145
	, RO_Push_7 = 146
	, RO_PushF_Neg1 = 147
	, RO_PushF_0 = 148
	, RO_PushF_1 = 149
	, RO_PushF_2 = 150
	, RO_PushF_3 = 151
	, RO_PushF_4 = 152
	, RO_PushF_5 = 153
	, RO_PushF_6 = 154
	, RO_PushF_7 = 155
};
