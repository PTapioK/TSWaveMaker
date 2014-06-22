#include "event.h"

Event::Event(string nID)
{
	eType = 0;
	param = "0";
	ID = nID;
}

Event::Event(Event *oEvent, string nID) {
	eType = oEvent->eType;
	param = oEvent->param;
	ID = nID;
}

Event::Event(int32_t neType, int32_t nparam, string nID)
{
	stringstream nP;
	nP << nparam;
	eType = neType;
	param = nP.str();
	ID = nID;
}

void Event::Save(int32_t count) {
	if(count == 1) {
		stringstream vSS;
		vSS << count << "," << eType << "," << "0" << "," << param;
		WriteValueToBuffer("Events", ID, vSS.str());
	} else if (count > 1) {
		stringstream vSS;
		vSS << eType << "," << "0" << "," << param;
		EditValueInBuffer("Events", ID, vSS.str(), count);
	}
}
