#include "TypeMap.hpp"

TypeTranslator::TypeTranslator()
{
	loadClassMap();
	loadSubtypeMap();
}

TypeTranslator::~TypeTranslator()
{

}

TypeTranslator& TypeTranslator::Get()
{
	static TypeTranslator instance;
	return instance;
}

std::string TypeTranslator::getClassName(int object_class)
{
	return Get().m_classes[object_class];
}

std::string TypeTranslator::getSubtypeName(int object_subtype)
{
	return Get().m_subtypes[object_subtype];
}

void TypeTranslator::loadClassMap()
{
	m_classes[0] =	"Protostar";
	m_classes[1] =	"Tauri Star";
	m_classes[2] =	"Main Sequence Star";
	m_classes[3] =	"Subgiant Star";
	m_classes[4] =	"Giant Star";
	m_classes[5] =	"Supergiant Star";
	m_classes[6] =	"Hypergiant Star";

	m_classes[7] =	"Brown Dwarf";
	m_classes[8] =	"White Dwarf";
	m_classes[9] =	"Black Dwarf";
	m_classes[10] = "Neutron Star";
	m_classes[11] = "Black Hole";

	m_classes[12] = "Moon";
	m_classes[13] = "Protoplanet";
	m_classes[14] = "Dwarf Planet";
	m_classes[15] = "MesoPlanet";
	m_classes[16] = "Sub-Earth Planet";
	m_classes[17] = "Earth-size Planet";
	m_classes[18] = "Super Earth";
	m_classes[19] = "Mini Neptune";
	m_classes[20] = "Neptune-size";
	m_classes[21] = "Super Neptune";
	m_classes[22] = "Mini Jupiter";
	m_classes[23] = "Jupiter-size";
	m_classes[24] = "Super Jupiter";
	m_classes[25] = "Planetar";

	m_classes[26] = "Space Station";
	m_classes[27] = "SpaceShip";
	m_classes[28] = "Rocket";

	m_classes[29] = "Wolf-Rayet Star";

	m_classes[30] = "__ClassCount";
	m_classes[31] = "__Undefined";
}

void TypeTranslator::loadSubtypeMap()
{
	m_subtypes[0] =	 "Spectral type: O";
	m_subtypes[1] =	 "Spectral type: B";
	m_subtypes[2] =	 "Spectral type: A";
	m_subtypes[3] =	 "Spectral type: F";
	m_subtypes[4] =	 "Spectral type: G";
	m_subtypes[5] =	 "Spectral type: K";
	m_subtypes[6] =	 "Spectral type: M";
	m_subtypes[7] =	 "Spectral type: L";
	m_subtypes[8] =	 "Spectral type: T";
	m_subtypes[9] =	 "Spectral type: Y";
	m_subtypes[10] = "White Dwarf";
	m_subtypes[11] = "Pulsar";
	m_subtypes[12] = "Magnetar";
	m_subtypes[13] = "Pulsar and Magnetar";
	m_subtypes[14] = "Stellar size Black Hole";
	m_subtypes[15] = "Intermediate size Black Hole";
	m_subtypes[16] = "SuperMassive Black Hole";
	m_subtypes[17] = "Miniature Black Hole";
	m_subtypes[18] = "Quasar";
	m_subtypes[19] = "Quasistar";
	m_subtypes[20] = "Other Star type";

	m_subtypes[21] = "Rocky Moon";
	m_subtypes[22] = "Icy Moon";
	m_subtypes[23] = "Other Moon type";
	m_subtypes[24] = "Protoplanet";
	m_subtypes[25] = "Gas Giant";
	m_subtypes[26] = "Ice Giant";
	m_subtypes[27] = "Gas Dwarf";
	m_subtypes[28] = "Helium Planet";
	m_subtypes[29] = "Ice Planet";
	m_subtypes[30] = "Metal Planet";
	m_subtypes[31] = "Water Planet";
	m_subtypes[32] = "Lava Planet";
	m_subtypes[33] = "Terresial/Rocky Planet";
	m_subtypes[34] = "Other Planet Type";

	m_subtypes[35] = "Space Station";
	m_subtypes[36] = "SpaceShip";
	m_subtypes[37] = "Rocket";

	m_subtypes[38] = "Wolf-Rayet Star";

	m_subtypes[39] = "__SubtypeCount";
	m_subtypes[40] = "__Undefined";
}
