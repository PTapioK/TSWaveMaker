#include "allies.h"

Allies::Allies()
{
	description = "Made with TSWaveMaker";
	playerTeams.clear();
}

void Allies::setDescription(QString newDescription)
{
	description = newDescription;
}

void Allies::addPlayerToTeam(int32_t spawnPoint, QString team)
{
	std::set<int32_t> newSpawns;
	if (playerTeams.find(team) != playerTeams.end()) {
		newSpawns = playerTeams[team];
	}
	newSpawns.insert(spawnPoint);
	playerTeams[team] = newSpawns;
}

void Allies::clearTeams()
{
	playerTeams.clear();
}

void Allies::save()
{
	if (!playerTeams.empty()) {
		QString section = QString("AllyBySpawnLocation") + QString::number(alliesID);

		file.saveLineToBuffer("Basic", "AllyBySpawnDefault", QString::number(alliesID));
		file.saveLineToBuffer(section, "Description", description);

		for (auto teamsIT = playerTeams.begin(); teamsIT != playerTeams.end(); ++teamsIT) {
			QString str;
			QTextStream valueSS(&str);
			for (auto playersIT = teamsIT->second.begin(); playersIT != teamsIT->second.end();) {
				valueSS << *playersIT;
				if (++playersIT != teamsIT->second.end()) {
					valueSS << ",";
				}
			}
			file.saveLineToBuffer(section, teamsIT->first, valueSS.readAll());
		}
	}
}

bool Allies::isEmpty()
{
	return playerTeams.empty();
}

std::set<int32_t> Allies::getPlayersByTeam(QString team)
{
	std::set<int32_t> players;
	if (playerTeams.find(team) != playerTeams.end()) {
		players = playerTeams[team];
	}
	return players;
}

QString Allies::getDescription() const
{
	return description;
}
