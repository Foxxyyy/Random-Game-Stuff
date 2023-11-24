//Resources
#TD - Texture Dictionary
#TX - Texture Map
#VD - Volume Data
#BD - Bounds Dictionary
#FT - Fragment
#FD - Fragment Dictionary
#SC - Script
#ST - String Table
#SP - SpeedTree
#TB - Terrain Bounds
#SI - Sector Info
#SG - Sector Grass
#AS - Animation Scene
#AT - Action Tree
#GD - Gringo Dictionary
#NM - Nav Mesh
#CS - Cover Set
#CD - Cover Grid
#SF - ScaleForm
#PFL - Particle Effects Library
#PRP - Props
#CDT - Cutscene Dictionary
#EDT - Expressions Dictionary
#PDT - Posematchers Dictionary

//Regular files
RPF - Rage Package File
BK2 - Bink Video 2
DAT - Data File
NVN - Compiled Shader
FXC - Compiled Shader
CUTBIN - Cutscene Binary
SCO - Unused Script
AWC - Audio Wave Container
TR - AI Program
CSV - Comma-Seperated Values File
CFG - Config File
REFGROUP - Reference Group
FXLIST - Effects List
PTXLIST - Effects List
MODELLIST - Models List
EMIT List - Emissions List
SHADERLIST - Shaders List
TEXLIST - Textures List
XLIST - Streaming List
RAW - Raw Texture Data
EXPL - Explosion Data
VEHSIM - Vehicle Simulation
VEHSTUCK - Vehicle Stuck
ENV - Environment Data
CLOTHMANAGER - Clothes Update Data
TODLIGHT - Timecycle Data
TRAFFIC - Actors Traffic Data
MTL - Material Data
WEAP - Weapon Data
FX - Visual Data
FXM - Material Visual Data
PPP - Post-Processing Elements
RMPTX - Particle Effects Data
TUNE - Game Data
TEXTUNE - Texture Data

//SC-CL
enum RDRScriptOpcodes
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
