#include "Credits.hpp"

Credits::Credits(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::CREDITS)
	, m_sm_color(sf::Color::Black)
	, m_next_state(STATE::NONE)
	, m_outro_time(0)
{
	music.pause();

	view->setCenter(winSize / 2.f);

	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
}

Credits::~Credits()
{
	music.resume();
}

void Credits::InitState()
{
	m_credits.reserve(50);

	view->setCenter(winSize.x / 2, -0.8 * winSize.y);
	m_viewposY = view->getCenter().y;
	m_starViewSize = view->getSize().y;

	sf::Vector2f position(winSize.x / 2, 0);
	const float empty_space = winSize.y / 6;
	const float small_space = winSize.y / 36;

	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Completely Inaccurate Space Simulator",	winSize.x / 32, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + 2 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"created by CoconutOnPalm",					winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"(with some help)",							winSize.x / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(128, 128, 128, 128))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Created using KEngine based on SFML",		winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Cool backgrounds",							winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"NASA and ESA",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"with their Hubble Space Telescope <3",		winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Invaluable feedback:",						winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	//m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"dronowanie.czest.pl",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	//m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Blurred Pink",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my friends <3",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"and of course my cat",						winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music",									winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Micha³ Kapica from Blurred Pink",			winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 1.5 * small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music from YouTube Audio library:",		winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Benjamin Martins",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Bobby Richards",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Godmode",									winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Jesse Gallagher",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Unicorn Heads",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music folder: *AppDir*\\Audio\\Music",		winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Sound Effects",							winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"created using Audacity",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Fonts",									winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Google's OpenSans font",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Budget",									winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"huh?",										winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Project menager",							winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my cat",									winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Sales",									winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"ducks from a nearby lake",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Programmers",								winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"StackOverflow",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my cat again",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"SFML forum",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"helpful guys form YouTube",				winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Special Thanks to",						winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my family",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my friends",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"dronowanie.czest.pl",						winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Blurred Pink",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"lizard-shoes.com",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"a furry mammal that I admire",				winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"GIMP",										winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Google drawings",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Raw Therapee",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Audacity",									winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 4 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y),		 position, ke::Origin::MIDDLE_MIDDLE, "KEngine/Sources/Logos/KEngineLOGO_nosfml.png", L"",	winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(1001, 304),				 position, ke::Origin::MIDDLE_MIDDLE, "Textures/sfml-logo-big.png", L"",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 5 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y),		 position, ke::Origin::MIDDLE_MIDDLE, "res/CISS_Logo.png", L"",								winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::White,	   sf::Color(192, 192, 192, 192)));
	m_credits.back()->reverseRenderOrder();

	m_credits_music.addSong("Audio/Music/Cartoon - Nikolai Heidlas.wav");
	m_credits_music.enableLoop(false);
	m_credits_music.setVolume(AppSettings::MusicVolume());
	m_credits_music.play();
}

void Credits::reloadState()
{
	m_credits.clear();



	view->setCenter(winSize.x / 2, m_viewposY * (view->getSize().y / m_starViewSize));
	m_starViewSize = view->getSize().y;

	sf::Vector2f position(winSize.x / 2, 0);
	const float empty_space = winSize.y / 6;
	const float small_space = winSize.y / 36;

	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Completely Inaccurate Space Simulator", winSize.x / 32, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + 2 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"created by CoconutOnPalm", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"(with some help)", winSize.x / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(128, 128, 128, 128))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Created using KEngine based on SFML", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Cool backgrounds", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"NASA and ESA", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"with their Hubble Space Telescope <3", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Invaluable feedback:", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	//m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"dronowanie.czest.pl",					winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	//m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Blurred Pink",							winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my friends <3", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"and of course my cat", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Micha³ Kapica from Blurred Pink", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 1.5 * small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music from YouTube Audio library:", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Benjamin Martins", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Bobby Richards", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Godmode", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Jesse Gallagher", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Unicorn Heads", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Music folder: *AppDir*\\Audio\\Music", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Sound Effects", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"created using Audacity", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Fonts", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Google's OpenSans font", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Budget", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"huh?", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Project menager", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my cat", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Sales", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"ducks from a nearby lake", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Programmers", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"StackOverflow", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my cat again", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"SFML forum", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"helpful guys form YouTube", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Special Thanks to", winSize.x / 40, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my family", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"my friends", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"dronowanie.czest.pl", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Blurred Pink", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"lizard-shoes.com", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"a furry mammal that I admire", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"GIMP", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Google drawings", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Raw Therapee", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + small_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y / 18), position, ke::Origin::MIDDLE_MIDDLE, nullptr, L"Audacity", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 4 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y), position, ke::Origin::MIDDLE_MIDDLE, "KEngine/Sources/Logos/KEngineLOGO_nosfml.png", L"", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(1001, 304), position, ke::Origin::MIDDLE_MIDDLE, "Textures/sfml-logo-big.png", L"", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 192))); position.y += m_credits.back()->getSize().y + 5 * empty_space;
	m_credits.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.x, winSize.y), position, ke::Origin::MIDDLE_MIDDLE, "res/CISS_Logo.png", L"", winSize.x / 50, ke::Origin::MIDDLE_MIDDLE, sf::Color::White, sf::Color(192, 192, 192, 192)));
	m_credits.back()->reverseRenderOrder();



}

void Credits::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (p_quitCode == StateQuitCode::STATE_QUIT)
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 256, dt);

		if (m_sm_color == ke::Colorf(sf::Color::Black))
		{
			switch (m_next_state)
			{
			case STATE::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view, false);
				break;
			default:
				ke::throw_error("Credits::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}


		m_outro_time = m_outro_clock.getElapsedTime().asMilliseconds();

		if (m_outro_time > 10000) // safety guard
		{
			switch (m_next_state)
			{
			case STATE::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view, false);
				break;
			default:
				ke::throw_error("Credits::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}
	}
	else
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
	}

	ke::SmoothViewMove(view, sf::Vector2f(m_credits.back()->getShapeCenter()), sf::Vector2f(winSize.x / 2, -0.8 * winSize.y), 64, dt);

	m_viewposY = view->getCenter().y;
}

void Credits::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::MAIN_MENU;
	}
}

void Credits::renderBackground()
{

}

void Credits::renderByView()
{
	for (auto& itr : m_credits)
		itr->render(window);
}

void Credits::renderByWindow()
{
	m_stateMask.render(window);
}

StateQuitCode Credits::Quit()
{
	return p_quitCode;
}
