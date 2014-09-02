#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <eosim/core/cevent.hpp>
#include <string>

const std::string endW = "EndWork";
const std::string endRv = "EndRemove";
const std::string endRp = "EndRepair";
const std::string tCafeE = "TomarCafeExperienced";
const std::string tCafeA = "TomarCafeAverage";
const std::string tCafeI = "TomarCafeInexperienced";


class EndWork: public eosim::core::BEvent {
public:
	EndWork(eosim::core::Model& model);
	~EndWork();
	void eventRoutine(eosim::core::Entity* who);
};

class StartRemove: public eosim::core::CEvent {
public:
	StartRemove(eosim::core::Model& model);
	~StartRemove();
	void eventRoutine();
};

class EndRemove: public eosim::core::BEvent {
public:
	EndRemove(eosim::core::Model& model);
	~EndRemove();
	void eventRoutine(eosim::core::Entity* who);
};

class StartRepair: public eosim::core::CEvent {
public:
	StartRepair(eosim::core::Model& model);
	~StartRepair();
	void eventRoutine();
};

class EndRepair: public eosim::core::BEvent {
public:
	EndRepair(eosim::core::Model& model);
	~EndRepair();
	void eventRoutine(eosim::core::Entity* who);
};

class TomarCafeExperienced: public eosim::core::BEvent {
public:
	TomarCafeExperienced(eosim::core::Model& model);
	~TomarCafeExperienced();
	void eventRoutine(eosim::core::Entity* who);
};

class TomarCafeAverage: public eosim::core::BEvent {
public:
	TomarCafeAverage(eosim::core::Model& model);
	~TomarCafeAverage();
	void eventRoutine(eosim::core::Entity* who);
};

class TomarCafeInexperienced: public eosim::core::BEvent {
public:
	TomarCafeInexperienced(eosim::core::Model& model);
	~TomarCafeInexperienced();
	void eventRoutine(eosim::core::Entity* who);
};


#endif


