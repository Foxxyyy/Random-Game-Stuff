//TESTS
using ResolveDevice_t = void** (__fastcall*)(char* path, char a2);
static ResolveDevice_t g_ResolveDevice_Orig = nullptr;
static uintptr_t ADDR_ResolveDevice = 0;

using MoveStaticNodesToRooms_t = __int64(__fastcall*)(__int64 sector);
static MoveStaticNodesToRooms_t g_MoveStaticNodesToRooms_Orig = nullptr;
static uintptr_t ADDR_MoveStaticNodesToRooms = 0;
std::atomic<int> g_MoveStaticNodesHits { 0 };
using QueryRoomInPoint_t = __int64(__fastcall*)(__int64 roomGroup, __m128* point);
static QueryRoomInPoint_t g_QueryRoomInPoint_Orig = nullptr;
static uintptr_t ADDR_QueryRoomInPoint = 0;
using GetLeafData_t = char(__fastcall*)(__int64 node, float* point, unsigned int* outIndex);
static GetLeafData_t g_GetLeafData_Orig = nullptr;
static uintptr_t ADDR_GetLeafData = 0;
using ResolveRoom_t = __int64(__fastcall*)(__int64 group, unsigned int key);
static ResolveRoom_t g_ResolveRoom_Orig = nullptr;
static uintptr_t ADDR_ResolveRoom = 0;
static bool g_ResolveRoomHookInstalled = false;

static bool IsReadablePtr(const void* p)
{
	if (!p) return false;

	MEMORY_BASIC_INFORMATION mbi {};
	if (!VirtualQuery(p, &mbi, sizeof(mbi))) return false;
	if (mbi.State != MEM_COMMIT) return false;
	if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) return false;
	return true;
}

static const char* SafeName(const char* p)
{
	return IsReadablePtr(p) ? p : "<invalid>";
}

static char g_CurrentRoomDrawable[256] {};
static void SetCurrentRoomDrawable(const char* name)
{
	if (name)
		snprintf(g_CurrentRoomDrawable, sizeof(g_CurrentRoomDrawable), "%s", name);
	else
		snprintf(g_CurrentRoomDrawable, sizeof(g_CurrentRoomDrawable), "<null>");
}

static __int64 __fastcall MoveStaticNodesToRooms_Hook(__int64 sector)
{
	g_MoveStaticNodesHits++;
	if (sector)
	{
		auto instances = *(__int64*)(sector + 432); //m_SectorDrawableInstances
		auto count = *(unsigned __int16*)(sector + 440); //count
		auto sectorHash = *(uint32_t*)(sector + 632);

		char buffer[512];
		snprintf(buffer, sizeof(buffer), "[MoveStaticNodesToRooms] sector=0x%llX hash=0x%08X instances=%u\n", (unsigned long long)sector, sectorHash, count);
		OutputDebugStringA(buffer);

		if (instances && count > 0)
		{
			for (uint32_t i = 0; i < count; i++)
			{
				auto inst = instances + (i * 288);
				auto name = *(const char**)(inst + 216); //v14

				float minW = *(float*)(inst + 172);
				SetCurrentRoomDrawable(name);

				auto room = *(__int64*)(inst + 16);
				auto flags = *(uint16_t*)(inst + 208);

				float minX = *(float*)(inst + 160);
				float minY = *(float*)(inst + 164);
				float minZ = *(float*)(inst + 168);

				float maxX = *(float*)(inst + 176);
				float maxY = *(float*)(inst + 180);
				float maxZ = *(float*)(inst + 184);
				float maxW = *(float*)(inst + 188);

				snprintf(buffer, sizeof(buffer),
					"[MoveStaticNodesToRooms] #%u name=%s inst=0x%llX room=0x%llX flags=0x%04X "
					"bbMin=(%.3f, %.3f, %.3f, %.3f) bbMax=(%.3f, %.3f, %.3f, %.3f)\n",
					i,
					SafeName(name),
					(unsigned long long)inst,
					(unsigned long long)room,
					flags,
					minX, minY, minZ, minW,
					maxX, maxY, maxZ, maxW);
				OutputDebugStringA(buffer);
			}
		}
	}
	return g_MoveStaticNodesToRooms_Orig(sector);
}

static __int64 __fastcall ResolveRoom_Hook(__int64 group, unsigned int key)
{
	__int64 room = g_ResolveRoom_Orig(group, key);
	char buffer[512];

	snprintf(buffer, sizeof(buffer), 
		"[ResolveRoom] obj=%s group=0x%llX key=0x%08X -> room=0x%llX\n",
		g_CurrentRoomDrawable,
		(unsigned long long)group,
		key,
		(unsigned long long)room);

	OutputDebugStringA(buffer);
	return room;
}

static void TryInstallResolveRoomHook(__int64 group)
{
	if (!group || g_ResolveRoomHookInstalled) return;

	auto vtbl = *(uintptr_t*)group;
	if (!vtbl) return;

	auto fn = *(uintptr_t*)(vtbl + 24); // virtual slot +24
	if (!fn) return;

	ADDR_ResolveRoom = fn;
	if (MH_CreateHook((LPVOID)ADDR_ResolveRoom, (LPVOID)&ResolveRoom_Hook, (LPVOID*)&g_ResolveRoom_Orig) == MH_OK)
	{
		if (MH_EnableHook((LPVOID)ADDR_ResolveRoom) == MH_OK)
		{
			g_ResolveRoomHookInstalled = true;
			char buffer[512];
			snprintf(buffer, sizeof(buffer), 
				"[ResolveRoom] Hooked resolver at 0x%llX from group=0x%llX vtbl=0x%llX\n",
				(unsigned long long)ADDR_ResolveRoom,
				(unsigned long long)group,
				(unsigned long long)vtbl);
			OutputDebugStringA(buffer);
		}
	}
}

static __int64 __fastcall QueryRoomInPoint_Hook(__int64 roomGroup, __m128* point)
{
	TryInstallResolveRoomHook(roomGroup);

	float x = point ? point->m128_f32[0] : 0.0f;
	float y = point ? point->m128_f32[1] : 0.0f;
	float z = point ? point->m128_f32[2] : 0.0f;
	__int64 roomPtr = g_QueryRoomInPoint_Orig(roomGroup, point);

	char buffer[512];
	snprintf(buffer, sizeof(buffer),
		"[QueryRoomInPoint] obj=%s group=0x%llX point=(%.3f, %.3f, %.3f) -> room=0x%llX\n",
		g_CurrentRoomDrawable,
		(unsigned long long)roomGroup,
		x, y, z,
		(unsigned long long)roomPtr);

	OutputDebugStringA(buffer);
	return roomPtr;
}

static char __fastcall GetLeafData_Hook(__int64 node, float* point, unsigned int* outIndex)
{
	unsigned int before = outIndex ? *outIndex : 0xCCCCCCCC;
	float px = point ? point[0] : 0.0f;
	float py = point ? point[1] : 0.0f;
	float pz = point ? point[2] : 0.0f;

	__int64 cur = node;
	__int64 finalNode = 0;
	const char* finalSide = "none";
	uint32_t* finalSpan = nullptr;
	uint32_t finalCount = 0;
	float finalPlaneX = 0.0f, finalPlaneY = 0.0f, finalPlaneZ = 0.0f, finalPlaneW = 0.0f;
	float finalSideValue = 0.0f;

	while (cur)
	{
		float nx = *(float*)(cur + 0x0);
		float ny = *(float*)(cur + 0x4);
		float nz = *(float*)(cur + 0x8);
		float nd = *(float*)(cur + 0xC);

		float side = (nx * px) + (ny * py) + (nz * pz) - nd;

		finalNode = cur;
		finalPlaneX = nx;
		finalPlaneY = ny;
		finalPlaneZ = nz;
		finalPlaneW = nd;
		finalSideValue = side;

		if (side < 0.0f)
		{
			__int64 leftChild = *(__int64*)(cur + 0x30);
			if (!leftChild)
			{
				finalSide = "left";
				finalSpan = *(uint32_t**)(cur + 0x10);
				finalCount = *(uint32_t*)(cur + 0x18);
				break;
			}
			cur = leftChild;
		}
		else
		{
			__int64 rightChild = *(__int64*)(cur + 0x38);
			if (!rightChild)
			{
				finalSide = "right";
				finalSpan = *(uint32_t**)(cur + 0x20);
				finalCount = *(uint32_t*)(cur + 0x28);
				break;
			}
			cur = rightChild;
		}
	}

	uint32_t leaf0 = (finalSpan && finalCount > 0) ? finalSpan[0] : 0xFFFFFFFF;
	uint32_t leaf1 = (finalSpan && finalCount > 1) ? finalSpan[1] : 0xFFFFFFFF;

	char ret = g_GetLeafData_Orig(node, point, outIndex);
	unsigned int after = outIndex ? *outIndex : 0xCCCCCCCC;
	char buffer[512];

	snprintf(buffer, sizeof(buffer),
		"[GetLeafData] obj=%s entry=0x%llX final=0x%llX point=(%.3f, %.3f, %.3f) "
		"plane=(%.6f, %.6f, %.6f, %.6f) side=%.6f terminal=%s "
		"span=0x%llX count=%u leaf[0]=0x%08X leaf[1]=0x%08X "
		"ret=%d out_before=0x%08X out_after=0x%08X\n",
		g_CurrentRoomDrawable,
		(unsigned long long)node,
		(unsigned long long)finalNode,
		px, py, pz,
		finalPlaneX, finalPlaneY, finalPlaneZ, finalPlaneW,
		finalSideValue, finalSide,
		(unsigned long long)finalSpan, finalCount, leaf0, leaf1,
		(int)ret,
		before, after
	);

	OutputDebugStringA(buffer);
	return ret;
}

static void InstallTest()
{
	ADDR_MoveStaticNodesToRooms = 0x14060FA40;
	MH_Initialize();
	MH_CreateHook((LPVOID)ADDR_MoveStaticNodesToRooms, (LPVOID)&MoveStaticNodesToRooms_Hook, (LPVOID*)&g_MoveStaticNodesToRooms_Orig);
	MH_EnableHook((LPVOID)ADDR_MoveStaticNodesToRooms);

	ADDR_QueryRoomInPoint = 0x140887670;
	MH_CreateHook((LPVOID)ADDR_QueryRoomInPoint, (LPVOID)&QueryRoomInPoint_Hook, (LPVOID*)&g_QueryRoomInPoint_Orig);
	MH_EnableHook((LPVOID)ADDR_QueryRoomInPoint);

	ADDR_GetLeafData = 0x140E653A0;
	MH_CreateHook((LPVOID)ADDR_GetLeafData, (LPVOID)&GetLeafData_Hook, (LPVOID*)&g_GetLeafData_Orig);
	MH_EnableHook((LPVOID)ADDR_GetLeafData);
}


static void** __fastcall ResolveDevice_Hook(char* path, char a2)
{
	if (path)
	{
		if (strncmp(path, "memory:", 7) && strncmp(path, "embedded:/", 10) && strncmp(path, "game:", 5))
		{
			
		}
	}
	return g_ResolveDevice_Orig(path, a2);
}

static void ResolveFileOverrideOffsets()
{
	if (GetGameVersion() == GameVersion::V40_PC_49078035)
		ADDR_ResolveDevice = 0x1400CA7D0;
	else
		ADDR_ResolveDevice = 0x1400CA710;
}

static void InstallFileOverrideHook()
{
	ResolveFileOverrideOffsets();
	MH_Initialize();
	MH_CreateHook((LPVOID)ADDR_ResolveDevice, (LPVOID)&ResolveDevice_Hook, (LPVOID*)&g_ResolveDevice_Orig);
	MH_EnableHook((LPVOID)ADDR_ResolveDevice);
}
