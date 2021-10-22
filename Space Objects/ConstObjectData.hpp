#pragma once

enum ObjectType
{
	UNDEFINED,
	CENTER_OF_MASS,
	STAR,
	PLANET,
	OTHER
};


enum ObjectClass
{
	// STARS:

	CLASS_PROTOSTAR,								// 0
	CLASS_TAURI_STAR,								// 1
	CLASS_MAIN_SEQUENCE_STAR,						// 2
	CLASS_SUBGIANT_STAR,							// 3
	CLASS_GIANT_STAR,								// 4
	CLASS_SUPERGIANT_STAR,							// 5
	CLASS_HYPERGIANT_STAR,							// 6
	
	
	// DEAD STARS AND STAR-LIKE				
	
	CLASS_BROWN_DWARF,								// 7
	CLASS_WHITE_DWARF,								// 8
	CLASS_BLACK_DWARF,								// 9
	CLASS_NEUTRON_STAR,								// 10
	CLASS_BLACK_HOLE,								// 11
	
	
	// PLANETS, DWARF PLANETS AND MOONS		
	
	CLASS_MOON,										// 12
	
	CLASS_PROTOPLANET,								// 13
	CLASS_DWARF_PLANET,								// 14
	CLASS_MESOPLANET,								// 15
	
	CLASS_SUB_EARTH_PLANET,							// 16
	CLASS_EARTH_SIZE_PLANET,						// 17
	CLASS_SUPER_EARTH_PLANET,						// 18
	
	CLASS_MINI_NEPTUNE,								// 19
	CLASS_NEPTUNE_SIZE,								// 20
	CLASS_SUPER_NEPTUNE,							// 21
	
	CLASS_MINI_JUPITER,								// 22
	CLASS_JUPITER_SIZE,								// 23
	CLASS_SUPER_JUPITER,							// 24
	
	CLASS_PLANETAR,									// 25
	
	
	// OTHER								
	
	CLASS_SPACE_STATION,							// 26
	CLASS_SPACESHIP,								// 27
	CLASS_ROCKET,									// 28
	

	// objects from new versions of app

	CLASS_WOLF_RAYET_STAR,							// 29


	CLASS_ObjectClassCount,							// 30
	
	CLASS_UNDEFINED
};


enum ObjectSubtype
{
	// SPECTRAL TYPES OF STARS				 

	SUBTYPE_O,										// 0
	SUBTYPE_B,										// 1
	SUBTYPE_A,										// 2
	SUBTYPE_F,										// 3
	SUBTYPE_G,										// 4
	SUBTYPE_K,										// 5
	SUBTYPE_M,										// 6
	SUBTYPE_L,										// 7
	SUBTYPE_T,										// 8
	SUBTYPE_Y,										// 9

	SUBTYPE_WHITE_DWARF,							// 10
	
	SUBTYPE_PULSAR,									// 11
	SUBTYPE_MAGNETAR,								// 12
	SUBTYPE_PULSAR_AND_MAGNETAR,					// 13
	
	SUBTYPE_STELLAR_SIZE_BH,						// 14
	SUBTYPE_INTERMEDIATE_SIZE_BH,					// 15
	SUBTYPE_SUPERMASSIVE_BH,						// 16
	SUBTYPE_MINIATURE_BH,							// 17
	
	SUBTYPE_QUASAR,									// 18
	SUBTYPE_QUASISTAR,								// 19
	
	SUBTYPE_OTHER_STAR_TYPE,						// 20
	
	
	// TYPES OF PLANETS						
	
	SUBTYPE_ROCKY_MOON,								// 21
	SUBTYPE_ICY_MOON,								// 22
	SUBTYPE_OTHER_MOON_TYPE,						// 23
	
	SUBTYPE_PROTOPLANET,							// 24
	
	SUBTYPE_GAS_GIANT,								// 25
	SUBTYPE_ICE_GIANT,								// 26
	SUBTYPE_GAS_DWARF,								// 27
	SUBTYPE_HELIUM_PLANET,							// 28
	
	SUBTYPE_ICE_PLANET,								// 29
	SUBTYPE_METAL_PLANET,							// 30
	SUBTYPE_WATER_PLANET,							// 31
	SUBTYPE_LAVA_PLANET,							// 32
	SUBTYPE_TERRESTRIAL,							// 33
	
	SUBTYPE_OTHER_PLANET_TYPE,						// 34
	
	
	// OTHER
	
	SUBTYPE_SPACE_STATION,							// 35
	SUBTYPE_SPACESHIP,								// 36
	SUBTYPE_ROCKET,									// 37


	// objects from new versions of app

	SUBTYPE_WOLF_RAYET_STAR,						// 38

	
	SUBTYPE_SubtypeCount,							// 39

	SUBTYPE_UNDEFINED
};