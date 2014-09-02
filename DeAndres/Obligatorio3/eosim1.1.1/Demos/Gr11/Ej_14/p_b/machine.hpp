#ifndef MACHINE_HPP_
#define MACHINE_HPP_

#include <eosim/core/entity.hpp>

class Machine: public eosim::core::Entity{
private:
    int number;
    int mechanich;
    double machineDown;
public:
	Machine(int number): number(number) {}
	int setMechanich(int mechanich) {this->mechanich = mechanich;}
	int getMechanich() {return this->mechanich;}
	int getNumber() {return number; }
	void setMachineDown(double time) {machineDown = time;}
	double getMachineDown() {return machineDown;}
	~Machine() {}
};

#endif

