#ifndef ALLIES_H
#define ALLIES_H

#include "../main.h"

class Allies
{
	public:
		Allies();

		void setDescription(QString newDescription);
		void addPlayerToTeam(int32_t spawnPoint, QString team);
		void clearTeams();
		void save();

		bool isEmpty();
		std::set<int32_t> getPlayersByTeam(QString team);
		QString getDescription() const;
	private:
		std::map <QString, std::set<int32_t>> playerTeams;
		QString description;
};

#endif // ALLIES_H
