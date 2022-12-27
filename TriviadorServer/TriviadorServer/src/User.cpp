#include "User.h"

User::User(const std::string& username, const std::string& password) :
	m_username(username),
	m_password(password)
{
	m_level = 0;
	m_gamesPlayed = 0;
	m_points = 0;
	m_ID = -1;
}

User::User(User&& user) noexcept
{
	*this = std::move(user);
}


void User::SetUsername(const std::string& username)
{
	m_username = username;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

void User::SetLevel(int level)
{
	m_level = level;
}

void User::SetGamesPlayed(int gamesPlayed)
{
	m_gamesPlayed = gamesPlayed;
}

void User::SetID(int ID)
{
	m_ID = ID;
}

void User::AddPoints(int points)
{
	m_points += points;
}

User& User::operator=(User&& user) noexcept
{
	if (this != &user)
	{
		
		m_username = std::exchange(user.m_username, std::string());
		m_password = std::exchange(user.m_password, std::string());
		m_level = std::exchange(user.m_level, 0);
		m_gamesPlayed = std::exchange(user.m_gamesPlayed, 0);
		m_points = std::exchange(user.m_points, 0);
		m_ID = std::exchange(user.m_ID, 0);
	}
	return *this;
}

void User::UpdateLevel(int matchPoints)
{
	AddPoints(matchPoints);
	m_level = m_level + static_cast<int>(m_points / 1000);
	m_points = m_points % 1000;
}

const std::string User::GetUsername() const
{
	return m_username;
}

const std::string User::GetPassword() const
{
	return m_password;
}

int User::GetLevel() const
{
	return m_level;
}

int User::GetGamesPlayed() const
{
	return m_gamesPlayed;
}

int User::GetPoints() const
{
	return m_points;
}

int User::GetID() const
{
	return m_ID;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << "Username: " << user.m_username << std::endl;
	os << "Password: " << user.m_password << std::endl;
	os << "Games played: " << user.m_gamesPlayed << std::endl;
	os << "Level: " << user.m_level << std::endl;

	return os;
}
